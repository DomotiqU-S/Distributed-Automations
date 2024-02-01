//
// Created by talgarr on 01/02/24.
//

#include "ActionDelay.hpp"

#include <utility>

ActionDelay::ActionDelay(std::string alias, time_t delay) : Action(std::move(alias)) {
    this->delay = delay;
}

ActionDelay::~ActionDelay() = default;

void ActionDelay::Do() {
    std::cout << "ActionDelay Do" << std::endl;
}
