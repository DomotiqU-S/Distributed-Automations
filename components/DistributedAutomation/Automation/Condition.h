// Created by talgarr on 25/01/24.
//

#ifndef DISTRIBUTED_SERVER_TEST_CONDITION_BAD_H
#define DISTRIBUTED_SERVER_TEST_CONDITION_H

#include "../../Library/cJSON.h"
#include "../../Library/cvector.h"
#include "../../Utils/VectorUtils.h"
#include "AutomationConstant.h"
#include <stdlib.h>
#include <stdbool.h>

enum ConditionType
{
    ConditionLogical,
    ConditionNumericState,
    ConditionState,
    ConditionTime,
    ConditionTrigger
};

enum ConditionLogicalType {
    and = 0,
    or = 1,
    not = 2
};

// Base class for all conditions
typedef struct Condition
{
    char* alias;
    enum ConditionType condition_type;
    cJSON *specific_params;
} Condition;

void Condition_Init(Condition *this, char *alias, enum ConditionType condition_type);
void Condition_InitFromJSON(Condition *this, cJSON *json);
void Condition_Free(Condition *this);
cJSON *Condition_GetJSON(Condition *this);
bool Condition_Verify(Condition *this);

//typedef struct ConditionLogical
//{
//    Condition condition;
//    char *logical;
//    cvector_vector_type(Condition) conditions;
//} ConditionLogical;
void ConditionLogical_Init(Condition *this, char *alias, enum ConditionLogicalType logical, cvector_vector_type(Condition) conditions);
cJSON *ConditionLogical_GetJSON(Condition *this, cJSON* base);
enum ConditionLogicalType ConditionLogical_GetLogical(Condition *this);
cvector_vector_type(Condition) ConditionLogical_GetConditions(Condition *this);
bool ConditionLogical_Verify(Condition *this);
bool ConditionLogical_VerifyAnd(Condition *this);
bool ConditionLogical_VerifyOr(Condition *this);
bool ConditionLogical_VerifyNot(Condition *this);

//typedef struct ConditionNumericState
//{
//    Condition condition;
//    char *entity_id;
//    char *attribute;
//    char *value_template;
//    double above;
//    double below;
//} ConditionNumericState;
void ConditionNumericState_Init(Condition *this, char *alias, char *entity_id, char *attribute, char *value_template, double above, double below);
cJSON *ConditionNumericState_GetJSON(Condition *this, cJSON* base);
char *ConditionNumericState_GetEntityId(Condition *this);
char *ConditionNumericState_GetAttribute(Condition *this);
char *ConditionNumericState_GetValueTemplate(Condition *this);
double ConditionNumericState_GetAbove(Condition *this);
double ConditionNumericState_GetBelow(Condition *this);
bool ConditionNumericState_Verify(Condition *this);

//typedef struct ConditionState
//{
//    Condition condition;
//    char *entity_id;
//    char *attribute;
//    time_t for_;
//    char* state;
//} ConditionState;
void ConditionState_Init(Condition *this, char *alias, char *entity_id, char *attribute, time_t for_, char* state);
cJSON *ConditionState_GetJSON(Condition *this, cJSON* base);
char *ConditionState_GetEntityId(Condition *this);
char *ConditionState_GetAttribute(Condition *this);
time_t ConditionState_GetFor(Condition *this);
char *ConditionState_GetState(Condition *this);
bool ConditionState_Verify(Condition *this);

//typedef struct ConditionTime
//{
//    Condition condition;
//    time_t after;
//    time_t before;
//    cvector_vector_type(char *) weekday;
//} ConditionTime;
void ConditionTime_Init(Condition *this, char *alias, time_t after, time_t before, cvector_vector_type(char *) weekday);
cJSON *ConditionTime_GetJSON(Condition *this, cJSON* base);
time_t ConditionTime_GetAfter(Condition *this);
time_t ConditionTime_GetBefore(Condition *this);
cvector_vector_type(char *) ConditionTime_GetWeekday(Condition *this);
bool ConditionTime_Verify(Condition *this);

//typedef struct ConditionTrigger
//{
//    Condition condition;
//    char * trigger_alias;
//} ConditionTrigger;
void ConditionTrigger_Init(Condition *this, char *alias, char *trigger_alias);
cJSON *ConditionTrigger_GetJSON(Condition *this, cJSON* base);
char *ConditionTrigger_GetTriggerAlias(Condition *this);
bool ConditionTrigger_Verify(Condition *this);

#endif // DISTRIBUTED_SERVER_TEST_CONDITION_BAD_H
