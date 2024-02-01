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
}

Automation::~Automation() = default;

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

void Automation::Run() {
    if (this->Verify()) {
        this->Do();
    }
}


