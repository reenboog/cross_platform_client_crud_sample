//
//  ManagerLayer.cpp
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 30.10.15.
//
//

#include "ManagerLayer.h"
#include "User.h"

#define zBack 0

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace std;

ManagerLayer::ManagerLayer() {
    _back = nullptr;
    _mntHead = nullptr;
    _headingNode = nullptr;
    _btnSettings = nullptr;
    _labelMail = nullptr;
    _labelRole = nullptr;
}

ManagerLayer::~ManagerLayer() {
    
}

bool ManagerLayer::init() {
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
        // heading
        _headingNode = Node::create();
        _headingNode->setPosition({0, 0});
        
        this->addChild(_headingNode);
        
        _mntHead = Sprite::create("mnt_meals_list_head.png");
        _mntHead->setAnchorPoint({0.0f, 1.0f});
        _mntHead->setPosition({0, visibleSize.height});
        
        _headingNode->addChild(_mntHead);
        
        // settings button
        _btnSettings = MenuItemImage::create("btn_settings.png", "btn_settings_on.png", CC_CALLBACK_0(ManagerLayer::onBtnSettingsPressed, this));
        _btnSettings->setAnchorPoint({1, 1});
        _btnSettings->setPosition({visibleSize.width, visibleSize.height});
        
        Menu *settingsMenu = Menu::create(_btnSettings, nullptr);
        settingsMenu->setPosition({0, 0});
        
        _headingNode->addChild(settingsMenu);

        // mail label
        _labelMail = Label::createWithTTF(User::sharedInstance()->getName(), "helvetica.ttf", 18);
        _labelMail->setOpacity(255 * 0.5f);
        _labelMail->setColor({93, 93, 93});
        _labelMail->setAnchorPoint({0, 1});
        _labelMail->setPosition({visibleSize.width * 0.03f, visibleSize.height * 0.98f});
        
        _headingNode->addChild(_labelMail);
        
        // calories consumed
        _labelRole = Label::createWithTTF("manager", "helvetica.ttf", 40);
        _labelRole->setColor({53, 172, 225});
        _labelRole->setAnchorPoint({0, 1});
        _labelRole->setPosition({visibleSize.width * 0.03f, visibleSize.height * 0.98f - _labelMail->getContentSize().height});
        
        _headingNode->addChild(_labelRole);
    }
    
    
    return true;
}

Scene* ManagerLayer::scene() {
    auto scene = Scene::create();
    auto layer = ManagerLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

#pragma mark - ui callbacks

void ManagerLayer::onBtnSettingsPressed() {
    //
}