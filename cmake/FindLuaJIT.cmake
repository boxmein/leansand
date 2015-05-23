FIND_PATH(LUA_INCLUDE_DIR luajit.h
  HINTS
  $ENV{LUA_DIR}
  PATH_SUFFIXES include/luajit-2.0 include/luajit2.0 include/luajit include
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr
  /usr/local
  /opt
  /opt/local
)

FIND_LIBRARY(LUA_LIBRARY 
  NAMES luajit-51 luajit-5.1 luajit
  HINTS
  $ENV{LUA_DIR}
  PATH_SUFFIXES lib64 lib
  PATHS
  ~/Library/Frameworks
  /Library/Frameworks
  /usr/local
  /usr
  /sw
  /opt/local
  /opt/csw
  /opt
)

IF(LUA_LIBRARY)
  IF(UNIX AND NOT APPLE)
    FIND_LIBRARY(LUA_MATH_LIBRARY m)
    SET( LUA_LIBRARIES "${LUA_LIBRARY};${LUA_MATH_LIBRARY}" CACHE STRING "Lua Libraries")
  ELSE(UNIX AND NOT APPLE)
    SET( LUA_LIBRARIES "${LUA_LIBRARY}" CACHE STRING "Lua Libraries")
  ENDIF(UNIX AND NOT APPLE)
ENDIF(LUA_LIBRARY)

INCLUDE(FindPackageHandleStandardArgs)
FIND_PACKAGE_HANDLE_STANDARD_ARGS(LuaJIT  DEFAULT_MSG  LUA_LIBRARIES LUA_INCLUDE_DIR)

MARK_AS_ADVANCED(LUA_INCLUDE_DIR LUA_LIBRARIES LUA_LIBRARY LUA_MATH_LIBRARY)
