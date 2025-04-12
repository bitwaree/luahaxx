/*-----------(START OF LICENSE NOTICE)-----------*/
/*
 * This file is part of LuaHaxx.
 *
 * NOTE: Initially this file was a part of HXO-loader, now also being used as
 * a stripped down version for luahaxx project.
 *
 * Copyright (C) 2024 bitware
*/
/*-----------(END OF LICENSE NOTICE)-----------*/

//utils.h: header for utils.c

#include "config.h"

void __attribute__((visibility("hidden"))) fixDIR(char *Dir);
void __attribute__((visibility("hidden"))) dircat(char *absolute, char *parent, char *child);
int __attribute__((visibility("hidden"))) fileExists(const char *filepath);
int __attribute__((visibility("hidden"))) dirExists(const char *path);
int __attribute__((visibility("hidden"))) CopyFile(char *source_file, char *destination_file);
