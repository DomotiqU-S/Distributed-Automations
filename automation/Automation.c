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
void Automation_Init(Automation *this, char *alias, char *description, cJSON *triggers, cJSON *conditions, cJSON *actions)
{
    this->alias = alias;
    this->description = description;
    if (triggers == NULL)
        this->triggers = cJSON_CreateArray();
    else
        this->triggers = triggers;

    if (conditions == NULL)
        this->conditions = cJSON_CreateArray();
    else
        this->conditions = conditions;

    if (actions == NULL)
        this->actions = cJSON_CreateArray();
    else
        this->actions = actions;
}

void Automation_InitFromJSON(Automation *this, cJSON *json)
{
    char* alias = cJSON_GetObjectItem(json, "alias")->valuestring;
    char* description = cJSON_GetObjectItem(json, "description")->valuestring;

    cJSON *triggers = cJSON_GetObjectItem(json, "triggers");
    cJSON *conditions = cJSON_GetObjectItem(json, "conditions");
    cJSON *actions = cJSON_GetObjectItem(json, "actions");

    Automation_Init(this, alias, description, triggers, conditions, actions);
}

cJSON *Automation_GetJSON(Automation *this)
{
    cJSON *json = cJSON_CreateObject();
    cJSON_AddStringToObject(json, "alias", this->alias);
    cJSON_AddStringToObject(json, "description", this->description);
    cJSON_AddItemReferenceToObject(json, "triggers", this->triggers);
    cJSON_AddItemReferenceToObject(json, "conditions", this->conditions);
    cJSON_AddItemReferenceToObject(json, "actions", this->actions);
    return json;
}

void Automation_Free(Automation *this){
    if (this->triggers != NULL) {
        cJSON_Delete(this->triggers);
    }
    if (this->conditions != NULL) {
        cJSON_Delete(this->conditions);
    }
    if (this->actions != NULL) {
        cJSON_Delete(this->actions);
    }

}
