
#ifndef ___TTT__Shared__
#define ___TTT__Shared__

#include "cocos2d.h"

class Shared {
private:
    Shared() {};
    virtual ~Shared() {};
public:
    static cocos2d::Animation* loadAnimation(const std::string &fileName, const std::string &name);
    
    static std::string formatValue(double value, bool skipSuffix = false);
};

#endif
