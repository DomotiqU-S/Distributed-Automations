//
// Created by talgarr on 13/02/24.
//

#ifndef DISTRIBUTED_AUTOMATIONS_TESTCONDITION_H
#define DISTRIBUTED_AUTOMATIONS_TESTCONDITION_H

#include <iostream>
#include "../DistributedAutomation/Automation/Condition/Condition.hpp"
#include "../DistributedAutomation/Automation/Condition/ConditionStringState.hpp"
#include "../DistributedAutomation/Automation/Condition/ConditionNumericState.hpp"
#include "../DistributedAutomation/Automation/Condition/ConditionTrigger.hpp"
#include "../DistributedAutomation/Automation/Condition/ConditionTime.hpp"
#include "../DistributedAutomation/Automation/Condition/ConditionLogical.hpp"


using namespace std;

class TestCondition {
public:
    TestCondition();
    ~TestCondition() = default;

private:
    string alias_good = "alias_good";
    string alias_bad = "alias_bad";
    string attribute_string_good = "attribute_string_good";
    string attribute_numeric_good = "attribute_numeric_good";
    string attribute_bad = "attribute_bad";
    time_t for_long = 1;
    time_t for_short = 0;
    string value_string_good = "value_good";
    string value_string_bad = "value_bad";
    float value_numeric_good = 1.0;
    float value_numeric_bad = -1.0;

    bool TestConditionStringState();
    bool TestConditionNumericState();
    bool TestConditionTrigger();
    bool TestConditionTime();
    bool TestConditionLogical();


    void Clean();
};


#endif //DISTRIBUTED_AUTOMATIONS_TESTCONDITION_H
