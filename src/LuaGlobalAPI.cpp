#include "leansand.h"

const char* luaPrintPrefix = "(lua): ";
const char* luaErrPrefix = "(lua) Error: ";

int luaPrintHook(lua_State* L) {
  int argc = lua_gettop(L);


  std::string text = "";

  for (int i = 1; i <= argc; i++) {
    text += ' ';
    text += luaL_tolstring(L, -1, NULL);
    lua_pop(L, 1);
  }

  cout << luaPrintPrefix << text << "\n";
  return 0;
}

int luaPanicHook(lua_State* L) {
  cerr << luaErrPrefix << "Panic: " << std::string(lua_tostring(L, -1));
  cerr.flush();

  // returning from here calls abort()
  // the alternative is long-jumping to somewhere, but since we depend on Lua
  // a lot then this is more acceptable
  return 0;
}

LuaGlobalAPI::LuaGlobalAPI() {
  L = luaL_newstate();

  if (L == NULL) {
    cerr << "luaL_newstate returned NULL, memory allocation error!";
  }

  luaL_openlibs(L);

  // Hook print events to redirected cout instead of stdout
  lua_pushcfunction(L, luaPrintHook);
  lua_setglobal(L, "print");

  // Create a global 'leansand' table

  lua_newtable(L);
  int ls = lua_gettop(L);

  lua_pushstring(L, VERSION);
  lua_setfield(L, ls, "version");

  lua_pushnumber(L, WIDTH);
  lua_setfield(L, ls, "width");

  lua_pushnumber(L, HEIGHT);
  lua_setfield(L, ls, "height");

#ifdef LUAJIT
  int luajit = 1;
#else
  int luajit = 0;
#endif

  lua_pushboolean(L, luajit);
  lua_setfield(L, ls, "luajit");

  lua_setglobal(L, "leansand");
}

LuaGlobalAPI::~LuaGlobalAPI() {

}

void LuaGlobalAPI::attachAPI(LuaAPI* api) {
  cout << "attaching new API to lua state\n" << api->name;

  lua_getglobal(L, "leansand");
  int ls = lua_gettop(L);

  lua_newtable(L);
  int table = lua_gettop(L);
  api->attach(L, table);

  lua_setfield(L, ls, api->name);

  // TODO: remember the definitions, so they can later be detached
}

void LuaGlobalAPI::detachAPI(LuaAPI* api) {
  // TODO: detach the definitions from attachAPI
  // do we need it?
}

void LuaGlobalAPI::runFile(string filename) {
  luaL_dofile(L, filename.c_str());
}
