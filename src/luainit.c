// luainit.c: This file contains the main thread for luahaxx.

// Copyright (C) 2025, bitware
// This file is a part of LuaHaxx Project.

#include "luainit.h"
#include "lualoader.h"
#include "config.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <pthread.h>

#include <sys/types.h>
#include <dirent.h>

// #include <unistd.h>


int NOEXPORT lua_init(struct LuaHaxxParameters *luahaxx_parameters)
{
    // get the path where lua files will be located
    char luadir[4096];
    dircat(luadir, luahaxx_parameters->modulePath, luahaxx_parameters->luahaxx_config.luadir);
    // search for lua/luac files
    DIR *dir;
    struct dirent *entry;
    char *lua_files[MAX_LUA_FILES];        // assuming a maximum number of files
    int count = 0;

    dir = opendir(luadir);
    if (dir == NULL)
    {
        free(luahaxx_parameters);
        return 1;
    }

    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_REG)
        { // Check if it is a regular file
            char *dot = strrchr(entry->d_name, '.');
            if (dot && !(!strcmp(dot, ".lua") || !strcmp(dot, ".luac")) == 0)
            {
                lua_files[count] = strdup(entry->d_name);
                count++;
            }
        }
    }
    closedir(dir);
    
    struct LuaLoaderParams *lualoaderparams;    // a dynamically allocated struct for passing
                                                //    parameters to the lua loader thread
    char current_filename[4096];
    if(luahaxx_parameters->luahaxx_config.ExecuteParallel)
    {
        // execute parallelly, start seperate thread for each file
        pthread_t thr;
        for(int i = 0; i < count ; i++)
        {
            dircat(current_filename, luadir, lua_files[i]);
            lualoaderparams = (struct LuaLoaderParams*) malloc(sizeof(struct LuaLoaderParams));
            strcpy(lualoaderparams->filename, current_filename);
            strcpy(lualoaderparams->baseName, luahaxx_parameters->baseName);
            lualoaderparams->enablegamepwnage = luahaxx_parameters->luahaxx_config.EnableGamePwnage;
            thr = 0;
            pthread_create(&thr, 0, (void *(*)(void*)) lua_loader_thread, lualoaderparams);
        }
    }
    else
    {
        // execute sequentially, load the next lua file only when the previous one exits
        for(int i = 0; i < count ; i++)
        {
            dircat(current_filename, luadir, lua_files[i]);
            lualoaderparams = (struct LuaLoaderParams*) malloc(sizeof(struct LuaLoaderParams));
            strcpy(lualoaderparams->filename, current_filename);
            strcpy(lualoaderparams->baseName, luahaxx_parameters->baseName);
            lualoaderparams->enablegamepwnage = luahaxx_parameters->luahaxx_config.EnableGamePwnage;
            lua_loader_thread(lualoaderparams);
        }
    }

    /*
    NOTE: NO this malloc() shouldn't cause a memeory leak as the memeory is freed by 
    lua_loader_thread() before exiting
    */

    for(int i = 0; i < count ; i++)
    {
        free(lua_files[count]);
    }
    free(luahaxx_parameters);
    return 0;
}
