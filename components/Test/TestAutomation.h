//
// Created by talgarr on 13/02/24.
//

#ifndef DISTRIBUTED_AUTOMATIONS_TESTAUTOMATION_H
#define DISTRIBUTED_AUTOMATIONS_TESTAUTOMATION_H

#include <iostream>
#include "../DistributedAutomation/Automation/Automation.hpp"

using namespace std;

class TestAutomation {
public:
    TestAutomation();
    ~TestAutomation() = default;

private:
    string alias_good = "alias_good";
    string attribute_string_good = "attribute_string_good";
    string attribute_numeric_good = "attribute_numeric_good";
    string attribute_end_good = "attribute_end_good";
    time_t for_long = 1;
    string value_string_good = "value_good";
    float value_numeric_good = 2;
    string value_string_bad = "value_bad";
    string description = "description";

    condition_variable cv;
    mutex cv_m;

    bool AutomationBasic();
    bool AutomationMultipleTrigger();
    bool AutomationCondition();

    bool AutomationMultipleCondition();

    bool AutomationMultipleAction();

    bool AutomationComplex();
};


#endif //DISTRIBUTED_AUTOMATIONS_TESTAUTOMATION_H
