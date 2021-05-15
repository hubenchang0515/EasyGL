#ifndef EASYGL_LOG_H
#define EASYGL_LOG_H

#include <stdio.h>


// Log Tag
#ifdef __linux__
    #define EASYGL_LOG_TAG_VERBOSE  "\033[97;1mVERBOSE\033[0m"
    #define EASYGL_LOG_TAG_DEBUG    "\033[96;1mDEBUG\033[0m"
    #define EASYGL_LOG_TAG_INFO     "\033[94;1mINFO\033[0m"
    #define EASYGL_LOG_TAG_WARNING  "\033[93;1mWARNING\033[0m"
    #define EASYGL_LOG_TAG_ERROR    "\033[91;1mERROR\033[0m"
#else
    #define EASYGL_LOG_TAG_VERBOSE  "VERBOSE"
    #define EASYGL_LOG_TAG_DEBUG    "DEBUG"
    #define EASYGL_LOG_TAG_INFO     "INFO"
    #define EASYGL_LOG_TAG_WARNING  "WARNING"
    #define EASYGL_LOG_TAG_ERROR    "ERROR"
#endif 


// enum of LOG_LEVEL
#define    EASYGL_LOG_LEVEL_ERROR      0
#define    EASYGL_LOG_LEVEL_WARNING    1
#define    EASYGL_LOG_LEVEL_INFO       2
#define    EASYGL_LOG_LEVEL_DEBUG      3
#define    EASYGL_LOG_LEVEL_VERBOSE    4


// Default LOG_LEVEL
#ifndef EASYGL_LOG_LEVEL
    #define EASYGL_LOG_LEVEL EASYGL_LOG_LEVEL_INFO
#endif // LOG_LEVEL


#if EASYGL_LOG_LEVEL >= EASYGL_LOG_LEVEL_VERBOSE
    #define VERBOSE(fmt, ...) fprintf(stdout, "[%s:%d][" EASYGL_LOG_TAG_VERBOSE "]: " fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#else
    #define VERBOSE(fmt, ...)
#endif

#if EASYGL_LOG_LEVEL >= EASYGL_LOG_LEVEL_DEBUG
    #define DEBUG(fmt, ...) fprintf(stdout, "[%s:%d][" EASYGL_LOG_TAG_DEBUG "]: " fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#else
    #define DEBUG(fmt, ...)
#endif

#if EASYGL_LOG_LEVEL >= EASYGL_LOG_LEVEL_INFO
    #define INFO(fmt, ...) fprintf(stdout, "[%s:%d][" EASYGL_LOG_TAG_INFO "]: " fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#else
    #define INFO(fmt, ...)
#endif

#if EASYGL_LOG_LEVEL >= EASYGL_LOG_LEVEL_WARNING
    #define WARNING(fmt, ...) fprintf(stdout, "[%s:%d][" EASYGL_LOG_TAG_WARNING "]: " fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#else
    #define WARNING(fmt, ...)
#endif

#if EASYGL_LOG_LEVEL >= EASYGL_LOG_LEVEL_ERROR
    #define ERROR(fmt, ...) fprintf(stderr, "[%s:%d][" EASYGL_LOG_TAG_ERROR "]: " fmt, __FILE__, __LINE__, ##__VA_ARGS__)
#else
    #define ERROR(fmt, ...)
#endif

#endif // EASYGL_LOG_H