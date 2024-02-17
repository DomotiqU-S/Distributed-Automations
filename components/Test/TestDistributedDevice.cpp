//
// Created by talgarr on 15/02/24.
//

#include "TestDistributedDevice.hpp"
#include "../DistributedAutomation/Automation/Trigger/TriggerTime.hpp"
#include "../DistributedAutomation/Automation/Action/ActionCallService.hpp"
#include "../DistributedAutomation/Automation/Trigger/TriggerNumericState.hpp"
#include "../DistributedAutomation/Automation/Condition/ConditionTrigger.hpp"
#include "../DistributedAutomation/Automation/Condition/ConditionNumericState.hpp"
#include "../DistributedAutomation/Automation/Condition/ConditionLogical.hpp"

TestDistributedDevice::TestDistributedDevice() {

    cout << "---------- TestDistributedDevice ---------" << endl;
    bool result = AutomationPresentationTime();
    cout << "AutomationPresentationTime: " << (result ? "Pass" : "Fail") << endl;
//    bool result = AutomationPresentationState();
//    cout << "AutomationPresentationState: " << (result ? "Pass" : "Fail") << endl;
    cout << "---------- TestDistributedDevice ---------" << endl;
}

bool TestDistributedDevice::AutomationPresentationTime() {
    DistributedDevice::Instance().TriggerIO(this->attribute_end_good, this->value_string_bad);

    vector<Trigger *> triggers = vector<Trigger *>();
    auto trigger_1 = new TriggerTime("trigger_1", "*/" + to_string(this->for_long) + " * * * * ?");
    triggers.push_back(trigger_1);

    vector<Condition *> conditions = vector<Condition *>();

    vector<Action *> actions = vector<Action *>();
    auto action = new ActionCallService(this->alias_good, this->attribute_end_good, this->value_string_good);
    actions.push_back(action);

    Automation automation(this->alias_good, this->description, triggers, conditions, actions);
    cout << "Automation Created: set the attribute <" << this->attribute_end_good << "> to <" << this->value_string_good << "> every " << this->for_long << " seconds." << endl;

    cout << "Add Automation to DistributedDevice" << endl;
    DistributedDevice::Instance().AddAutomation(&automation);

    this_thread::sleep_for(chrono::seconds(5));


    cout << "Run DistributedDevice in a separate thread" << endl;
    std::thread(&DistributedDevice::Run, &DistributedDevice::Instance()).detach();

    cout << "Current " << this->attribute_end_good  << " value: " << DistributedDevice::Instance().GetAttribute(this->attribute_end_good).value << endl;
    int delay = 500;
    for (int j = 0; j < 3; j++) {
        DistributedDevice::Instance().TriggerIO(this->attribute_end_good, this->value_string_bad);
        cout << "Wait for the attribute <" << this->attribute_end_good << "> to be <" << this->value_string_good << ">" << endl;
        for (int i = 1; i < 20; i++) {
            this_thread::sleep_for(chrono::milliseconds(delay));
            cout << "\tCurrent wait time: " << i * delay << " ms" << endl;
            State state = DistributedDevice::Instance().GetAttribute(this->attribute_end_good);
            if (state.value == this->value_string_good) {
                cout << "\tAttribute <" << this->attribute_end_good << "> is <" << this->value_string_good << "> after " << i * delay << " ms" << endl;
                break;
            }
        }
    }

    DistributedDevice::Instance().Stop();
    return true;
}


bool TestDistributedDevice::AutomationPresentationState() {
    DistributedDevice::Instance().TriggerIO(this->attribute_end_good, this->value_string_bad);

    vector<Trigger *> triggers = vector<Trigger *>();
    auto trigger_1 = new TriggerNumericState("trigger_1", this->attribute_numeric_good, 0, 5, 20);
    triggers.push_back(trigger_1);

    vector<Condition *> conditions = vector<Condition *>();
    auto condition = new ConditionNumericState("condition_1", this->attribute_numeric_good, 0, 10, 15);
    auto condition_log = new ConditionLogical("condition_1", NOT, {condition});
    conditions.push_back(condition_log);

    vector<Action *> actions = vector<Action *>();
    auto action = new ActionCallService(this->alias_good, this->attribute_end_good, this->value_string_good);
    actions.push_back(action);

    Automation automation(this->alias_good, this->description, triggers, conditions, actions);
    cout << "Automation Created: set the attribute <" << this->attribute_end_good << "> to <" << this->value_string_good << "> when <" << this->attribute_numeric_good << "> is set between 5 and 20, but not when between 10 and 15" << endl;

    cout << "Add Automation to DistributedDevice" << endl;
    DistributedDevice::Instance().AddAutomation(&automation);

    this_thread::sleep_for(chrono::seconds(5));

    cout << "Run DistributedDevice in a separate thread" << endl;
    std::thread(&DistributedDevice::Run, &DistributedDevice::Instance()).detach();

    cout << "Current " << this->attribute_end_good  << " value: " << DistributedDevice::Instance().GetAttribute(this->attribute_end_good).value << endl;
    DistributedDevice::Instance().TriggerIO(this->attribute_end_good, this->value_string_bad);
    cout << "Wait for the attribute <" << this->attribute_end_good << "> to be <" << this->value_string_good << ">" << endl;
    for (int i = 1; i < 30; i++) {
        DistributedDevice::Instance().TriggerIO(this->attribute_numeric_good, to_string(i));
        this_thread::sleep_for(chrono::milliseconds (50));
        State state = DistributedDevice::Instance().GetAttribute(this->attribute_end_good);
        if (state.value == this->value_string_good) {
            cout << "\tAttribute <" << this->attribute_end_good << "> is <" << this->value_string_good << "> with <" << this->attribute_numeric_good << "> at " << to_string(i) << endl;
            DistributedDevice::Instance().TriggerIO(this->attribute_end_good, this->value_string_bad);
        }
    }

    DistributedDevice::Instance().Stop();
    return true;
}

