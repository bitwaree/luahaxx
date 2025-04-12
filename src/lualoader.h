// lualoader.h: a header file for lualoader.c

// Copyright (C) 2025, bitware
// This file is a part of LuaHaxx Project.

#pragma once
#include <lua.h>

struct LuaLoaderParams{
    bool enablegamepwnage;
    char filename[4096];   // the lua file path
    char baseName[256];    // same as the hxo loader parameter
};

int NOEXPORT lua_loader_thread(struct LuaLoaderParams *lualoaderparams);

#if defined(USE_LIBGAMEPWNAGE) && USE_LIBGAMEPWNAGE == 1
struct ExportFuncToLua{
    int (*func) (lua_State *L);    // the Function
    char funcName[256];            // the export name
};

extern const struct ExportFuncToLua exportTable[];
extern const int numberofExportFunc;
#endif

