//
//  Skills.h
//  skill_market
//
//  Created by Alex Gievsky on 23.07.15.
//
//

#ifndef __skill_market__Skills__
#define __skill_market__Skills__

#include <map>

class Skill {
public:
    Skill(int skillId, const std::string &title, const std::string &description) {
        _title = title;
        _id = skillId;
        _description = description;
    }
    
    std::string getTitle() const {
        return _title;
    }
    
    int getId() const {
        return _id;
    }
    
    std::string getDescription() const {
        return _description;
    }
private:
    std::string _title;
    std::string _description;
    int _id;
};

class UserSkill {
public:
    UserSkill(const std::string &title, int level): _skill(0, title, "") {
        _level = level;
    }
    
    int getLevel() const {
        return _level;
    }
    
    std::string getTitle() const {
        return _skill.getTitle();
    }
    
private:
    Skill _skill;
    int _level;
};

class Skills {
public:
    static Skills* sharedInstance();
private:
    Skills(){}
    virtual ~Skills();
public:
    void add(int skillId, std::string &title, std::string &description);
    Skill* get(int skillId) const;
private:
    std::map<int, Skill*> _skills;
    
    static Skills *__sharedInstance;
};

#endif /* defined(__skill_market__Skills__) */
