//
//  CreateMealItemLayer.cpp
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 29.10.15.
//
//

#include "CreateMealItemLayer.h"
#include "ServerAPI.h"
#include "Goal.h"
#include "User.h"

#define zBack 0

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace ui;
using namespace std;

CreateMealItemLayer::~CreateMealItemLayer() {
    
}

CreateMealItemLayer::CreateMealItemLayer(): Layer() {
    _delegate = nullptr;
    _back = nullptr;
    _mntHeading = nullptr;
    _btnCancel = nullptr;
    _btnSave = nullptr;
    _sliderGroupNode = nullptr;
    _sliderCalories = nullptr;
    _labelCaloriesToConsumeCaption = nullptr;
    _textCaption = nullptr;
}

CreateMealItemLayer* CreateMealItemLayer::create(IOnItemCreated *delegate) {
    CreateMealItemLayer *pRet = new CreateMealItemLayer();
    
    if(pRet && pRet->init(delegate)) {
        pRet->autorelease();
        return pRet;
    } else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool CreateMealItemLayer::init(IOnItemCreated *delegate) {
    if(!Layer::init()) {
        return false;
    }
    
    _delegate = delegate;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // back
    {
        Sprite *mntHead = Sprite::create("mnt_meals_list_head.png");
        Sprite *mntProgress = Sprite::create("bg_progress_calories.png");
        Sprite *mntDate = Sprite::create("mnt_meals_list_date.png");
        
        _back = Sprite::create("back.png");
        
        _back->setColor({0, 0, 0});
        _back->setOpacity(0.7f * 255);
        _back->setAnchorPoint({0, 1});
        _back->setPosition({0.0f, visibleSize.height - mntHead->getContentSize().height - mntProgress->getContentSize().height - mntDate->getContentSize().height});
        
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
        _mntHeading = Sprite::create("mnt_create_item.png");
        _mntHeading->setAnchorPoint({0, 1});
        _mntHeading->setPosition(_back->getPosition());
        
        this->addChild(_mntHeading);
    }
    
    {
        // buttons
        _btnCancel = MenuItemImage::create("btn_cancel.png", "btn_cancel_on.png", CC_CALLBACK_0(CreateMealItemLayer::onBtnCancelPressed, this));
        _btnCancel->setAnchorPoint({0, 0});
        _btnCancel->setPosition({0, 0});
        
        _btnSave = MenuItemImage::create("btn_save.png", "btn_save_on.png", CC_CALLBACK_0(CreateMealItemLayer::onBtnSavePressed, this));
        _btnSave->setAnchorPoint({1, 0});
        _btnSave->setPosition({_mntHeading->getContentSize().width, 0});
        
        Menu *saveCancelMenu = Menu::create(_btnCancel, _btnSave, nullptr);
        saveCancelMenu->setPosition({0, 0});
        
        _mntHeading->addChild(saveCancelMenu);
    }
    
    {
        // a slider
        _sliderGroupNode = Node::create();
        _sliderGroupNode->setPosition({_mntHeading->getContentSize().width * 0.5f, _mntHeading->getContentSize().height * 0.83f});
        
        _mntHeading->addChild(_sliderGroupNode);
        
        _sliderCalories = ControlSlider::create("mnt_settings_calories_slider.png", "settings_calories_slider.png", "settings_calories_slider_thumb.png");
        _sliderCalories->addTargetWithActionForControlEvents(this, cccontrol_selector(CreateMealItemLayer::onSliderCaloriesChanged),
                                                             Control::EventType::VALUE_CHANGED);
        _sliderCalories->setMaximumAllowedValue(1);
        _sliderCalories->setMinimumAllowedValue(0.01);
        
        _sliderGroupNode->addChild(_sliderCalories);
    }
    
    {
        _labelCaloriesToConsumeCaption = Label::createWithTTF("10000", "helvetica.ttf", 25);
        _labelCaloriesToConsumeCaption->setColor({93, 93, 93});
        _labelCaloriesToConsumeCaption->setOpacity(0.7f * 255);
        _labelCaloriesToConsumeCaption->setAnchorPoint({0.5, 1});
        _labelCaloriesToConsumeCaption->setPosition({0, -_labelCaloriesToConsumeCaption->getContentSize().height * 0.65f});
        
        _sliderGroupNode->addChild(_labelCaloriesToConsumeCaption);
        
        _sliderCalories->setValue(0.5f);
        
        //this->setCaloriesToConsume(User::sharedInstance()->getGoal().getCalories());
    }
    
    {
        // caption
        _textCaption = TextField::create("A short description", "helvetica.ttf", 22);
        _mntHeading->addChild(_textCaption);
        
        _textCaption->addEventListener(CC_CALLBACK_2(CreateMealItemLayer::onTextMailEvent, this));
        _textCaption->setPosition({_mntHeading->getContentSize().width * 0.07f, _mntHeading->getContentSize().height * 0.45f});
        _textCaption->setMaxLength(26);
        _textCaption->setMaxLengthEnabled(true);
        _textCaption->setAnchorPoint({0, 0.5});
        _textCaption->setColor({93, 93, 93});
        _textCaption->setPlaceHolderColor({93, 93, 93, 100});
    }
    
    return true;
}

void CreateMealItemLayer::onBtnCancelPressed() {
    this->removeFromParent();
}

void CreateMealItemLayer::onBtnSavePressed() {
    // call API
}

void CreateMealItemLayer::onSliderCaloriesChanged(cocos2d::Ref *sender, cocos2d::extension::Control::EventType controlEvent) {
    float value = static_cast<ControlSlider*>(sender)->getValue();
    this->setCaloriesToConsume(kMaxKCaloriesPerIntake * value);
}

void CreateMealItemLayer::setCaloriesToConsume(unsigned int calories) {
    _labelCaloriesToConsumeCaption->setString(StringUtils::format("%i kCal", calories));
}

void CreateMealItemLayer::onTextMailEvent(cocos2d::Ref *sender, TextField::EventType event) {
}