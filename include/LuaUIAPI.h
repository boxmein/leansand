#ifndef LUAUIAPI_H
#define LUAUIAPI_H

#include <lua.hpp>

#include "LuaAPI.h"


/**
  \brief API to access user interface primitives in the game
  This is the first-ever Lua API for leansand. It can be used to define user
  interface objects.

  Right now it doesn't do much - attach() is called when the API is loaded into
  LuaGlobalAPI and detach() is called otherwise.
*/
class LuaUIAPI : public LuaAPI {
  public:
    LuaUIAPI();
    ~LuaUIAPI();
    void attach(lua_State* L, int table_index);
    void detach(lua_State* L, int table_index);
};

#endif
