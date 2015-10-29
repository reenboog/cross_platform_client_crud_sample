//
//  UserSettingsLayer.cpp
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 29.10.15.
//
//

#include "UserSettingsLayer.h"
#include "ServerAPI.h"

#define zBack 0

using namespace cocos2d;
using namespace std;

UserSettingsLayer::~UserSettingsLayer() {
    
}

UserSettingsLayer::UserSettingsLayer(): Layer() {
    _back = nullptr;
    _mntHeading = nullptr;
    _btnBack = nullptr;
}

bool UserSettingsLayer::init() {
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
        _btnBack = MenuItemImage::create("btn_back.png", "btn_back_on.png", CC_CALLBACK_0(UserSettingsLayer::onBtnBackPressed, this));
        _btnBack->setAnchorPoint({0, 1});
        _btnBack->setPosition({0, visibleSize.height});
        
        Menu *backMenu = Menu::create(_btnBack, nullptr);
        backMenu->setPosition({0, 0});
        
        this->addChild(backMenu);
    }

    return true;
}

#pragma mark - UI callbacks

void UserSettingsLayer::onBtnBackPressed() {
    this->removeFromParent();
}

void UserSettingsLayer::onBtnSavePressed() {
    //
}