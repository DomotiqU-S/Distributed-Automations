//
// Created by talgarr on 25/01/24.
//

#include "Trigger.h"


// Trigger
void Trigger_Init(Trigger *this, char *alias, enum TriggerType platform) {
    this->alias = alias;
    this->platform = platform;
}

void Trigger_Free(Trigger *this)
{
    cJSON_Delete(this->specific_params);
}

void Trigger_InitFromJSON(Trigger *this, cJSON *json) {
    char *alias = cJSON_GetObjectItem(json, ALIAS)->valuestring;
    this->alias = malloc(sizeof(char) * strlen(alias) + 1);
    strcpy(this->alias, alias);

    cJSON_DeleteItemFromObject(json, ALIAS);
    this->platform = cJSON_GetObjectItem(json, PLATFORM)->valueint;
    cJSON_DeleteItemFromObject(json, PLATFORM);
    this->specific_params = json;
}

cJSON *Trigger_GetJSON(Trigger *this) {
    cJSON *trigger_json = cJSON_CreateObject();
    cJSON_AddStringToObject(trigger_json, ALIAS, this->alias);
    cJSON_AddNumberToObject(trigger_json, PLATFORM, this->platform);
    switch (this->platform) {
        case TriggerNumericState:
            return TriggerNumericState_GetJSON(this, trigger_json);
        case TriggerState:
            return TriggerState_GetJSON(this, trigger_json);
        case TriggerTime:
            return TriggerTime_GetJSON(this, trigger_json);
        case TriggerTimePattern:
            return TriggerTimePattern_GetJSON(this, trigger_json);
        default:
            return trigger_json;
    }
}


// TriggerNumericState
void
TriggerNumericState_Init(Trigger *this, char *alias, char *attribute, char *value_template, double above, double below,
                         time_t for_, cvector_vector_type(char*)entity_id) {
    Trigger_Init(this, alias, TriggerNumericState);
    this->specific_params = cJSON_CreateObject();

    VectorUtils_AddCvector2Cjson(entity_id, this->specific_params, ENTITY_ID);
    cJSON_AddItemToObject(this->specific_params, ATTRIBUTE, cJSON_CreateString(attribute));
    cJSON_AddItemToObject(this->specific_params, VALUE_TEMPLATE, cJSON_CreateString(value_template));
    cJSON_AddNumberToObject(this->specific_params, ABOVE, above);
    cJSON_AddNumberToObject(this->specific_params, BELOW, below);
    cJSON_AddNumberToObject(this->specific_params, FOR, for_);
}

cJSON *TriggerNumericState_GetJSON(Trigger *this, cJSON *base) {
    cJSON_AddStringToObject(base, ATTRIBUTE, TriggerNumericState_GetAttribute(this));
    cJSON_AddStringToObject(base, VALUE_TEMPLATE, TriggerNumericState_GetValueTemplate(this));
    cJSON_AddNumberToObject(base, ABOVE, TriggerNumericState_GetAbove(this));
    cJSON_AddNumberToObject(base, BELOW, TriggerNumericState_GetBelow(this));
    cJSON_AddNumberToObject(base, FOR, TriggerNumericState_GetFor(this));
    VectorUtils_AddCvector2Cjson(TriggerState_GetEntityID(this), base, ENTITY_ID);
    return base;
}


char *TriggerNumericState_GetValueTemplate(Trigger *this) {
    return cJSON_GetObjectItem(this->specific_params, VALUE_TEMPLATE)->valuestring;
}

double TriggerNumericState_GetAbove(Trigger *this) {
    return cJSON_GetObjectItem(this->specific_params, ABOVE)->valuedouble;
}

double TriggerNumericState_GetBelow(Trigger *this) {
    return cJSON_GetObjectItem(this->specific_params, BELOW)->valuedouble;
}

time_t TriggerNumericState_GetFor(Trigger *this) {
    return (time_t) cJSON_GetNumberValue(cJSON_GetObjectItem(this->specific_params, FOR));
}

