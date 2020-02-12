#include "logger.h"

/*
 * Initialize logger once for the app.
 * Creates log file (path is taken from env variable).
 * If file already exists truncates it.
 */
Logger *init_logger(void) {
    Logger *logger = malloc(sizeof(*logger));
    char *log_file_path = getenv("SNAKE_LOG_FILE");

    logger->lf = NULL;
    logger->logfunc_cnt = 0;
    logger->logfuncs = NULL;
    logger->objects = NULL;

    FILE *log_file = fopen(log_file_path, "w");
    if (log_file) {
        char session_start_time[LOG_TIME_SIZE];
        set_formatted_time(session_start_time);
        fprintf(log_file, "SESSION [%s]\n", session_start_time);
        logger->lf = log_file;
    } else {
        printf("Can't open log file: %s\n", log_file_path);
        printf("Set 'SNAKE_LOG_FILE' in order to suppress this message.\n");
        fflush(stdout);
    }

    return logger;
}


/*
 * Adds log function to logger. See perform_log.
 */
void add_logfunc(Logger *logger, LogFunc logfunc, void *object) {
    logger->logfuncs = realloc(logger->logfuncs, ++(logger->logfunc_cnt));
    logger->objects = realloc(logger->objects, logger->logfunc_cnt);
    logger->logfuncs[logger->logfunc_cnt-1] = logfunc;
    logger->objects[logger->logfunc_cnt-1] = object;
}


/*
 * Logs objects with corresponding log functions.
*/
void perform_log(Logger *logger) {
    LogFunc func = NULL;
    void *obj = NULL;
    char log_time[LOG_TIME_SIZE];
    set_formatted_time(log_time);

    if (logger->lf) {
        for (int i = 0; i < logger->logfunc_cnt; i++) {
            func = logger->logfuncs[i];
            obj = logger->objects[i];
            if (obj && func) {
                fprintf(logger->lf, "[%s] - ", log_time);
                func(logger->objects[i], logger->lf);
            }
        }
    }
}


/*
 * Closes log file, frees log functions and objects' arrays.
 * Real objects are not touched.
 */
void deinit_logger(Logger *logger) {
    if (logger) {
        if (logger->lf) fclose(logger->lf);
        if (logger->logfuncs) free(logger->logfuncs);
        if (logger->objects) free(logger->objects);
    }
}


/*
 * Shortcut for strftime function.
 */
void set_formatted_time(char *otime) {
    time_t t ;
    struct tm *tmp ;
    time(&t);
    tmp = localtime(&t);
    strftime(otime, LOG_TIME_SIZE, "%x %H:%M:%S", tmp);
}
