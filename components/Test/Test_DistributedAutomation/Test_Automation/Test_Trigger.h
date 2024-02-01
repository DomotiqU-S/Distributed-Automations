//
// Created by talgarr on 27/01/24.
//

#ifndef DISTRIBUTED_SERVER_TEST_TRIGGER_H
#define DISTRIBUTED_SERVER_TEST_TRIGGER_H

#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include "../../../DistributedAutomation/Automation/Trigger.h"

void Test_Trigger_Run();
bool Test_TriggerNumericState_Init();
bool Test_TriggerState_Init();
bool Test_TriggerTime_Init();
bool Test_TriggerTimePattern_Init();


#endif //DISTRIBUTED_SERVER_TEST_TRIGGER_H
