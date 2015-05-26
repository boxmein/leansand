#ifndef LUAAPI_H
#define LUAAPI_H

#include <lua.hpp>


/**
  \brief An object representing a bunch of Lua functions / etc together.
  \sa LuaGlobalAPI
*/
class LuaAPI {
  public:
    /** Name of the API (eg for leansand.ui the name = "ui") **/
    char* name;
    /** You can put stuff in here, but this doesn't initialize the Lua structure */
    LuaAPI();
    ~LuaAPI();

    /**
      \brief Called when the API is attached onto the LuaGlobalAPI.
      There will be a lua_newtable() at index table_index in the Lua stack, so
      populate it with whatever you want and make sure the stack ends up even.
      After the attach() call, the new table will be attached to leansand, using
      the name provided above.

      \param L the lua state
      \param table_index the index in the stack containing a table just for this api
    */
    void attach(lua_State* L, int table_index);
    /**
      \brief TODO: implement module un-loading
    */
    void detach(lua_State* L, int table_index);
};

#endif
