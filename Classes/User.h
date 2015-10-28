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
    enum Role {
        UR_User,
        UR_Manager
    };
    
    static void purge();
    
    static User* sharedInstance();
    
    std::string getName() const;
    void setName(const std::string &name);
    
    Role getRole() const;
    void setRole(Role role);
    
    User(Role role, const std::string &name) {
        _role = role;
        _name = name;
    }
private:
    virtual ~User() {}
    User() {
        _role = UR_User;
    }
private:
    std::string _name;
    Role _role;
    
    static User *__sharedInstance;
};

#endif /* defined(__skill_market__User__) */
