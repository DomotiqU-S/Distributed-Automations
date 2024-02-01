//
// Created by talgarr on 25/01/24.
//

#ifndef DISTRIBUTED_SERVER_TRIGGER_H
#define DISTRIBUTED_SERVER_TRIGGER_H

#include "../../Library/cJSON.h"
#include "../../Library/cvector.h"
#include <stdlib.h>
#include "time.h"
#include <stdbool.h>
#include "../../Utils/VectorUtils.h"
#include "AutomationConstant.h"

enum TriggerType {
    TriggerNumericState = 0,
    TriggerState = 1,
    TriggerTime = 2,
    TriggerTimePattern = 3
};

// Trigger
// Base class for all triggers
typedef struct Trigger {
    char *alias;
    enum TriggerType platform;
    cJSON *specific_params;
} Trigger;

void Trigger_Init(Trigger *this, char *alias, enum TriggerType platform);
void Trigger_Free(Trigger *this);
void Trigger_InitFromJSON(Trigger *this, cJSON *json);
cJSON *Trigger_GetJSON(Trigger *this);

// TriggerNumericState

//typedef struct TriggerNumericState {
//    Trigger trigger;
//    cvector_vector_type(char *) entity_id;
//    char *attribute;
//    char *value_template;
//    double above;
//    double below;
//    Time for_;
//} TriggerNumericState;
void
TriggerNumericState_Init(Trigger *this, char *alias, char *attribute, char *value_template, double above, double below,
                         time_t for_, cvector_vector_type(char*)entity_id);
cJSON *TriggerNumericState_GetJSON(Trigger *this, cJSON *base);
char *TriggerNumericState_GetValueTemplate(Trigger *this);
double TriggerNumericState_GetAbove(Trigger *this);
double TriggerNumericState_GetBelow(Trigger *this);
time_t TriggerNumericState_GetFor(Trigger *this);
char *TriggerNumericState_GetAttribute(Trigger *this);


// TriggerState

//typedef struct TriggerState {
//    Trigger trigger;
//    cvector_vector_type(char *) entity_id;
//    cvector_vector_type(char *) from;
//    cvector_vector_type(char *) to;
//    Time for_;
//} TriggerState;
void TriggerState_Init(Trigger *this, char *alias, char **from, char **to, time_t for_, char **entity_id);
cJSON *TriggerState_GetJSON(Trigger *this, cJSON *base);
cvector_vector_type(char *)TriggerState_GetFrom(Trigger *this);
cvector_vector_type(char *)TriggerState_GetTo(Trigger *this);
cvector_vector_type(char *)TriggerState_GetEntityID(Trigger *this);
time_t TriggerState_GetFor(Trigger *this);

// TriggerTime

//typedef struct TriggerTime {
//    Trigger trigger;
//    Time at;
//} TriggerTime;
void TriggerTime_Init(Trigger *this, char *alias, time_t at);
cJSON *TriggerTime_GetJSON(Trigger *this, cJSON *base);
bool TriggerTime_Enable(Trigger *this);
time_t TriggerTime_GetAt(Trigger *this);
long TriggerTime_GetNextInterrupt(Trigger *this, time_t now);



// TriggerTimePattern

//typedef struct TriggerTimePattern {
//    Trigger trigger;
//    Time pattern;
//} TriggerTimePattern;
void TriggerTimePattern_Init(Trigger *this, char *alias, time_t pattern);
cJSON *TriggerTimePattern_GetJSON(Trigger *this, cJSON *base);
bool TriggerTimePattern_Enable(Trigger *this);
time_t TriggerTimePattern_GetPattern(Trigger *this);
long TriggerTimePattern_GetNextInterrupt(Trigger *this, time_t now);

#endif // DISTRIBUTED_SERVER_TRIGGER_H
