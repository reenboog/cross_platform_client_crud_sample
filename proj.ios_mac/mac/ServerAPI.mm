
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

#pragma mark - Login/Signup

void ServerAPI::logIn(const string &mail, const string &password, OnLoggedInCallback logInCallback, OnFailedToLogInCallback logInFailureCallback) {
    if(__sharedInstance == nullptr) {
        ServerAPI::sharedInstance();
    }
    
    [PFUser logInWithUsernameInBackground: [NSString stringWithUTF8String: mail.c_str()]
                                 password: [NSString stringWithUTF8String: password.c_str()]
                                    block:^(PFUser *user, NSError *error) {
                                        if(user) {
                                            User::sharedInstance()->setId([[PFUser currentUser].objectId UTF8String]);
                                            // get goals
                                            PFQuery *query = [PFQuery queryWithClassName: @"DailyGoal"];
                                            [query whereKey: @"userId" equalTo: user.objectId];
                                            [query findObjectsInBackgroundWithBlock:^(NSArray *objects, NSError *error) {
                                                if(!error) {
                                                    int goal = kAverageKCaloriesPerDay;
                                                    if([objects count] != 0) {
                                                        PFObject *goalObj = [objects firstObject];
                                                        
                                                        goal = [goalObj[@"caloriesToConsume"] intValue];
                                                    }
                                                    
                                                    User::sharedInstance()->setGoal(goal);
                                                }
                                                
                                                logInCallback();
                                            }];
                                        } else {
                                            NSString *errorString = [error userInfo][@"error"];
                                            
                                            string errorStr = errorString ? [errorString UTF8String] : "Error loading in.";
                                            
                                            logInFailureCallback("error", errorStr);
                                        }
                                    }];
}

void ServerAPI::logout() {
    [PFUser logOut];
    User::purge();
}

void ServerAPI::wakeUp(OnLoggedInCallback logInCallback, OnFailedToLogInCallback failedToWakeUpCallback) {
    if(__sharedInstance == nullptr) {
        ServerAPI::sharedInstance();
    }
    
    PFUser *currentUser = [PFUser currentUser];
    if(currentUser) {
        User::sharedInstance()->setId([currentUser.objectId UTF8String]);
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
            
            string errorStr = errorString ? [errorString UTF8String] : "Error signing up.";
            
            signUpFailureCallback("error", errorStr);
        }
    }];
}

#pragma mark - Roles

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
                
                string errorStr = errorString ? [errorString UTF8String] : "Error applying a role.";
                
                signUpFailureCallback("error", errorStr);
            }
        }];
    }];
}

#pragma mark - Goals

void ServerAPI::createDefaultGoal(OnSignedUpCallback signUpCallback, OnFailedToSignUpCallback signUpFailureCallback) {
    PFObject *goalObj = [PFObject objectWithClassName: @"DailyGoal"];
    
    goalObj[@"caloriesToConsume"] = [NSNumber numberWithInt: User::sharedInstance()->getGoal().getCalories()];
    goalObj[@"userId"] = [NSString stringWithUTF8String: User::sharedInstance()->getId().c_str()];
    
    [goalObj saveInBackgroundWithBlock:^(BOOL succeeded, NSError *error) {
        if(succeeded) {
            signUpCallback();
        } else {
            NSString *errorString = [error userInfo][@"error"];
            
            string errorStr = errorString ? [errorString UTF8String] : "Error creating a goal.";
            
            signUpFailureCallback("error", errorStr);
        }
    }];
}

void ServerAPI::updateGoal(int calories, OnGoalUpdatedCallback goalUpdatedCallback, onFailedToUpdateGoalCallback failedToUpdateGoalCallback) {
    ServerAPI::updateGoalForUser(User::sharedInstance()->getId(), calories, goalUpdatedCallback, failedToUpdateGoalCallback);
}

void ServerAPI::updateGoalForUser(const string &userId, int calories, OnGoalUpdatedCallback goalUpdatedCallback, onFailedToUpdateGoalCallback failedToUpdateGoalCallback) {
    if(__sharedInstance == nullptr) {
        ServerAPI::sharedInstance();
    }
    
    // get goal !
    // set values
    // save in background
    PFQuery *query = [PFQuery queryWithClassName: @"DailyGoal"];
    [query whereKey: @"userId" equalTo: [NSString stringWithUTF8String: userId.c_str()]];
    [query findObjectsInBackgroundWithBlock:^(NSArray *objects, NSError *error) {
        if(!error) {
            PFObject *goalObj = [objects firstObject];
            goalObj[@"caloriesToConsume"] = [NSNumber numberWithInt: calories];
            
            [goalObj saveInBackgroundWithBlock:^(BOOL succeeded, NSError *error) {
                if(succeeded) {
                    goalUpdatedCallback(calories);
                } else {
                    NSString *errorString = [error userInfo][@"error"];
                    
                    string errorStr = errorString ? [errorString UTF8String] : "Error loading in.";

                    failedToUpdateGoalCallback("error", errorStr);
                }
            }];
        } else {
            NSString *errorString = [error userInfo][@"error"];
            
            string errorStr = errorString ? [errorString UTF8String] : "Error updating a goal.";
            failedToUpdateGoalCallback("error", errorStr);
        }
    }];
}

#pragma mark - Meals

void ServerAPI::createMeal(const string &caption, int calories, OnMealCreatedCallback createdCallback, onFailedToCreateMealCallback failedToCreateCallback) {
    if(__sharedInstance == nullptr) {
        ServerAPI::sharedInstance();
    }
    
    // start parse stuff here
    PFObject *meal = [PFObject objectWithClassName: @"Meal"];
    [meal setObject: [NSString stringWithUTF8String: caption.c_str()] forKey: @"caption"];
    [meal setObject: [PFUser currentUser] forKey: @"consumedBy"];
    [meal setObject: [NSNumber numberWithInt: calories] forKey: @"calories"];
    
    [meal saveInBackgroundWithBlock:^(BOOL succeeded, NSError *error) {
        if(!error) {
            createdCallback();
        } else {
            NSString *errorString = [error userInfo][@"error"];
            
            string errorStr = errorString ? [errorString UTF8String] : "Error creating a meal.";
            
            failedToCreateCallback("error", errorStr);
        }
        
    }];
}