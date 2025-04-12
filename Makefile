# Copyright (C) 2025, bitware
# This file is a part of LuaHaxx Project.
# https://github.com/bitwaree/luahaxx

# can be modified as per the system
CC=gcc
CFLAGS=-Wall -Werror
LDFLAGS=
LIBGAMEPWNAGE=on
OUTPUT_FILE=luahaxx.hxo
# must be specified via cli or modifying makefile
LUAENGINE=null


# don't modify
SOURCE_FILES=src/hxomain.c src/luainit.c src/lualoader.c src/utils.c
EXTRA_SOURCE=src/gamepwnage/exports.c

ifneq ($(LIBGAMEPWNAGE), off)
# libgamepwnage is enabled
override CFLAGS += -DUSE_LIBGAMEPWNAGE=1
SOURCE_FILES += $(EXTRA_SOURCE)
endif

ifeq ($(LUAENGINE), lua)
# default lua is enabled
override CFLAGS += -DLUA=1 -DLUAJIT=0
override LDFLAGS += -l:liblua.a
else ifeq ($(LUAENGINE), lua-jit)
# lua jit is enabled
override CFLAGS += -DLUA=0 -DLUAJIT=1
override LDFLAGS += -l:libluajit.a -lm
else
#$(error LUAENGINE not specified! run 'make help' for more info.)
endif

all:
ifneq ($(LUAENGINE), lua)
ifneq ($(LUAENGINE), lua-jit)
	$(error LUAENGINE not specified! Run 'make help' for more info.)
endif
endif
	
	@ # proceed the the compilation process
	$(CC) -c $(CFLAGS) -fPIC $(SOURCE_FILES)
	$(CC) -o $(OUTPUT_FILE) *.o -shared $(LDFLAGS)


clean:
	@ # remove all generated files
	@ rm -v *.o *.hxo

help:
	@ echo "[LuaHaxx Peoject by bitware.]"
	@ echo "https://github.com/bitwaree/luahaxx"
	@ echo ""
	@ echo "    Reqires: 1. Lua or Lua-jit; 2. GamePwnage (https://github.com/bitwaree/gamepwnage)"
	@ echo "To build from source execute 'make LUAENGINE=<lua-interpreter>'"
	@ echo "    'LUAENGINE=lua' for default lua interpreter (https://lua.org)"
	@ echo "    'LUAENGINE=lua-jit' for lua-jit interpreter (https://luajit.org)"
	@ echo ""
	@ echo "Other Flags includes:"
	@ echo "    'CFLAGS', 'LDFLAGS', 'LIBGAMEPWNAGE'"
