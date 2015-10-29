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
    
    void onBtnSettingsPressed();
    
    CREATE_FUNC(ManagerLayer);
private:
    cocos2d::Sprite *_back;
    
    cocos2d::Node *_headingNode;
    cocos2d::Sprite *_mntHead;
    cocos2d::MenuItemImage *_btnSettings;
    cocos2d::Label *_labelMail;
    cocos2d::Label *_labelRole;
};

#endif /* defined(__ttt_c_tracker__ManagerLayer__) */
