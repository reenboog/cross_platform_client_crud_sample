//
//  MealGroup.h
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 28.10.15.
//
//

#ifndef __ttt_c_tracker__MealGroup__
#define __ttt_c_tracker__MealGroup__

#include "Meal.h"
#include "Date.h"

#include <vector>

class MealGroup {
public:
    virtual ~MealGroup() {}
    MealGroup() {}
    
    void add(const Meal &m);
    const Meal& get(unsigned int idx) const;
    
    // basic crud operations
    Meal* getById(const std::string &mealId);
    
    MealGroup selectForDate(const Date &date) const;
    MealGroup selectBetweenDates(const Date &dateFrom, const Date &dateTo, int timeFrom = 0, int timeTo = 24 * 3600) const;
    
    int getTotalCalories() const;

    bool update(const std::string &mealId, const Meal &m);
    bool remove(const std::string &mealId);
    //
    
    unsigned int size() const;
private:
    std::vector<Meal> _meals;
};

#endif /* defined(__ttt_c_tracker__MealGroup__) */