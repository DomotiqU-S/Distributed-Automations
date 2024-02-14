//
// Created by talgarr on 13/02/24.
//

#include "TestCondition.h"

TestCondition::TestCondition() {
   cout << "---------- TestCondition ----------" << endl;
    cout << "TestConditionStringState: " << (TestConditionStringState() ? "Pass" : "Fail" ) << endl;
    cout << "TestConditionNumericState: " << (TestConditionNumericState() ? "Pass" : "Fail" ) << endl;
    cout << "TestConditionTrigger: " << (TestConditionTrigger() ? "Pass" : "Fail" ) << endl;
    cout << "TestConditionTime: " << (TestConditionTime() ? "Pass" : "Fail" ) << endl;
    cout << "TestConditionLogical: " << (TestConditionLogical() ? "Pass" : "Fail" ) << endl;
    cout << "---------- TestCondition ----------" << endl;
}

bool TestCondition::TestConditionStringState() {
    ConditionStringState condition_1(this->alias_good, this->attribute_string_good, this->for_short, this->value_string_good);

    DistributedDevice::Instance().TriggerIO(this->attribute_string_good, this->value_string_good);
    if (not condition_1.Verify("")){
        return false;
    }

    DistributedDevice::Instance().TriggerIO(this->attribute_string_good, this->value_string_bad);
    if (condition_1.Verify("")){
        return false;
    }

    ConditionStringState condition_2(this->alias_good, this->attribute_string_good, this->for_long, this->value_string_good);
    DistributedDevice::Instance().TriggerIO(this->attribute_string_good, this->value_string_bad);
    DistributedDevice::Instance().TriggerIO(this->attribute_string_good, this->value_string_good);
    if (condition_2.Verify("")){
        return false;
    }

    this_thread::sleep_for(chrono::seconds(this->for_long));
    if (not condition_2.Verify("")){
        return false;
    }
    return true;
}

bool TestCondition::TestConditionNumericState() {
    ConditionNumericState condition_1(this->alias_good, this->attribute_string_good, this->for_short, 0, this->value_numeric_good * 2);

    DistributedDevice::Instance().TriggerIO(this->attribute_string_good, to_string(this->value_numeric_good));
    if (not condition_1.Verify("")){
        return false;
    }

    DistributedDevice::Instance().TriggerIO(this->attribute_string_good, to_string(this->value_numeric_bad));
    if (condition_1.Verify("")){
        return false;
    }

    ConditionNumericState condition_2(this->alias_good, this->attribute_string_good, this->for_long, 0, this->value_numeric_good * 2);
    DistributedDevice::Instance().TriggerIO(this->attribute_string_good, to_string(this->value_numeric_bad));
    DistributedDevice::Instance().TriggerIO(this->attribute_string_good, to_string(this->value_numeric_good));
    if (condition_2.Verify("")){
        return false;
    }

    this_thread::sleep_for(chrono::seconds(this->for_long));
    if (not condition_2.Verify("")){
        return false;
    }
    return true;
}

bool TestCondition::TestConditionTrigger() {

    return false;

}

bool TestCondition::TestConditionTime() {

//    ConditionTime condition_1(this->alias_good, );
//
//    DistributedDevice::Instance().TriggerIO(this->attribute_string_good, to_string(this->value_numeric_good));
//    if (not condition_1.Verify("")){
//        return false;
//    }
//
//    DistributedDevice::Instance().TriggerIO(this->attribute_string_good, to_string(this->value_numeric_bad));
//    if (condition_1.Verify("")){
//        return false;
//    }
//
    return false;

}

bool TestCondition::TestConditionLogical() {
    return false;

}
