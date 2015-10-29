//
//  Goal.h
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 28.10.15.
//
//

#ifndef __ttt_c_tracker__Goal__
#define __ttt_c_tracker__Goal__

#define kMaxKCaloriesPerDay 10000
#define kAverageCaloriesPerDay 2500
#define kMinCaloriesPerDay 800

class Goal {
public:
    virtual ~Goal() {}
    
    Goal(unsigned int calories, const std::string userId);
    
    const std::string& getUserId() const;
    int getCalories() const;
    
    Goal() {
        _calories = kAverageCaloriesPerDay;
    }
private:
    unsigned int _calories;
    std::string _userId;
};

#endif /* defined(__ttt_c_tracker__Goal__) */