// SPDX-FileCopyrightText: 2025 Avinal Kumar avinal.xlvii@gmail.com
// SPDX-License-Identifier: MIT

#pragma once
#include <functional>
#include <iostream>
#include <string>
#include <vector>

inline int g_failures = 0;

struct TestCase {
  std::string name;
  std::function<void()> fn;
};

inline std::vector<TestCase> &test_registry() {
  static std::vector<TestCase> r;
  return r;
}

/* helper to build unique identifiers from __LINE__ */
#define TEST_CONCAT_INNER(a, b) a##b
#define TEST_CONCAT(a, b) TEST_CONCAT_INNER(a, b)

/*
   Usage:
     TEST("Some name with spaces") { ... }
*/
#define TEST(name)                                                             \
  static void TEST_CONCAT(test_func_, __LINE__)();                             \
  static bool TEST_CONCAT(test_reg_, __LINE__) = []() {                        \
    test_registry().push_back({name, TEST_CONCAT(test_func_, __LINE__)});      \
    return true;                                                               \
  }();                                                                         \
  static void TEST_CONCAT(test_func_, __LINE__)()

#define EXPECT_EQ(a, b)                                                        \
  do {                                                                         \
    if ((a) != (b)) {                                                          \
      std::cout << "[FAILED] " << __FILE__ << ":" << __LINE__ << ": expected " \
                << #a << " == " << #b << " but got " << (a) << "\n";           \
      ++g_failures;                                                            \
    }                                                                          \
  } while (0)

#define EXPECT_NE(a, b)                                                        \
  do {                                                                         \
    if ((a) == (b)) {                                                          \
      std::cout << "[FAILED] " << __FILE__ << ":" << __LINE__ << ": expected " \
                << #a << " != " << #b << "\n";                                 \
      ++g_failures;                                                            \
    }                                                                          \
  } while (0)

#define EXPECT_TRUE(a)                                                         \
  do {                                                                         \
    if (!(a)) {                                                                \
      std::cout << "[FAILED] " << __FILE__ << ":" << __LINE__                  \
                << ": expected true: " << #a << "\n";                          \
      ++g_failures;                                                            \
    }                                                                          \
  } while (0)

inline int tests_summary() {
  std::cout << "Running " << test_registry().size() << " tests...\n";
  for (auto &t : test_registry()) {
    std::cout << "[ RUN     ] " << t.name << "\n";
    try {
      t.fn();
    } catch (const std::exception &e) {
      std::cout << "[  ERROR  ] exception: " << e.what() << "\n";
      ++g_failures;
    } catch (...) {
      std::cout << "[  ERROR  ] unknown exception\n";
      ++g_failures;
    }
    std::cout << "[   DONE  ] " << t.name << "\n";
  }

  if (g_failures == 0)
    std::cout << "\nAll tests passed \\^_^/\n";
  else
    std::cout << "\n" << g_failures << " tests failed /^.^\\\n";

  return g_failures;
}
