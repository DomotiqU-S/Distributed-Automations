//
// Created by talgarr on 01/02/24.
//

#include "ConditionTime.hpp"

ConditionTime::ConditionTime(string alias, tm after, tm before, vector<string> weekday) : Condition(alias) {
    this->after = after;
    this->before = before;
    this->weekday = std::move(weekday);

}

bool ConditionTime::Verify() {
    return false;
}

ConditionTime::~ConditionTime() = default;
