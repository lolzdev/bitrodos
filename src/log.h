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

void info(char *format, ...);
void warn(char *format, ...);
void error(char *format, ...);
void fatal(char *format, ...);

#endif
