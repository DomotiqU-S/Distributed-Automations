//
// Created by talgarr on 08/01/24.
//

#include "Automation.h"

/**
 * @brief Construct a new Automation:: Automation object
 *
 * @param alias Name abd ID of the automation
 * @param description Description of the automation
 * @param triggers Trigger of the automation. Following https://www.home-assistant.io/docs/automation/trigger/, only Numeric State, State, Time, and Time Pattern are supported.
 * @param conditions Condition of the automation. Following https://www.home-assistant.io/docs/automation/condition/, only Logical, Numeric State, State (without Sun based), Time, and Trigger are supported.
 * @param actions Action of the automation. Following https://www.home-assistant.io/docs/automation/action/, only a Device Action is supported as a service.
 */
void Automation_Init(Automation *this, char *alias, char *description)
{
    this->alias = alias;
    this->description = description;
    this->triggers = NULL;
    this->conditions = NULL;
    this->actions = NULL;
}

void Automation_InitFromJSON(Automation *this, cJSON *json)
{
    char *alias = cJSON_GetObjectItem(json, "alias")->valuestring;
    char *description = cJSON_GetObjectItem(json, "description")->valuestring;

    Automation_Init(this, alias, description);

    cJSON *triggers_json = cJSON_GetObjectItem(json, "triggers");

    for (int i; i < cJSON_GetArraySize(triggers_json); i++)
    {
        cJSON *item = cJSON_GetArrayItem(triggers_json, i);
        Trigger trigger;
        Trigger_InitFromJSON(&trigger, item);
        Automation_AddTrigger(this, trigger);
    }

    cJSON *conditions_json = cJSON_GetObjectItem(json, "conditions");
    for (int i; i < cJSON_GetArraySize(conditions_json); i++)
    {
        cJSON *item = cJSON_GetArrayItem(conditions_json, i);
        Condition condition;
        Condition_InitFromJSON(&condition, item);
        Automation_AddCondition(this, condition);
    }

    cJSON *actions_json = cJSON_GetObjectItem(json, "actions");
    for (int i; i < cJSON_GetArraySize(actions_json); i++)
    {
        cJSON *item = cJSON_GetArrayItem(actions_json, i);
        Action action;
        Action_InitFromJSON(&action, item);
        Automation_AddAction(this, action);
    }
}

cJSON *Automation_GetJSON(Automation *this)
{
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "alias", this->alias);
    cJSON_AddStringToObject(json, "description", this->description);

    cJSON_AddArrayToObject(json, "triggers");
    for (int i; i < cvector_size(this->triggers); i++)
        cJSON_AddItemToArray(cJSON_GetObjectItem(json, "triggers"), Trigger_GetJSON(&this->triggers[i]));

    cJSON_AddArrayToObject(json, "conditions");
    for (int i; i < cvector_size(this->conditions); i++)
        cJSON_AddItemToArray(cJSON_GetObjectItem(json, "conditions"), Condition_GetJSON(&this->conditions[i]));

    cJSON_AddArrayToObject(json, "actions");
    for (int i; i < cvector_size(this->actions); i++)
        cJSON_AddItemToArray(cJSON_GetObjectItem(json, "actions"), Action_GetJSON(&this->actions[i]));

    return json;
}

void Automation_Free(Automation *this)
{
    for (int i; i < cvector_size(this->triggers); i++)
        Trigger_Free(&this->triggers[i]);
    cvector_free(this->triggers);

    for (int i; i < cvector_size(this->conditions); i++)
        Condition_Free(&this->conditions[i]);
    cvector_free(this->conditions);

    for (int i; i < cvector_size(this->actions); i++)
        Action_Free(&this->actions[i]);
    cvector_free(this->actions);

    free(this->alias);
    free(this->description);
    free(this);
}

/**
 * @brief Verifies the automation object.
 *
 * This function verifies the automation object by performing necessary checks and validations.
 *
 * @param this The automation object to be verified.
 * @return true if the automation object is valid, false otherwise.
 */
bool Automation_Verify(Automation *this)
{
    for (int i; i < cvector_size(this->conditions); i++)
        if (!Condition_Verify(&this->conditions[i]))
            return false;
    return true;
}

void Automation_AddTrigger(Automation *this, Trigger trigger)
{
    cvector_push_back(this->triggers, trigger);
}

void Automation_AddCondition(Automation *this, Condition condition)
{
    cvector_push_back(this->conditions, condition);
}

void Automation_AddAction(Automation *this, Action action)
{
    cvector_push_back(this->actions, action);
}