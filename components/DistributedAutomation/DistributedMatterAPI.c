//
// Created by talgarr on 08/01/24.
//

#include "DistributedMatterAPI.h"

char *DistributedMatterAPI_SendMessage(char *alias, char *message) {
    return "OK";
}

bool DistributedMatterAPI_SendAutomation(char *alias, char *message) {
    return true;
}


bool DistributedMatterAPI_GetDevices(cvector_vector_type(char*)alias) {
    cvector_vector_type(char*) devices_alias = NULL;
    cvector_push_back(devices_alias, "device1");
    cvector_push_back(devices_alias, "device2");
    
    // Add element of devices_alias not already in alias
    for (size_t i = 0; i < cvector_size(devices_alias); ++i) {
        for (size_t j = 0; j < cvector_size(alias); ++j) {
            if (strcmp(devices_alias[i], alias[j]) == 0)
                break;
            if (j == cvector_size(alias) - 1)
                cvector_push_back(alias, devices_alias[i]);
        }
    }

    return true;
}


char *DistributedMatterAPI_GetAutomations(char *alias) {
    Automation automation;
    cJSON *trigger = cJSON_CreateArray();
    cJSON *trigger1 = cJSON_CreateObject();
    cJSON_AddItemToObject(trigger1, "id", cJSON_CreateString("trigger1"));
    cJSON_AddItemReferenceToArray(trigger, trigger1);
    Automation_Init(&automation, "bacon", "description");
    return cJSON_PrintUnformatted(Automation_GetJSON(&automation));
}


