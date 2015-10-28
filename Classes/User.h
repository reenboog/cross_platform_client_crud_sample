//
//  User.h
//  skill_market
//
//  Created by Alex Gievsky on 21.07.15.
//
//

#ifndef __skill_market__User__
#define __skill_market__User__

#include "Goal.h"
#include "MealGroup.h"

class User {
public:
    enum Role {
        UR_User,
        UR_Manager
    };
    
    static void purge();
    
    static User* sharedInstance();
    
    // id
    void setId(const std::string &userId);
    const std::string& getId() const;
    
    // name
    std::string getName() const;
    void setName(const std::string &name);
    
    // roles
    Role getRole() const;
    void setRole(Role role);
    
    // goals
    void setGoal(const Goal &g);
    const Goal& getGoal() const;
    
    // meal
    void addMeal(const Meal &m);
    Meal* getMeal(const std::string &mealId);
    bool setMeal(const std::string &mealId, const Meal &m);
    bool removeMeal(const std::string &mealId);
    
    const MealGroup& getAllMeal() const;
    //
    
    virtual ~User() {}
    
    User(Role role, const std::string &name) {
        _role = role;
        _name = name;
    }
private:
    User() {
        _role = UR_User;
    }
private:
    std::string _name;
    std::string _id;
    Role _role;
    Goal _goal;
    MealGroup _allMealConsumed;
    
    static User *__sharedInstance;
};

#endif /* defined(__skill_market__User__) */
