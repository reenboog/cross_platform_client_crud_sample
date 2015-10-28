//
//  User.cpp
//  skill_market
//
//  Created by Alex Gievsky on 21.07.15.
//
//

#include "User.h"

using std::string;

User* User::__sharedInstance = nullptr;

User* User::sharedInstance() {
    if(__sharedInstance == nullptr) {
        __sharedInstance = new User();
    }
    
    return __sharedInstance;
}

void User::purge() {
    if(__sharedInstance != nullptr) {
        __sharedInstance = nullptr;
        delete __sharedInstance;
    }
}

string User::getName() const {
    return _name;
}

void User::setName(const string &name) {
    _name = name;
}

#pragma mark - Roles

User::Role User::getRole() const {
    return _role;
}

void User::setRole(User::Role role) {
    _role = role;
}

#pragma mark - Meal group

void User::addMeal(const Meal &m) {
    _allMealConsumed.add(m);
}

Meal* User::getMeal(const std::string &mealId) {
    return _allMealConsumed.getById(mealId);
}

bool User::setMealConsumed(const std::string &mealId, const Meal &m) {
    return _allMealConsumed.update(mealId, m);
}

bool User::removeMeal(const std::string &mealId) {
    return _allMealConsumed.remove(mealId);
}