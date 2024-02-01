//
// Created by talgarr on 01/02/24.
//

#include "ConditionLogical.hpp"

#include <utility>

bool ConditionLogical::Verify() {
    switch (this->logicalOperator) {
        case AND:
            for (auto &condition : this->conditions) {
                if (!condition->Verify()) {
                    return false;
                }
            }
            return true;
        case OR:
            for (auto &condition : this->conditions) {
                if (condition->Verify()) {
                    return true;
                }
            }
            return false;
        case NOT:
            for (auto &condition : this->conditions) {
                if (!condition->Verify()) {
                    return true;
                }
            }
            return false;
    }
    return false;
}

ConditionLogical::ConditionLogical(char *alias, LogicalOperator logicalOperator, vector<Condition *> conditions) : Condition(alias){
    this->logicalOperator = logicalOperator;
    this->conditions = std::move(conditions);
}

ConditionLogical::~ConditionLogical() = default;
