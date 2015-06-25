local leansand = {}
package.loaded[...] = leansand
local ffi = require("ffi")

leansand.api = require("leansand.api")
leansand.test = require("leansand.test")

leansand.api.include("leansand.h")

return leansand
