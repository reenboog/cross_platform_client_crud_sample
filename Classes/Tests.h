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

static  void test() {
    Test("GOALS", testGoals);
    Test("DATES", testDates);
}

#endif /* defined(__ttt_c_tracker__Tests__) */
