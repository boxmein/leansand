#include "TestClass.h"
using namespace std;

TestClass::TestClass(const char* t) {
  cout << "in constructor\n";
  text = t;
}

void TestClass::test() {
  cout << "in test: " << text << "\n";
}

TestClass::~TestClass() {
  cout << "in destructor\n";
}


LUAAPI void* TestClass_new(const char* t) {
  return reinterpret_cast<void*>(new TestClass(t));
}

LUAAPI void TestClass_test(void* ptr) {
  reinterpret_cast<TestClass*>(ptr)->test();
}

LUAAPI void TestClass_gc(void* ptr) {
  cout << "in gc\n";
  delete reinterpret_cast<TestClass*>(ptr);
}
