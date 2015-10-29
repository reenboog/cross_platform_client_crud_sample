
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
    
    //
    
    // start parse stuff here
    
    int consumedAtTime = Date::time();
    Date consumedAtDate = Date::now();
    
    // prepare NSDate
    //NSString *currentStrDate = @"2008/08/18 13-45-01";
    NSString *currentStrDate = [NSString stringWithFormat: @"%i/%i/%i", consumedAtDate.getYear(), consumedAtDate.getMonth(), consumedAtDate.getDay()];
    NSDateFormatter *dateFormatterStr = [[NSDateFormatter new] autorelease];
    
    [dateFormatterStr setTimeZone: [NSTimeZone timeZoneForSecondsFromGMT: 0]];
    [dateFormatterStr setDateFormat: @"yyyy/MM/dd"];
    
    NSDate *dateFromStr = [dateFormatterStr dateFromString: currentStrDate];
    
    //
    
    PFObject *meal = [PFObject objectWithClassName: @"Meal"];
    [meal setObject: [NSString stringWithUTF8String: caption.c_str()] forKey: @"caption"];
    [meal setObject: [NSString stringWithUTF8String: User::sharedInstance()->getId().c_str()] forKey: @"consumedBy"];
    [meal setObject: [NSNumber numberWithInt: calories] forKey: @"calories"];
    [meal setObject: [NSNumber numberWithInt: consumedAtTime] forKey: @"consumedAtTime"];
    [meal setObject: dateFromStr forKey: @"consumedAtDate"];
    
    
    [meal saveInBackgroundWithBlock:^(BOOL succeeded, NSError *error) {
        // Kick off the new query, refresh the table, and then - once that's all
        // taken care of - re-enable the item entry UI.
        if(!error) {
            //Meal(const Date &date, unsigned int time, const std::string &caption, const std::string userId, unsigned int calories, const std::string mealId);
            string mealId = meal.objectId ? [meal.objectId UTF8String] : "unknown";
            
            Meal newMeal(consumedAtDate, consumedAtTime, caption, User::sharedInstance()->getId(), calories, mealId);
            
            createdCallback(newMeal);
        } else {
            NSString *errorString = [error userInfo][@"error"];
            
            string errorStr = errorString ? [errorString UTF8String] : "Error creating a meal.";
            
            failedToCreateCallback("error", errorStr);
        }
        
    }];
}

void ServerAPI::fetchAvailableMeals(OnMealsFetchedCallback mealsFetchedCallback, onFailedToFetchMealsCallback mealsFetchFailedCallback) {
    if(__sharedInstance == nullptr) {
        ServerAPI::sharedInstance();
    }
    
    PFQuery *query = [PFQuery queryWithClassName: @"Meal"];
    [query whereKey: @"consumedBy" equalTo: [NSString stringWithUTF8String: User::sharedInstance()->getId().c_str()]];
    [query orderByAscending: @"consumedAtDate"];
    [query addAscendingOrder: @"consumedAtTime"];
    [query findObjectsInBackgroundWithBlock:^(NSArray *objects, NSError *error) {
        if(!error) {
            for(PFObject *object in objects) {
                int time = object[@"consumedAtTime"] ? [object[@"consumedAtTime"] intValue] : 0;
                string caption = object[@"caption"] ? [object[@"caption"] UTF8String] : "undefined";
                string userId = object[@"consumedBy"] ? [object[@"consumedBy"] UTF8String] : "user x";
                string mealId = object.objectId ? [object.objectId UTF8String] : "unknown id";
                int calories = object[@"calories"] ? [object[@"calories"] intValue] : 0;
                
                NSDate *date = object[@"consumedAtDate"] ? object[@"consumedAtDate"] : [NSDate date];
                
                NSDateComponents *components = [[NSCalendar currentCalendar] components: NSCalendarUnitDay | NSCalendarUnitMonth | NSCalendarUnitYear
                                                                               fromDate: date];
                
                int day = [components day];
                int month = [components month];
                int year = [components year];
                
                // Meal(const Date &date, unsigned int time, const std::string &caption, const std::string userId, unsigned int calories, const std::string mealId);
                Meal meal(Date(year, month, day), time, caption, userId, calories, mealId);
                
                User::sharedInstance()->addMeal(meal);
            }
            
            mealsFetchedCallback(User::sharedInstance()->getAllMeal());
        } else {
            NSString *errorString = [error userInfo][@"error"];
            
            string errorStr = errorString ? [errorString UTF8String] : "Error fetching meals.";
            
            mealsFetchFailedCallback("error", errorStr);
        }
    }];
}