char *TriggerNumericState_GetAttribute(Trigger *this) {
    return cJSON_GetObjectItem(this->specific_params, ATTRIBUTE)->valuestring;
}

// TriggerState
void TriggerState_Init(Trigger *this, char *alias, char **from, char **to, time_t for_, char **entity_id) {
    Trigger_Init(this, alias, TriggerState);
    this->specific_params = cJSON_CreateObject();
    VectorUtils_AddCvector2Cjson(to, this->specific_params, TO);
    VectorUtils_AddCvector2Cjson(from, this->specific_params, FROM);
    VectorUtils_AddCvector2Cjson(entity_id, this->specific_params, ENTITY_ID);
    cJSON_AddNumberToObject(this->specific_params, FOR, for_);
}


cJSON *TriggerState_GetJSON(Trigger *this, cJSON *base) {
    cvector_vector_type(char *)to = TriggerState_GetTo(this);
    VectorUtils_AddCvector2Cjson(to, base, TO);
    cvector_free(to);

    cvector_vector_type(char *)from = TriggerState_GetFrom(this);
    VectorUtils_AddCvector2Cjson(from, base, FROM);
    cvector_free(from);

    cvector_vector_type(char *)entity_id = TriggerState_GetEntityID(this);
    VectorUtils_AddCvector2Cjson(entity_id, base, ENTITY_ID);
    cvector_free(entity_id);

    cJSON_AddNumberToObject(base, FOR, TriggerState_GetFor(this));

    return base;
}

cvector_vector_type(char *)TriggerState_GetFrom(Trigger *this) {
    return VectorUtils_CjsonArray2Cvector(cJSON_GetObjectItem(this->specific_params, FROM));
}

cvector_vector_type(char *)TriggerState_GetTo(Trigger *this) {
    return VectorUtils_CjsonArray2Cvector(cJSON_GetObjectItem(this->specific_params, TO));
}

cvector_vector_type(char *)TriggerState_GetEntityID(Trigger *this) {
    return VectorUtils_CjsonArray2Cvector(cJSON_GetObjectItem(this->specific_params, ENTITY_ID));
}

time_t TriggerState_GetFor(Trigger *this) {
    return cJSON_GetNumberValue(cJSON_GetObjectItem(this->specific_params, FOR));
}

// TriggerTime
void TriggerTime_Init(Trigger *this, char *alias, time_t at) {
    Trigger_Init(this, alias, TriggerTime);
    this->specific_params = cJSON_CreateObject();
    cJSON_AddNumberToObject(this->specific_params, AT, at);
}

cJSON *TriggerTime_GetJSON(Trigger *this, cJSON *base) {
    cJSON_AddNumberToObject(base, AT, TriggerTime_GetAt(this));
    return base;
}

bool TriggerTime_Enable(Trigger *this) {

    return false;
}

time_t TriggerTime_GetAt(Trigger *this) {
    return cJSON_GetNumberValue(cJSON_GetObjectItem(this->specific_params, AT));
}

long TriggerTime_GetNextInterrupt(Trigger *this, time_t now) {
}


// TriggerTimePattern
void TriggerTimePattern_Init(Trigger *this, char *alias, time_t pattern) {
    Trigger_Init(this, alias, TriggerTimePattern);
    this->specific_params = cJSON_CreateObject();
    cJSON_AddNumberToObject(this->specific_params, PATTERN, pattern);
}

cJSON *TriggerTimePattern_GetJSON(Trigger *this, cJSON *base) {
    cJSON_AddNumberToObject(base, PATTERN, TriggerTimePattern_GetPattern(this));
    return base;
}

bool TriggerTimePattern_Enable(Trigger *this) {
    return false;
}

time_t TriggerTimePattern_GetPattern(Trigger *this) {
    return cJSON_GetNumberValue(cJSON_GetObjectItem(this->specific_params, PATTERN));
}

long TriggerTimePattern_GetNextInterrupt(Trigger *this, time_t now){}
