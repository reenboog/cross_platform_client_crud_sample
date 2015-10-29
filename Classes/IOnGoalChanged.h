//
//  IOnGoalChanged.h
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 29.10.15.
//
//

#ifndef ttt_c_tracker_IOnGoalChanged_h
#define ttt_c_tracker_IOnGoalChanged_h

class IOnGoalChanged {
public:
    virtual void onGoalChanged(int newGoal) = 0;
};

class IOnGoalChangedForUser {
public:
    virtual void onGoalChanged(const std::string &userId, int newGoal) = 0;
};

#endif
