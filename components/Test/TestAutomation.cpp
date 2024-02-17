//
// Created by talgarr on 13/02/24.
//

#include <future>
#include "TestAutomation.h"
#include "../DistributedAutomation/Automation/Trigger/TriggerStringState.hpp"
#include "../DistributedAutomation/Automation/Trigger/TriggerNumericState.hpp"
#include "../DistributedAutomation/Automation/Condition/ConditionTrigger.hpp"
#include "../DistributedAutomation/Automation/Condition/ConditionNumericState.hpp"
#include "../DistributedAutomation/Automation/Condition/ConditionLogical.hpp"
#include "../DistributedAutomation/Automation/Action/ActionDelay.hpp"
#include "../DistributedAutomation/Automation/Action/ActionCallService.hpp"

TestAutomation::TestAutomation() {
    cout << "---------- TestAutomation ---------" << endl;
    cout << "AutomationPresentationTime: " << (AutomationBasic() ? "Pass" : "Fail") << endl;
//    cout << "AutomationMultipleTrigger: " << (AutomationMultipleTrigger() ? "Pass" : "Fail") << endl;
//    cout << "AutomationCondition: " << (AutomationCondition() ? "Pass" : "Fail") << endl;
//    cout << "AutomationMultipleCondition: " << (AutomationMultipleCondition() ? "Pass" : "Fail") << endl;
//    cout << "AutomationMultipleAction: " << (AutomationMultipleAction() ? "Pass" : "Fail") << endl;
//    cout << "AutomationComplex: " << (AutomationComplex() ? "Pass" : "Fail") << endl;
    cout << "---------- TestAutomation ---------" << endl;
}

bool TestAutomation::AutomationBasic() {
    vector<Trigger *> triggers = vector<Trigger *>();
    auto trigger_1 = new TriggerTime("trigger_1", "*/" + to_string(this->for_long) + " * * * * ?");
    triggers.push_back(trigger_1);

    vector<Condition *> conditions = vector<Condition *>();

    vector<Action *> actions = vector<Action *>();
    auto action = new ActionCallService(this->alias_good, this->attribute_end_good, this->value_string_good);
    actions.push_back(action);

    Automation automation(this->alias_good, this->description, triggers, conditions, actions);
    thread t(&Automation::Run, &automation, &this->cv, &this->cv_m);
    t.detach();

    auto future = std::async(std::launch::async, [this, &automation] {
        unique_lock<mutex> lock(this->cv_m);
        this->cv.wait(lock);
        if (automation.Verify()) {
            automation.Do();
        }
    });

    this_thread::sleep_for(chrono::milliseconds (50));
    State state = DistributedDevice::Instance().GetAttribute(this->attribute_end_good);
    if (state.value == this->value_string_good) {
        return false;
    }

    future.wait_for(chrono::seconds(this->for_long));
    state = DistributedDevice::Instance().GetAttribute(this->attribute_end_good);
    if (state.value != this->value_string_good) {
        return false;
    }

    automation.Stop();
    return true;
}

bool TestAutomation::AutomationMultipleTrigger() {
    vector<Trigger *> triggers = vector<Trigger *>();
    auto trigger_1 = new TriggerStringState("trigger_1", this->attribute_string_good, 0, "", this->value_string_good);
    triggers.push_back(trigger_1);
    auto trigger_2 = new TriggerNumericState("trigger_2", this->attribute_numeric_good, 0, 0, 255);
    triggers.push_back(trigger_2);

    vector<Condition *> conditions = vector<Condition *>();

    vector<Action *> actions = vector<Action *>();
    auto action = new ActionCallService(this->alias_good, this->attribute_end_good, this->value_string_good);
    actions.push_back(action);

    Automation automation(this->alias_good, this->description, triggers, conditions, actions);
    thread t(&Automation::Run, &automation, &this->cv, &this->cv_m);
    t.detach();

    thread t2([this, &automation] {
        unique_lock<mutex> lock(this->cv_m);
        this->cv.wait(lock);
        if (automation.Verify()) {
            automation.Do();
        }
    });

    this_thread::sleep_for(chrono::milliseconds (50));
    State state = DistributedDevice::Instance().GetAttribute(this->attribute_end_good);
    if (state.value == this->value_string_good) {
        return false;
    }

    DistributedDevice::Instance().TriggerIO(this->attribute_string_good, this->value_string_good);

    this_thread::sleep_for(chrono::milliseconds (50));
    state = DistributedDevice::Instance().GetAttribute(this->attribute_end_good);
    if (state.value != this->value_string_good) {
        return false;
    }

    t2.join();

    DistributedDevice::Instance().TriggerIO(this->attribute_end_good, this->value_string_bad);

    thread t3([this, &automation] {
        unique_lock<mutex> lock(this->cv_m);
        this->cv.wait(lock);
        if (automation.Verify()) {
            automation.Do();
        }
    });

    this_thread::sleep_for(chrono::milliseconds (50));
    state = DistributedDevice::Instance().GetAttribute(this->attribute_end_good);
    if (state.value == this->value_string_good) {
        return false;
    }

    DistributedDevice::Instance().TriggerIO(this->attribute_numeric_good, to_string(this->value_numeric_good));

    this_thread::sleep_for(chrono::milliseconds (50));
    state = DistributedDevice::Instance().GetAttribute(this->attribute_end_good);
    if (state.value != this->value_string_good) {
        return false;
    }

    automation.Stop();
    return true;
}


