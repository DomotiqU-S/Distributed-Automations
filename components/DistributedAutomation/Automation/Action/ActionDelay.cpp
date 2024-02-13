//
// Created by talgarr on 01/02/24.
//

#include "ActionDelay.hpp"

#include <utility>

ActionDelay::ActionDelay(string alias, time_t delay_s) : Action(std::move(alias)) {
    this->delay = delay_s;
}

ActionDelay::~ActionDelay() = default;

void ActionDelay::Do() {
    cout << "ActionDelay::Do() " << this->alias << " delay: " << this->delay << endl;
    this_thread::sleep_for(chrono::seconds(this->delay));
}
