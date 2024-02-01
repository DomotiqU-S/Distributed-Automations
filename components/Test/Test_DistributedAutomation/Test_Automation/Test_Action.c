//
// Created by talgarr on 27/01/24.
//

#include "Test_Action.h"

void Test_Action_Run() {
    printf("----------------------------------------\n");
    printf("Test_Action_Run\n");
    printf("Test_ActionCallService_Init: %s\n", Test_ActionCallService_Init() ? "passed" : "failed");
    printf("Test_ActionDelay_Init: %s\n", Test_ActionDelay_Init() ? "passed" : "failed");
    printf("----------------------------------------\n");
}


bool Test_ActionCallService_Init() {
    char *alias = "alias";
    char *service = "service";
    cJSON *service_data = cJSON_CreateObject();
    cJSON_AddStringToObject(service_data, "key", "value");

    Action action;
    ActionCallService_Init(&action, alias, service, service_data);
    cJSON *json = Action_GetJSON(&action);
    char *string = cJSON_PrintUnformatted(json);

    Action action_2;
    Action_InitFromJSON(&action_2, json);
    cJSON *json_2 = Action_GetJSON(&action_2);
    char *string_2 = cJSON_PrintUnformatted(json_2);

    cJSON *expected_json = cJSON_CreateObject();
    cJSON_AddStringToObject(expected_json, ALIAS, alias);
    cJSON_AddNumberToObject(expected_json, ACTION_TYPE, ActionCallService);
    cJSON_AddStringToObject(expected_json, SERVICE, service);
    cJSON_AddItemToObject(expected_json, SERVICE_DATA, service_data);
    char *expected_string = cJSON_PrintUnformatted(expected_json);

    bool result = (strcmp(string, expected_string) == 0) && (strcmp(string_2, expected_string) == 0);
    return result;
}


bool Test_ActionDelay_Init() {
    char *alias = "alias";
    char *delay = "delay";

    Action action;
    ActionDelay_Init(&action, alias, delay);
    cJSON *json = Action_GetJSON(&action);
    char *string = cJSON_PrintUnformatted(json);

    Action action_2;
    Action_InitFromJSON(&action_2, json);
    cJSON *json_2 = Action_GetJSON(&action_2);
    char *string_2 = cJSON_PrintUnformatted(json_2);

    cJSON *expected_json = cJSON_CreateObject();
    cJSON_AddStringToObject(expected_json, ALIAS, alias);
    cJSON_AddNumberToObject(expected_json, ACTION_TYPE, ActionDelay);
    cJSON_AddStringToObject(expected_json, DELAY, delay);

    char *expected_string = cJSON_PrintUnformatted(expected_json);

    bool result = (strcmp(string, expected_string) == 0) && (strcmp(string_2, expected_string) == 0);
    return result;
}