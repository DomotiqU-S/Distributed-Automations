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

TestAutomation::TestAutomation() {
    cout << "---------- TestAutomation ---------" << endl;
    cout << "AutomationIntegration: " << (AutomationIntegration() ? "Pass" : "Fail") << endl;
    cout << "---------- TestAutomation ---------" << endl;
}

bool TestAutomation::AutomationIntegration() {
    vector<Trigger *> triggers = vector<Trigger *>();
    auto trigger_1 = new TriggerStringState("trigger_1", this->attribute_string_good, 0, "", "on");
    triggers.push_back(trigger_1);
    auto trigger_2 = new TriggerNumericState("trigger_2", this->attribute_string_good, 0, 0, 255);
    triggers.push_back(trigger_2);
    auto trigger_3 = new TriggerTime("trigger_3", "*/" + to_string(this->for_long) + " * * * * ?");
    triggers.push_back(trigger_3);

    vector<Condition *> conditions = vector<Condition *>();
    vector<Condition *> conditions_log = vector<Condition *>();
    auto condition_1 = new ConditionTrigger("condition_1", "trigger_3");
    conditions_log.push_back(condition_1);
    auto condition_2 = new ConditionNumericState("condition_2", this->attribute_string_good, 0, 30, 255);
    conditions_log.push_back(condition_2);
    auto condition_3 = new ConditionLogical("condition_3", AND, conditions_log);
    conditions.push_back(condition_3);

    vector<Action *> actions = vector<Action *>();
    auto action = new ActionDelay(this->alias_good, this->for_long);
    actions.push_back(action);

    Automation automation(this->alias_good, this->description, triggers, conditions, actions);

    thread t(&Automation::Run, &automation, &this->cv, &this->cv_m);
    t.detach();

    auto future = std::async(std::launch::async, [this] {
        unique_lock<mutex> lock(this->cv_m);
        this->cv.wait(lock);
    });

    auto status = future.wait_for(50ms);
    if (status == std::future_status::ready) {
        return false;
    }

    status = future.wait_for(chrono::seconds(this->for_long));
    if (status == std::future_status::ready) {
        return false;
    }

    status = future.wait_for(chrono::seconds(this->for_long));
    if (status != std::future_status::ready) {
        return false;
    }

    automation.Stop();
    return false;
}

