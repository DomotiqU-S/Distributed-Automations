//
// Created by talgarr on 01/02/24.
//

#include "Condition.hpp"

Condition::Condition(string alias) {
    this->alias = alias;
}

bool Condition::Verify(string alias) {
    return false;
}


Condition::~Condition() = default;
