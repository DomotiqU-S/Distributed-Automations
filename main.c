#include <stdio.h>
#include <stdlib.h>
#include "automation/Automation.h"
#include "library/cJSON.h"
#include "automation/DistributedServer.h"

int main() {
    Automation automation;
    cJSON *trigger = cJSON_CreateArray();
    cJSON *trigger1 = cJSON_CreateObject();
    cJSON_AddItemToObject(trigger1, "id", cJSON_CreateString("trigger1"));
    cJSON_AddItemReferenceToArray(trigger, trigger1);
    Automation_Init(&automation, "alvead", "description", trigger, NULL, NULL);

    DistributedServer server;
    DistributedServer_Init(&server);
    DistributedServer_AddDevice(&server, "alias");
    DistributedServer_AddDevice(&server, "alias2");
    DistributedServer_AddAutomationToDevice(&server, "alias2", automation);
    DistributedServer_RemoveAutomationFromDevice(&server, "alias2", automation.alias);

    size_t i;
    for (i = 0; i < cvector_size(server.devices_alias); ++i) {
        printf("v[%lu] = %s\n", i, server.devices_alias[i]);
        for (size_t j = 0; j < cvector_size(server.automations_by_devices[i]); ++j) {
            printf("v[%lu][%lu] = %s\n", i, j, server.automations_by_devices[i][j].alias);
        }
    }

    DistributedServer_Free(&server);

    return 0;
}
