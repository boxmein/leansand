#include "LuaUIAPI.h"
using namespace std;

LuaUIAPI::LuaUIAPI() {}
LuaUIAPI::~LuaUIAPI() {}
const char* LuaUIAPI::getName() { return "ui"; }

void LuaUIAPI::detach(lua_State* L, int table_index) {
  //
}
void LuaUIAPI::attach(lua_State* L, int table_index) {
  Luna<UIComponent>::Register(L, table_index);
  lua_pop(L, 1);
}
