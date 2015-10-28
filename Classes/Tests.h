//
//  Tests.h
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 28.10.15.
//
//

#ifndef __ttt_c_tracker__Tests__
#define __ttt_c_tracker__Tests__

#include "cocos2d.h"

using namespace cocos2d;

#include "Goal.h"
#include "Meal.h"
#include "MealGroup.h"
#include "User.h"
#include "Date.h"

#define Assert(name, e) {if(!(e)) {CCLOG("FAILED %s", name);} else {CCLOG("passed %s", name);}}
#define Test(name, f) {CCLOG(""); CCLOG("Testing %s", name); f(); CCLOG("----------------------------------------------------------");}

static void testGoals() {
    {
        Goal g;
        Assert("default calories", g.getCalories() == kAverageCaloriesPerDay);
    }
    
    {
        Goal g(100, "123");
        Assert("cal = 100", g.getCalories() == 100);
        Assert("user id check", g.getUserId() == "123");
    }
}

static void testDates() {
    {
        // Date(int year, int month, int day, int hours = 0, int minutes = 0, int seconds = 0);
        Date d(2015, 10, 28);
        Assert("is today valid", d.isValid());
    }
    
    {
        Date d(0, 0, 0);
        Assert("all zeroes", d.isValid() == false);
    }
    
    {
        Date d(-1, -1, -1);
        Assert("all neg", d.isValid() == false);
    }
    
    {
        Date d(2015, 11, 31);
        Assert("invalid year", d.isValid() == false);
    }
    
    {
        Date d(2008, 2, 29);
        Assert("leap year (2008) check", d.isLeapYear());
    }
    
    {
        Date d(2008, 2, 29);
        Assert("is leap year (2008) valid", d.isValid());
    }
    
    {
        Date d(2016, 2, 29);
        Assert("is leap (2016).", d.isLeapYear());
    }
    
    {
        Date d(2015, 2, 29);
        Assert("is invalid (29.02.2015).", d.isValid() == false);
    }
    
    {
        Date d(2015, 12, 32);
        Assert("is invalid (2015.12.32).", d.isValid() == false);
    }
}

static void testMeals() {
    // Meal(const Date &date, unsigned int time, const std::string &caption, const std::string userId, unsigned int calories, const std::string mealId);
    {
        Meal m(Date(2015, 10, 28), 13, "m1", "123", 999, "111");
        
        Assert("consumption time check.", m.getConsumptionTime() == 13);
    }
    
    {
        Meal m(Date(2015, 10, 28), 13, "m1", "123", 999, "111");
        
        Assert("id check", m.getId() == "111");
    }
    
    {
        Meal m(Date(2015, 10, 28), 13, "m1", "123", 999, "111");
        
        Assert("user id check", m.getUserId() == "123");
    }
    
    {
        Meal m(Date(2015, 10, 28), 13, "m1", "123", 999, "111");
        m.setConsumptionTime(20);
        
        Assert("consumption time change", m.getConsumptionTime() == 20);
    }
    
    {
        Meal m(Date(2015, 10, 28), 13, "m1", "123", 999, "111");
        m.setCalories(5000);
        
        Assert("calories change", m.getCalories() == 5000);
    }
    
    {
        Meal m(Date(2015, 10, 28), 13, "m1", "123", 999, "111");
        m.setCaption("qqq");
        
        Assert("caption change", m.getCaption() == "qqq");
    }
}

static void testMealGroups() {
    {
        MealGroup g;
        
        Meal m1(Date(2015, 10, 28), 13, "m1", "123", 999, "111");
        Meal m2(Date(2015, 10, 29), 13, "m2", "124", 111, "222");
        
        g.add(m1);
        g.add(m2);
        
        Assert("get by index", g.get(1).getUserId() == "124");
    }
    
    {
        MealGroup g;
        
        Meal m1(Date(2015, 10, 28), 13, "m1", "123", 999, "111");
        Meal m2(Date(2015, 10, 29), 13, "m2", "124", 111, "222");
        Meal m3(Date(2015, 10, 29), 13, "m2", "125", 111, "223");
        
        g.add(m1);
        g.add(m2);
        g.add(m3);
        
        Assert("get by id", g.getById("222")->getUserId() == "124");
    }
    
    {
        MealGroup g;
        
        Meal m1(Date(2015, 10, 28), 13, "m1", "123", 999, "111");
        Meal m2(Date(2015, 10, 29), 13, "m2", "124", 111, "222");
        Meal m3(Date(2015, 10, 29), 13, "m2", "125", 111, "223");
        
        g.add(m1);
        g.add(m2);
        g.add(m3);
        
        Assert("count", g.size() == 3);
    }
    
    {
        MealGroup g;
        
        Meal m1(Date(2015, 10, 28), 13, "m1", "123", 999, "111");
        Meal m2(Date(2015, 10, 29), 13, "m2", "124", 111, "222");
        Meal m3(Date(2015, 10, 29), 13, "m2", "125", 111, "223");
        
        g.add(m1);
        g.add(m2);
        g.add(m3);
        
        g.update("111", m3);
        
        Assert("update", g.get(0).getUserId() == "125");
    }
    
    {
        MealGroup g;
        
        Meal m1(Date(2015, 10, 28), 13, "m1", "123", 999, "111");
        Meal m2(Date(2015, 10, 29), 13, "m2", "124", 111, "222");
        Meal m3(Date(2015, 10, 29), 13, "m2", "125", 111, "223");
        
        g.add(m1);
        g.add(m2);
        g.add(m3);
        
        Assert("fake update", g.update("111111", m3) == false);
    }
    
    {
        MealGroup g;
        
        Meal m1(Date(2015, 10, 28), 13, "m1", "123", 999, "111");
        Meal m2(Date(2015, 10, 29), 13, "m2", "124", 111, "222");
        Meal m3(Date(2015, 10, 29), 13, "m2", "125", 111, "223");
        
        g.add(m1);
        g.add(m2);
        g.add(m3);
        
        g.remove("222");
        
        Assert("delete", g.size() == 2);
    }
    
    {
        MealGroup g;
        
        Meal m1(Date(2015, 10, 28), 13, "m1", "123", 999, "111");
        Meal m2(Date(2015, 10, 29), 13, "m2", "124", 111, "222");
        Meal m3(Date(2015, 10, 29), 13, "m2", "125", 111, "223");
        
        g.add(m1);
        g.add(m2);
        g.add(m3);
        
        g.update("111111", m3);
        
        Assert("fake delete", g.size() == 3);
    }
}

static  void test() {
    Test("GOALS", testGoals);
    Test("DATES", testDates);
    Test("MEALS", testMeals);
    Test("MEAL GROUPS", testMealGroups);
}

#endif /* defined(__ttt_c_tracker__Tests__) */
