//#include <stdio.h>
//#include "components/Library/cvector.h"
//#include "components/DistributedAutomation/Automation/Action.h"
//#include "components/DistributedAutomation/Automation/Automation.h"
//#include "components/DistributedAutomation/DistributedServer.h"
//#include "components/DistributedAutomation/DistributedDevice.h"
#include "components/Test/Test_DistributedAutomation/Test_Automation/Test_Trigger.h"
#include "components/Test/Test_DistributedAutomation/Test_Automation/Test_Action.h"
#include "components/Test/Test_DistributedAutomation/Test_Automation/Test_Condition.h"


#include <time.h>
#include <sys/time.h>

int main() {


    Test_Trigger_Run();
    Test_Action_Run();
    Test_Condition_Run();

    return 0;

//
//    Trigger trigger = {"You bought bacon"};
//    Condition condition = {"Are you hungry?"};
//    Action action = {"Cook bacon"};
//
//
//    Automation automation = {};
//    Automation_Init(&automation, "alvead", "description");
//    Automation_AddAction(&automation, action);
//    Automation_AddCondition(&automation, condition);
//    Automation_AddTrigger(&automation, trigger);
//
//    cJSON *json = Automation_GetJSON(&automation);
//    char *string = cJSON_Print(json);
//    printf("%s\n", string);
//
//    DistributedDevice *device;
//    DistributedDevice_Init(device);
//    DistributedDevice_AddAutomation(device, automation);
//    DistributedDevice_Free(device);
//
//
//    DistributedServer server;
//    DistributedServer_Init(&server);
//    DistributedServer_Free(&server);

    return 0;
}
