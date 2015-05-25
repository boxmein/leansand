#include "leansand.h"

const char* luaPrintPrefix = "(lua): ";
const char* luaErrPrefix = "(lua) Error: ";

int luaPrintHook(lua_State* L) {
  int argc = lua_gettop(L);
  cout << luaPrintPrefix;
  
  for (int i = 1; i <= argc; i++) {
    cout << ' ';
    
    int type = lua_type(L, i);
    switch (type) {
      case LUA_TNIL:
        cout << "nil";
        break;
      case LUA_TNUMBER:
      case LUA_TSTRING:
        cout << lua_tostring(L, i);
        break;
      case LUA_TBOOLEAN:
        cout << std::boolalpha << (bool)lua_toboolean(L, i);
        break;
      default:
        cout << lua_typename(L, type) << ": " << lua_topointer(L, i);
        break;
    }
  }

  cout << "\n";
  return 0;
}

int luaPanicHook(lua_State* L) {
  cerr << luaErrPrefix << "Panic: " << std::string(lua_tostring(L, -1));
  cerr.flush();

  cleanup();

  // returning from here calls abort()
  // the alternative is long-jumping to somewhere, but since we depend on Lua
  // a lot then this is more acceptable
  return 0;
}

LuaAPIManager::LuaAPIManager() {
  L = luaL_newstate();

  if (L == NULL) {
    cerr << "luaL_newstate returned NULL, memory allocation error!";
  }

  luaL_openlibs(L);

  // Hook print events to redirected cout instead of stdout
  lua_pushcfunction(L, luaPrintHook);
  lua_setglobal(L, "print");

  // Hook errors outside protected environments to the panic hook
  lua_atpanic(L, luaPanicHook);

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

LuaAPIManager::~LuaAPIManager() {

}

void LuaAPIManager::attachAPI(LuaAPI* api) {
  cout << "attaching new API to lua state\n" << api->name;

  lua_getglobal(L, "leansand");
  int ls = lua_gettop(L);

  lua_newtable(L);
  int table = lua_gettop(L);
  api->attach(L, table);

  lua_setfield(L, ls, api->name);

  // TODO: remember the definitions, so they can later be detached
}

void LuaAPIManager::detachAPI(LuaAPI* api) {
  // TODO: detach the definitions from attachAPI
  // do we need it?
}

void LuaAPIManager::runFile(string filename) {
  luaL_loadfile(L, filename.c_str());
  lua_call(L, 0, 0);
}
