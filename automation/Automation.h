//
// Created by talgarr on 08/01/24.
//

#ifndef SERVER_S3_AUTOMATION_H
#define SERVER_S3_AUTOMATION_H

#include "../library/cJSON.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"

typedef struct Automation
{
    char* alias;
    char* description;
    cJSON *triggers;
    cJSON *conditions;
    cJSON *actions;
} Automation;

void Automation_Init(Automation *this, char *alias, char *description, cJSON *triggers, cJSON *conditions, cJSON *actions);
void Automation_InitFromJSON(Automation *this, cJSON *json);
cJSON *Automation_GetJSON(Automation *this);
void Automation_Free(Automation *this);

#endif // SERVER_S3_AUTOMATION_H
