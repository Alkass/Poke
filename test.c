#include <stdio.h>
#include "poke.h"

test_case_status main_test(logger* l, void* data) {
  l->debug_log(l, FATAL, "hello world");
  return UNKNOWN;
}

test_case_status on_success_test(logger* l, void* data) {
  return FAILED;
}

test_case_status on_success_success_test(logger* l, void* data) {
  return PASSED;
}

int main() {
  test_node* tn = new_test("title", "criteria", main_test);
  tn->on_success = new_test("on_success test", "criteria", on_success_test);
  tn->on_success->on_success = new_test("on_success success text", "criteria", on_success_success_test);
  run_tests(tn, NULL);
  return 0;
}
