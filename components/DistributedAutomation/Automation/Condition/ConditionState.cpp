//
// Created by talgarr on 01/02/24.
//

#include "ConditionState.hpp"

bool ConditionState::Verify() {
    return false;
}

ConditionState::ConditionState(char *alias, string entity_id, string attribute, time_t for_, string state) : Condition(alias) {
    this->entity_id = std::move(entity_id);
    this->attribute = std::move(attribute);
    this->for_ = for_;
    this->state = std::move(state);

}

ConditionState::~ConditionState() = default;
