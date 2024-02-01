//
// Created by talgarr on 08/01/24.
//

#ifndef SERVER_S3_AUTOMATION_H
#define SERVER_S3_AUTOMATION_H

#include "../../Library/cJSON.h"
#include "../../Library/cvector.h"

#include "Trigger.h"
#include "Condition.h"
#include "Action.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


typedef struct Automation
{
    char *alias;
    char *description;
    cvector_vector_type(Trigger)triggers;
    cvector_vector_type(Condition)conditions;
    cvector_vector_type(Action)actions;
} Automation;

void Automation_Init(Automation *this, char *alias, char *description);
void Automation_InitFromJSON(Automation *this, cJSON *json);
void Automation_AddTrigger(Automation *this, Trigger trigger);
void Automation_AddCondition(Automation *this, Condition condition);
void Automation_AddAction(Automation *this, Action action);
cJSON *Automation_GetJSON(Automation *this);
void Automation_Free(Automation *this);

bool Automation_Verify(Automation *this);


#endif // SERVER_S3_AUTOMATION_H
