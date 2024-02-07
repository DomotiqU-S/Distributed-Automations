//
// Created by talgarr on 01/02/24.
//

#include "TriggerTimePattern.hpp"

TriggerTimePattern::TriggerTimePattern(string alias, tm pattern)  : Trigger(std::move(alias)) {
    this->pattern = pattern;

}

void TriggerTimePattern::SetTrigger(condition_variable *cv_mother, mutex *cv_m_mother) {
    sleep(15);
    cv_mother.notify_all();
}

TriggerTimePattern::~TriggerTimePattern() = default;
