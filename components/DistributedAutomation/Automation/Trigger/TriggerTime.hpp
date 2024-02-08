//
// Created by talgarr on 01/02/24.
//

#ifndef CPP_TRIGGERTIMEPATTERN_HPP
#define CPP_TRIGGERTIMEPATTERN_HPP

#include "Trigger.hpp"
#include "../../../Library/croncpp/croncpp.h"
#include <iostream>

class TriggerTime : public Trigger {
protected:
    cron::cronexpr pattern;

    condition_variable cv;
    mutex cv_m;
    bool running;

public:
    TriggerTime(string alias, const string& pattern);

    [[noreturn]] void Run(condition_variable *cv_mother) override;
    void Stop() override;
    ~TriggerTime();
};

#endif //CPP_TRIGGERTIMEPATTERN_HPP
