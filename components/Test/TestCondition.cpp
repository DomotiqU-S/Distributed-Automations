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
    ConditionTrigger condition(this->alias_good, this->value_string_good);
    if (condition.Verify(this->value_string_bad)){
        return false;
    }

    if (not condition.Verify(this->value_string_good)){
        return false;
    }

    if (condition.Verify("")){
        return false;
    }

    return true;

}

bool TestCondition::TestConditionTime() {
    time_t now = time(nullptr);
    tm after = *localtime(&now);
    time_t then = now + 1;
    tm before = *localtime(&then);

    ConditionTime condition(this->alias_good, after, before, {});

    if (not condition.Verify("")){
        return false;
    }

    this_thread::sleep_for(chrono::seconds (2));
    if (condition.Verify("")){
        return false;
    }


    now = time(nullptr);
    after = *localtime(&now);
    then = now + 1;
    before = *localtime(&then);
    vector<string> weekdays = {"sun", "mon", "tue", "wed", "thu", "fri", "sat"};
    condition = ConditionTime(this->alias_good, after, before, weekdays);

    if (not condition.Verify("")){
        return false;
    }

    this_thread::sleep_for(chrono::seconds (2));
    if (condition.Verify("")){
        return false;
    }


    now = time(nullptr);
    after = *localtime(&now);
    then = now + 1;
    before = *localtime(&then);
    weekdays = {weekdays[after.tm_wday]};

    condition = ConditionTime(this->alias_good, after, before, weekdays);

    if (not condition.Verify("")){
        return false;
    }

    this_thread::sleep_for(chrono::seconds (2));
    if (condition.Verify("")){
        return false;
    }

    return true;

}

bool TestCondition::TestConditionLogical() {
    auto condition_1 = new ConditionTrigger(this->alias_good, this->value_string_good);
    auto condition_2 = new ConditionStringState(this->alias_good, this->attribute_string_good, this->for_short, this->value_string_good);

    // Test AND
    ConditionLogical condition_log_and(this->alias_good, AND, {condition_1, condition_2});

    DistributedDevice::Instance().TriggerIO(this->attribute_string_good, this->value_string_good);
    if (not condition_log_and.Verify(this->value_string_good)){
        return false;
    }

    DistributedDevice::Instance().TriggerIO(this->attribute_string_good, this->value_string_bad);
    if (condition_log_and.Verify(this->value_string_good)){
        return false;
    }

    DistributedDevice::Instance().TriggerIO(this->attribute_string_good, this->value_string_good);
    if (condition_log_and.Verify(this->value_string_bad)){
        return false;
    }

    DistributedDevice::Instance().TriggerIO(this->attribute_string_good, this->value_string_bad);
    if (condition_log_and.Verify(this->value_string_bad)){
        return false;
    }

    // Test OR
    condition_1 = new ConditionTrigger(this->alias_good, this->value_string_good);
    condition_2 = new ConditionStringState(this->alias_good, this->attribute_string_good, this->for_short, this->value_string_good);

    ConditionLogical condition_log_or(this->alias_good, OR, {condition_1, condition_2});

    DistributedDevice::Instance().TriggerIO(this->attribute_string_good, this->value_string_good);
    if (not condition_log_or.Verify(this->value_string_good)){
        return false;
    }

    DistributedDevice::Instance().TriggerIO(this->attribute_string_good, this->value_string_bad);
    if (not condition_log_or.Verify(this->value_string_good)){
        return false;
    }

    DistributedDevice::Instance().TriggerIO(this->attribute_string_good, this->value_string_good);
    if (not condition_log_or.Verify(this->value_string_bad)){
        return false;
    }

    DistributedDevice::Instance().TriggerIO(this->attribute_string_good, this->value_string_bad);
    if (condition_log_or.Verify(this->value_string_bad)){
        return false;
    }

    // Test NOT
    condition_1 = new ConditionTrigger(this->alias_good, this->value_string_good);
    condition_2 = new ConditionStringState(this->alias_good, this->attribute_string_good, this->for_short, this->value_string_good);

    ConditionLogical condition_log_not(this->alias_good, NOT, {condition_1, condition_2});

    DistributedDevice::Instance().TriggerIO(this->attribute_string_good, this->value_string_good);
    if (condition_log_not.Verify(this->value_string_good)){
        return false;
    }

    DistributedDevice::Instance().TriggerIO(this->attribute_string_good, this->value_string_bad);
    if (not condition_log_not.Verify(this->value_string_good)){
        return false;
    }

    DistributedDevice::Instance().TriggerIO(this->attribute_string_good, this->value_string_good);
    if (not condition_log_not.Verify(this->value_string_bad)){
        return false;
    }

    DistributedDevice::Instance().TriggerIO(this->attribute_string_good, this->value_string_bad);
    if (not condition_log_not.Verify(this->value_string_bad)){
        return false;
    }

    return true;
}
