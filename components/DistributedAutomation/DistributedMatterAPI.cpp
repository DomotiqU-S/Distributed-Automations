//
// Created by talgarr on 01/02/24.
//

#include "DistributedMatterAPI.hpp"

vector<string> DistributedMatterAPI::GetDevices() {
    vector<string> devices_alias = {"device1", "device2"};
    return devices_alias;
}

vector<Automation> DistributedMatterAPI::GetAutomations(const string& alias) {
    vector<Trigger *> triggers = vector<Trigger *>();
    vector<Condition *> conditions = vector<Condition *>();
    vector<Action *> actions = vector<Action *>();
    Automation automation("alias", "descript", triggers, conditions, actions);
    vector<Automation> automation_vector = vector<Automation>();
    automation_vector.push_back(automation);
    return automation_vector;
}

bool DistributedMatterAPI::AddAutomationToDevice(const string& device_alias, const Automation& automation) {
    return false;
}

bool DistributedMatterAPI::RemoveAutomationToDevice(const string &device_alias, const string& automation_alias) {
    return false;
}




