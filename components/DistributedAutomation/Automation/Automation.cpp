//
// Created by talgarr on 01/02/24.
//

#include "Automation.hpp"


/**
 * @brief Construct a new Automation:: Automation object
 *
 * @param alias Name abd ID of the automation
 * @param description Description of the automation
 * @param triggers Trigger of the automation. Following https://www.home-assistant.io/docs/automation/trigger/, only Numeric State, State, Time, and Time Pattern are supported.
 * @param conditions Condition of the automation. Following https://www.home-assistant.io/docs/automation/condition/, only Logical, Numeric State, State (without Sun based), Time, and Trigger are supported.
 * @param actions Action of the automation. Following https://www.home-assistant.io/docs/automation/action/, only a Device Action is supported as a service.
 */
Automation::Automation(string alias, string description, vector<Trigger *> triggers, vector<Condition *> conditions,
                       vector<Action *> actions) {
    this->alias = std::move(alias);
    this->description = std::move(description);
    this->triggers = std::move(triggers);
    this->conditions = std::move(conditions);
    this->actions = std::move(actions);

    this->has_triggered = false;
    this->running = true;
}

Automation::~Automation(){
    for (auto &trigger : this->triggers) {
        delete trigger;
    }
    for (auto &condition : this->conditions) {
        delete condition;
    }
    for (auto &action : this->actions) {
        delete action;
    }
}

void Automation::AddTrigger(Trigger *trigger) {
    this->triggers.push_back(trigger);
}

void Automation::AddCondition(Condition *condition) {
    this->conditions.push_back(condition);
}

void Automation::AddAction(Action *action) {
    this->actions.push_back(action);
}

string Automation::GetAlias() {
    return this->alias;
}

string Automation::GetDescription() {
    return this->description;
}

vector<Condition *> Automation::GetConditions() {
    return this->conditions;
}

vector<Action *> Automation::GetActions() {
    return this->actions;
}

vector<Trigger *> Automation::GetTriggers() {
    return this->triggers;
}

bool Automation::Verify() {
    for (auto &condition : this->conditions) {
        if (!condition->Verify()) {
            return false;
        }
    }
    return true;
}

void Automation::Do() {
    for (auto &action : this->actions) {
        action->Do();
    }
}

void Automation::Run(condition_variable *cv_mother, mutex *cv_m_mother) {
    this->SetTrigger();
    while (this-running){
        unique_lock<mutex> lock_(this->cv_m);
        {
            unique_lock<mutex> lock(*cv_m_mother);
            this->has_triggered = true;
            cv_mother->notify_all();
        }
        this->cv.wait(lock_);
    }
}


bool Automation::HasTriggered() {
    if (this->has_triggered)
    {
        this->has_triggered = false;
        return true;
    }
    else{
        return false;
    }
}

void Automation::SetTrigger() {
    for (auto &trigger : this->triggers) {
        trigger->SetTrigger(&this->cv, &this->cv_m);
    }
}



