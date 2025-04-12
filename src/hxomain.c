// hxomain.c: reads config, initializes luahaxx

// Copyright (C) 2025, bitware
// This file is a part of LuaHaxx Project.

#include <hxo-user.h>
#include <stdio.h>
#include <string.h>

#include "inih/ini.h"
#include "luainit.h"
#include "utils.h"

int NOEXPORT fn_ini_handler(void *user, const char *section, const char *name, const char *value);

size_t _init_hxo(struct HXOParam *hxoParameter)  //HXO entrypoint
{
    //check for the hxo version
    if (hxo_cmpversion(hxoParameter->hxo_version, "1.2.0") == -1) {
        fprintf(stderr, "ERROR: HXO-loader version 1.2.0+ needed!\n"); 
        return -1;
    }

    struct LuaHaxxParameters *luahaxx_parameters = malloc(sizeof(struct LuaHaxxParameters));
    struct LuaHaxxConfig *luahaxx_config = &luahaxx_parameters->luahaxx_config;
    // set default values
    luahaxx_config->enable = 1;
    luahaxx_config->ExecuteParallel = 1;
    luahaxx_config->EnableGamePwnage = USE_LIBGAMEPWNAGE;
    strcpy(luahaxx_config->luadir, "luahaxx");

    char inifile[4096];
    dircat(inifile, hxoParameter->modulePath, INI_CONFIG_FILE);

    if(ini_parse(inifile, fn_ini_handler, luahaxx_config) < 0)
    {
        //ini not found
        printf("[!] %s not found, continuing with default config values.\n", INI_CONFIG_FILE);
    }
    if(!luahaxx_config->enable)
    {
        // luahaxx is disabled
        free(luahaxx_parameters);
        return -1;
    }

    // copy hxo_loader parameters
    strcpy(luahaxx_parameters->baseName, hxoParameter->baseName);
    strcpy(luahaxx_parameters->basePath, hxoParameter->basePath);
    strcpy(luahaxx_parameters->moduleName, hxoParameter->moduleName);
    strcpy(luahaxx_parameters->modulePath, hxoParameter->modulePath);


    // start a thread
    if(hxo_createthread((void *(*)(void*)) lua_init, (void *) luahaxx_parameters))
    {
        // if thread creation failed
        fprintf(stderr, "failed to create thread");
        free(luahaxx_parameters);
        return -1;
    }

    return 0;
}

// a ini handler for INIh
int NOEXPORT fn_ini_handler(void *user, const char *section, const char *name, const char *value)
{

    struct LuaHaxxConfig *cf = (struct LuaHaxxConfig*) user;
    if(!strcmp(section, "LuaHaxx"))
    {
        //configs
        if(!strcmp(name, "enable"))
            cf->enable = atoi(value);
        if(!strcmp(name, "ExecuteParallel"))
            cf->ExecuteParallel = atoi(value);
        if(!strcmp(name, "EnableGamePwnage"))
        {
            #if defined(USE_LIBGAMEPWNAGE) && USE_LIBGAMEPWNAGE == 1
            cf->EnableGamePwnage = atoi(value);
            #else
            fprintf(stderr, "[!] Error at ini parsing...this version doesn't include libgamepwnage.\n");
            cf->EnableGamePwnage = 0;
            #endif
        }

        if(!strcmp(name, "luadir")) {
            if(strlen(value) < 4096) {
                strcpy(cf->luadir, value);
            } else {
                fprintf(stderr, "[!] Error at ini parsing...too long path\n");
            }
        }
    }
    else 
    {
        return 0;
    }
    return 1;
}
