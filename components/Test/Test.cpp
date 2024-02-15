//
// Created by talgarr on 13/02/24.
//

#include "Test.hpp"

Test::Test() {
    DistributedDevice::Instance().TriggerIO("numeric_attribute", "12");
    DistributedDevice::Instance().TriggerIO("state_attribute", "on");

    cout << "========= Test ========="  << endl;
    TestAutomation automation = TestAutomation();
    TestTrigger trigger = TestTrigger();
    TestCondition condition = TestCondition();
    TestAction action = TestAction();
    cout << "========= Test ========="  << endl;
}

