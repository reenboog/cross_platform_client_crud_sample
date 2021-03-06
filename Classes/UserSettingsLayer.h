//
//  UserSettingsLayer.h
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 29.10.15.
//
//

#ifndef __ttt_c_tracker__UserSettingsLayer__
#define __ttt_c_tracker__UserSettingsLayer__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

class IOnGoalChanged;

class UserSettingsLayer: public cocos2d::Layer {
public:
    UserSettingsLayer();
    ~UserSettingsLayer();
    
    virtual bool init(IOnGoalChanged *delegate);
    
    void onBtnBackPressed();
    void onBtnSavePressed();
    void onBtnLogoutPressed();
    
    void onSliderCaloriesChanged(cocos2d::Ref *sender, cocos2d::extension::Control::EventType controlEvent);
    
    static UserSettingsLayer* create(IOnGoalChanged *delegate);
private:
    void setCaloriesToConsume(unsigned int calories);
private:
    cocos2d::Sprite *_back;
    cocos2d::Sprite *_mntHeading;
    cocos2d::MenuItemImage *_btnBack;
    cocos2d::MenuItemImage *_btnSave;
    cocos2d::MenuItemImage *_btnLogout;
    
    cocos2d::Node *_sliderGroupNode;
    cocos2d::extension::ControlSlider *_sliderCalories;
    cocos2d::Label *_labelSliderCaption;
    cocos2d::Label *_labelCaloriesToConsumeCaption;
    
    IOnGoalChanged *_goalChangedDelegate;
};

#endif /* defined(__ttt_c_tracker__UserSettingsLayer__) */