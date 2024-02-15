//
// Created by talgarr on 13/02/24.
//

#include "Test.hpp"

Test::Test() {
    DistributedDevice::Instance().TriggerIO("numeric_attribute", "12");
    DistributedDevice::Instance().TriggerIO("state_attribute", "on");

    cout << "========= Test ========="  << endl;
//    TestTrigger trigger = TestTrigger();
//    TestCondition condition = TestCondition();
    TestAction action = TestAction();
//    TestAutomation automation = TestAutomation();
    cout << "========= Test ========="  << endl;
}

