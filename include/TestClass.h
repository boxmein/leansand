#ifndef TESTCLASS_H
#define TESTCLASS_H

#include "leansand.h"

class TestClass{
  private:
    const char* text;

  public:
    TestClass(const char* t);
    ~TestClass();
    void test();
};

LUAAPI void* TestClass_new(const char* t);
LUAAPI void TestClass_test(void* ptr);
LUAAPI void TestClass_gc(void* ptr);

#endif
