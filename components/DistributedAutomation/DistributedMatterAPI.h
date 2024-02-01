//
// Created by talgarr on 08/01/24.
//

#include "../Library/cJSON.h"
#include "../Library/cvector.h"
#include <stdbool.h>
#include "Automation/Automation.h"

char *DistributedMatterAPI_SendMessage(char *alias, char *message);
cJSON *DistributedMatterAPI_SendMessageJSON(char *alias, char *message);
bool DistributedMatterAPI_GetDevices(cvector_vector_type(char*));
char *DistributedMatterAPI_GetAutomations(char *alias);

