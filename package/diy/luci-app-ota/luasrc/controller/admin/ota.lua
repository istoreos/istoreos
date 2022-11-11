--[[
LuCI - Lua Configuration Interface
Copyright 2021 jjm2473
]]--

module("luci.controller.admin.ota",package.seeall)
require "luci.util"

function index()
  entry({"admin", "system", "ota"}, post_on({ apply = "1" }, "action_ota"), _("OTA"), 69)
  entry({"admin", "system", "ota", "check"}, post("action_check"))
  entry({"admin", "system", "ota", "download"}, post("action_download"))
  entry({"admin", "system", "ota", "progress"}, call("action_progress"))
  entry({"admin", "system", "ota", "cancel"}, post("action_cancel"))
end

local function ota_exec(cmd)
  local nixio = require "nixio"
  local os   = require "os"
  local fs   = require "nixio.fs"
  local rshift  = nixio.bit.rshift

  local oflags = nixio.open_flags("wronly", "creat")
  local lock, code, msg = nixio.open("/var/lock/ota_api.lock", oflags)
  if not lock then
    return 255, "", "Open stdio lock failed: " .. msg
  end

  -- Acquire lock
  local stat, code, msg = lock:lock("tlock")
  if not stat then
    lock:close()
    return 255, "", "Lock stdio failed: " .. msg
  end

  local r = os.execute(cmd .. " >/var/log/ota.stdout 2>/var/log/ota.stderr")
  local e = fs.readfile("/var/log/ota.stderr")
  local o = fs.readfile("/var/log/ota.stdout")

  fs.unlink("/var/log/ota.stderr")
  fs.unlink("/var/log/ota.stdout")

  lock:lock("ulock")
  lock:close()

  e = e or ""
  if r == 256 and e == "" then
    e = "os.execute failed, is /var/log full or not existed?"
  end
  return rshift(r, 8), o or "", e or ""
end

local function image_supported(image)
  return (os.execute("sysupgrade -T %q >/dev/null" % image) == 0)
end

function action_ota()
  local image_tmp = "/tmp/firmware.img"
  local http = require "luci.http"
  if http.formvalue("apply") == "1" then
    if not luci.dispatcher.test_post_security() then
      return
    end
    if not image_supported(image_tmp) then
      luci.template.render("admin_system/ota", {image_invalid = true})
      return
    end
    local keep = (http.formvalue("keep") == "1") and "" or "-n"
    luci.template.render("admin_system/ota_flashing", {
      title = luci.i18n.translate("Flashing…"),
      msg   = luci.i18n.translate("The system is flashing now.<br /> DO NOT POWER OFF THE DEVICE!<br /> Wait a few minutes before you try to reconnect. It might be necessary to renew the address of your computer to reach the device again, depending on your settings."),
      addr  = (#keep > 0) and "192.168.1.1" or nil
    })
    fork_exec("sleep 1; killall dropbear uhttpd; sleep 1; /sbin/sysupgrade %s %q" %{ keep, image_tmp })
  else
    luci.template.render("admin_system/ota")
  end
end

function action_check()
  local r,o,e = ota_exec("ota check")
  local ret = {
    code = 500,
    msg = "Unknown"
  }
  if r == 0 then
    ret.code = 0
    ret.msg = o
  elseif r == 1 then
    ret.code = 1
    ret.msg = o
  else
    ret.code = 500
    ret.msg = e
  end
  luci.http.prepare_content("application/json")
  luci.http.write_json(ret)
end

function action_download()
  local r,o,e = ota_exec("ota download")
  local ret = {
    code = 500,
    msg = "Unknown"
  }
  if r == 0 then
    ret.code = 0
    ret.msg = ""
  else
    ret.code = 500
    ret.msg = e
  end
  luci.http.prepare_content("application/json")
  luci.http.write_json(ret)
end

function action_progress()
  local r,o,e = ota_exec("ota progress")
  local ret = {
    code = 500,
    msg = "Unknown"
  }
  if r == 0 then
    ret.code = 0
    ret.msg = "done"
  elseif r == 1 or r == 2 then
    ret.code = r
    ret.msg = o
  else
    ret.code = 500
    ret.msg = e
  end
  luci.http.prepare_content("application/json")
  luci.http.write_json(ret)
end

function action_cancel()
  local r,o,e = ota_exec("ota cancel")
  local ret = {
    code = 500,
    msg = "Unknown"
  }
  if r == 0 then
    ret.code = 0
    ret.msg = "ok"
  else
    ret.code = 500
    ret.msg = e
  end
  luci.http.prepare_content("application/json")
  luci.http.write_json(ret)
end

function fork_exec(command)
	local pid = nixio.fork()
	if pid > 0 then
		return
	elseif pid == 0 then
		-- change to root dir
		nixio.chdir("/")

		-- patch stdin, out, err to /dev/null
		local null = nixio.open("/dev/null", "w+")
		if null then
			nixio.dup(null, nixio.stderr)
			nixio.dup(null, nixio.stdout)
			nixio.dup(null, nixio.stdin)
			if null:fileno() > 2 then
				null:close()
			end
		end

		-- replace with target command
		nixio.exec("/bin/sh", "-c", command)
	end
end
