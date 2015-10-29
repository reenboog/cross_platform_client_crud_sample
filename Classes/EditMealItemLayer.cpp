//
//  EditMealItemLayer.cpp
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 29.10.15.
//
//

#include "EditMealItemLayer.h"
#include "IOnItemModified.h"
#include "ServerAPI.h"
#include "Goal.h"
#include "User.h"
#include "LayerBlocker.h"
#include "Toast.h"

#define zBack 0

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace ui;
using namespace std;

EditMealItemLayer::~EditMealItemLayer() {
    
}

EditMealItemLayer::EditMealItemLayer(): Layer() {
    _delegate = nullptr;
    _back = nullptr;
    _mntHeading = nullptr;
    _btnBack = nullptr;
    _btnSave = nullptr;
    
    _sliderCalories = nullptr;
    _sliderGroupNode = nullptr;
    _labelSliderCaption = nullptr;
    _labelCaloriesToConsumeCaption = nullptr;
    
    _mntText = nullptr;
    _textCaption = nullptr;
}

EditMealItemLayer* EditMealItemLayer::create(IOnItemModified *delegate, const string &itemId) {
    EditMealItemLayer *pRet = new EditMealItemLayer();
    
    if(pRet && pRet->init(delegate, itemId)) {
        pRet->autorelease();
        return pRet;
    } else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool EditMealItemLayer::init(IOnItemModified *delegate, const string &itemId) {
    if(!Layer::init()) {
        return false;
    }
    
    _delegate = delegate;
    _itemId = itemId;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // back
    {
        _back = Sprite::create("back.png");
        _back->setPosition({static_cast<float>(visibleSize.width / 2.0), static_cast<float>(visibleSize.height / 2.0)});
        
        Size backSize = _back->getContentSize();
        
        _back->setScale(visibleSize.width / backSize.width, visibleSize.height / backSize.height);
        
        this->addChild(_back, zBack);
    }
    
    {
        // parent blocker
        MenuItemImage *btn = MenuItemImage::create("blank.png", "blank.png", [](Ref *){});
        btn->setScale(visibleSize.width / btn->getContentSize().width, visibleSize.height / btn->getContentSize().height);
        btn->setOpacity(0);
        
        Menu *blockMenu = Menu::create(btn, nullptr);
        blockMenu->setPosition({visibleSize.width * 0.5f, visibleSize.height * 0.5f});
        
        this->addChild(blockMenu);
    }
    
    {
        // heading
        _mntHeading = Sprite::create("mnt_edit_item_heading.png");
        _mntHeading->setAnchorPoint({0.5f, 1.0f});
        _mntHeading->setPosition({visibleSize.width * 0.5f, visibleSize.height});
        
        this->addChild(_mntHeading);
        
        // back button
        _btnBack = MenuItemImage::create("btn_back.png", "btn_back_on.png", CC_CALLBACK_0(EditMealItemLayer::onBtnBackPressed, this));
        _btnBack->setAnchorPoint({0, 1});
        _btnBack->setPosition({0, visibleSize.height});
        
        Menu *backMenu = Menu::create(_btnBack, nullptr);
        backMenu->setPosition({0, 0});
        
        this->addChild(backMenu);
    }
    
    {
        // delete button
        _btnDelete = MenuItemImage::create("btn_delete_item.png", "btn_delete_item_on.png", CC_CALLBACK_0(EditMealItemLayer::onBtnDeletePressed, this));
        _btnDelete->setAnchorPoint({0.5f, 0});
        _btnDelete->setPosition({visibleSize.width * 0.5f, 0});
        
        Menu *deletetMenu = Menu::create(_btnDelete, nullptr);
        deletetMenu->setPosition({0, 0});
        
        this->addChild(deletetMenu);
    }
    
    {
        // save button
        _btnSave = MenuItemImage::create("btn_settings_save.png", "btn_settings_save_on.png", CC_CALLBACK_0(EditMealItemLayer::onBtnSavePressed, this));
        _btnSave->setAnchorPoint({0.5f, 0});
        _btnSave->setPosition({visibleSize.width * 0.5f, _btnDelete->getContentSize().height});
        
        Menu *saveMenu = Menu::create(_btnSave, nullptr);
        saveMenu->setPosition({0, 0});
        
        this->addChild(saveMenu);
    }
    
    {
        // a slider
        _sliderGroupNode = Node::create();
        _sliderGroupNode->setPosition({visibleSize.width * 0.5f, visibleSize.height * 0.5f + _btnSave->getContentSize().height * 0.5f});
        
        this->addChild(_sliderGroupNode);
        
        _sliderCalories = ControlSlider::create("mnt_settings_calories_slider.png", "settings_calories_slider.png", "settings_calories_slider_thumb.png");
        _sliderCalories->addTargetWithActionForControlEvents(this, cccontrol_selector(EditMealItemLayer::onSliderCaloriesChanged),
                                                             Control::EventType::VALUE_CHANGED);
        _sliderCalories->setMaximumAllowedValue(1);
        _sliderCalories->setMinimumAllowedValue(0.01);
        
        _sliderGroupNode->addChild(_sliderCalories);
    }
    
    {
        // captions
        _labelSliderCaption = Label::createWithTTF("Value", "helvetica.ttf", 26);
        _labelSliderCaption->setColor({53, 172, 225});
        _labelSliderCaption->setAnchorPoint({0, 0.0});
        _labelSliderCaption->setPosition({-_sliderCalories->getContentSize().width * 0.5f, _labelSliderCaption->getContentSize().height});
        
        _sliderGroupNode->addChild(_labelSliderCaption);
    }
    
    {
        _labelCaloriesToConsumeCaption = Label::createWithTTF("0", "helvetica.ttf", 25);
        _labelCaloriesToConsumeCaption->setColor({93, 93, 93});
        _labelCaloriesToConsumeCaption->setOpacity(0.7f * 255);
        _labelCaloriesToConsumeCaption->setAnchorPoint({0.5, 1});
        _labelCaloriesToConsumeCaption->setPosition({0, -_labelCaloriesToConsumeCaption->getContentSize().height});
        
        _sliderGroupNode->addChild(_labelCaloriesToConsumeCaption);
        
        _sliderCalories->setValue(1.0f * User::sharedInstance()->getMeal(_itemId)->getCalories() / kMaxKCaloriesPerIntake);
    }
    
    {
        // text
        _mntText = Sprite::create("mnt_edit_item_text.png");
        _mntText->setPosition({visibleSize.width * 0.5f, _sliderGroupNode->getPositionY() + _btnDelete->getContentSize().height * 1.6f});
        
        this->addChild(_mntText);
    }
    
    {
        // caption
        _textCaption = TextField::create("A short description", "helvetica.ttf", 22);
        _mntText->addChild(_textCaption);
        
        _textCaption->addEventListener(CC_CALLBACK_2(EditMealItemLayer::onTextMailEvent, this));
        _textCaption->setPosition({_mntText->getContentSize().width * 0.025f, _mntHeading->getContentSize().height * 0.38f});
        _textCaption->setMaxLength(26);
        _textCaption->setString(User::sharedInstance()->getMeal(_itemId)->getCaption());
        _textCaption->setMaxLengthEnabled(true);
        _textCaption->setAnchorPoint({0, 0.5});
        _textCaption->setColor({93, 93, 93});
        _textCaption->setPlaceHolderColor({93, 93, 93, 100});
    }

 
    return true;
}

void EditMealItemLayer::onBtnBackPressed() {
    this->removeFromParent();
}

void EditMealItemLayer::onBtnSavePressed() {
    LayerBlocker::block(this);
    
    Toast::show(this, "Updating...", 2);
    
    auto onItemUpdated = [this](const string &itemId, const string &newCaption, int newCalories) {
        LayerBlocker::unblock(this);
        
        Meal meal = *User::sharedInstance()->getMeal(_itemId);
        meal.setCaption(newCaption);
        meal.setCalories(newCalories);
        
        User::sharedInstance()->setMeal(_itemId, meal);
        
        // call delegates
        _delegate->onItemUpdated(itemId, newCaption, newCalories);
        
        Toast::show(static_cast<Layer*>(this->getParent()), "Updated", 1);
        
        this->removeFromParent();
    };
    
    auto onFailedToUpdateItem = [=](const string &error, const string &description) {
        LayerBlocker::unblock(this);
        
        Toast::show(this, description);
    };
    
    ServerAPI::updateMeal(_itemId, _textCaption->getString(), _sliderCalories->getValue() * kMaxKCaloriesPerIntake, onItemUpdated, onFailedToUpdateItem);
}

void EditMealItemLayer::onBtnDeletePressed() {
    // call api
}

void EditMealItemLayer::onSliderCaloriesChanged(Ref *sender, Control::EventType controlEvent) {
    float value = static_cast<ControlSlider*>(sender)->getValue();
    this->setCaloriesToConsume(kMaxKCaloriesPerIntake * value);
}

void EditMealItemLayer::setCaloriesToConsume(unsigned int calories) {
    _labelCaloriesToConsumeCaption->setString(StringUtils::format("%i kCal", calories));
}

void EditMealItemLayer::onTextMailEvent(cocos2d::Ref *sender, cocos2d::ui::TextField::EventType event) {
    
}