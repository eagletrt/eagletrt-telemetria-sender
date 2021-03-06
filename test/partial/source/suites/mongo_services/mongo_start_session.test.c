#include "../../../../../services/mongo_service/mongo_service.h"
#include "../../../../../state_machine/state_machine_condition.h"


condition_t condition;

/*
    1 host
    2 port
    3 db
    4 collection
    5 pilot
    6 race
    7 model_version
*/
int main(int argc, char *argv[]) {
    condition.session.pilots = (char **)malloc(1 * sizeof(char *));
    condition.session.races = (char **)malloc(1 * sizeof(char *));
    condition.session.pilots[0] = (char *)malloc((strlen(argv[5]) + 1) * sizeof(char));
    condition.session.races[0] = (char *)malloc((strlen(argv[6]) + 1) * sizeof(char));

    strcpy(condition.session.pilots[0], argv[5]);
    strcpy(condition.session.races[0], argv[6]);

    condition.session.pilots_count = 1;
    condition.session.selected_pilot = 0;
    condition.session.races_count = 1;
    condition.session.selected_race = 0;

    condition.structure.model_version = strdup(argv[7]);

    condition.mongodb.host = (char *)malloc((strlen(argv[1]) + 1) * sizeof(char));
    condition.mongodb.db = (char *)malloc((strlen(argv[3]) + 1) * sizeof(char));
    condition.mongodb.collection = (char *)malloc((strlen(argv[4]) + 1) * sizeof(char));

    strcpy(condition.mongodb.host, argv[1]);
    condition.mongodb.port = atoi(argv[2]);
    strcpy(condition.mongodb.db, argv[3]);
    strcpy(condition.mongodb.collection, argv[4]);

    mongoSetup();
    int res = mongoStartSession();
    return res;
}