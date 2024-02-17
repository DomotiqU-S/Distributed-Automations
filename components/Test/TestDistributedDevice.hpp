//
// Created by talgarr on 15/02/24.
//

#ifndef DISTRIBUTED_AUTOMATIONS_TESTDISTRIBUTEDDEVICE_HPP
#define DISTRIBUTED_AUTOMATIONS_TESTDISTRIBUTEDDEVICE_HPP

#include "../DistributedAutomation/DistributedDevice.hpp"

class TestDistributedDevice {
public:
    TestDistributedDevice();
    ~TestDistributedDevice() = default;

private:
    string alias_good = "alias_good";
    string attribute_string_good = "open";
    string attribute_numeric_good = "brightness";
    string attribute_end_good = "color"; //"attribute_end_good";
    time_t for_long = 5;
    string value_string_good = "red";
    float value_numeric_good = 2;
    string value_string_bad = "blue";
    string description = "description";

    bool AutomationPresentationTime();
    bool AutomationPresentationState();
};


#endif //DISTRIBUTED_AUTOMATIONS_TESTDISTRIBUTEDDEVICE_HPP
