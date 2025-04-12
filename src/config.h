// config.h: BUILD time configurations.

// Copyright (C) 2025, bitware
// This file is a part of LuaHaxx Project.

#pragma once
#include <stdbool.h>

#define INI_CONFIG_FILE "luahaxx.ini"    //the ini config for luahaxx
#define MAX_LUA_FILES 256

// enable definations for accessing libgamepwnage api, disabled by default
#ifndef USE_LIBGAMEPWNAGE
#define USE_LIBGAMEPWNAGE 0
#endif

#ifndef NOEXPORT
#define NOEXPORT __attribute__((visibility("hidden")))
#endif

#ifndef NOEXPORT
#define NOEXPORT __attribute__((visibility("hidden")))
#endif

// the parsed ini data
struct LuaHaxxConfig{
    bool enable;           // enable/disable luahaxx
    bool ExecuteParallel;  // if enabled luahaxx will run lua codes in parallel
    bool EnableGamePwnage; // will enable api for accessing libgamepwnage API
    char luadir[4096];     // the directory where .lua/.luac files will be placed
};
