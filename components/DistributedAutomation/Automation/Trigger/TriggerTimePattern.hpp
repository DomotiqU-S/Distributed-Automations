//
// Created by talgarr on 01/02/24.
//

#ifndef CPP_TRIGGERTIMEPATTERN_HPP
#define CPP_TRIGGERTIMEPATTERN_HPP

#include "Trigger.hpp"

class TriggerTimePattern : public Trigger {
protected:
    tm pattern{};

public:
    TriggerTimePattern(string alias, tm pattern);
    ~TriggerTimePattern();
};

#endif //CPP_TRIGGERTIMEPATTERN_HPP
