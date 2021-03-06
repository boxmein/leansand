
#ifndef LEANSAND_H
#define LEANSAND_H

#include <SDL2/SDL.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <ctime>
#include <stdint.h>
#include <string>

using namespace std;

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#pragma once
#pragma comment(lib, "SDL2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment(lib, "lua5.3.0.lib")
#endif

#define VERSION "0.0.2"
#define WIDTH 612
#define HEIGHT 384
#define TARGET_FPS 60

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS 0
#endif

#ifndef EXIT_FAILURE
#define EXIT_FAILURE 1
#endif

#include "LeanSandGame.h"
#include "LuaGlobalAPI.h"

#endif
