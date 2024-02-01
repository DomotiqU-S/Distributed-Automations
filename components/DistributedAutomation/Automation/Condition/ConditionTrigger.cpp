//
// Created by talgarr on 01/02/24.
//

#include "ConditionTrigger.hpp"

ConditionTrigger::ConditionTrigger(string alias, string trigger_alias)  : Condition(alias) {
    this->trigger_alias = std::move(trigger_alias);

}

bool ConditionTrigger::Verify() {
    return false;
}

ConditionTrigger::~ConditionTrigger() = default;
