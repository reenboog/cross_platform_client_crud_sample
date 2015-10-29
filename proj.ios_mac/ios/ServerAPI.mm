
#include "ServerAPI.h"

#include "User.h"

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
            // get user id
            NSString *userId = [PFUser currentUser].objectId;
            User::sharedInstance()->setId([userId UTF8String]);
            
            ServerAPI::sharedInstance()->applyDefaultRole(signUpCallback, signUpFailureCallback);
        } else {
            NSString *errorString = [error userInfo][@"error"];
            
            signUpFailureCallback("error", [errorString UTF8String]);
        }
    }];
}

void ServerAPI::createMeal(const string &caption, int calories, OnMealCreatedCallback createdCallback, onFailedToCreateMeal failedToCreateCallback) {
    if(__sharedInstance == nullptr) {
        ServerAPI::sharedInstance();
    }
    
    //
    
    // start parse stuff here
    PFObject *meal = [PFObject objectWithClassName: @"Meal"];
    [meal setObject: [NSString stringWithUTF8String: caption.c_str()] forKey: @"caption"];
    [meal setObject: [PFUser currentUser] forKey: @"consumedBy"];
    [meal setObject: [NSNumber numberWithInt: calories] forKey: @"calories"];
    
    [meal saveInBackgroundWithBlock:^(BOOL succeeded, NSError *error) {
        // Kick off the new query, refresh the table, and then - once that's all
        // taken care of - re-enable the item entry UI.
        if(!error) {
            createdCallback();
        } else {
            NSString *errorString = [error userInfo][@"error"];
            
            failedToCreateCallback("error", [errorString UTF8String]);
        }
        
    }];
}

void ServerAPI::applyDefaultRole(OnSignedUpCallback signUpCallback, OnFailedToSignUpCallback signUpFailureCallback) {
    PFQuery *queryRole = [PFRole query];
    
    [queryRole whereKey: @"name" equalTo: @"user"];
    [queryRole getFirstObjectInBackgroundWithBlock: ^(PFObject *object, NSError *error) {
        PFRole *role = (PFRole *)object;
        
        [role.users addObject: [PFUser currentUser]];
        [role saveInBackgroundWithBlock:^(BOOL succeeded, NSError *error) {
            if(!error) {
                User::sharedInstance()->setRole(User::Role::UR_User);
                
                ServerAPI::sharedInstance()->createDefaultGoal(signUpCallback, signUpFailureCallback);
            } else {
                NSString *errorString = [error userInfo][@"error"];
                
                signUpFailureCallback("error", [errorString UTF8String]);
            }
        }];
    }];
}

void ServerAPI::createDefaultGoal(OnSignedUpCallback signUpCallback, OnFailedToSignUpCallback signUpFailureCallback) {
    PFObject *goalObj = [PFObject objectWithClassName: @"DailyGoal"];

    goalObj[@"caloriesToConsume"] = [NSNumber numberWithInt: User::sharedInstance()->getGoal().getCalories()];
    goalObj[@"userId"] = [NSString stringWithUTF8String: User::sharedInstance()->getId().c_str()];

    [goalObj saveInBackgroundWithBlock:^(BOOL succeeded, NSError *error) {
        if(succeeded) {
            signUpCallback();
        } else {
            NSString *errorString = [error userInfo][@"error"];
            signUpFailureCallback("error", [errorString UTF8String]);
        }
    }];
}