//
// Created by talgarr on 01/02/24.
//

#ifndef CPP_CONDITIONNUMERICSTATE_HPP
#define CPP_CONDITIONNUMERICSTATE_HPP

#include "Condition.hpp"

class ConditionNumericState : public Condition
{
protected:
    string attribute;
    string value_template;
    double above;
    double below;

public:
    explicit ConditionNumericState(char *alias, string attribute, string value_template, double above, double below);
    ~ConditionNumericState() override;
    bool Verify() override;
};

#endif //CPP_CONDITIONNUMERICSTATE_HPP
