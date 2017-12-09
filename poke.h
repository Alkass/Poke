#ifndef POKE_H
#define POKE_H

#include "logger.h"

typedef enum test_case_status_e {
  UNKNOWN = 0,
  PASSED,
  FAILED
} test_case_status;

typedef struct test_node_s {
  char* title;
  char* criteria;
  test_case_status (*test)(logger*, void*);
  struct test_node_s* on_success;
  struct test_node_s* on_failure;
} test_node;

__attribute__((constructor)) static void init_poke();
__attribute__((destructor)) static void kill_poke();

test_node* new_test(char* title, char* criterna, test_case_status (*test)(logger*, void*));
bool run_test(test_node*, void*);
void run_tests(test_node*, void*);
#endif
