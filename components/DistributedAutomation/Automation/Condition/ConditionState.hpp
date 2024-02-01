//
// Created by talgarr on 01/02/24.
//

#ifndef CPP_CONDITIONSTATE_HPP
#define CPP_CONDITIONSTATE_HPP

#include "Condition.hpp"

class ConditionState : public Condition
{
protected:
    string attribute;
    time_t for_;
    string state;

public:
    explicit ConditionState(string alias, string attribute, string state, time_t for_);
    ~ConditionState() override;
    bool Verify() override;
};

#endif //CPP_CONDITIONSTATE_HPP
