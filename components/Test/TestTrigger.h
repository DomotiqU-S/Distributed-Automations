//
// Created by talgarr on 13/02/24.
//

#ifndef DISTRIBUTED_AUTOMATIONS_TESTTRIGGER_H
#define DISTRIBUTED_AUTOMATIONS_TESTTRIGGER_H

#include <iostream>
#include "../DistributedAutomation/Automation/Trigger/TriggerNumericState.hpp"
#include "../DistributedAutomation/Automation/Trigger/TriggerStringState.hpp"
#include "../DistributedAutomation/Automation/Trigger/TriggerTime.hpp"

using namespace std;

class TestTrigger {
public:
    TestTrigger();
    ~TestTrigger() = default;

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

    condition_variable cv;
    mutex cv_m;

    bool TestTriggerNumericState();
    bool TestTriggerStringState();
    bool TestTriggerTime();

    void WaitFor();
};


#endif //DISTRIBUTED_AUTOMATIONS_TESTTRIGGER_H
