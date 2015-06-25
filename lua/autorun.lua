leansand = require("leansand")
ffi = require("ffi")

ffi.C.luatest("Hello, World!");

function closure()
  print("in closure")
  local i = leansand.test.newTestClass("Hello, class-based World!")
  print("instance is " .. tostring(i))
  i:test()
  i = nil
end

closure()
print("after closure")
