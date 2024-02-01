//
// Created by talgarr on 01/02/24.
//

#include "ConditionState.hpp"

bool ConditionState::Verify() {
    return false;
}

ConditionState::ConditionState(string alias, string attribute, string state, time_t for_) : Condition(alias) {
    this->attribute = std::move(attribute);
    this->for_ = for_;
    this->state = std::move(state);

}

ConditionState::~ConditionState() = default;
