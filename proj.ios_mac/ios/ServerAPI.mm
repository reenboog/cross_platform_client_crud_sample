//
//  SkillMarket.mm
//  skill_market
//
//  Created by Alex Gievsky on 15.07.15.
//
//

#include "ServerAPI.h"

#include "User.h"
#include "Skills.h"

#include "json/document.h"

#define kAPIDebugMode true

// API nodes
#define kAPIBaseURL "http://skillsmarketbackend.herokuapp.com/"
#define kAPINodeLogIn "login/"
#define kAPINodeSignUp "signup/"
#define kAPINodeUser "user/"
#define kAPINodeSkills "skill/"

#define SM_API_NODE(node) (string(kAPIBaseURL) + string(node))
//
#define kVKLogInMethod "vk"

#define kVKAppSecretKey "6WFW8yufwMmcQsiDUQdH"
#define kVKAppId "4992348"


#define kUserIdJSONKey "user_id"
#define kUserAccessTokenJSONKey "access_token"

#define kStatusJSONKey "status"
#define kUserNameJSONKey "fname"
#define kUserLastNameJSONKey "lname"
#define kDescriptionJSONKey "description"
#define kResponseStatusOk "ok"
#define kResponseStatusFail "fail"

#define kDefaultsAccessTokenKey "sm_access_token_key"
#define kDefaultsUserIdKey "sm_user_id_key"

using std::string;
using std::function;

using namespace cocos2d;
using namespace network;

ServerAPI* ServerAPI::__sharedInstance = nullptr;

#pragma mark - ServerAPI

ServerAPI::~ServerAPI() {
    
}

ServerAPI::ServerAPI() {
    
}

ServerAPI* ServerAPI::sharedInstance() {
    if(__sharedInstance == nullptr) {
        __sharedInstance = new ServerAPI();
        
        __sharedInstance->_accessToken = UserDefault::getInstance()->getStringForKey(kDefaultsAccessTokenKey, "");
        __sharedInstance->_userId = UserDefault::getInstance()->getStringForKey(kDefaultsUserIdKey, "");
    }
    
    return __sharedInstance;
}

void ServerAPI::purge() {
    delete __sharedInstance;
    __sharedInstance = nullptr;
}

void ServerAPI::onHttpResponse(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response) {
}

void ServerAPI::onLoggedInWithSocialNetwork(const string &snUserId, const string &snAccessToken) {
};


void ServerAPI::logIn(OnLoggedInWithAPICallback logInCallback, OnFailedToLogInWithAPICallback logInFailureCallback) {
    if(__sharedInstance == nullptr) {
        ServerAPI::sharedInstance();
    }
}

void ServerAPI::wakeUp(OnLoggedInWithAPICallback logInCallback, OnFailedToLogInWithAPICallback failedToWakeUpCallback) {
}

void ServerAPI::signUp(OnSignedUpCallback signUpCallback, OnFailedToSignUpCallback signUpFailureCallback) {
    if(__sharedInstance == nullptr) {
        ServerAPI::sharedInstance();
    }
}

void ServerAPI::fetchUserNameAndLastName(OnUserNameAndLastNameFetchedCallback userNameFetchedCallback,
                              OnFailedToFetchUserNameAndLastNameCallback userNameFetchFailureCallback) {
    
    if(__sharedInstance == nullptr) {
        ServerAPI::sharedInstance();
    }
    
    
}

void ServerAPI::fetchAllSkills(OnSkillsFetchedCallback onSkillsFetchedCallback,
                                    OnFailedToFetchSkillsCallback onFailedToFetchSkillsCallback) {
    if(__sharedInstance == nullptr) {
        ServerAPI::sharedInstance();
    }
}

void ServerAPI::fetchUserSkills(OnSkillsFetchedCallback onSkillsFetchedCallback,
                            OnFailedToFetchSkillsCallback onFailedToFetchSkillsCallback) {
    if(__sharedInstance == nullptr) {
        ServerAPI::sharedInstance();
    }
}