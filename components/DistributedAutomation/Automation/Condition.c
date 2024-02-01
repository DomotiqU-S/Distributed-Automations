//
// Created by talgarr on 25/01/24.
//

#include "Condition.h"

// Condition
void Condition_Init(Condition *this, char *alias, enum ConditionType condition_type) {
    this->alias = alias;
    this->condition_type = condition_type;
    this->specific_params = NULL;
}

void Condition_InitFromJSON(Condition *this, cJSON *json) {
    char *alias = cJSON_GetObjectItem(json, ALIAS)->valuestring;
    this->alias = malloc(sizeof(char) * strlen(alias) + 1);
    strcpy(this->alias, alias);

    this->condition_type = cJSON_GetObjectItem(json, CONDITION_TYPE)->valueint;
    cJSON_DeleteItemFromObject(json, ALIAS);
    cJSON_DeleteItemFromObject(json, CONDITION_TYPE);
    this->specific_params = json;
}

void Condition_Free(Condition *this) {
    cJSON_Delete(this->specific_params);
}

cJSON *Condition_GetJSON(Condition *this) {
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, ALIAS, this->alias);
    cJSON_AddNumberToObject(json, CONDITION_TYPE, this->condition_type);
    switch (this->condition_type) {
        case ConditionLogical:
            return ConditionLogical_GetJSON(this, json);
        case ConditionNumericState:
            return ConditionNumericState_GetJSON(this, json);
        case ConditionState:
            return ConditionState_GetJSON(this, json);
        case ConditionTime:
            return ConditionTime_GetJSON(this, json);
        case ConditionTrigger:
            return ConditionTrigger_GetJSON(this, json);
        default:
            return json;

    }
}

bool Condition_Verify(Condition *this) {
    switch (this->condition_type) {
        case ConditionLogical:
            return ConditionLogical_Verify(this);
        case ConditionNumericState:
            return ConditionNumericState_Verify(this);
        case ConditionState:
            return ConditionState_Verify(this);
        case ConditionTime:
            return ConditionTime_Verify(this);
        case ConditionTrigger:
            return ConditionTrigger_Verify(this);
        default:
            return false;
    }
}

// ConditionLogical

void ConditionLogical_Init(Condition *this, char *alias, enum ConditionLogicalType logical, cvector_vector_type(Condition)conditions) {
    Condition_Init(this, alias, ConditionLogical);
    this->specific_params = cJSON_CreateObject();
    cJSON_AddNumberToObject(this->specific_params, LOGICAL, logical);

    cJSON *conditions_json = cJSON_CreateArray();
    cJSON_AddItemToObject(this->specific_params, CONDITIONS, conditions_json);
    for (int i = 0; i < cvector_size(conditions); ++i) {
        cJSON_AddItemToArray(conditions_json, Condition_GetJSON(&conditions[i]));
    }
}

cJSON *ConditionLogical_GetJSON(Condition *this, cJSON *base) {
    cJSON_AddNumberToObject(base, LOGICAL, ConditionLogical_GetLogical(this));
    cJSON_AddItemToObject(base, CONDITIONS, cJSON_GetObjectItem(this->specific_params, CONDITIONS));
    return base;
}

enum ConditionLogicalType ConditionLogical_GetLogical(Condition *this) {
    return cJSON_GetObjectItem(this->specific_params, LOGICAL)->valueint;
}

cvector_vector_type(Condition)ConditionLogical_GetConditions(Condition *this) {
    cJSON *conditions_json = cJSON_GetObjectItem(this->specific_params, CONDITIONS);
    cvector_vector_type(Condition)conditions = NULL;
    for (int i = 0; i < cJSON_GetArraySize(conditions_json); ++i) {
        cJSON *condition_json = cJSON_GetArrayItem(conditions_json, i);
        Condition condition;
        Condition_InitFromJSON(&condition, condition_json);
        cvector_push_back(conditions, condition);
    }
    return conditions;
}

int8_t recursion_depth = 0;
#define MAX_RECURSION_DEPTH 5

