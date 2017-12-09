#include "logger.h"
#include <stdio.h>
#include <stdio.h>   // vprintf
#include <stdarg.h>  // va_list, va_start, va_end

void debug_log(logger* l, log_type lt, char* format, ...) {
  switch (lt) {
    case FATAL:
        l->fatal_count++;
        printf("  \033[1;31mFATAL\033[0;00m: ");
        break;
    case ERROR:
        l->error_count++;
        printf("  \033[0;31mERROR\033[0;00m: ");
        break;
    case WARN:
        l->warn_count++;
        printf("  \033[1;33mWARN\033[0;00m:  ");
        break;
    case PASS:
        l->pass_count++;
        printf("  \033[0;32mPASS\033[0;00m:  ");
        break;
    case INFO:
        l->info_count++;
        printf("  \033[0;34mINFO\033[0;00m:  ");
        break;
    default:
        printf("  \033[1;30mUNKNOWN\033[0;00m: ");
  }
  va_list args;
  va_start(args, format);
  vprintf(format, args);
  va_end(args);
  printf("\n");
}

bool init_logger(logger* l) {
  l->fatal_count = 0;
  l->error_count = 0;
  l->warn_count  = 0;
  l->info_count  = 0;
  l->pass_count  = 0;
  l->log         = debug_log;
  return true;
}
