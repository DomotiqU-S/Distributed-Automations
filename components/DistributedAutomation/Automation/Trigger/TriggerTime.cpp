//
// Created by talgarr on 01/02/24.
//

#include "TriggerTime.hpp"

TriggerTime::TriggerTime(string alias, tm at)  : Trigger(std::move(alias)) {
    this->at = at;
}

void TriggerTime::SetTrigger(condition_variable *cv_mother, mutex *cv_m_mother) {
//    this_thread::sleep_until(chrono::system_clock::from_time_t(mktime(&at)));
    this_thread::sleep_until(chrono::system_clock::from_time_t(mktime(&at)));
    cv_mother.notify_all();
}

TriggerTime::~TriggerTime() = default;

