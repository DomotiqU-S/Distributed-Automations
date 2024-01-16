//
// Created by talgarr on 08/01/24.
//

#include "MatterAPI.h"

char *MatterAPI_SendMessage(char *alias, char *message)
{
    return "OK";
}

cJSON *MatterAPI_SendMessageJSON(char *alias, char *message)
{
    cJSON *json = cJSON_Parse(message);
    return json;
}