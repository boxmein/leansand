local api = {}
local ffi = require("ffi")

function api.include(name)
  local file = io.open("leansand/include/" .. name, "r")

  local line, match
  while true do
    line = file:read()
    if not line then break end

    match = string.match(line, "LUAAPI (.+;)")
    if match then
      ffi.cdef(match)
    end
  end

  file:close()
end

return api