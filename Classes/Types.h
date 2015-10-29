
#ifndef TTT_Types_h
#define TTT_Types_h

typedef std::function <void (void)> OnLoggedInCallback;
typedef std::function <void (const std::string&, const std::string&)> OnFailedToLogInCallback;

typedef std::function <void (void)> OnSignedUpCallback;
typedef std::function <void (const std::string&, const std::string&)> OnFailedToSignUpCallback;
typedef std::function <void (void)> OnLoggedOutCallback;

typedef std::function <void (void)> OnMealCreatedCallback;
typedef std::function <void (const std::string&, const std::string&)> onFailedToCreateMealCallback;

typedef std::function <void (unsigned int)> OnGoalUpdatedCallback;
typedef std::function <void (const std::string&, const std::string&)> onFailedToUpdateGoalCallback;

//
//typedef std::function <void (const std::string&, const std::string&)> OnUserNameAndLastNameFetchedCallback;
//typedef std::function <void (const std::string&, const std::string&)> OnFailedToFetchUserNameAndLastNameCallback;
//
//
//typedef std::function <void (void)> OnSkillsFetchedCallback;
//typedef std::function <void (const std::string&, const std::string&)> OnFailedToFetchSkillsCallback;

#endif