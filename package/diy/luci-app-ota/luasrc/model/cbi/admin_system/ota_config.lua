local m, s, o

m = Map("ota")

s=m:section(NamedSection, "network")
s.anonymous=true

o = s:option(Flag, "ipv4", translate("IPv4 only"), translate("Use IPv4 network for OTA operations"))

return m
