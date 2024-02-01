//
// Created by talgarr on 01/02/24.
//

#ifndef CPP_CONDITIONSTATE_HPP
#define CPP_CONDITIONSTATE_HPP

#include "Condition.hpp"

class ConditionState : public Condition
{
protected:
    string entity_id;
    string attribute;
    time_t for_;
    string state;

public:
    explicit ConditionState(char *alias, string entity_id, string attribute, time_t for_, string state);
    ~ConditionState() override;
    bool Verify() override;
};

#endif //CPP_CONDITIONSTATE_HPP
