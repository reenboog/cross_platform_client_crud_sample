//
//  MealsLayer.h
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 27.10.15.
//
//

#ifndef __ttt_c_tracker__MealsLayer__
#define __ttt_c_tracker__MealsLayer__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

class MealsLayer: public cocos2d::Layer {
public:
    MealsLayer();
    ~MealsLayer();
    
    static cocos2d::Scene* scene();
    
    virtual bool init();
    
    CREATE_FUNC(MealsLayer);
private:
    cocos2d::Sprite *_back;
    cocos2d::Layer *_layout;
};

#endif /* defined(__ttt_c_tracker__MealsLayer__) */
