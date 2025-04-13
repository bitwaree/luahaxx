// exports.c: contains export/registration table for various APIs.

// Copyright (C) 2025, bitware
// This file is a part of LuaHaxx Project.

#include "config.h"
#include "lualoader.h"

#if defined(USE_LIBGAMEPWNAGE) && USE_LIBGAMEPWNAGE == 1
#include "gamepwnage/definitions.h"
#endif

#include "misc/definitions.h"

const struct ExportFuncToLua exportTable[] = {
    /*
    This is a array of function to be exported in each Lua Instance
    Usage:
    {    Function    ,    "Name"    }
    */
    #if defined(USE_LIBGAMEPWNAGE) && USE_LIBGAMEPWNAGE == 1
    // TODO: update when libgamepwnage is ready
    #endif
    // misc/extra apis below
    { write_int, "write_int" },
    { read_int, "read_int" },
    { write_byte, "write_byte" },
    { read_byte, "read_byte" },
    { delaySec, "delay" }
};

const int numberofExportFunc = sizeof(exportTable)/sizeof(struct ExportFuncToLua);
