//
//  EditMealItemLayer.h
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 29.10.15.
//
//

#ifndef __ttt_c_tracker__EditMealItemLayer__
#define __ttt_c_tracker__EditMealItemLayer__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

class IOnItemModified;

class EditMealItemLayer: public cocos2d::Layer {
public:
    EditMealItemLayer();
    ~EditMealItemLayer();
    
    virtual bool init(IOnItemModified *delegate, const std::string &itemId);
    static EditMealItemLayer* create(IOnItemModified *delegate, const std::string &itemId);
    
    // ui callbacks
    void onBtnBackPressed();
    void onBtnSavePressed();
    void onBtnDeletePressed();
    
    void onSliderCaloriesChanged(cocos2d::Ref *sender, cocos2d::extension::Control::EventType controlEvent);
    void onTextMailEvent(cocos2d::Ref *sender, cocos2d::ui::TextField::EventType event);
private:
    void setCaloriesToConsume(unsigned int calories);
private:
    IOnItemModified *_delegate;
    std::string _itemId;
    
    cocos2d::Sprite *_back;
    cocos2d::Sprite *_mntHeading;
    cocos2d::MenuItemImage *_btnBack;
    cocos2d::MenuItemImage *_btnSave;
    cocos2d::MenuItemImage *_btnDelete;
    
    cocos2d::Node *_sliderGroupNode;
    cocos2d::extension::ControlSlider *_sliderCalories;
    cocos2d::Label *_labelSliderCaption;
    cocos2d::Label *_labelCaloriesToConsumeCaption;
    cocos2d::Sprite *_mntText;
    cocos2d::ui::TextField *_textCaption;
};

#endif /* defined(__ttt_c_tracker__EditMealItemLayer__) */
