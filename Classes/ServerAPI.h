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

#define kResponseStatusUserDoesNotExist "user_not_found"
#define kResponseStatusUserAlreadyExists "user_already_exists"

class ServerAPI {
public:
    enum SessionState {
        SS_LoggedIn,
        SS_LoggedOut
    };
public:
    static void purge();

    static void wakeUp(OnLoggedInWithAPICallback logInCallback, OnFailedToLogInWithAPICallback failedToWakeUpCallback);
    static void logIn(OnLoggedInWithAPICallback logInCallback, OnFailedToLogInWithAPICallback loginFailureCallback);
    
    static void fetchUserNameAndLastName(OnUserNameAndLastNameFetchedCallback userNameFetchedCallback,
                                         OnFailedToFetchUserNameAndLastNameCallback userNameFetchFailureCallback);
    
    static void fetchAllSkills(OnSkillsFetchedCallback onSkillsFetchedCallback,
                               OnFailedToFetchSkillsCallback onFailedToFetchSkillsCallback);
    
    static void fetchUserSkills(OnSkillsFetchedCallback onSkillsFetchedCallback,
                                OnFailedToFetchSkillsCallback onFailedToFetchSkillsCallback);
    
    static void signUp(OnSignedUpCallback signUpCallback, OnFailedToSignUpCallback signUpFailureCallback);
    
    static ServerAPI* sharedInstance();
private:
    
    ServerAPI();
    virtual ~ServerAPI();
    
    void onLoggedInWithSocialNetwork(const std::string &snUserId, const std::string &snAccessToken);
public:
    void onHttpResponse(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
private:
    std::string _accessToken;
    std::string _userId;
    
    OnLoggedInWithAPICallback _logInCallback;
    OnFailedToLogInWithAPICallback _logInFailureCallback;
    
    static ServerAPI *__sharedInstance;
};

#endif