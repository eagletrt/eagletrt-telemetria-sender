#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "./jsmn/jsmn.h"

typedef struct {
 	char* broker_host;
  	int broker_port;
  	char* mqtt_topic;

  	char* mongo_host;
  	int mongo_port;
  	char* mongo_db;

  	int sending_time;
    int status_checker;

	char** pilots;
	int pilots_size;

	char** races;
	int races_size;
} config_t;

extern int verbose;

config_t* config_setup(const char* cfgpath);
int config_quit(config_t* cfg);

#endif