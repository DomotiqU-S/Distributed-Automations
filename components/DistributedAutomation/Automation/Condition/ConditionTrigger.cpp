//
// Created by talgarr on 01/02/24.
//

#include "ConditionTrigger.hpp"

#include <utility>

ConditionTrigger::ConditionTrigger(string alias, string trigger_alias)  : Condition(std::move(alias)) {
    this->trigger_alias = std::move(trigger_alias);

}

bool ConditionTrigger::Verify(string alias) {
    return this->trigger_alias == alias;
}

ConditionTrigger::~ConditionTrigger() = default;
