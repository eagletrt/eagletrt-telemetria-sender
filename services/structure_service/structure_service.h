#ifndef TELEMETRY_STRUCTURE_SERVICE
#define TELEMETRY_STRUCTURE_SERVICE

/* IMPORTS */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <sys/timeb.h>
#include <sys/sysinfo.h>
#include <bson.h>
#include <pthread.h>
#include "../../state_machine/state_machine_condition.h"
#include "../can_service/can_service.h"
#include "../log_service/log_service.h"
#include "../gps_service/gps_service.h"
#include "structure_identifiers.h"

/* EXTERN */

extern condition_t condition;

/* TYPES */

typedef struct {
	long timestamp;
	int value;
} inverters_right_speed_data;

typedef struct {
	long timestamp;
	int value;
} inverters_right_temperature_igbt_data;

typedef struct {
	long timestamp;
	int value;
} inverters_right_temperature_motors_data;

typedef struct {
	inverters_right_speed_data *speed;
	int speed_count;
	int speed_size;
	inverters_right_temperature_igbt_data *temperature_igbt;
	int temperature_igbt_count;
	int temperature_igbt_size;
	inverters_right_temperature_motors_data *temperature_motors;
	int temperature_motors_count;
	int temperature_motors_size;
} inverters_right_data;

typedef struct {
	long timestamp;
	int value;
} inverters_left_speed_data;

typedef struct {
	long timestamp;
	int value;
} inverters_left_temperature_igbt_data;

typedef struct {
	long timestamp;
	int value;
} inverters_left_temperature_motors_data;

typedef struct {
	inverters_left_speed_data *speed;
	int speed_count;
	int speed_size;
	inverters_left_temperature_igbt_data *temperature_igbt;
	int temperature_igbt_count;
	int temperature_igbt_size;
	inverters_left_temperature_motors_data *temperature_motors;
	int temperature_motors_count;
	int temperature_motors_size;
} inverters_left_data;

typedef struct {
	inverters_right_data right;
	inverters_left_data left;
} inverters_data;

typedef struct {
	double max;
	double min;
	double average;
} bms_hv_temperature_value_data;

typedef struct {
	long timestamp;
	bms_hv_temperature_value_data value;
} bms_hv_temperature_data;

typedef struct {
	double max;
	double min;
	double total;
} bms_hv_voltage_value_data;

typedef struct {
	long timestamp;
	bms_hv_voltage_value_data value;
} bms_hv_voltage_data;

typedef struct {
	double current;
	double pow;
} bms_hv_current_value_data;

typedef struct {
	long timestamp;
	bms_hv_current_value_data value;
} bms_hv_current_data;

typedef struct {
	int fault_id;
	int fault_index;
} bms_hv_errors_value_data;

typedef struct {
	long timestamp;
	bms_hv_errors_value_data value;
} bms_hv_errors_data;

typedef struct {
	int fault_id;
	int fault_index;
} bms_hv_warnings_value_data;

typedef struct {
	long timestamp;
	bms_hv_warnings_value_data value;
} bms_hv_warnings_data;

typedef struct {
	bms_hv_temperature_data *temperature;
	int temperature_count;
	int temperature_size;
	bms_hv_voltage_data *voltage;
	int voltage_count;
	int voltage_size;
	bms_hv_current_data *current;
	int current_count;
	int current_size;
	bms_hv_errors_data *errors;
	int errors_count;
	int errors_size;
	bms_hv_warnings_data *warnings;
	int warnings_count;
	int warnings_size;
} bms_hv_data;

typedef struct {
	double voltage;
	double temperature;
} bms_lv_values_value_data;

typedef struct {
	long timestamp;
	bms_lv_values_value_data value;
} bms_lv_values_data;

typedef struct {
	long timestamp;
	int value;
} bms_lv_errors_data;

typedef struct {
	bms_lv_values_data *values;
	int values_count;
	int values_size;
	bms_lv_errors_data *errors;
	int errors_count;
	int errors_size;
} bms_lv_data;

typedef struct {
	double latitude_GGA_safe;
	double longitude_GGA_safe;
	double latitude_GGA;
	double longitude_GGA;
	double altitude_GGA;
	char* ns_indicator_GGA;
	char* ew_indicator_GGA;
	char* utc_time_GGA;
	double latitude_GLL;
	double longitude_GLL;
	char* ns_indicator_GLL;
	char* ew_indicator_GLL;
	char* utc_time_GLL;
	double ground_speed_knots_VTG;
	double ground_speed_human_VTG;
	double latitude_RMC;
	double longitude_RMC;
	char* ns_indicator_RMC;
	char* ew_indicator_RMC;
	char* utc_time_RMC;
	char* date_RMC;
	double ground_speed_knots_RMC;
} gps_new_value_data;

typedef struct {
	long timestamp;
	gps_new_value_data value;
} gps_new_data;

typedef struct {
	double latitude_m;
	int latitude_o;
	double longitude_m;
	int longitude_o;
	double speed;
	double altitude;
} gps_old_location_value_data;

