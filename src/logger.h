#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LOG_TIME_SIZE 50  /* must be big enough to hold formatted datetime */


typedef void (*LogFunc)(void*, FILE*);

typedef struct {
    FILE *lf;
    LogFunc *logfuncs;
    void **objects;
    int logfunc_cnt;
} Logger;


Logger *init_logger(void);
void add_logfunc(Logger *logger, LogFunc logfunc, void*);
void perform_log(Logger *logger);
void deinit_logger(Logger *logger);
void set_formatted_time(char *otime);


#endif
