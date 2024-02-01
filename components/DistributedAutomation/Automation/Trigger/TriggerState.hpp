//
// Created by talgarr on 01/02/24.
//

#ifndef CPP_TRIGGERSTATE_HPP
#define CPP_TRIGGERSTATE_HPP

#include <vector>
#include "Trigger.hpp"

class TriggerState : public Trigger {
protected:
    string attribute;
    string from_state;
    string to_state;
    time_t for_{};
public:
    TriggerState(string alias, string attribute, string from_state, string to_state, time_t for_);
    ~TriggerState();
};

#endif //CPP_TRIGGERSTATE_HPP
