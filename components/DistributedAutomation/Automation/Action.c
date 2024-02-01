//
// Created by talgarr on 27/01/24.
//

#include <string.h>
#include "Action.h"

void Action_Init(Action *this, char *alias, enum ActionType type) {
    this->alias = alias;
    this->action_type = type;
}

void Action_Free(Action *this) {
    cJSON_Delete(this->specific_params);
}

cJSON *Action_GetJSON(Action *this) {
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, ALIAS, this->alias);
    cJSON_AddItemToObject(json, ACTION_TYPE, cJSON_CreateNumber(this->action_type));
    switch (this->action_type) {
        case ActionCallService:
            return ActionCallService_GetJSON(this, json);
        case ActionDelay:
            return ActionDelay_GetJSON(this, json);
        default:
            return cJSON_CreateObject();
    }
}

void Action_InitFromJSON(Action *this, cJSON *json) {
    char *alias = cJSON_GetObjectItem(json, ALIAS)->valuestring;
    this->alias = malloc(sizeof(char) * strlen(alias) + 1);
    strcpy(this->alias, alias);
    this->action_type = cJSON_GetObjectItem(json, ACTION_TYPE)->valueint;

    cJSON_DeleteItemFromObject(json, ALIAS);
    cJSON_DeleteItemFromObject(json, ACTION_TYPE);
    this->specific_params = json;
}

void Action_Do(Action *this) {
    switch (this->action_type) {
        case ActionCallService:
            ActionCallService_Do(this);
            break;
        case ActionDelay:
            ActionDelay_Do(this);
            break;
        default:
            break;
    }
}

// ActionCallService
void ActionCallService_Do(Action *this) {
    char *summary = cJSON_Print(Action_GetJSON(this));
    printf("%s\n", summary);
}

void ActionCallService_Init(Action *this, char *alias, const char *service, cJSON *service_data) {
    Action_Init(this, alias, ActionCallService);
    cJSON *specif_param = cJSON_CreateObject();
    cJSON_AddItemToObject(specif_param, SERVICE, cJSON_CreateString(service));
    cJSON_AddItemToObject(specif_param, SERVICE_DATA, service_data);
    this->specific_params = specif_param;
}

cJSON *ActionCallService_GetJSON(Action *this, cJSON* base) {
    cJSON_AddItemToObject(base, SERVICE, cJSON_CreateString(ActionCallService_GetService(this)));
    cJSON_AddItemToObject(base, SERVICE_DATA, ActionCallService_GetServiceData(this));
    return base;
}


cJSON *ActionCallService_GetServiceData(Action *this) {
    return cJSON_GetObjectItem(this->specific_params, SERVICE_DATA);
}

char *ActionCallService_GetService(Action *this) {
    return cJSON_GetObjectItem(this->specific_params, SERVICE)->valuestring;
}


// ActionDelay
void ActionDelay_Do(Action *this) {
    char *summary = cJSON_Print(Action_GetJSON(this));
    printf("%s\n", summary);
}

void ActionDelay_Init(Action *this, char *alias, char *delay) {
    Action_Init(this, alias, ActionDelay);
    cJSON *specif_param = cJSON_CreateObject();
    cJSON_AddStringToObject(specif_param, DELAY, delay);
    this->specific_params = specif_param;
}

char *ActionDelay_GetDelay(Action *this) {
    return cJSON_GetObjectItem(this->specific_params, DELAY)->valuestring;
}

cJSON *ActionDelay_GetJSON(Action *this, cJSON* base) {
    cJSON_AddStringToObject(base, DELAY, ActionDelay_GetDelay(this));
    return base;
}

void ActionDelay_InitFromJSON(Action *this, cJSON *json) {
    char *delay = cJSON_GetObjectItem(json, DELAY)->valuestring;
    ActionDelay_Init(this, this->alias, delay);
}
