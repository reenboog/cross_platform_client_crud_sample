//
//  CreateMealItemLayer.h
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 29.10.15.
//
//

#ifndef __ttt_c_tracker__CreateMealItemLayer__
#define __ttt_c_tracker__CreateMealItemLayer__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

class IOnItemCreated;

class CreateMealItemLayer: public cocos2d::Layer {
public:
    CreateMealItemLayer();
    ~CreateMealItemLayer();
    
    virtual bool init(IOnItemCreated *delegate);
    
    void onBtnCancelPressed();
    void onBtnSavePressed();
    
    void onSliderCaloriesChanged(cocos2d::Ref *sender, cocos2d::extension::Control::EventType controlEvent);
    void setCaloriesToConsume(unsigned int calories);
    
    void onTextMailEvent(cocos2d::Ref *sender, cocos2d::ui::TextField::EventType event);
    
    static CreateMealItemLayer* create(IOnItemCreated *delegate);
private:
    IOnItemCreated *_delegate;
    
    cocos2d::Sprite *_back;
    cocos2d::Sprite *_mntHeading;
    cocos2d::MenuItemImage *_btnCancel;
    cocos2d::MenuItemImage *_btnSave;
    
    cocos2d::Node *_sliderGroupNode;
    cocos2d::extension::ControlSlider *_sliderCalories;
    cocos2d::Label *_labelCaloriesToConsumeCaption;
    
    cocos2d::ui::TextField *_textCaption;
};

#endif /* defined(__ttt_c_tracker__CreateMealItemLayer__) */