bool TestAutomation::AutomationCondition() {
    vector<Trigger *> triggers = vector<Trigger *>();
    auto trigger_1 = new TriggerStringState("trigger_1", this->attribute_string_good, 0, "", this->value_string_good);
    triggers.push_back(trigger_1);
    auto trigger_2 = new TriggerNumericState("trigger_2", this->attribute_string_good, 0, 0, 255);
    triggers.push_back(trigger_2);

    vector<Condition *> conditions = vector<Condition *>();
    vector<Condition *> conditions_log = vector<Condition *>();
    auto condition_1 = new ConditionTrigger("condition_1", "trigger_3");
    conditions_log.push_back(condition_1);
    auto condition_2 = new ConditionNumericState("condition_2", this->attribute_string_good, 0, 30, 255);
    conditions_log.push_back(condition_2);
    auto condition_3 = new ConditionLogical("condition_3", AND, conditions_log);
    conditions.push_back(condition_3);

    vector<Action *> actions = vector<Action *>();
    auto action = new ActionCallService(this->alias_good, this->attribute_end_good, this->value_string_good);
    actions.push_back(action);

    Automation automation(this->alias_good, this->description, triggers, conditions, actions);
    thread t(&Automation::Run, &automation, &this->cv, &this->cv_m);
    t.detach();

    auto future = std::async(std::launch::async, [this, &automation] {
        unique_lock<mutex> lock(this->cv_m);
        this->cv.wait(lock);
        if (automation.Verify()) {
            automation.Do();
        }
    });

    this_thread::sleep_for(chrono::milliseconds (50));
    State state = DistributedDevice::Instance().GetAttribute(this->attribute_end_good);
    if (state.value == this->value_string_good) {
        return false;
    }

    future.wait_for(chrono::seconds(this->for_long));
    state = DistributedDevice::Instance().GetAttribute(this->attribute_end_good);
    if (state.value != this->value_string_good) {
        return false;
    }

    automation.Stop();
    return true;
}

bool TestAutomation::AutomationMultipleCondition() {
    vector<Trigger *> triggers = vector<Trigger *>();
    auto trigger_1 = new TriggerStringState("trigger_1", this->attribute_string_good, 0, "", this->value_string_good);
    triggers.push_back(trigger_1);
    auto trigger_2 = new TriggerNumericState("trigger_2", this->attribute_string_good, 0, 0, 255);
    triggers.push_back(trigger_2);

    vector<Condition *> conditions = vector<Condition *>();
    vector<Condition *> conditions_log = vector<Condition *>();
    auto condition_1 = new ConditionTrigger("condition_1", "trigger_3");
    conditions_log.push_back(condition_1);
    auto condition_2 = new ConditionNumericState("condition_2", this->attribute_string_good, 0, 30, 255);
    conditions_log.push_back(condition_2);
    auto condition_3 = new ConditionLogical("condition_3", AND, conditions_log);
    conditions.push_back(condition_3);

    vector<Action *> actions = vector<Action *>();
    auto action = new ActionCallService(this->alias_good, this->attribute_end_good, this->value_string_good);
    actions.push_back(action);

    Automation automation(this->alias_good, this->description, triggers, conditions, actions);
    thread t(&Automation::Run, &automation, &this->cv, &this->cv_m);
    t.detach();

    auto future = std::async(std::launch::async, [this, &automation] {
        unique_lock<mutex> lock(this->cv_m);
        this->cv.wait(lock);
        if (automation.Verify()) {
            automation.Do();
        }
    });

    this_thread::sleep_for(chrono::milliseconds (50));
    State state = DistributedDevice::Instance().GetAttribute(this->attribute_end_good);
    if (state.value == this->value_string_good) {
        return false;
    }

    future.wait_for(chrono::seconds(this->for_long));
    state = DistributedDevice::Instance().GetAttribute(this->attribute_end_good);
    if (state.value != this->value_string_good) {
        return false;
    }

    automation.Stop();
    return true;
}

