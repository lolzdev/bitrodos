#ifndef LOG_H
#define LOG_H

#define CRITICAL_ASSERT(message, ...) do { \
    if (!(__VA_ARGS__)) { \
        fatal(message); \
    } \
} while(0)

#include <stdarg.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>

void info(char *format, ...);
void warn(char *format, ...);
void error(char *format, ...);
void fatal(char *format, ...);

int l_info(lua_State *L);
int l_warn(lua_State *L);
int l_error(lua_State *L);

#endif
