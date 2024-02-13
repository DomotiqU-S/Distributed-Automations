//
// Created by talgarr on 01/02/24.
//

#include "ConditionTime.hpp"

ConditionTime::ConditionTime(string alias, tm after, tm before, vector<string> weekday) : Condition(alias) {
    this->after = after;
    this->before = before;
    this->weekday = std::move(weekday);

}

bool ConditionTime::Verify(string alias) {
    time_t now = time(nullptr);
    tm *ltm = localtime(&now);
    if (ltm->tm_hour < after.tm_hour and ltm->tm_hour > before.tm_hour) {
        return false;
    }
    if (ltm->tm_min < after.tm_min and ltm->tm_min > before.tm_min) {
        return false;
    }
    if (weekday.empty()) {
        return true;
    }
    for (const auto &i : weekday) {
        switch (ltm->tm_wday) {
            case 0:
                if (i == "sun")
                    return true;
                break;
            case 1:
                if (i == "mon")
                    return true;
                break;
            case 2:
                if (i == "tue")
                    return true;
                break;
            case 3:
                if (i == "wed")
                    return true;
                break;
            case 4:
                if (i == "thu")
                    return true;
                break;
            case 5:
                if (i == "fri")
                    return true;
                break;
            case 6:
                if (i == "sat")
                    return true;
                break;
            default:
                return false;
        }
    }
    return false;
}

ConditionTime::~ConditionTime() = default;
