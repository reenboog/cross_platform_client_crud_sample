//
//  Meal.h
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 28.10.15.
//
//

#ifndef __ttt_c_tracker__Meal__
#define __ttt_c_tracker__Meal__

#include "Date.h"

class Meal {
public:
    virtual ~Meal();
    
    Meal(const Date &date, unsigned int time, const std::string &caption, const std::string userId, unsigned int calories, const std::string mealId);
    
    Meal(const Meal &r);
    Meal& operator=(const Meal &r);
    
    //
    void setConsumptionTime(unsigned int time);
    void setCaption(const std::string &c);
    void setCalories(int c);
    //
    
    const Date& getConsumptioDate() const;
    unsigned int getConsumptionTime() const;
    const std::string& getCaption() const;
    const std::string& getUserId() const;
    unsigned int getCalories() const;
    const std::string getId() const;
private:
    Meal() {}
private:
    Date *_consumptionDate;
    unsigned int _consumptionTime;
    std::string _caption;
    std::string _userId;
    unsigned int _calories;

    std::string _id;
};

#endif /* defined(__ttt_c_tracker__Meal__) */
