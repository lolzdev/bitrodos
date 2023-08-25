#include <log.h>

void print_time()
{
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    printf("[%d:%d:%d]", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
}

void info(char *format, ...)
{
    va_list argp;
    va_start(argp, format);
    printf("\033[0;34m[INFO]\033[0m");
    print_time();
    printf(": ");
    vprintf(format, argp);
    printf("\n");
    va_end(argp);
}

void warn(char *format, ...)
{
    va_list argp;
    va_start(argp, format);
    printf("\033[0;33m[WARN]\033[0m");
    print_time();
    printf(": ");
    vprintf(format, argp);
    printf("\n");
    va_end(argp);
}

void error(char *format, ...)
{
    va_list argp;
    va_start(argp, format);
    printf("\033[0;31m[ERROR]\033[0m");
    print_time();
    printf(": ");
    vprintf(format, argp);
    printf("\n");
    va_end(argp);
}

void fatal(char *format, ...)
{
    va_list argp;
    va_start(argp, format);
    printf("\033[0;31m[FATAL]\033[0m");
    print_time();
    printf(": ");
    vprintf(format, argp);
    printf("\n");
    va_end(argp);
    exit(EXIT_FAILURE);
}
