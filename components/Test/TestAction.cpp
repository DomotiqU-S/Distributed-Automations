//
// Created by talgarr on 13/02/24.
//

#include "TestAction.h"

TestAction::TestAction() {
    cout << "---------- TestAction ---------" << endl;
    cout << "TestActionDelay: " << (TestActionDelay() ? "Pass" : "Fail") << endl;
    cout << "TestActionCallService: " << (TestActionCallService() ? "Pass" : "Fail") << endl;
    cout << "---------- TestAction ---------" << endl;


}

bool TestAction::TestActionDelay() {
    time_t now = time(nullptr);
    ActionDelay action_1(this->alias_good, this->for_long);
    action_1.Do();

    if (time(nullptr) - now < this->for_long) {
        return false;
    }

    return true;
}

bool TestAction::TestActionCallService() {
    DistributedDevice::Instance().TriggerIO(this->attribute_string_good, this->value_string_bad);
    ActionCallService action_1(this->alias_good, this->attribute_string_good, this->value_string_good);
    action_1.Do();
    State s1 = DistributedDevice::Instance().GetAttribute(this->attribute_string_good);
    time_t now = time(nullptr);
    if (now - s1.time > 1 or s1.value != this->value_string_good) {
        return false;
    }

    return true;
}
