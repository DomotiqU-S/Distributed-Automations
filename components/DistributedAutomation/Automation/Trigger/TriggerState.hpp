//
// Created by talgarr on 01/02/24.
//

#ifndef CPP_TRIGGERSTATE_HPP
#define CPP_TRIGGERSTATE_HPP

#include <vector>
#include "Trigger.hpp"

class TriggerState : public Trigger {
protected:
    vector<string> entity_id;
    vector<string> from_state;
    vector<string> to_state;
    time_t for_{};
public:
    TriggerState(string alias, vector<string> entity_id, vector<string> from_state, vector<string> to_state, time_t for_);
    ~TriggerState();
};

#endif //CPP_TRIGGERSTATE_HPP
