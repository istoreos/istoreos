-- Copyright 2022 jjm2473 <jjm2473@gmail.com>
-- Licensed to the public under the Apache License 2.0.

module("luci.controller.admin.compat", package.seeall)

function action_fatab()
	local dsp = require "luci.dispatcher"

	luci.http.redirect(dsp.build_url("admin/system/mounts"))
end
