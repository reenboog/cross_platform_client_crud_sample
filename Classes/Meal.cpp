//
//  Meal.cpp
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 28.10.15.
//
//

#include "Meal.h"

using namespace std;

Meal::~Meal() {
    delete _consumptionDate;
}

Meal::Meal(const Date &date, unsigned int time, const string &caption, const string userId, unsigned int calories, const string mealId): _consumptionDate(nullptr) {
    _consumptionDate = new Date(date);
    _consumptionTime = time;
    _caption = caption;
    _userId = userId;
    _calories = calories;
    _id = mealId;
}

Meal::Meal(const Meal &r) {
    _consumptionDate = new Date(r.getConsumptioDate());
    _consumptionTime = r.getConsumptionTime();
    _caption = r.getCaption();
    _userId = r.getUserId();
    _calories = r.getCalories();
    _id = r.getId();
}

Meal& Meal::operator=(const Meal &r) {
    if(&r == this) {
        return *this;
    }
    
    _consumptionDate = new Date(r.getConsumptioDate());
    _consumptionTime = r.getConsumptionTime();
    _caption = r.getCaption();
    _userId = r.getUserId();
    _calories = r.getCalories();
    _id = r.getId();
    
    return *this;
}

const Date& Meal::getConsumptioDate() const {
    return *_consumptionDate;
}


unsigned int Meal::getConsumptionTime() const {
    return _consumptionTime;
}

const std::string& Meal::getCaption() const {
    return _caption;
}

const std::string& Meal::getUserId() const {
    return _userId;
}

unsigned int Meal::getCalories() const {
    return _calories;
}

const std::string Meal::getId() const {
    return _id;
}

void Meal::setConsumptionTime(unsigned int time) {
    _consumptionTime = time;
}

void Meal::setCaption(const string &c) {
    _caption = c;
}

void Meal::setCalories(int c) {
    _calories = c;
}