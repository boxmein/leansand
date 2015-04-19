#ifndef LUAGLOBALAPI_H
#define LUAGLOBALAPI_H

#include "leansand.h"
#include "LuaAPI.h"
#include <lua.hpp>

/**
  \brief Lua state and API management
  \sa LuaAPI

  This class represents a Lua state with a bunch of loaded extras ("APIs"), as
  well as the ability to run code inside that Lua state. To setup, simply
  construct the object and attachAPI() as much as you need. Then, runFile() with
  a Lua script file.
*/
class LuaGlobalAPI {
  public:
    /**
      Constructs a new LuaGlobalAPI, with its own lua_State and empty list of
      APIs to be loaded later.
    */
    LuaGlobalAPI();
    ~LuaGlobalAPI();

    /**
      Attaches a new LuaAPI* (a thing that defines a Lua API) to the state.
    */
    void attachAPI(LuaAPI* api);
    void detachAPI(LuaAPI* api);

    /**
      Run a file inside this Lua state
    */
    void runFile(string filename);

  private:
    /** Global Lua state */
    lua_State* L;
};

#endif
