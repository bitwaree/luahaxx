// exports.c: contains export/registration table for various APIs.

// Copyright (C) 2025, bitware
// This file is a part of LuaHaxx Project.

#include "../config.h"
#include "../lualoader.h"

#include <stdio.h>
int hello(lua_State *L) {
    //check and fetch the arguments
    printf("Hellow >w<, this is a test function API\n");
    //return number of results
    return 1;
}

#if defined(USE_LIBGAMEPWNAGE) && USE_LIBGAMEPWNAGE == 1
const struct ExportFuncToLua exportTable[] = {
    /*
    This is a array of function to be exported in each Lua Instance
    Usage:
    {    Function    ,    "Name"    }
    */
    {hello, "hello"}
};

const int numberofExportFunc = sizeof(exportTable)/sizeof(struct ExportFuncToLua);
#endif
