// lualoader.c: manages, exports APIs, invokes lua files.

// Copyright (C) 2025, bitware
// This file is a part of LuaHaxx Project.

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <stdio.h>
#include <stdlib.h>

#include "luainit.h"
#include "lualoader.h"

void NOEXPORT ExportFunctions(lua_State *L);

int NOEXPORT lua_loader_thread(struct LuaLoaderParams *lualoaderparams)
{
    lua_State *L;

    L = luaL_newstate();
    luaL_openlibs(L);                           // Load Lua libraries

    #if defined(USE_LIBGAMEPWNAGE) && USE_LIBGAMEPWNAGE == 1
    if(lualoaderparams->enablegamepwnage)
        ExportFunctions(L);
    #endif
    if (luaL_loadfile(L, lualoaderparams->filename))              // load but the Lua script
    {
        // handle any error may have occured while loading the file and exit thread
        fprintf(stderr, "\nLuaHaxX ERROR while loading file %s:\n\t%s\n", lualoaderparams->filename, lua_tostring(L, -1));
        fflush(stderr);
        lua_close(L);  
        free(lualoaderparams);
        return 1;
    }

    if (lua_pcall(L, 0, 0, 0))                  // Run the loaded Lua script
    {
        // handle any error may have occured while running the file and exit thread
        fprintf(stderr, "\nLuaHaxX ERROR while running file %s:\n\t%s\n", lualoaderparams->filename, lua_tostring(L, -1));
        fflush(stderr);
        lua_close(L);
        free(lualoaderparams);
        return 1;
    }

    // printf("%s exited successfully\n", lualoaderparams->filename);
    lua_close(L);                               // close the lua state
    free(lualoaderparams);                      // free the struct
    return 0;
}

#if defined(USE_LIBGAMEPWNAGE) && USE_LIBGAMEPWNAGE == 1
void NOEXPORT ExportFunctions(lua_State *L)
{
    // register each functions/apis form the export table
    for(int i = 0; i < numberofExportFunc; i++)
    {
        lua_pushcfunction(L, exportTable[i].func);
        lua_setglobal(L, exportTable[i].funcName);
    }
}
#endif
