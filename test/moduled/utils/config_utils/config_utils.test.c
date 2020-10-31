#include "config_utils.test.h"

MunitSuite *get_config_utils_suite()
{
    MunitSuite *sub_suites = (MunitSuite *)malloc(1 * sizeof(MunitSuite));
    sub_suites[0] = *get_config_utils_new_config_and_delete_config_suite();

    MunitSuite *suite = (MunitSuite *)malloc(sizeof(MunitSuite));
    suite->prefix = "/config_utils";
    suite->tests = NULL;
    suite->suites = sub_suites;
    suite->iterations = 1;
    suite->options = MUNIT_SUITE_OPTION_NONE;

    return suite;
}