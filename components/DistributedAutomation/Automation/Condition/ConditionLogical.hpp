//
// Created by talgarr on 01/02/24.
//

#ifndef CPP_CONDITIONLOGICAL_HPP
#define CPP_CONDITIONLOGICAL_HPP

#include <vector>
#include "Condition.hpp"

enum LogicalOperator
{
    AND,
    OR,
    NOT
};

class ConditionLogical : public Condition
{
protected:
    LogicalOperator logicalOperator;
    vector<Condition *> conditions;

public:
    explicit ConditionLogical(char *alias, LogicalOperator logicalOperator, vector<Condition *> conditions);
    ~ConditionLogical() override;
    bool Verify() override;
};

#endif //CPP_CONDITIONLOGICAL_HPP
