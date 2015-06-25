#include "LuaAPIManager.h"
using namespace std;

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
        cout << boolalpha << (bool)lua_toboolean(L, i);
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
  cerr << luaErrPrefix << "Panic: " << string(lua_tostring(L, -1));
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
}

LuaAPIManager::~LuaAPIManager() {

}

void LuaAPIManager::addPackagePath(string path) {
  lua_getglobal(L, "package");
  lua_getfield(L, -1, "path");
  std::string current = lua_tostring(L, -1);
  current.append(";");
  current.append(path);
  lua_pop(L, 1);
  lua_pushstring(L, current.c_str());
  lua_setfield(L, -2, "path");
  lua_pop(L, 1);
}

void LuaAPIManager::runFile(string filename) {
  struct stat buffer;
  if(stat(filename.c_str(),&buffer)==0){
    luaL_loadfile(L, filename.c_str());
    lua_call(L, 0, 0);
  }
}
