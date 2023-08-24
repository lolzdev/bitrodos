#ifndef TEST_H
#define TEST_H

#include <stdio.h>

#define OK do { \
    printf("\033[0;32m[SUCCESS]\033[0m: %s\n", __func__); \
    return 0; \
} while(0);

#define RUN_TEST(test) do { \
    tested++; \
    if (test() != 0) { \
       failed++; \
    } \
} while (0);

#define TEST(...) do { \
    if (!(__VA_ARGS__)) { \
        printf("\033[0;31m[FAIL]\033[0m: %s\n", __func__); \
        return 1; \
    } \
} while(0);

static int tested = 0;
static int failed = 0;

#endif