bool TestAutomation::AutomationMultipleAction() {
    vector<Trigger *> triggers = vector<Trigger *>();
    auto trigger_1 = new TriggerStringState("trigger_1", this->attribute_string_good, 0, "", this->value_string_good);
    triggers.push_back(trigger_1);
    auto trigger_2 = new TriggerNumericState("trigger_2", this->attribute_string_good, 0, 0, 255);
    triggers.push_back(trigger_2);

    vector<Condition *> conditions = vector<Condition *>();
    vector<Condition *> conditions_log = vector<Condition *>();
    auto condition_1 = new ConditionTrigger("condition_1", "trigger_3");
    conditions_log.push_back(condition_1);
    auto condition_2 = new ConditionNumericState("condition_2", this->attribute_string_good, 0, 30, 255);
    conditions_log.push_back(condition_2);
    auto condition_3 = new ConditionLogical("condition_3", AND, conditions_log);
    conditions.push_back(condition_3);

    vector<Action *> actions = vector<Action *>();
    auto action = new ActionCallService(this->alias_good, this->attribute_end_good, this->value_string_good);
    actions.push_back(action);

    Automation automation(this->alias_good, this->description, triggers, conditions, actions);
    thread t(&Automation::Run, &automation, &this->cv, &this->cv_m);
    t.detach();

    auto future = std::async(std::launch::async, [this, &automation] {
        unique_lock<mutex> lock(this->cv_m);
        this->cv.wait(lock);
        if (automation.Verify()) {
            automation.Do();
        }
    });

    this_thread::sleep_for(chrono::milliseconds (50));
    State state = DistributedDevice::Instance().GetAttribute(this->attribute_end_good);
    if (state.value == this->value_string_good) {
        return false;
    }

    future.wait_for(chrono::seconds(this->for_long));
    state = DistributedDevice::Instance().GetAttribute(this->attribute_end_good);
    if (state.value != this->value_string_good) {
        return false;
    }

    automation.Stop();
    return true;
}

bool TestAutomation::AutomationComplex() {
    vector<Trigger *> triggers = vector<Trigger *>();
    auto trigger_1 = new TriggerStringState("trigger_1", this->attribute_string_good, 0, "", this->value_string_good);
    triggers.push_back(trigger_1);
    auto trigger_2 = new TriggerNumericState("trigger_2", this->attribute_string_good, 0, 0, 255);
    triggers.push_back(trigger_2);

    vector<Condition *> conditions = vector<Condition *>();
    vector<Condition *> conditions_log = vector<Condition *>();
    auto condition_1 = new ConditionTrigger("condition_1", "trigger_3");
    conditions_log.push_back(condition_1);
    auto condition_2 = new ConditionNumericState("condition_2", this->attribute_string_good, 0, 30, 255);
    conditions_log.push_back(condition_2);
    auto condition_3 = new ConditionLogical("condition_3", AND, conditions_log);
    conditions.push_back(condition_3);

    vector<Action *> actions = vector<Action *>();
    auto action = new ActionCallService(this->alias_good, this->attribute_end_good, this->value_string_good);
    actions.push_back(action);

    Automation automation(this->alias_good, this->description, triggers, conditions, actions);
    thread t(&Automation::Run, &automation, &this->cv, &this->cv_m);
    t.detach();

    auto future = std::async(std::launch::async, [this, &automation] {
        unique_lock<mutex> lock(this->cv_m);
        this->cv.wait(lock);
        if (automation.Verify()) {
            automation.Do();
        }
    });

    this_thread::sleep_for(chrono::milliseconds (50));
    State state = DistributedDevice::Instance().GetAttribute(this->attribute_end_good);
    if (state.value == this->value_string_good) {
        return false;
    }

    future.wait_for(chrono::seconds(this->for_long));
    state = DistributedDevice::Instance().GetAttribute(this->attribute_end_good);
    if (state.value != this->value_string_good) {
        return false;
    }

    automation.Stop();
    return true;
}

