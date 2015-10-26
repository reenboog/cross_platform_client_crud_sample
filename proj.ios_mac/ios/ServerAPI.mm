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

#import <Parse/Parse.h>

using namespace cocos2d;
using namespace network;
using namespace std;

ServerAPI* ServerAPI::__sharedInstance = nullptr;

#pragma mark - ServerAPI

ServerAPI::~ServerAPI() {
    
}

ServerAPI::ServerAPI() {
    
}

ServerAPI* ServerAPI::sharedInstance() {
    if(__sharedInstance == nullptr) {
        __sharedInstance = new ServerAPI();
        
        [Parse setApplicationId: [NSString stringWithUTF8String: kAppKey]
                      clientKey: [NSString stringWithUTF8String: kClientKey]];
    }
    
    return __sharedInstance;
}

void ServerAPI::purge() {
    delete __sharedInstance;
    __sharedInstance = nullptr;
}

//void ServerAPI::onHttpResponse(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response) {
//}
//
//void ServerAPI::onLoggedInWithSocialNetwork(const string &snUserId, const string &snAccessToken) {
//};
//
//
//void ServerAPI::logIn(OnLoggedInCallback logInCallback, OnFailedToLogInCallback logInFailureCallback) {
//    if(__sharedInstance == nullptr) {
//        ServerAPI::sharedInstance();
//    }
//}
//
void ServerAPI::wakeUp(OnLoggedInCallback logInCallback, OnFailedToLogInCallback failedToWakeUpCallback) {
    if(__sharedInstance == nullptr) {
        ServerAPI::sharedInstance();
    }
    
    
}
//
//void ServerAPI::signUp(OnSignedUpCallback signUpCallback, OnFailedToSignUpCallback signUpFailureCallback) {
//    if(__sharedInstance == nullptr) {
//        ServerAPI::sharedInstance();
//    }
//}
//
//void ServerAPI::fetchUserNameAndLastName(OnUserNameAndLastNameFetchedCallback userNameFetchedCallback,
//                              OnFailedToFetchUserNameAndLastNameCallback userNameFetchFailureCallback) {
//    
//    if(__sharedInstance == nullptr) {
//        ServerAPI::sharedInstance();
//    }
//    
//    
//}
//
//void ServerAPI::fetchAllSkills(OnSkillsFetchedCallback onSkillsFetchedCallback,
//                                    OnFailedToFetchSkillsCallback onFailedToFetchSkillsCallback) {
//    if(__sharedInstance == nullptr) {
//        ServerAPI::sharedInstance();
//    }
//}
//
//void ServerAPI::fetchUserSkills(OnSkillsFetchedCallback onSkillsFetchedCallback,
//                            OnFailedToFetchSkillsCallback onFailedToFetchSkillsCallback) {
//    if(__sharedInstance == nullptr) {
//        ServerAPI::sharedInstance();
//    }
//}