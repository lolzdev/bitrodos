#ifndef TEST_H
#define TEST_H

#define OK do { \
    return 0; \
} while(0);

#define RUN_TEST(test) do { \
    if (test() != 0) { \
        return 1; \
    } \
} while (0);

#define TEST(...) do { \
    if (!(__VA_ARGS__)) { \
        return 1; \
    } \
} while(0);

#endif
