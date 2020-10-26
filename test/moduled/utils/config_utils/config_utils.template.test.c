#include "config_utils.h"

/* INTERNAL FUNCTIONS SIGNATURES AND CONSTANTS */

static const int MAX_TOKENS_COUNT = 100;
static int getJsonString(FILE *config_file, char **json_string);
static int getJsonTokens(const char* json_string, int json_length, jsmntok_t** json_tokens);
static char* extractString(jsmntok_t token, const char *json_string);
static char* getStringValue(const jsmntok_t *json_tokens, const char *json_string, int *i);
static int getIntValue(const jsmntok_t *json_tokens, const char *json_string, int *i);
static char** getStringArrayValue(const jsmntok_t *json_tokens, const char *json_string, int *size, int *i);
static int* getIntArrayValue(const jsmntok_t *json_tokens, const char *json_string, int *size, int *i);
static double* getDoubleArrayValue(const jsmntok_t *json_tokens, const char *json_string, int *size, int *i);
static void parseMqttObject(const jsmntok_t *json_tokens, const char *json_string, config_t *config, int *i);
static void parseMongodbObject(const jsmntok_t *json_tokens, const char *json_string, config_t *config, int *i);
static void parseJsonTokens(const jsmntok_t *json_tokens, int tokens_length, const char *json_string, config_t *config);

/* EXPORTED FUNCTIONS */

config_t* newConfig() {
    config_t *config = (config_t*) malloc(sizeof(config_t));
    
    // {{GENERATE_CONFIG_ALLOCATOR}}

    return config;
}

void parseConfigFile(const char* path, config_t **config) {
    FILE *config_file = fopen(path, "r");

    if (config_file == NULL) {
        *config = NULL;
    }
    else {
        char *json_string;
        jsmntok_t *json_tokens;
        int json_length, tokens_length;
        json_length = getJsonString(config_file, &json_string);
        fclose(config_file);
        tokens_length = getJsonTokens(json_string, json_length, &json_tokens);
        parseJsonTokens(json_tokens, tokens_length, json_string, *config);
    }
}

void deleteConfig(config_t *config) {
    // {{GENERATE_CONFIG_DEALLOCATOR}}
}

void printConfig(const config_t* config) {
    // {{GENERATE_CONFIG_PRINT}}
}

/* INTERNAL FUNCTIONS DEFINITIONS */

static int getJsonString(FILE *config_file, char **json_string) {
    char* line;
    size_t lineLength = 0;
    int json_length = 0;

    getline(&line, &lineLength, config_file);
    json_length += lineLength;
    *json_string = (char*) malloc(sizeof(char) * json_length);
	strcpy(*json_string, line);

    while (getline(&line, &lineLength, config_file) != -1) {       	
		json_length += lineLength;
		*json_string = (char*) realloc(*json_string, sizeof(char) * json_length);
		strcat(*json_string, line);
    }

    return json_length;
}

static int getJsonTokens(const char* json_string, int json_length, jsmntok_t** json_tokens) {
    jsmn_parser parser;
    jsmn_init(&parser);
    *json_tokens = (jsmntok_t*) malloc(sizeof(jsmntok_t) * MAX_TOKENS_COUNT);
    int tokens_length = jsmn_parse(&parser, json_string, json_length, *json_tokens, MAX_TOKENS_COUNT);
    return tokens_length;
}

static char* extractString(jsmntok_t token, const char *json_string) {
    unsigned int length = token.end - token.start;
    char* key = malloc(sizeof(char) * (length + 1));
	memcpy(key, &json_string[token.start], length);
	key[length] = '\0';
    return key;
}

static char* getStringValue(const jsmntok_t *json_tokens, const char *json_string, int *i) {
    ++(*i);
    const jsmntok_t token = json_tokens[*i];
    return extractString(token, json_string);
}

static int getIntValue(const jsmntok_t *json_tokens, const char *json_string, int *i) {
    ++(*i);
    const jsmntok_t token = json_tokens[*i];
    return atoi(extractString(token, json_string));
}

static double getDoubleValue(const jsmntok_t *json_tokens, const char *json_string, int *i) {
    ++(*i);
    const jsmntok_t token = json_tokens[*i];
    return atof(extractString(token, json_string));
}

static char** getStringArrayValue(const jsmntok_t *json_tokens, const char *json_string, int *size, int *i) {
    char **string_array;

    ++(*i);
    *size = json_tokens[*i].size;
    string_array = (char**) malloc(sizeof(char*) * *size);

    for (int j = 0; j < *size; ++j) {
        ++(*i);
        char* child = extractString(json_tokens[*i], json_string);
        string_array[j] = child;
    }

    return string_array;
}

static int* getIntArrayValue(const jsmntok_t *json_tokens, const char *json_string, int *size, int *i) {
    int *int_array;

    ++(*i);
    *size = json_tokens[*i].size;
    int_array = (int*) malloc(sizeof(int) * *size);

    for (int j = 0; j < *size; ++j) {
        ++(*i);
        char* child = extractString(json_tokens[*i], json_string);
        int_array[j] = atoi(child);
    }

    return int_array;
}

static double* getDoubleArrayValue(const jsmntok_t *json_tokens, const char *json_string, int *size, int *i) {
    double *double_array;

    ++(*i);
    *size = json_tokens[*i].size;
    double_array = (double*) malloc(sizeof(double) * *size);

    for (int j = 0; j < *size; ++j) {
        ++(*i);
        char* child = extractString(json_tokens[*i], json_string);
        double_array[j] = atof(child);
    }

    return double_array;
}

// {{GENERATE_CONFIG_PARSER}}