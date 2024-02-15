//
// Created by talgarr on 13/02/24.
//

#include <future>
#include "TestTrigger.h"
#include "../DistributedAutomation/DistributedDevice.hpp"

TestTrigger::TestTrigger() {
    cout << "---------- TestTrigger ----------" << endl;
    cout << "TestTriggerNumericState: " << (TestTriggerNumericState() ? "Pass" : "Fail") << endl;
    cout << "TestTriggerStringState: " << (TestTriggerStringState() ? "Pass" : "Fail") << endl;
    cout << "TestTriggerTime: " << (TestTriggerTime() ? "Pass" : "Fail") << endl;
    cout << "---------- TestTrigger ----------" << endl;
}

bool TestTrigger::TestTriggerNumericState() {
    // Short
    DistributedDevice::Instance().TriggerIO(this->attribute_numeric_good, to_string(this->value_numeric_bad));
    auto trigger = new TriggerNumericState(this->alias_good, this->attribute_numeric_good, this->for_short, 0,
                                           this->value_numeric_good * 2);
    trigger->Run(&this->cv, &this->cv_m);


    auto future = std::async(std::launch::async, [this] {
        unique_lock<mutex> lock(this->cv_m);
        this->cv.wait(lock);
    });
    this_thread::sleep_for(chrono::milliseconds(50));
    trigger->IO(this->attribute_numeric_good, to_string(this->value_numeric_bad));
    this_thread::sleep_for(chrono::milliseconds(50));
    auto status = future.wait_for(0ms);
    if (status == std::future_status::ready) {
        return false;
    }

    trigger->IO(this->attribute_numeric_good, to_string(this->value_numeric_good));
    this_thread::sleep_for(chrono::milliseconds(50));
    status = future.wait_for(0ms);
    if (status != std::future_status::ready) {
        return false;
    }

    // Long
    DistributedDevice::Instance().TriggerIO(this->attribute_numeric_good, to_string(this->value_numeric_bad));
    delete trigger;
    trigger = new TriggerNumericState(this->alias_good, this->attribute_numeric_good, this->for_long, 0,
                                      this->value_numeric_good * 2);
    trigger->Run(&this->cv, &this->cv_m);

    future = std::async(std::launch::async, [this] {
        unique_lock<mutex> lock(this->cv_m);
        this->cv.wait(lock);
    });
    this_thread::sleep_for(chrono::milliseconds(50));
    trigger->IO(this->attribute_numeric_good, to_string(this->value_numeric_good));
    this_thread::sleep_for(chrono::milliseconds(50));
    status = future.wait_for(0ms);
    if (status == std::future_status::ready) {
        return false;
    }

    this_thread::sleep_for(chrono::seconds(this->for_long));
    trigger->IO(this->attribute_numeric_good, to_string(this->value_numeric_good));
    this_thread::sleep_for(chrono::milliseconds(50));
    status = future.wait_for(0ms);
    if (status != std::future_status::ready) {
        return false;
    }

//    delete trigger;
    trigger->Stop();
    delete trigger;
    return true;
}

bool TestTrigger::TestTriggerStringState() {
    // Short and to_state
    auto trigger = new TriggerStringState(this->alias_good, this->attribute_string_good, this->for_short, "", this->value_string_good);
    trigger->Run(&this->cv, &this->cv_m);

    auto future = std::async(std::launch::async, [this] {
        unique_lock<mutex> lock(this->cv_m);
        this->cv.wait(lock);
    });
    this_thread::sleep_for(chrono::milliseconds(50));
    trigger->IO(this->attribute_string_good, this->value_string_bad);
    this_thread::sleep_for(chrono::milliseconds(50));
    auto status = future.wait_for(0ms);
    if (status == std::future_status::ready) {
        return false;
    }

    trigger->IO(this->attribute_string_good, this->value_string_good);
    this_thread::sleep_for(chrono::milliseconds(50));
    status = future.wait_for(0ms);
    if (status != std::future_status::ready) {
        return false;
    }

    // Long and to_state
    trigger = new TriggerStringState(this->alias_good, this->attribute_string_good, this->for_long, "", this->value_string_good);
    trigger->Run(&this->cv, &this->cv_m);

    future = std::async(std::launch::async, [this] {
        unique_lock<mutex> lock(this->cv_m);
        this->cv.wait(lock);
    });

    trigger->IO(this->attribute_string_good, this->value_string_good);
    this_thread::sleep_for(chrono::milliseconds(50));
    status = future.wait_for(0ms);
    if (status == std::future_status::ready) {
        return false;
    }

    trigger->IO(this->attribute_string_good, this->value_string_bad);
    this_thread::sleep_for(chrono::milliseconds(50));
    status = future.wait_for(0ms);
    if (status == std::future_status::ready) {
        return false;
    }

    trigger->IO(this->attribute_string_good, this->value_string_good);
    this_thread::sleep_for(chrono::milliseconds(50));
    status = future.wait_for(0ms);
    if (status == std::future_status::ready) {
        return false;
    }

    this_thread::sleep_for(chrono::seconds(this->for_long));
    trigger->IO(this->attribute_string_good, this->value_string_good);
    this_thread::sleep_for(chrono::milliseconds(50));
    status = future.wait_for(0ms);
    if (status != std::future_status::ready) {
        return false;
    }

    trigger->Stop();
    delete trigger;

    // Short and from_state
    trigger = new TriggerStringState(this->alias_good, this->attribute_string_good, this->for_short, this->value_string_good, "");
    trigger->Run(&this->cv, &this->cv_m);

    future = std::async(std::launch::async, [this] {
        unique_lock<mutex> lock(this->cv_m);
        this->cv.wait(lock);
    });
    this_thread::sleep_for(chrono::milliseconds(50));
    trigger->IO(this->attribute_string_good, this->value_string_bad);
    this_thread::sleep_for(chrono::milliseconds(50));
    status = future.wait_for(0ms);
    if (status == std::future_status::ready) {
        return false;
    }

    trigger->IO(this->attribute_string_good, this->value_string_good);
    this_thread::sleep_for(chrono::milliseconds(50));
    status = future.wait_for(0ms);
    if (status == std::future_status::ready) {
        return false;
    }

    trigger->IO(this->attribute_string_good, this->value_string_bad);
    this_thread::sleep_for(chrono::milliseconds(50));
    status = future.wait_for(0ms);
    if (status != std::future_status::ready) {
        return false;
    }

    trigger->Stop();
    delete trigger;

    // Long and from_state
    trigger = new TriggerStringState(this->alias_good, this->attribute_string_good, this->for_long, this->value_string_good, "");
    trigger->Run(&this->cv, &this->cv_m);

    future = std::async(std::launch::async, [this] {
        unique_lock<mutex> lock(this->cv_m);
        this->cv.wait(lock);
    });

    trigger->IO(this->attribute_string_good, this->value_string_bad);
    this_thread::sleep_for(chrono::milliseconds(50));
    status = future.wait_for(0ms);
    if (status == std::future_status::ready) {
        return false;
    }

    trigger->IO(this->attribute_string_good, this->value_string_good);
    this_thread::sleep_for(chrono::milliseconds(50));
    status = future.wait_for(0ms);
    if (status == std::future_status::ready) {
        return false;
    }

    trigger->IO(this->attribute_string_good, this->value_string_bad);
    this_thread::sleep_for(chrono::milliseconds(50));
    status = future.wait_for(0ms);
    if (status == std::future_status::ready) {
        return false;
    }

    this_thread::sleep_for(chrono::seconds(this->for_long));
    trigger->IO(this->attribute_string_good, this->value_string_good);
    this_thread::sleep_for(chrono::milliseconds(50));
    status = future.wait_for(0ms);
    if (status != std::future_status::ready) {
        return false;
    }

    trigger->Stop();
    delete trigger;
    return true;
}

