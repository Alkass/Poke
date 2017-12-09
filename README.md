# Poke
Poke is a little C library that allows for the writing of a chain of test cases. Think of it as a tree structure where each node has two children: an `on_success` node and an `on_failure` node. A runner function iterates over the chain of test cases and invokes the `on_success` test case if the ancestor function has passed or `on_failure` otherwise.

## Getting Started

[![asciicast](https://asciinema.org/a/151885.png)](https://asciinema.org/a/151885)

### How Does it Work?
The rules are as simple and as straightforward as they could be. Every test case you write will have the form of a function of type `test_case_status` and will take two arguments: a `logger` object and a generic data holder (`void*`) that may contain anything. Here's what a typical test case would look like:

```c
test_case_status my_test(logger* l, void* data) {
  l->log(l, FATAL, "This is a fatal message"); // Other options are ERROR, WARN, PASS, and INFO
  return UNKNOWN; // Other options are PASSED and FAILED
}

test_case_status on_success_test(logger* l, void* data) {
  l->log(l, INFO, "This is an informative message");
  return PASSED;
}

test_case_status on_failure_test(logger* l, void* data) {
  l->log(l, PASS, "This is a success indicator");
  return PASSED;
}

int main() {
  test_node* tn = new_test("Test 1", "Criteria of Test 1", my_test);
  tn->on_success = new_test("Test 2", "Criteria of Test 2", on_success_test);
  tn->on_failure = new_test("Test 2", "Criteria of Test 2", on_failure_test);

  // NOTE: You can continue to append test cases to your chain as follows:
  // tn->on_success->on_success = new_test("Test 3", "Criteria of Test 3", on_success_test);
  // tn->on_success->on_failure = new_test("Test 3", "Criteria of Test 3", on_success_test);

  run_tests(tn, NULL); // The second argument (NULL in this case) is a generic
                       // heap-allocated object that gets passed down to every
                       // test function as void*

  // NOTE: If you want to only run an existing test case without running down
  // the chain, use run_test(tn, NULL) instead

  return 0;
}
```

The test case's return value can be one of three valid values: `PASSED`, `FAILED`, and `UNKNOWN`.

> The value `UNKNOWN` allows the test runner to decide whether the test has passed or failed. If at least one FATAL or ERROR messages is printed, the test will be treated as a failure. Any other scenario is considered a pass.

Now, your test case function is useless on its own; You need to pack it as a test case and hand it over to a runner function.

### Installing the Library
#### Installing From Source
Check out the source code

```bash
$ git clone https://github.com/alkass/Poke.git Poke && cd Poke
```

Build the source

```bash
$ make
```

> To verify that the library was built successfully, you may run `make test`. If this passes, everything is good to go.

Now you'll have a static library file named `poke.a` under your current directory. This is the only file you need to build your test cases.

Import the `poke.h` header file inside a source file

```c
#include "poke.h"
```

That will give you access to everything you need to utilize the library. To compile your test case, simply pass the source file(s) and the compiled library file to your compiler:

```bash
$ gcc main.c poke.a # Assuming main.c is your source file path and poke.a is the static library path
```

## Author
[Fadi Hanna Al-Kass](https://github.com/alkass)
