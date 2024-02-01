//
// Created by talgarr on 29/01/24.
//

#include "Test_Condition.h"

void Test_Condition_Run() {
    printf("----------------------------------------\n");
    printf("Test_Condition_Run\n");
    printf("Test_ConditionLogical_Init: %s\n", Test_ConditionLogical_Init() ? "passed" : "failed");
    printf("Test_ConditionNumericState_Init: %s\n", Test_ConditionNumericState_Init() ? "passed" : "failed");
    printf("Test_ConditionState_Init: %s\n", Test_ConditionState_Init() ? "passed" : "failed");
    printf("Test_ConditionTime_Init: %s\n", Test_ConditionTime_Init() ? "passed" : "failed");
    printf("Test_ConditionTrigger_Init: %s\n", Test_ConditionTrigger_Init() ? "passed" : "failed");
    printf("----------------------------------------\n");

}


bool Test_ConditionLogical_Init() {
    char *alias_child_1 = "alias_child_1";
    char *trigger_alias_child_1 = "trigger_alias_child_1";
    Condition condition_child_1;
    ConditionTrigger_Init(&condition_child_1, alias_child_1, trigger_alias_child_1);

    char *alias_child_2 = "alias_child_2";
    char *trigger_alias_child_2 = "trigger_alias_child_2";
    Condition condition_child_2;
    ConditionTrigger_Init(&condition_child_2, alias_child_2, trigger_alias_child_2);

    char* alias = "alias";
    enum ConditionLogicalType logical = and;
    cvector_vector_type(Condition) conditions = NULL;
    cvector_push_back(conditions, condition_child_1);
    cvector_push_back(conditions, condition_child_2);

    Condition condition;
    ConditionLogical_Init(&condition, alias, logical, conditions);
    cJSON *json = Condition_GetJSON(&condition);
    char *string = cJSON_PrintUnformatted(json);

    Condition condition_2;
    Condition_InitFromJSON(&condition_2, json);
    cJSON *json_2 = Condition_GetJSON(&condition_2);
    char *string_2 = cJSON_PrintUnformatted(json_2);

    cJSON *expected_json = cJSON_CreateObject();
    cJSON_AddStringToObject(expected_json, ALIAS, alias);
    cJSON_AddNumberToObject(expected_json, CONDITION_TYPE, ConditionLogical);
    cJSON_AddNumberToObject(expected_json, LOGICAL, logical);
    cJSON *conditions_json = cJSON_CreateArray();
    cJSON_AddItemToObject(expected_json, CONDITIONS, conditions_json);
    cJSON_AddItemToArray(conditions_json, Condition_GetJSON(&condition_child_1));
    cJSON_AddItemToArray(conditions_json, Condition_GetJSON(&condition_child_2));
    char *expected_string = cJSON_PrintUnformatted(expected_json);

    bool result = (strcmp(string, expected_string) == 0) && (strcmp(string_2, expected_string) == 0);

    return result;
}

bool Test_ConditionNumericState_Init() {
    char *alias = "alias";
    char *entity_id = "entity_id";
    char *attribute = "attribute";
    double above_value = 1.0;
    double below_value = 2.0;
    char *value_template = "value_template";


    Condition condition;
    ConditionNumericState_Init(&condition, alias, entity_id, attribute, value_template, above_value, below_value);
    cJSON *json = Condition_GetJSON(&condition);
    char *string = cJSON_PrintUnformatted(json);

    Condition condition_2;
    Condition_InitFromJSON(&condition_2, json);
    cJSON *json_2 = Condition_GetJSON(&condition_2);
    char *string_2 = cJSON_PrintUnformatted(json_2);

    cJSON *expected_json = cJSON_CreateObject();
    cJSON_AddStringToObject(expected_json, ALIAS, alias);
    cJSON_AddNumberToObject(expected_json, CONDITION_TYPE, ConditionNumericState);
    cJSON_AddStringToObject(expected_json, ENTITY_ID, entity_id);
    cJSON_AddStringToObject(expected_json, ATTRIBUTE, attribute);
    cJSON_AddStringToObject(expected_json, VALUE_TEMPLATE, value_template);
    cJSON_AddNumberToObject(expected_json, ABOVE, above_value);
    cJSON_AddNumberToObject(expected_json, BELOW, below_value);
    char *expected_string = cJSON_PrintUnformatted(expected_json);

    bool result = (strcmp(string, expected_string) == 0) && (strcmp(string_2, expected_string) == 0);

    return result;
}