bool TestTrigger::TestTriggerTime() {
    //Every second
    auto trigger_1 = new TriggerTime(this->alias_good, "*/" + to_string(this->for_long) + " * * * * ?");

    thread t1(&TriggerTime::Run, trigger_1, &this->cv, &this->cv_m);
    t1.detach();
    auto future_1 = std::async(std::launch::async, [this] {
        unique_lock<mutex> lock(this->cv_m);
        this->cv.wait(lock);
    });

    auto status_1 = future_1.wait_for(50ms);
    if (status_1 == std::future_status::ready) {
        return false;
    }

    status_1 = future_1.wait_for(chrono::seconds(this->for_long));
    if (status_1 != std::future_status::ready) {
        return false;
    }

    future_1 = std::async(std::launch::async, [this] {
        unique_lock<mutex> lock(this->cv_m);
        this->cv.wait(lock);
    });

    status_1 = future_1.wait_for(50ms);
    if (status_1 == std::future_status::ready) {
        return false;
    }

    status_1 = future_1.wait_for(chrono::seconds(this->for_long));
    if (status_1 != std::future_status::ready) {
        return false;
    }

    trigger_1->Stop();
    delete trigger_1;

    //Every second one time
    auto trigger_2 = new TriggerTime(this->alias_good, "*/" + to_string(this->for_long) + " * * * * ?", true);

    thread t2(&TriggerTime::Run, trigger_2, &this->cv, &this->cv_m);
    t2.detach();
    auto future_2 = std::async(std::launch::async, [this] {
        unique_lock<mutex> lock(this->cv_m);
        this->cv.wait(lock);
    });

    auto status_2 = future_2.wait_for(50ms);
    if (status_2 == std::future_status::ready) {
        return false;
    }

    status_2 = future_2.wait_for(chrono::seconds(this->for_long));
    if (status_2 != std::future_status::ready) {
        return false;
    }

    future_2 = std::async(std::launch::async, [this] {
        unique_lock<mutex> lock(this->cv_m);
        this->cv.wait(lock);
    });

    status_2 = future_2.wait_for(50ms);
    if (status_2 == std::future_status::ready) {
        return false;
    }

    status_2 = future_2.wait_for(chrono::seconds(this->for_long));
    if (status_2 == std::future_status::ready) {
        return false;
    }

    trigger_2->Stop();
    delete trigger_2;

    //Specific time
    time_t now = time(nullptr);
    tm next_time = *localtime(&now);
    string pattern = to_string(next_time.tm_sec + this->for_long) + " " + to_string(next_time.tm_min) + " " + to_string(next_time.tm_hour) + " " +
                     to_string(next_time.tm_mday) + " " + to_string(next_time.tm_mon + 1) + " ?";

    auto trigger_3 = new TriggerTime(this->alias_good, pattern);

    thread t3(&TriggerTime::Run, trigger_3, &this->cv, &this->cv_m);
    t3.detach();
    auto future_3 = std::async(std::launch::async, [this] {
        unique_lock<mutex> lock(this->cv_m);
        this->cv.wait(lock);
    });

    auto status_3 = future_3.wait_for(50ms);
    if (status_3 == std::future_status::ready) {
        return false;
    }

    status_3 = future_3.wait_for(chrono::seconds(this->for_long));
    if (status_3 != std::future_status::ready) {
        return false;
    }

    trigger_3->Stop();
    delete trigger_3;
    return true;
}

