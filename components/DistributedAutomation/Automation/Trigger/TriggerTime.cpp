//
// Created by talgarr on 01/02/24.
//

#include "TriggerTime.hpp"

TriggerTime::TriggerTime(string alias, const string& pattern)  : Trigger(std::move(alias)) {
    this->running = false;

    try
    {
        this->pattern = cron::make_cron(pattern);
    }
    catch (cron::bad_cronexpr const & ex)
    {
        std::cerr << ex.what() << '\n';
    }
}

[[noreturn]] void TriggerTime::Run(condition_variable *cv_mother) {
    this->running = true;
    while (this->running) {
        std::time_t now = std::time(nullptr);
        std::time_t next = cron::cron_next(this->pattern, now);
        std::unique_lock<std::mutex> lock(this->cv_m);
        this->cv.wait_for(lock,chrono::seconds(next - now), [&]{return not this->running;});
        cv_mother->notify_one();
    }
}

void TriggerTime::Stop() {
    this->running = false;
    this->cv.notify_one();
}


TriggerTime::~TriggerTime() = default;
