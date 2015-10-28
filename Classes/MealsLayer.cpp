//
//  MealsLayer.cpp
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 27.10.15.
//
//

#include "MealsLayer.h"
#include "ServerAPI.h"

#define zBack 0

using namespace cocos2d;
//using namespace ui;
using namespace std;


MealsLayer::~MealsLayer() {
    
}

MealsLayer::MealsLayer(): Layer() {
    _back = nullptr;
    
    _layout = nullptr;
    _mntHead = nullptr;
    _headingNode = nullptr;
    _btnSettings = nullptr;
    _labelMail = nullptr;
    _labelCaloriesConsumed = nullptr;
    _bgProgressCalories = nullptr;
    _progressCaloriesConsumed = nullptr;
    _mntDate = nullptr;
}

Scene* MealsLayer::scene() {
    auto scene = Scene::create();
    auto layer = MealsLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool MealsLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    
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
        // main layout
        
        _layout = Layer::create();
        this->addChild(_layout);
    }
    
    {
        // heading
        _headingNode = Node::create();
        _headingNode->setPosition({0, 0});

        this->addChild(_headingNode);
        
        _mntHead = Sprite::create("mnt_meals_list_head.png");
        _mntHead->setAnchorPoint({0.0f, 1.0f});
        _mntHead->setPosition({0, visibleSize.height});
        
        _headingNode->addChild(_mntHead);
        
        // settings button
        _btnSettings = MenuItemImage::create("btn_settings.png", "btn_settings_on.png", CC_CALLBACK_0(MealsLayer::onBtnSettingsPressed, this));
        _btnSettings->setAnchorPoint({1, 1});
        _btnSettings->setPosition({visibleSize.width, visibleSize.height});
        
        Menu *settingsMenu = Menu::create(_btnSettings, nullptr);
        settingsMenu->setPosition({0, 0});

        _headingNode->addChild(settingsMenu);
        
        // mail label
        _labelMail = Label::createWithTTF("alex.gievsky@gmail.com", "helvetica.ttf", 18);
        _labelMail->setOpacity(255 * 0.5f);
        _labelMail->setColor({93, 93, 93});
        _labelMail->setAnchorPoint({0, 1});
        _labelMail->setPosition({visibleSize.width * 0.03f, visibleSize.height * 0.98f});
        
        _headingNode->addChild(_labelMail);
        
        // calories consumed
        _labelCaloriesConsumed = Label::createWithTTF("2300 / 4500", "helvetica.ttf", 40);
        _labelCaloriesConsumed->setColor({53, 172, 225});
        _labelCaloriesConsumed->setAnchorPoint({0, 1});
        _labelCaloriesConsumed->setPosition({visibleSize.width * 0.03f, visibleSize.height * 0.98f - _labelMail->getContentSize().height});
        
        _headingNode->addChild(_labelCaloriesConsumed);
        
        // calories progress
        _bgProgressCalories = Sprite::create("bg_progress_calories.png");
        _bgProgressCalories->setAnchorPoint({0, 1});
        _bgProgressCalories->setPosition({0.0f, visibleSize.height - _mntHead->getContentSize().height});
        
        _headingNode->addChild(_bgProgressCalories);
        
        // calories progress
        _progressCaloriesConsumed = ProgressTimer::create(Sprite::create("progress_calories.png"));
        
        _progressCaloriesConsumed->setPosition(_bgProgressCalories->getContentSize().width / 2.0, _bgProgressCalories->getContentSize().height / 2.0);
        _progressCaloriesConsumed->setType(ProgressTimer::Type::BAR);
        _progressCaloriesConsumed->setMidpoint({0, 0});
        _progressCaloriesConsumed->setBarChangeRate({1, 0});
        
        _progressCaloriesConsumed->setPercentage(70);
        
        _bgProgressCalories->addChild(_progressCaloriesConsumed);
        
        // date mount
        _mntDate = Sprite::create("mnt_meals_list_date.png");
        _mntDate->setAnchorPoint({0, 1});
        _mntDate->setPosition({0, _bgProgressCalories->getPositionY() - _bgProgressCalories->getContentSize().height});
        
        _headingNode->addChild(_mntDate);

    }
    
    
    ///////////
    
    //this->createMeal("test", CCRANDOM_0_1() * 100);
    
    return true;
}

void MealsLayer::createMeal(const std::string &caption, int calories) {
    auto onMealCreated = [=]() {
        CCLOG("created!");
    };
    
    auto onFailedToCreateMEal = [=](const string &error, const string &description) {
        CCLOG("failed to create!");
    };
    
    ServerAPI::createMeal(caption, calories, onMealCreated, onFailedToCreateMEal);
}

#pragma mark - UI callbacks

void MealsLayer::onBtnSettingsPressed() {
    
}