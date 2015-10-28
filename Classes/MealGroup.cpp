//
//  MealGroup.cpp
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 28.10.15.
//
//

#include "MealGroup.h"

void MealGroup::add(const Meal &m) {
    _meals.push_back(m);
}

const Meal& MealGroup::get(unsigned int idx) const {
    return _meals[idx];
}

unsigned int MealGroup::size() const {
    return _meals.size();
}

Meal* MealGroup::getById(const std::string &mealId) {
    for(int i = 0; i < _meals.size(); ++i) {
        if(_meals[i].getId() == mealId) {
            return &(_meals[i]);
        }
    }
    
    return nullptr;
}

bool MealGroup::update(const std::string &mealId, const Meal &m) {
    Meal *found = this->getById(mealId);
    
    if(found == nullptr) {
        return false;
    }
    
    *found = m;
    
    return true;
}

bool MealGroup::remove(const std::string &mealId) {
    for(int i = 0; i < _meals.size(); ++i) {
        if(_meals[i].getId() == mealId) {
            _meals.erase(_meals.begin() + i);
            
            return true;
        }
    }
    
    return false;
}