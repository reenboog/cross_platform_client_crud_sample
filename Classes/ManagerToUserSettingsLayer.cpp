//
//  ManagerToUserSettingsLayer.cpp
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 30.10.15.
//
//

#include "ManagerToUserSettingsLayer.h"

#include "ServerAPI.h"
#include "LayerBlocker.h"
#include "Toast.h"

#include "IOnGoalChanged.h"

#include "ManagerLayer.h"

#define zBack 0

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace std;

ManagerToUserSettingsLayer::~ManagerToUserSettingsLayer() {
    
}

ManagerToUserSettingsLayer::ManagerToUserSettingsLayer(): Layer() {
    _back = nullptr;
    _mntHeading = nullptr;
    _btnBack = nullptr;
    _btnSave = nullptr;
    _sliderGroupNode = nullptr;
    _sliderCalories = nullptr;
    _labelSliderCaption = nullptr;
    _labelCaloriesToConsumeCaption = nullptr;
    
    _goalChangedDelegate = nullptr;
}

ManagerToUserSettingsLayer* ManagerToUserSettingsLayer::create(IOnGoalChangedForUser *delegate, const std::string &userId, int goal) {
    ManagerToUserSettingsLayer *pRet = new ManagerToUserSettingsLayer();
    
    if(pRet && pRet->init(delegate, userId, goal)) {
        pRet->autorelease();
        return pRet;
    } else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool ManagerToUserSettingsLayer::init(IOnGoalChangedForUser *delegate, const std::string &userId, int goal) {
    if(!Layer::init()) {
        return false;
    }
    
    _goalChangedDelegate = delegate;
    _userId = userId;
    _userGoal = goal;
    
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
        _mntHeading = Sprite::create("mnt_settings_heading.png");
        _mntHeading->setAnchorPoint({0.5f, 1.0f});
        _mntHeading->setPosition({visibleSize.width * 0.5f, visibleSize.height});
        
        this->addChild(_mntHeading);
        
        // back button
        _btnBack = MenuItemImage::create("btn_back.png", "btn_back_on.png", CC_CALLBACK_0(ManagerToUserSettingsLayer::onBtnBackPressed, this));
        _btnBack->setAnchorPoint({0, 1});
        _btnBack->setPosition({0, visibleSize.height});
        
        Menu *backMenu = Menu::create(_btnBack, nullptr);
        backMenu->setPosition({0, 0});
        
        this->addChild(backMenu);
    }
    
    {
        // save button
        _btnSave = MenuItemImage::create("btn_settings_save.png", "btn_settings_save_on.png", CC_CALLBACK_0(ManagerToUserSettingsLayer::onBtnSavePressed, this));
        _btnSave->setAnchorPoint({0.5f, 0});
        _btnSave->setPosition({visibleSize.width * 0.5f, 0});
        
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
        _sliderCalories->addTargetWithActionForControlEvents(this, cccontrol_selector(ManagerToUserSettingsLayer::onSliderCaloriesChanged),
                                                             Control::EventType::VALUE_CHANGED);
        _sliderCalories->setMaximumAllowedValue(1);
        _sliderCalories->setMinimumAllowedValue(0.1);
        
        _sliderGroupNode->addChild(_sliderCalories);
    }
    
    {
        // captions
        _labelSliderCaption = Label::createWithTTF("Daily goal", "helvetica.ttf", 26);
        _labelSliderCaption->setColor({53, 172, 225});
        _labelSliderCaption->setAnchorPoint({0, 0.0});
        _labelSliderCaption->setPosition({-_sliderCalories->getContentSize().width * 0.5f, _labelSliderCaption->getContentSize().height});
        
        _sliderGroupNode->addChild(_labelSliderCaption);
    }
    
    {
        _labelCaloriesToConsumeCaption = Label::createWithTTF("10000", "helvetica.ttf", 25);
        _labelCaloriesToConsumeCaption->setColor({93, 93, 93});
        _labelCaloriesToConsumeCaption->setOpacity(0.7f * 255);
        _labelCaloriesToConsumeCaption->setAnchorPoint({0.5, 1});
        _labelCaloriesToConsumeCaption->setPosition({0, -_labelCaloriesToConsumeCaption->getContentSize().height});
        
        _sliderGroupNode->addChild(_labelCaloriesToConsumeCaption);
        
        _sliderCalories->setValue(1.0f * _userGoal / kMaxKCaloriesPerDay);
    }
    
    return true;
}

#pragma mark - UI callbacks

void ManagerToUserSettingsLayer::onBtnBackPressed() {
    this->removeFromParent();
}

void ManagerToUserSettingsLayer::onBtnSavePressed() {
    LayerBlocker::block(this);
    
    Toast::show(this, "Saving...", 2);
    
    auto onGoalChanged = [this](unsigned int newGoal) {
        LayerBlocker::unblock(this);
        
        _goalChangedDelegate->onGoalChanged(_userId, newGoal);
        
        Toast::show(static_cast<Layer*>(this->getParent()), "Saved", 1);
        
        this->removeFromParent();
    };
    
    auto onFaileToChangeGoal = [=](const string &error, const string &description) {
        LayerBlocker::unblock(this);
        
        Toast::show(this, "Error updating goal");
    };
    
    ServerAPI::updateGoalForUser(_userId, _sliderCalories->getValue() * kMaxKCaloriesPerDay, onGoalChanged, onFaileToChangeGoal);
}

void ManagerToUserSettingsLayer::onSliderCaloriesChanged(Ref *sender, Control::EventType controlEvent) {
    float value = static_cast<ControlSlider*>(sender)->getValue();
    this->setCaloriesToConsume(kMaxKCaloriesPerDay * value);
}

void ManagerToUserSettingsLayer::setCaloriesToConsume(unsigned int calories) {
    _labelCaloriesToConsumeCaption->setString(StringUtils::format("%i kCal", calories));
}