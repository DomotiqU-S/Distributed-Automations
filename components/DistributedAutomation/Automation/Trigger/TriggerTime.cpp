//
// Created by talgarr on 01/02/24.
//

#include "TriggerTime.hpp"

TriggerTime::TriggerTime(string alias, tm at)  : Trigger(std::move(alias)) {
    this->at = at;
}

TriggerTime::~TriggerTime() = default;

