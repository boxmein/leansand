#ifndef LUAAPI_H
#define LUAAPI_H

#include <lua.hpp>

class LuaGlobalAPI {
  public:
    LuaGlobalAPI();
    ~LuaGlobalAPI();
    void attachAPI(LuaAPI* api);
    void detachAPI(LuaAPI* api);
    void runFile(string filename);

  private:
    /** Global Lua state */
    lua_State* L;
};

#endif