bool Test_ConditionState_Init() {
    char *alias = "alias";
    char *entity_id = "entity_id";
    char *attribute = "attribute";
    time_t now;
    time(&now);
    char *state = "state";


    Condition condition;
    ConditionState_Init(&condition, alias, entity_id, attribute, now, state);
    cJSON *json = Condition_GetJSON(&condition);
    char *string = cJSON_PrintUnformatted(json);

    Condition condition_2;
    Condition_InitFromJSON(&condition_2, json);
    cJSON *json_2 = Condition_GetJSON(&condition_2);
    char *string_2 = cJSON_PrintUnformatted(json_2);

    cJSON *expected_json = cJSON_CreateObject();
    cJSON_AddStringToObject(expected_json, ALIAS, alias);
    cJSON_AddNumberToObject(expected_json, CONDITION_TYPE, ConditionState);
    cJSON_AddStringToObject(expected_json, ENTITY_ID, entity_id);
    cJSON_AddStringToObject(expected_json, ATTRIBUTE, attribute);
    cJSON_AddNumberToObject(expected_json, FOR, now);
    cJSON_AddStringToObject(expected_json, STATE, state);
    char *expected_string = cJSON_PrintUnformatted(expected_json);

    bool result = (strcmp(string, expected_string) == 0) && (strcmp(string_2, expected_string) == 0);

    return result;
}

bool Test_ConditionTime_Init() {
    char *alias = "alias";
    time_t after;
    time(&after);
    time_t before = after + 1000;
    cvector_vector_type(char *) weekdays = NULL;
    cvector_push_back(weekdays, "mon");
    cvector_push_back(weekdays, "tue");
    cvector_push_back(weekdays, "wed");

    Condition condition;
    ConditionTime_Init(&condition, alias, after, before, weekdays);
    cJSON *json = Condition_GetJSON(&condition);
    char *string = cJSON_PrintUnformatted(json);

    Condition condition_2;
    Condition_InitFromJSON(&condition_2, json);
    cJSON *json_2 = Condition_GetJSON(&condition_2);
    char *string_2 = cJSON_PrintUnformatted(json_2);

    cJSON *expected_json = cJSON_CreateObject();
    cJSON_AddStringToObject(expected_json, ALIAS, alias);
    cJSON_AddNumberToObject(expected_json, CONDITION_TYPE, ConditionTime);
    cJSON_AddNumberToObject(expected_json, AFTER, after);
    cJSON_AddNumberToObject(expected_json, BEFORE, before);
    VectorUtils_AddCvector2Cjson(weekdays, expected_json, WEEKDAY);
    char *expected_string = cJSON_PrintUnformatted(expected_json);

    bool result = (strcmp(string, expected_string) == 0) && (strcmp(string_2, expected_string) == 0);

    return result;
}

bool Test_ConditionTrigger_Init() {
    char *alias = "alias";
    char *trigger_alias = "trigger_alias";

    Condition condition;
    ConditionTrigger_Init(&condition, alias, trigger_alias);
    cJSON *json = Condition_GetJSON(&condition);
    char *string = cJSON_PrintUnformatted(json);

    Condition condition_2;
    Condition_InitFromJSON(&condition_2, json);
    cJSON *json_2 = Condition_GetJSON(&condition_2);
    char *string_2 = cJSON_PrintUnformatted(json_2);

    cJSON *expected_json = cJSON_CreateObject();
    cJSON_AddStringToObject(expected_json, ALIAS, alias);
    cJSON_AddNumberToObject(expected_json, CONDITION_TYPE, ConditionTrigger);
    cJSON_AddStringToObject(expected_json, TRIGGER_ALIAS, trigger_alias);
    char *expected_string = cJSON_PrintUnformatted(expected_json);

    bool result = (strcmp(string, expected_string) == 0) && (strcmp(string_2, expected_string) == 0);

    return result;
}
