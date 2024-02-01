//
// Created by talgarr on 01/02/24.
//

#include "TriggerTimePattern.hpp"

TriggerTimePattern::TriggerTimePattern(string alias, tm pattern)  : Trigger(std::move(alias)) {
    this->pattern = pattern;

}

TriggerTimePattern::~TriggerTimePattern() = default;
