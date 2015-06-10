#ifndef LEANSAND_H
#define LEANSAND_H

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>
#include <vector>

#include <SDL2/SDL.h>

#include "LeanSandGame.h"
#include "LuaAPIManager.h"
#include "LuaUIAPI.h"
#include "UIRect.h"


#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#pragma once
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#ifdef LUAJIT
#pragma comment(lib, "luajit.lib")
#else
#pragma comment(lib, "lua5.1.0.lib")
#endif
#pragma comment(linker, "/SUBSYSTEM:windows")
#endif

#define VERSION "0.0.1"
#define WIDTH 612
#define HEIGHT 384
#define TARGET_FPS 60

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif

#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif

int cleanup();

#endif
