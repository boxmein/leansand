local test = {}
local leansand = require("leansand")
local ffi = require("ffi")

leansand.api.include("TestClass.h")

function test.newTestClass(...)
  local instance = setmetatable({}, test.TestClass)
  instance:__init(...)
  return instance
end

test.TestClass = {}
test.TestClass.__index = test.TestClass

function test.TestClass:__init(t)
  self.ptr = ffi.gc(ffi.C.TestClass_new(t), ffi.C.TestClass_gc);
end

function test.TestClass:__gc()
  print("gc")
end

function test.TestClass:test()
  ffi.C.TestClass_test(self.ptr)
end

return test
