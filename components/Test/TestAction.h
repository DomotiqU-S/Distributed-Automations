//
// Created by talgarr on 13/02/24.
//

#ifndef DISTRIBUTED_AUTOMATIONS_TESTACTION_H
#define DISTRIBUTED_AUTOMATIONS_TESTACTION_H

#include <iostream>
#include <condition_variable>
#include "../DistributedAutomation/Automation/Action/ActionDelay.hpp"
#include "../DistributedAutomation/Automation/Action/ActionCallService.hpp"
#include "../DistributedAutomation/DistributedDevice.hpp"

using namespace std;

class TestAction {
public:
    TestAction();
    ~TestAction() = default;

private:
    string alias_good = "alias_good";
    string attribute_string_good = "attribute_string_good";
    time_t for_long = 1;
    string value_string_good = "value_good";
    string value_string_bad = "value_bad";

    bool TestActionDelay();
    bool TestActionCallService();

};


#endif //DISTRIBUTED_AUTOMATIONS_TESTACTION_H
