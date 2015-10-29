//
//  ManagerLayer.h
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 30.10.15.
//
//

#ifndef __ttt_c_tracker__ManagerLayer__
#define __ttt_c_tracker__ManagerLayer__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "MealGroup.h"

class ManagerLayer: public cocos2d::Layer {
public:
    ManagerLayer();
    virtual ~ManagerLayer();
    
    static cocos2d::Scene* scene();
    
    virtual bool init();
    
    CREATE_FUNC(ManagerLayer);
private:
    cocos2d::Sprite *_back;
};

#endif /* defined(__ttt_c_tracker__ManagerLayer__) */
