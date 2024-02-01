//
// Created by talgarr on 01/02/24.
//

#ifndef CPP_TRIGGERNUMERICSTATE_HPP
#define CPP_TRIGGERNUMERICSTATE_HPP

#include <vector>
#include <string>
#include <utility>
#include "Trigger.hpp"

using namespace std;

class TriggerNumericState : public Trigger{
protected:
    vector<string> entity_id;
    string attribute;
    string value_template;
    double above{};
    double below{};
    time_t for_{};

public:
    TriggerNumericState(string alias, vector<string> entity_id, string attribute, string value_template, double above, double below, time_t for_);
    ~TriggerNumericState();

};


#endif //CPP_TRIGGERNUMERICSTATE_HPP
