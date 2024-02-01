//
// Created by talgarr on 01/02/24.
//

#ifndef CPP_AUTOMATION_HPP
#define CPP_AUTOMATION_HPP


#include <vector>
#include "Trigger/Trigger.hpp"
#include "Condition/Condition.hpp"
#include "Action/Action.hpp"

class Automation {
private:
    string alias;
    string description;
    vector<Condition *> conditions;
    vector<Action *> actions;
    vector<Trigger *> triggers;

public:
    Automation(string alias, string description, vector<Trigger *> triggers, vector<Condition *> conditions, vector<Action *> actions);
    ~Automation();

    //Setter
    void AddTrigger(Trigger *trigger);
    void AddCondition(Condition *condition);
    void AddAction(Action *action);

    //Getter
    string GetAlias();
    string GetDescription();
    vector<Condition *> GetConditions();
    vector<Action *> GetActions();
    vector<Trigger *> GetTriggers();

    //Functional
    void Run();
    bool Verify();
    void Do();
};


#endif //CPP_AUTOMATION_HPP
