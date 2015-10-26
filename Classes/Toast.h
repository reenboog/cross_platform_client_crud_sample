
#ifndef __TTT__Toast__
#define __TTT__Toast__

#include "cocos2d.h"

#define kToastDefaultDelay 3.0f

class Toast: public cocos2d::Node {
public:
    static void show(cocos2d::Layer *layer, const std::string &str, float delay = kToastDefaultDelay);
    
    virtual ~Toast() {}
private:
    Toast() {};
    
    bool init(const std::string &str, float delay);
};

#endif