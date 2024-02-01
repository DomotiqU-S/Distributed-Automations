//
// Created by talgarr on 25/01/24.
//

#ifndef DISTRIBUTED_SERVER_ACTION_H
#define DISTRIBUTED_SERVER_ACTION_H

#include "../../Library/cJSON.h"
#include "AutomationConstant.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

enum ActionType {
    ActionCallService = 0,
    ActionDelay = 1
};


// Action
typedef struct Action {
    char *alias;
    enum ActionType action_type;
    cJSON *specific_params;
} Action;
void Action_Do(Action *this);
void Action_Init(Action *this, char *alias, enum ActionType type);
void Action_Free(Action *this);
void Action_InitFromJSON(Action *this, cJSON *json);
cJSON *Action_GetJSON(Action *this);


// ActionCallService

//typedef struct ActionCallService
//{
//    Action action;
//    char *service;
//    cJSON *service_data;
//} ActionCallService;
void ActionCallService_Do(Action *this);
void ActionCallService_Init(Action *this, char *alias, const char *service, cJSON *service_data);
cJSON *ActionCallService_GetJSON(Action *this, cJSON* base);
cJSON *ActionCallService_GetServiceData(Action *this);
char *ActionCallService_GetService(Action *this);


// ActionDelay

//typedef struct ActionDelay
//{
//    Action action;
//    char *delay;
//} ActionDelay;
void ActionDelay_Do(Action *this);
void ActionDelay_Init(Action *this, char *alias, char *delay);
cJSON *ActionDelay_GetJSON(Action *this, cJSON* base);
char *ActionDelay_GetDelay(Action *this);


#endif // DISTRIBUTED_SERVER_ACTION_H
