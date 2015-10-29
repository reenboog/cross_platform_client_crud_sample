//
//  ManagerToUserSettingsLayer.h
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 30.10.15.
//
//

#ifndef __ttt_c_tracker__ManagerToUserSettingsLayer__
#define __ttt_c_tracker__ManagerToUserSettingsLayer__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

class IOnGoalChangedForUser;

class ManagerToUserSettingsLayer: public cocos2d::Layer {
public:
    ManagerToUserSettingsLayer();
    ~ManagerToUserSettingsLayer();
    
    virtual bool init(IOnGoalChangedForUser *delegate, const std::string &userId, int goal);
    
    void onBtnBackPressed();
    void onBtnSavePressed();
    
    void onSliderCaloriesChanged(cocos2d::Ref *sender, cocos2d::extension::Control::EventType controlEvent);
    
    static ManagerToUserSettingsLayer* create(IOnGoalChangedForUser *delegate, const std::string &userId, int goal);
private:
    void setCaloriesToConsume(unsigned int calories);
private:
    cocos2d::Sprite *_back;
    cocos2d::Sprite *_mntHeading;
    cocos2d::MenuItemImage *_btnBack;
    cocos2d::MenuItemImage *_btnSave;
    
    cocos2d::Node *_sliderGroupNode;
    cocos2d::extension::ControlSlider *_sliderCalories;
    cocos2d::Label *_labelSliderCaption;
    cocos2d::Label *_labelCaloriesToConsumeCaption;
    
    IOnGoalChangedForUser *_goalChangedDelegate;
    
    std::string _userId;
    int _userGoal;
};


#endif /* defined(__ttt_c_tracker__ManagerToUserSettingsLayer__) */
