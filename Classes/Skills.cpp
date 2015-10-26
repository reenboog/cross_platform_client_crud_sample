//
//  Skills.cpp
//  skill_market
//
//  Created by Alex Gievsky on 23.07.15.
//
//

#include "Skills.h"

#include <string>

using std::string;

Skills* Skills::__sharedInstance = nullptr;

Skills::~Skills() {
    for(auto it = _skills.begin(); it != _skills.end(); ++it) {
        if(it->second != nullptr) {
            delete it->second;
        }
    }
    
    _skills.clear();
}

Skills* Skills::sharedInstance() {
    if(__sharedInstance == nullptr) {
        __sharedInstance = new Skills();
    }
    
    return __sharedInstance;
}

void Skills::add(int skillId, string &title, string &description) {
    auto skillIt = _skills.find(skillId);
    
    if(skillIt != _skills.end()) {
        delete skillIt->second;
        _skills.erase(skillIt);
    }
    
    _skills.insert({skillId, new Skill(skillId, title, description)});
}

Skill* Skills::get(int skillId) const {
    Skill *skill = nullptr;
    
    auto skillIt = _skills.find(skillId);
    
    if(skillIt != _skills.end()) {
        skill = skillIt->second;
    }
    
    return skill;
}