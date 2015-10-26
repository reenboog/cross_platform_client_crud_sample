
#ifndef _TTT__LayerBlocker__
#define _TTT__LayerBlocker__

#include "cocos2d.h"

class LayerBlocker: public cocos2d::Node {
public:
    static void block(cocos2d::Layer *target, float delay = -1);
    static void unblock(cocos2d::Layer *target);
    
    virtual ~LayerBlocker() {}
private:
    LayerBlocker() {};
    
    bool init(cocos2d::Layer *target, float delay);
};

#endif