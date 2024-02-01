//
// Created by talgarr on 27/01/24.
//

#include "Test_Trigger.h"


void Test_Trigger_Run(){
    printf("----------------------------------------\n");
    printf("Test_Trigger_Run\n");
    printf("Test_TriggerNumericState_Init: %s\n", Test_TriggerNumericState_Init() ? "passed" : "failed");
    printf("Test_TriggerState_Init: %s\n", Test_TriggerState_Init() ? "passed" : "failed");
    printf("Test_TriggerTime_Init: %s\n", Test_TriggerTime_Init() ? "passed" : "failed");
    printf("Test_TriggerTimePattern_Init: %s\n", Test_TriggerTimePattern_Init() ? "passed" : "failed");
    printf("----------------------------------------\n");

}

bool Test_TriggerNumericState_Init(){
    char *alias = "alias";
    char *attribute = "attribute";
    char *value_template = "value_template";
    double above = 1.0;
    double below = 2.0;
    time_t now;
    time(&now);
    char *entity_id1 = "entity_id1";

    Trigger trigger;
    cvector_vector_type(char *) entity_id = NULL;
    cvector_push_back(entity_id, entity_id1);
    TriggerNumericState_Init(&trigger, alias, attribute, value_template, above, below, now, entity_id);
    cJSON *json = Trigger_GetJSON(&trigger);
    char *string = cJSON_PrintUnformatted(json);
    Trigger_Free(&trigger);

    Trigger trigger_2;
    Trigger_InitFromJSON(&trigger_2, json);
    cJSON *json_2 = Trigger_GetJSON(&trigger_2);
    char *string_2 = cJSON_PrintUnformatted(json_2);

    cJSON *expected_json = cJSON_CreateObject();
    cJSON_AddStringToObject(expected_json, ALIAS, alias);
    cJSON_AddNumberToObject(expected_json, PLATFORM, TriggerNumericState);
    cJSON_AddStringToObject(expected_json, ATTRIBUTE, attribute);
    cJSON_AddStringToObject(expected_json, VALUE_TEMPLATE, value_template);
    cJSON_AddNumberToObject(expected_json, ABOVE, above);
    cJSON_AddNumberToObject(expected_json, BELOW, below);
    cJSON_AddNumberToObject(expected_json, FOR, now);
    cJSON_AddItemToObject(expected_json, ENTITY_ID, cJSON_CreateStringArray(entity_id, cvector_size(entity_id)));
    char *expected_string = cJSON_PrintUnformatted(expected_json);

    bool result = (strcmp(string, expected_string) == 0) && (strcmp(string_2, expected_string) == 0);

    cJSON_free(expected_json);
    return result;
}

bool Test_TriggerState_Init(){
    char *from1 = "from1";
    char *to1 = "to1";
    char *alias = "alias";
    time_t now;
    time(&now);
    char *entity_id1 = "entity_id1";

    Trigger trigger;
    cvector_vector_type(char *) from = NULL;
    cvector_push_back(from, from1);
    cvector_vector_type(char *) to = NULL;
    cvector_push_back(to, to1);
    cvector_vector_type(char *) entity_id = NULL;
    cvector_push_back(entity_id, entity_id1);
    TriggerState_Init(&trigger, alias, from, to, now, entity_id);
    cJSON *json = Trigger_GetJSON(&trigger);
    char *string = cJSON_PrintUnformatted(json);
    Trigger_Free(&trigger);

    Trigger trigger_2;
    Trigger_InitFromJSON(&trigger_2, json);
    cJSON *json_2 = Trigger_GetJSON(&trigger_2);
    char *string_2 = cJSON_PrintUnformatted(json_2);

    cJSON *expected_json = cJSON_CreateObject();
    cJSON_AddStringToObject(expected_json, ALIAS, alias);
    cJSON_AddNumberToObject(expected_json, PLATFORM, TriggerState);
    cJSON_AddItemToObject(expected_json, TO, cJSON_CreateStringArray(to, cvector_size(to)));
    cJSON_AddItemToObject(expected_json, FROM, cJSON_CreateStringArray(from, cvector_size(from)));
    cJSON_AddItemToObject(expected_json, ENTITY_ID, cJSON_CreateStringArray(entity_id, cvector_size(entity_id)));
    cJSON_AddNumberToObject(expected_json, FOR, now);
    char *expected_string = cJSON_PrintUnformatted(expected_json);

    bool result = (strcmp(string, expected_string) == 0) && (strcmp(string_2, expected_string) == 0);

    cJSON_free(expected_json);
    return result;
}

bool Test_TriggerTime_Init(){
    char *alias = "alias";
    time_t now;
    time(&now);

    Trigger trigger;
    TriggerTime_Init(&trigger, alias, now);
    cJSON *json = Trigger_GetJSON(&trigger);
    char *string = cJSON_PrintUnformatted(json);
    Trigger_Free(&trigger);

    Trigger trigger_2;
    Trigger_InitFromJSON(&trigger_2, json);
    cJSON *json_2 = Trigger_GetJSON(&trigger_2);
    char *string_2 = cJSON_PrintUnformatted(json_2);

    cJSON *expected_json = cJSON_CreateObject();
    cJSON_AddStringToObject(expected_json, ALIAS, alias);
    cJSON_AddNumberToObject(expected_json, PLATFORM, TriggerTime);
    cJSON_AddNumberToObject(expected_json, AT, now);
    char *expected_string = cJSON_PrintUnformatted(expected_json);

    bool result = (strcmp(string, expected_string) == 0) && (strcmp(string_2, expected_string) == 0);

    cJSON_free(expected_json);
    return result;
}

bool Test_TriggerTimePattern_Init(){
    char *alias = "alias";
    time_t now;
    time(&now);

    Trigger trigger;
    TriggerTimePattern_Init(&trigger, alias, now);
    cJSON *json = Trigger_GetJSON(&trigger);
    char *string = cJSON_PrintUnformatted(json);
    Trigger_Free(&trigger);

    Trigger trigger_2;
    Trigger_InitFromJSON(&trigger_2, json);
    cJSON *json_2 = Trigger_GetJSON(&trigger_2);
    char *string_2 = cJSON_PrintUnformatted(json_2);

    cJSON *expected_json = cJSON_CreateObject();
    cJSON_AddStringToObject(expected_json, ALIAS, alias);
    cJSON_AddNumberToObject(expected_json, PLATFORM, TriggerTimePattern);
    cJSON_AddNumberToObject(expected_json, PATTERN, now);
    char *expected_string = cJSON_PrintUnformatted(expected_json);

    bool result = (strcmp(string, expected_string) == 0) && (strcmp(string_2, expected_string) == 0);

    cJSON_free(expected_json);
    return result;
}

