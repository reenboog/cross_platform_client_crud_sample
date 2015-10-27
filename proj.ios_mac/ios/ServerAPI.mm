
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
void ServerAPI::logIn(const string &mail, const string &password, OnLoggedInCallback logInCallback, OnFailedToLogInCallback logInFailureCallback) {
    if(__sharedInstance == nullptr) {
        ServerAPI::sharedInstance();
    }
    
    [PFUser logInWithUsernameInBackground: [NSString stringWithUTF8String: mail.c_str()]
                                 password: [NSString stringWithUTF8String: password.c_str()]
                                    block:^(PFUser *user, NSError *error) {
                                        if(user) {
                                            logInCallback();
                                        } else {
                                            NSString *errorString = [error userInfo][@"error"];

                                            logInFailureCallback("error", [errorString UTF8String]);
                                        }
                                    }];
}

void ServerAPI::wakeUp(OnLoggedInCallback logInCallback, OnFailedToLogInCallback failedToWakeUpCallback) {
    if(__sharedInstance == nullptr) {
        ServerAPI::sharedInstance();
    }
    
    PFUser *currentUser = [PFUser currentUser];
    if(currentUser) {
        logInCallback();
    } else {
        failedToWakeUpCallback("", "");
    }
}

void ServerAPI::signUp(const string &mail, const string &password, OnSignedUpCallback signUpCallback, OnFailedToSignUpCallback signUpFailureCallback) {
    if(__sharedInstance == nullptr) {
        ServerAPI::sharedInstance();
    }
    
    PFUser *user = [PFUser user];
    user.username = [NSString stringWithUTF8String: mail.c_str()];
    user.password = [NSString stringWithUTF8String: password.c_str()];
    
    [user signUpInBackgroundWithBlock: ^(BOOL succeeded, NSError *error) {
        if(!error) {
            signUpCallback();
        } else {
            NSString *errorString = [error userInfo][@"error"];
            
            signUpFailureCallback("error", [errorString UTF8String]);
        }
    }];
}
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