//
// Created by talgarr on 01/02/24.
//

#include "ConditionNumericState.hpp"

#include <utility>

ConditionNumericState::ConditionNumericState(char *alias, string attribute, string value_template,
                                             double above, double below)  : Condition(alias) {
    this->attribute = std::move(attribute);
    this->value_template = std::move(value_template);
    this->above = above;
    this->below = below;
}

bool ConditionNumericState::Verify() {


    return false;
}

ConditionNumericState::~ConditionNumericState() = default;
