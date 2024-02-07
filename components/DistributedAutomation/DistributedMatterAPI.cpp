//
// Created by talgarr on 01/02/24.
//

#include "DistributedMatterAPI.hpp"
#include "Automation/Trigger/TriggerState.hpp"
#include "Automation/Condition/ConditionLogical.hpp"
#include "Automation/Condition/ConditionTrigger.hpp"
#include "Automation/Condition/ConditionState.hpp"
#include "Automation/Action/ActionDelay.hpp"
#include "Automation/Trigger/TriggerTime.hpp"

vector<string> DistributedMatterAPI::GetDevices() {
    vector<string> devices_alias = {"device1", "device2"};
    return devices_alias;
}

vector<Automation *> DistributedMatterAPI::GetAutomations(const string& alias) {
    vector<Trigger *> triggers = vector<Trigger *>();
    auto trigger_1 = new TriggerState("trigger_1", "brightness", "0", "", 0);
    triggers.push_back(trigger_1);
    auto trigger_2 = new TriggerTime("trigger_2", "0 15 10 * * ?");
    triggers.push_back(trigger_2);
    auto trigger_3 = new TriggerTime("trigger_3", "*/5 * * * * ?");
    triggers.push_back(trigger_3);

//    vector<Condition *> conditions_log = vector<Condition *>();
//    auto condition_1 = new ConditionTrigger("condition_1", "trigger_1");
//    conditions_log.push_back(condition_1);
//    auto condition_2 = new ConditionState("condition_2", "power", "on", 0);
//    conditions_log.push_back(condition_2);
//    auto condition_3 = new ConditionLogical("condition_3", NOT, conditions_log);
    vector<Condition *> conditions = vector<Condition *>();
//    conditions.push_back(condition_3);

    vector<Action *> actions = vector<Action *>();
    auto action = new ActionDelay("action_1", 0);
    actions.push_back(action);

    vector<Automation*> automation_vector;
    for  (int i = 0; i < 1; i++) {
        automation_vector.push_back(new Automation("alias", "descript", triggers, conditions, actions));
    }
    return automation_vector;
}

bool DistributedMatterAPI::AddAutomationToDevice(const string& device_alias, const Automation& automation) {
    return false;
}

bool DistributedMatterAPI::RemoveAutomationToDevice(const string &device_alias, const string& automation_alias) {
    return false;
}




