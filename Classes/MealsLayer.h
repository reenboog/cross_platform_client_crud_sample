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
    
    void createMeal(const std::string &caption, int calories);
    
    void onBtnSettingsPressed();
    
    CREATE_FUNC(MealsLayer);
private:
    cocos2d::Sprite *_back;
    cocos2d::Layer *_layout;
    
    // heading
    cocos2d::Node *_headingNode;
    cocos2d::Sprite *_mntHead;
    cocos2d::MenuItemImage *_btnSettings;
    cocos2d::Label *_labelMail;
    cocos2d::Label *_labelCaloriesConsumed;
    cocos2d::Sprite *_bgProgressCalories;
    cocos2d::ProgressTimer *_progressCaloriesConsumed;
    
};

#endif /* defined(__ttt_c_tracker__MealsLayer__) */
