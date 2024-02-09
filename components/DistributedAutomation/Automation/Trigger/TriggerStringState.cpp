//
// Created by talgarr on 08/02/24.
//

#include "TriggerStringState.hpp"

TriggerStringState::TriggerStringState(std::string alias, std::string attribute, time_t for_s,
                                       std::string from_state, std::string to_state) : TriggerState(std::move(alias),
                                                                                          std::move(attribute), for_s) {
    this->from_state = std::move(from_state);
    this->to_state = std::move(to_state);
}

void TriggerStringState::IO(string attribute, string value) {
    if (attribute.empty() or value.empty())
        return;
    if (this->attribute == attribute) {
        if (this->from_state == this->previous_value or this->to_state == value) {
            this->IOSup();
        }
        else {
            this->Stop();
        }
        this->previous_value = value;
    }
}

