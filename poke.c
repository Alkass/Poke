#include "poke.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "logger.h"

__attribute__((constructor)) void init_poke() {
  printf("--- Starting Tests ---\n\n");
}

__attribute__((destructor)) void kill_poke() {
  printf("\n--- Testing Ended ---\n");
}

test_node* new_test(char* title, char* criteria, test_case_status (*test)(logger* l, void* data)) {
  if (!title || !criteria || !test) {
    return NULL;
  }
  else {
    test_node* tn = (test_node*)calloc(1, sizeof(test_node));
    tn->title = (char*)calloc(sizeof(char), strlen(title) + 1);
    tn->criteria = (char*)calloc(sizeof(char), strlen(criteria) + 1);
    strcpy(tn->title, title);
    strcpy(tn->criteria, criteria);
    tn->test = test;
    tn->on_success = NULL;
    tn->on_failure = NULL;
    return tn;
  }
}

bool run_test(test_node* t, void* data) {
  if (!t) {
    return false;
  }
  if (!t->title || !t->criteria || !t->test) {
    return false;
  }
  printf("* Running %s...\n", t->title);
  printf("  Criteria: %s\n", t->criteria);
  logger l;
  init_logger(&l);
  test_case_status tcs = t->test(&l, data);
  printf("  Results: FATAL %d, ERROR: %d, WARN: %d, PASS: %d, INFO: %d\n\n", l.fatal_count, l.error_count, l.warn_count, l.pass_count, l.info_count);
  if (tcs == UNKNOWN) {
    if (l.fatal_count || l.error_count) {
      return false;
    }
    else {
      return true;
    }
  }
  return tcs == PASSED;
}

void run_tests(test_node* l, void* data) {
  if (!l) {
    return;
  }
  if (run_test(l, data)) {
    if (l->on_success) {
      run_tests(l->on_success, data);
    }
    else {
      run_tests(l->on_failure, data);  
    }
  }
}
