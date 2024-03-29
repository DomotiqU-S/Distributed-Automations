//
// Created by talgarr on 01/02/24.
//

#ifndef CPP_CONDITIONTRIGGER_HPP
#define CPP_CONDITIONTRIGGER_HPP


#include "Condition.hpp"

class ConditionTrigger : public Condition
{
protected:
    string trigger_alias;

public:
    explicit ConditionTrigger(string alias, string trigger_alias);
    ~ConditionTrigger() override;
    bool Verify(string trigger_alias) override;
};


#endif //CPP_CONDITIONTRIGGER_HPP
