// luainit.h: a header for luainit.c

// Copyright (C) 2025, bitware
// This file is a part of LuaHaxx Project.

#pragma once
#include "config.h"

struct LuaHaxxParameters{
    char baseName[256];                     //Containing the elf executable name
    char basePath[4096];                    //elf executable path
    char moduleName[256];                   //The hxo module's file name
    char modulePath[4096];                  //the hxo module's absolute path
    struct LuaHaxxConfig luahaxx_config;    //the INI values
};


int NOEXPORT lua_init(struct LuaHaxxParameters *luahaxx_parameters);
