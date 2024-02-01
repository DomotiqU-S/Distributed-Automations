//
// Created by talgarr on 29/01/24.
//

#ifndef DISTRIBUTED_SERVER_TEST_CONDITION_H
#define DISTRIBUTED_SERVER_TEST_CONDITION_H

#include "../../../DistributedAutomation/Automation/Condition.h"
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

void Test_Condition_Run();

bool Test_ConditionLogical_Init();
bool Test_ConditionNumericState_Init();
bool Test_ConditionState_Init();
bool Test_ConditionTime_Init();
bool Test_ConditionTrigger_Init();

#endif //DISTRIBUTED_SERVER_TEST_CONDITION_H
