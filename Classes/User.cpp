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

std::string User::getLastName() const {
    return _lastName;
}

void User::setLastName(const string &lastName) {
    _lastName = lastName;
}

void User::save() {
    // user Defaults here
    //UserDefault::getInstance()
}