//
// Created by talgarr on 27/01/24.
//

#ifndef DISTRIBUTED_SERVER_TEST_ACTION_H
#define DISTRIBUTED_SERVER_TEST_ACTION_H

#include "../../../DistributedAutomation/Automation/Action.h"
#include "../../../DistributedAutomation/Automation/AutomationConstant.h"
#include <stdbool.h>
#include <stdio.h>
#include "string.h"

void Test_Action_Run();

bool Test_ActionCallService_Init();
bool Test_ActionDelay_Init();

#endif //DISTRIBUTED_SERVER_TEST_ACTION_H
