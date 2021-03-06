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
        Assert("default calories", g.getCalories() == kAverageKCaloriesPerDay);
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
    
    {
        Assert("time check: 1:32", Date::timeStrForSeconds(5520) == "1:32");
    }
    
    {
        Assert("time check: 0:00", Date::timeStrForSeconds(0) == "0:00");
    }
    
    {
        Assert("time check: 11:02", Date::timeStrForSeconds(39720) == "11:02");
    }
    
    {
        Assert("time check: 11:02 (additional seconds)", Date::timeStrForSeconds(39725) == "11:02");
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

static void testUsers() {
    {
        User u(User::Role::UR_User, "alex");
        
        Assert("role", u.getRole() == User::Role::UR_User);
    }
    
    {
        User u(User::Role::UR_User, "alex");
        
        Assert("name", u.getName() == "alex");
    }
    
    {
        User u(User::Role::UR_User, "alex");
        u.setName("max");
        
        Assert("set name", u.getName() == "max");
    }
    
    {
        User u(User::Role::UR_User, "alex");
        u.setRole(User::Role::UR_Manager);
        
        Assert("set role", u.getRole() == User::Role::UR_Manager);
    }
    
    {
        User u(User::Role::UR_User, "alex");
        u.setRole(User::Role::UR_Manager);
        
        Assert("default goal", u.getGoal().getCalories() == kAverageKCaloriesPerDay);
    }
    
    {
        User u(User::Role::UR_User, "alex");
        
        u.setId("111");
        
        Assert("set user id", u.getId() == "111");
    }
    
    {
        User u(User::Role::UR_User, "alex");
        u.setId("333");
        
        u.setGoal(3000);
        
        Assert("user-goal id sync", u.getGoal().getCalories() == 3000);
    }
    
    {
        User u(User::Role::UR_User, "alex");
        u.setId("qq");
        
        u.addMeal(Meal(Date(2015, 2, 1), 12, "Meal 1", "qq", 111, "1"));
        u.addMeal(Meal(Date(2015, 3, 1), 120, "Meal 2", "qq", 500, "2"));
        u.addMeal(Meal(Date(2015, 4, 1), 120, "Meal 3", "qq", 99, "3"));
        
        Assert("add 3 meals", u.getAllMeal().size() == 3);
    }
    
    {
        User u(User::Role::UR_User, "alex");
        u.setId("qq");
        
        u.addMeal(Meal(Date(2015, 2, 1), 12, "Meal 1", "qq", 111, "1"));
        u.addMeal(Meal(Date(2015, 3, 1), 120, "Meal 2", "qq", 500, "2"));
        u.addMeal(Meal(Date(2015, 4, 1), 120, "Meal 3", "qq", 99, "3"));
        
        u.setMeal("2", Meal(Date(2015, 4, 10), 0, "Meal Updated", "qq", 9999, "2"));
        
        Assert("update meal", u.getMeal("2")->getCaption() == "Meal Updated");
    }
    
    {
        User u(User::Role::UR_User, "alex");
        u.setId("qq");
        
        u.addMeal(Meal(Date(2015, 2, 1), 12, "Meal 1", "qq", 111, "1"));
        u.addMeal(Meal(Date(2015, 3, 1), 120, "Meal 2", "qq", 500, "2"));
        u.addMeal(Meal(Date(2015, 4, 1), 120, "Meal 3", "qq", 99, "3"));
        
        u.removeMeal("2");
        
        Assert("delete meal", u.getMeal("2") == nullptr && u.getAllMeal().size() == 2);
    }
}

static  void test() {
    Test("GOALS", testGoals);
    Test("DATES", testDates);
    Test("MEALS", testMeals);
    Test("MEAL GROUPS", testMealGroups);
    Test("USERS", testUsers);
}

#endif /* defined(__ttt_c_tracker__Tests__) */
