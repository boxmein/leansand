#ifndef LUAAPIMANAGER_H
#define LUAAPIMANAGER_H

#include <iostream>
#include <iomanip>
#include <string>
#include <sys/stat.h>

#include <lua.hpp>

#include "leansand.h"


/**
  \brief Lua state and API management
  \sa LuaAPI

  This class represents a Lua state with a bunch of loaded extras ("APIs"), as
  well as the ability to run code inside that Lua state. To setup, simply
  construct the object and attachAPI() as much as you need. Then, runFile() with
  a Lua script file.
*/
class LuaAPIManager {
  public:
    /**
      Constructs a new LuaAPIManager, with its own lua_State and empty list of
      APIs to be loaded later.
    */
    LuaAPIManager();
    ~LuaAPIManager();

    /**
      Add a string to package.path (that's where Lua searches for its modules)
    */
    void addPackagePath(std::string path);

    /**
      Run a file inside this Lua state
    */
    void runFile(std::string filename);

  private:
    /** Global Lua state */
    lua_State* L;
};

#endif
