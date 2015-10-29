//
//  Goal.cpp
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 28.10.15.
//
//

#include "Goal.h"

using namespace std;

Goal::Goal(unsigned int calories, const std::string userId) {
    _calories = calories;
    _userId = userId;
}

const string& Goal::getUserId() const {
    return _userId;
}

int Goal::getCalories() const {
    return _calories;
}

void Goal::setCalories(int c) {
    _calories = c;
}