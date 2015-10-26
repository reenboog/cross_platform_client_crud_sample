//
//  Localized.h
//  astroGems
//
//  Created by Alex Gievsky on 30.10.13.
//
//

#ifndef __TTT__Localized__H_
#define __TTT__Localized__H_

#include <map>
#include <string>

#include "cocos2d.h"

class Localized {
    typedef std::map<std::string, std::string> StringStringMap;
private:
    virtual ~Localized();
    Localized();
public:
    static std::string getString(const std::string &key);
    
    static std::string languageShortNameForType(cocos2d::LanguageType type);

    static void purge();
    
    static void load();
private:
    StringStringMap strings;
    static Localized *__sharedInstance;
};

#endif /* defined(__astroGems__Localized__) */
