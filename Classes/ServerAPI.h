//
//  SkillMarketAPI.h
//  skill_market
//
//  Created by Alex Gievsky on 15.07.15.
//
//

#ifndef TTT_SERVER_API_H
#define TTT_SERVER_API_H

#include "network/HttpCLient.h"

#include "Types.h"

#define kAppKey "GEL3070XbPLwO7PTUXwOkeXg5CmH84rC4e9wIlJD"
#define kClientKey "P11fWn0ifZpsdRm7ysAX6I9ENgkQbNmB0xUgRMkz"

class ServerAPI {
public:
    enum SessionState {
        SS_LoggedIn,
        SS_LoggedOut
    };
public:
    static void purge();

    static void wakeUp(OnLoggedInCallback logInCallback, OnFailedToLogInCallback failedToWakeUpCallback);
    static void logIn(const std::string &mail, const std::string &password, OnLoggedInCallback logInCallback, OnFailedToLogInCallback loginFailureCallback);
    static void logout();
    static void signUp(const std::string &mail, const std::string &password, OnSignedUpCallback signUpCallback, OnFailedToSignUpCallback signUpFailureCallback);
    
    // meals
    static void createMeal(const std::string &caption, int calories, OnMealCreatedCallback createdCallback, onFailedToCreateMealCallback failedToCreateCallback);
    
    // goals
    static void updateGoal(int calories, OnGoalUpdatedCallback goalUpdatedCallback, onFailedToUpdateGoalCallback failedToUpdateGoalCallback);
    static void updateGoalForUser(const std::string &userId, int calories, OnGoalUpdatedCallback goalUpdatedCallback, onFailedToUpdateGoalCallback failedToUpdateGoalCallback);
    
    static ServerAPI* sharedInstance();
private:
    void applyDefaultRole(OnSignedUpCallback signUpCallback, OnFailedToSignUpCallback signUpFailureCallback);
    void createDefaultGoal(OnSignedUpCallback signUpCallback, OnFailedToSignUpCallback signUpFailureCallback);
private:
    
    ServerAPI();
    virtual ~ServerAPI();
    
//    void onLoggedInWithSocialNetwork(const std::string &snUserId, const std::string &snAccessToken);
public:
//    void onHttpResponse(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
private:
    
//    OnLoggedInCallback _logInCallback;
//    OnFailedToLogInCallback _logInFailureCallback;
    
    static ServerAPI *__sharedInstance;
};

#endif