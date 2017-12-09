#ifndef LOGGER_H
#define LOGGER_H

#include <stdbool.h>

typedef unsigned int uint;

typedef enum log_type_e {
  FATAL = 0,
  ERROR,
  WARN,
  INFO,
  PASS
} log_type;

typedef struct logger_s {
  uint fatal_count;
  uint error_count;
  uint warn_count;
  uint info_count;
  uint pass_count;
  bool (*log)(struct logger_s*, log_type, char*, ...);
} logger;

bool debug_log(logger*, log_type, char*, ...);
bool init_logger(logger*);

#endif
