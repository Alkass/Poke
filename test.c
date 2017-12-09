#include <stdio.h>
#include <time.h>   // time_t
#include <stdlib.h> // rand
#include <unistd.h> // sleep
#include "poke.h"

test_case_status my_test(logger* l, void* data) {
  time_t t;
  srand(time(&t));
  if (rand() % 2) {
    l->log(l, PASS, "This is a success indicator");
  }
  else {
    l->log(l, FATAL, "This is a fatal message");
  }
  sleep(1);
  return UNKNOWN;
}

int main() {
  test_node* tn = new_test("Test 1", "Criteria of Test 1", my_test);
  tn->on_success = new_test("Test 2", "Criteria of Test 2", my_test);
  tn->on_failure = new_test("Test 2", "Criteria of Test 2", my_test);

  tn->on_success->on_success = new_test("Test 3", "Criteria of Test 3", my_test);
  tn->on_success->on_failure = new_test("Test 3", "Criteria of Test 3", my_test);

  tn->on_success->on_success->on_success = new_test("Test 4", "Criteria of Test 4", my_test);
  tn->on_success->on_failure->on_failure = new_test("Test 4", "Criteria of Test 4", my_test);

  tn->on_success->on_failure->on_success = new_test("Test 5", "Criteria of Test 5", my_test);
  tn->on_success->on_failure->on_failure = new_test("Test 5", "Criteria of Test 5", my_test);

  tn->on_success->on_failure->on_success->on_success = new_test("Test 6", "Criteria of Test 6", my_test);
  tn->on_success->on_failure->on_success->on_failure = new_test("Test 6", "Criteria of Test 6", my_test);

  run_tests(tn, NULL);
  return 0;
}
