module("luci.controller.eqos", package.seeall)

function index()
	if not nixio.fs.access("/etc/config/eqos") then
		return
	end
	
	entry({"admin", "network", "eqos"}, cbi("eqos"), _("EQoS"))
end
