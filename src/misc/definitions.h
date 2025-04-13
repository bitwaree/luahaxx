// // misc/definitions.h: contains extra APIs for memory management form lua.

// Copyright (C) 2025, bitware
// This file is a part of LuaHaxx Project.

#pragma once

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <stdint.h>
#include <unistd.h>

// write_int(address, value, size)
// size can be 8, 16, 32 (default), 64 bits
int write_int(lua_State *L) {
    int *address = (int*) luaL_checkinteger(L, 1);
    int64_t value = (int64_t) luaL_checkinteger(L, 2);
    int bit_len =(int) luaL_checkinteger(L, 3);

    switch (bit_len) {
    case 8:
        *((int8_t*) address) = (int8_t) value;
        break;
    case 16:
        *((int16_t*) address) = (int16_t) value;
        break;
    case 32:
        *((int32_t*) address) = (int32_t) value;
        break;
    case 64:
        *((int64_t*) address) = (int64_t) value;
        break;
    default:
        *((int*) address) = (int) value;
        break;
    }
    return 0;
}
// value = read_int(address, size)
// size can be 8, 16, 32 (default), 64 bits
int read_int(lua_State *L) {
    int *address = (int*) luaL_checkinteger(L, 1);
    int bit_len =(int) luaL_checkinteger(L, 2);
    int64_t value = 0;

    switch (bit_len) {
    case 8:
        value = *((int8_t*) address);
        break;
    case 16:
        value = *((int16_t*) address);
        break;
    case 32:
        value = *((int32_t*) address);
        break;
    case 64:
        value = *((int64_t*) address);
        break;
    default:
        value = *((int*) address);
        break;
    }
    lua_pushinteger(L, value);
    return 1;
}

// write_byte(address, value)
// byte has to be in integer and in range of 0-255
int write_byte(lua_State *L) {
    uint8_t *address = (uint8_t *) luaL_checkinteger(L, 1);
    uint8_t value = (uint8_t) luaL_checkinteger(L, 2);

    *address = value;
    return 0;
}
// value = read_byte(address)
// value will be in integer and in range of 0-255
int read_byte(lua_State *L) {
    uint8_t *address = (uint8_t *) luaL_checkinteger(L, 1);
    uint8_t value = *address;

    lua_pushinteger(L, value);
    return 1;
}
// delay(secoonds)
int delaySec(lua_State *L) {
    int t = (int) luaL_checkinteger(L, 1);
    sleep(t);
    return 0;
}