bool ConditionLogical_Verify(Condition *this) {
    recursion_depth++;
    bool result = false;
    if (recursion_depth < MAX_RECURSION_DEPTH) {
        switch (ConditionLogical_GetLogical(this)) {
            case and:
                result = ConditionLogical_VerifyAnd(this);
            case or:
                result = ConditionLogical_VerifyOr(this);
            case not:
                result = ConditionLogical_VerifyNot(this);
            default:
                result = false;
        }
    }
    recursion_depth--;
    return result;
}

bool ConditionLogical_VerifyAnd(Condition *this) {
    cvector_vector_type(Condition)conditions = ConditionLogical_GetConditions(this);
    for (int i = 0; i < cvector_size(conditions); ++i) {
        if (!Condition_Verify(&conditions[i])) {
            return false;
        }
    }
    return true;
}

bool ConditionLogical_VerifyOr(Condition *this) {
    cvector_vector_type(Condition)conditions = ConditionLogical_GetConditions(this);
    for (int i = 0; i < cvector_size(conditions); ++i) {
        if (Condition_Verify(&conditions[i])) {
            return true;
        }
    }
    return false;
}

bool ConditionLogical_VerifyNot(Condition *this) {
    cvector_vector_type(Condition)conditions = ConditionLogical_GetConditions(this);
    for (int i = 0; i < cvector_size(conditions); ++i) {
        if (Condition_Verify(&conditions[i])) {
            return false;
        }
    }
    return true;
}

// ConditionNumericState
void ConditionNumericState_Init(Condition *this, char *alias, char *entity_id, char *attribute, char *value_template,
                                double above, double below) {
    Condition_Init(this, alias, ConditionNumericState);
    this->specific_params = cJSON_CreateObject();
    cJSON_AddStringToObject(this->specific_params, ENTITY_ID, entity_id);
    cJSON_AddStringToObject(this->specific_params, ATTRIBUTE, attribute);
    cJSON_AddStringToObject(this->specific_params, VALUE_TEMPLATE, value_template);
    cJSON_AddNumberToObject(this->specific_params, ABOVE, above);
    cJSON_AddNumberToObject(this->specific_params, BELOW, below);
}

cJSON *ConditionNumericState_GetJSON(Condition *this, cJSON *base) {
    cJSON_AddStringToObject(base, ENTITY_ID, ConditionNumericState_GetEntityId(this));
    cJSON_AddStringToObject(base, ATTRIBUTE, ConditionNumericState_GetAttribute(this));
    cJSON_AddStringToObject(base, VALUE_TEMPLATE, ConditionNumericState_GetValueTemplate(this));
    cJSON_AddNumberToObject(base, ABOVE, ConditionNumericState_GetAbove(this));
    cJSON_AddNumberToObject(base, BELOW, ConditionNumericState_GetBelow(this));
    return base;
}

char *ConditionNumericState_GetEntityId(Condition *this) {
    return cJSON_GetObjectItem(this->specific_params, ENTITY_ID)->valuestring;
}

char *ConditionNumericState_GetAttribute(Condition *this) {
    return cJSON_GetObjectItem(this->specific_params, ATTRIBUTE)->valuestring;
}

char *ConditionNumericState_GetValueTemplate(Condition *this) {
    return cJSON_GetObjectItem(this->specific_params, VALUE_TEMPLATE)->valuestring;
}

double ConditionNumericState_GetAbove(Condition *this) {
    return cJSON_GetNumberValue(cJSON_GetObjectItem(this->specific_params, ABOVE));
}

double ConditionNumericState_GetBelow(Condition *this) {
    return cJSON_GetNumberValue(cJSON_GetObjectItem(this->specific_params, BELOW));
}

bool ConditionNumericState_Verify(Condition *this) {
    return false;
}

