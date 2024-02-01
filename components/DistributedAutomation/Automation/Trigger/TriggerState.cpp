//
// Created by talgarr on 01/02/24.
//

#include "TriggerState.hpp"

TriggerState::TriggerState(string alias, string attribute, string from_state, string to_state, time_t for_) : Trigger(std::move(alias)) {
    this->attribute = std::move(attribute);
    this->from_state = std::move(from_state);
    this->to_state = std::move(to_state);
    this->for_ = for_;
}

TriggerState::~TriggerState() = default;
