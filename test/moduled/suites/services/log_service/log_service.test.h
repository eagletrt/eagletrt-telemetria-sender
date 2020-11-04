#ifndef TELEMETRY_TEST_LOG_SERVICE
#define TELEMETRY_TEST_LOG_SERVICE

/** IMPORTS **/

#include "../../../libs/munit/munit.h"
#include "./debug_config_path/debug_config_path.test.h"
#include "./debug_gps_port/debug_gps_port.test.h"
#include "./debug_generic/debug_generic.test.h"
#include "./info_transition/info_transition.test.h"
#include "./info_starting_up/info_starting_up.test.h"
#include "./info_gps_plugged/info_gps_plugged.test.h"
#include "./info_quitting/info_quitting.test.h"
#include "./info_new_session/info_new_session.test.h"
#include "./success_started_up/success_started_up.test.h"
#include "./success_insertion/success_insertion.test.h"
#include "./success_quitting/success_quitting.test.h"
#include "./error_parsing_config/error_parsing_config.test.h"
#include "./error_opening_gps/error_opening_gps.test.h"

/* EXPORTED SUITE */

MunitSuite* get_log_service_suite();

#endif