// ConditionState
void ConditionState_Init(Condition *this, char *alias, char *entity_id, char *attribute, time_t for_, char *state) {
    Condition_Init(this, alias, ConditionState);
    this->specific_params = cJSON_CreateObject();
    cJSON_AddStringToObject(this->specific_params, ENTITY_ID, entity_id);
    cJSON_AddStringToObject(this->specific_params, ATTRIBUTE, attribute);
    cJSON_AddNumberToObject(this->specific_params, FOR, for_);
    cJSON_AddStringToObject(this->specific_params, STATE, state);
}

cJSON *ConditionState_GetJSON(Condition *this, cJSON *base) {
    cJSON_AddStringToObject(base, ENTITY_ID, ConditionState_GetEntityId(this));
    cJSON_AddStringToObject(base, ATTRIBUTE, ConditionState_GetAttribute(this));
    cJSON_AddNumberToObject(base, FOR, ConditionState_GetFor(this));
    cJSON_AddStringToObject(base, STATE, ConditionState_GetState(this));
    return base;
}

char *ConditionState_GetEntityId(Condition *this) {
    return cJSON_GetObjectItem(this->specific_params, ENTITY_ID)->valuestring;
}

char *ConditionState_GetAttribute(Condition *this) {
    return cJSON_GetObjectItem(this->specific_params, ATTRIBUTE)->valuestring;
}

time_t ConditionState_GetFor(Condition *this) {
    return cJSON_GetNumberValue(cJSON_GetObjectItem(this->specific_params, FOR));
}

char *ConditionState_GetState(Condition *this) {
    return cJSON_GetObjectItem(this->specific_params, STATE)->valuestring;
}

bool ConditionState_Verify(Condition *this) {
    return false;
}

// ConditionTime
void ConditionTime_Init(Condition *this, char *alias, time_t after, time_t before, cvector_vector_type(char *)weekday) {
    Condition_Init(this, alias, ConditionTime);
    this->specific_params = cJSON_CreateObject();
    cJSON_AddNumberToObject(this->specific_params, AFTER, after);
    cJSON_AddNumberToObject(this->specific_params, BEFORE, before);
    VectorUtils_AddCvector2Cjson(weekday, this->specific_params, WEEKDAY);
}

cJSON *ConditionTime_GetJSON(Condition *this, cJSON *base) {
    cJSON_AddNumberToObject(base, AFTER, ConditionTime_GetAfter(this));
    cJSON_AddNumberToObject(base, BEFORE, ConditionTime_GetBefore(this));

    cJSON_AddItemToObject(base, WEEKDAY, cJSON_GetObjectItem(this->specific_params, WEEKDAY));

    return base;
}

time_t ConditionTime_GetAfter(Condition *this) {
    return cJSON_GetNumberValue(cJSON_GetObjectItem(this->specific_params, AFTER));
}

time_t ConditionTime_GetBefore(Condition *this) {
    return cJSON_GetNumberValue(cJSON_GetObjectItem(this->specific_params, BEFORE));
}

cvector_vector_type(char *)ConditionTime_GetWeekday(Condition *this) {
    return VectorUtils_CjsonArray2Cvector(cJSON_GetObjectItem(this->specific_params, WEEKDAY));
}

bool ConditionTime_Verify(Condition *this) {
    return false;
}

// ConditionTrigger
void ConditionTrigger_Init(Condition *this, char *alias, char *trigger_alias) {
    Condition_Init(this, alias, ConditionTrigger);
    this->specific_params = cJSON_CreateObject();
    cJSON_AddStringToObject(this->specific_params, ALIAS, alias);
    cJSON_AddStringToObject(this->specific_params, TRIGGER_ALIAS, trigger_alias);
}

cJSON *ConditionTrigger_GetJSON(Condition *this, cJSON *base) {
    cJSON_AddStringToObject(base, TRIGGER_ALIAS, ConditionTrigger_GetTriggerAlias(this));
    return base;
}

char *ConditionTrigger_GetTriggerAlias(Condition *this) {
    return cJSON_GetObjectItem(this->specific_params, TRIGGER_ALIAS)->valuestring;
}

bool ConditionTrigger_Verify(Condition *this) {

    return false;
}