#include "misc_utils.test.h"

/* EXPORTED SUITE */

MunitSuite* get_misc_utils_suite() {
  MunitSuite* sub_suites = (MunitSuite*) malloc(5 * sizeof(MunitSuite));
  sub_suites[0] = *get_misc_utils_clone_strings_array_suite();
  sub_suites[1] = *get_misc_utils_free_strings_array_suite();
  sub_suites[2] = *get_misc_utils_print_strings_array_suite();
  sub_suites[3] = *get_misc_utils_print_int_array_suite();
  sub_suites[3] = *get_misc_utils_print_double_array_suite();

  MunitSuite* suite = (MunitSuite*) malloc(sizeof(MunitSuite));
  suite->prefix = "/misc-utils";
  suite->tests = NULL;
  suite->suites = sub_suites;
  suite->iterations = 1;
  suite->options = MUNIT_SUITE_OPTION_NONE;

  return suite;
}