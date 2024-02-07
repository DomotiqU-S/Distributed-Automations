//
// Created by talgarr on 01/02/24.
//

#include "TriggerNumericState.hpp"


TriggerNumericState::TriggerNumericState(string alias, vector<string> entity_id, string attribute, string value_template,
                                         double above, double below, time_t for_) : Trigger(std::move(alias)) {

    this->entity_id = std::move(entity_id);
    this->attribute = std::move(attribute);
    this->value_template = std::move(value_template);
    this->above = above;
    this->below = below;
    this->for_ = for_;

}

void TriggerNumericState::SetTrigger(condition_variable *cv_mother, mutex *cv_m_mother) {
    return;
}

TriggerNumericState::~TriggerNumericState() = default;