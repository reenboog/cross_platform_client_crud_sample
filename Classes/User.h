//
//  User.h
//  skill_market
//
//  Created by Alex Gievsky on 21.07.15.
//
//

#ifndef __skill_market__User__
#define __skill_market__User__

class User {
public:
    static void purge();
    
    static User* sharedInstance();
    
    std::string getName() const;
    void setName(const std::string &name);
    
    std::string getLastName() const;
    void setLastName(const std::string &lastName);
    
    void save();
private:
    virtual ~User() {}
    User() {}
private:
    std::string _name;
    std::string _lastName;
    
    static User *__sharedInstance;
};

#endif /* defined(__skill_market__User__) */