typedef struct {
	long timestamp;
	gps_old_location_value_data value;
} gps_old_location_data;

typedef struct {
	int hours;
	int minutes;
	int seconds;
} gps_old_time_value_data;

typedef struct {
	long timestamp;
	gps_old_time_value_data value;
} gps_old_time_data;

typedef struct {
	long timestamp;
	int value;
} gps_old_true_track_mode_data;

typedef struct {
	gps_old_location_data *location;
	int location_count;
	int location_size;
	gps_old_time_data *time;
	int time_count;
	int time_size;
	gps_old_true_track_mode_data *true_track_mode;
	int true_track_mode_count;
	int true_track_mode_size;
} gps_old_data;

typedef struct {
	gps_new_data *new;
	int new_count;
	int new_size;
	gps_old_data old;
} gps_data;

typedef struct {
	double x;
	double y;
	double z;
	double scale;
} imu_gyro_value_data;

typedef struct {
	long timestamp;
	imu_gyro_value_data value;
} imu_gyro_data;

typedef struct {
	double x;
	double y;
	double z;
	double scale;
} imu_accel_value_data;

typedef struct {
	long timestamp;
	imu_accel_value_data value;
} imu_accel_data;

typedef struct {
	double speed;
	double speedms;
	int error_flag;
} front_wheels_encoders_right_value_data;

typedef struct {
	long timestamp;
	front_wheels_encoders_right_value_data value;
} front_wheels_encoders_right_data;

typedef struct {
	double speed;
	double speedms;
	int error_flag;
} front_wheels_encoders_left_value_data;

typedef struct {
	long timestamp;
	front_wheels_encoders_left_value_data value;
} front_wheels_encoders_left_data;

typedef struct {
	front_wheels_encoders_right_data *right;
	int right_count;
	int right_size;
	front_wheels_encoders_left_data *left;
	int left_count;
	int left_size;
} front_wheels_encoders_data;

typedef struct {
	double meters;
	double rotations;
	double angle;
	double clock_period;
} distance_value_data;

typedef struct {
	long timestamp;
	distance_value_data value;
} distance_data;

typedef struct {
	long timestamp;
	int value;
} throttle_data;

typedef struct {
	int is_breaking;
	int pressure_front;
	int pressure_back;
} brake_value_data;

typedef struct {
	long timestamp;
	brake_value_data value;
} brake_data;

typedef struct {
	long timestamp;
	double value;
} steering_wheel_encoder_data;

typedef struct {
	int control;
	int cooling;
	int map;
} steering_wheel_gears_value_data;

typedef struct {
	long timestamp;
	steering_wheel_gears_value_data value;
} steering_wheel_gears_data;

typedef struct {
	steering_wheel_encoder_data *encoder;
	int encoder_count;
	int encoder_size;
	steering_wheel_gears_data *gears;
	int gears_count;
	int gears_size;
	int marker;
} steering_wheel_data;

typedef struct {
	int id;
	long timestamp;
	char* sessionName;
	inverters_data inverters;
	bms_hv_data bms_hv;
	bms_lv_data bms_lv;
	gps_data gps;
	imu_gyro_data *imu_gyro;
	int imu_gyro_count;
	int imu_gyro_size;
	imu_accel_data *imu_accel;
	int imu_accel_count;
	int imu_accel_size;
	front_wheels_encoders_data front_wheels_encoders;
	distance_data *distance;
	int distance_count;
	int distance_size;
	throttle_data *throttle;
	int throttle_count;
	int throttle_size;
	brake_data *brake;
	int brake_count;
	int brake_size;
	steering_wheel_data steering_wheel;
} data_t;


/**
 * The enum type that describes a result for a gather-structure operation
*/
typedef enum { 
    GATHER_IDLE, 
    GATHER_ENABLE, 
    GATHER_KEEP, 
    GATHER_ERROR 
} gather_code;

/* FUNCTIONS */

/**
 * Creates and returns an empty data structure, that will contain all the messages gathered in a certain amount of 
 * time and translated to a bson document.
 * @return The empty data structure
*/
data_t* structureCreate();
/**
 * Converts a data structure to a bson document
 * @param document The document to translate in a bson document
 * @param bson_document The pointer where the created bson document will be stored
*/
void structureToBson(data_t *document, bson_t **bson_document);
/**
 * Deallocates the passed data structure
 * @param document The data structure to deallocate 
*/
void structureDelete(data_t *document);
/**
 * Starts two threads, one that listens to the canbus and another that listens for the gps. Both threads parse the messages and fill the data structure. 
 * They will be stopped and destroyed after a certain amount of time.
 * @param document The data structure variable to fill with the data obtained parsing the can and gps messages
 * @result the gather code resulted from the function. GATHER_IDLE and GATHER ENABLED if a steering wheel message to enable or 
 * disable the telemetry was received. GATHER_KEEP if it was succesfull and no message to change he telemetry status was received 
 * and GATHER_ERROR if there was an error.
*/
gather_code gatherStructure(data_t* document);
void resetStructureId();

#endif