//
//  ItemFilterLayer.cpp
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 30.10.15.
//
//

#include "ItemFilterLayer.h"

#define zBack 0

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace ui;
using namespace std;

ItemFIlterLayer::~ItemFIlterLayer() {
    
}

ItemFIlterLayer::ItemFIlterLayer() {
    _back = nullptr;
    _mntHeading = nullptr;
    _btnClose = nullptr;
    
    _textFrom = nullptr;
    _textTo = nullptr;
    
    _delegate = nullptr;
}

ItemFIlterLayer* ItemFIlterLayer::create(IOnFilterApplied *delegate) {
    ItemFIlterLayer *pRet = new ItemFIlterLayer();
    
    if(pRet && pRet->init(delegate)) {
        pRet->autorelease();
        return pRet;
    } else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool ItemFIlterLayer::init(IOnFilterApplied *delegate) {
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
        _mntHeading = Sprite::create("mnt_filter_heading.png");
        _mntHeading->setAnchorPoint({0, 1});
        _mntHeading->setPosition(_back->getPosition());
        
        this->addChild(_mntHeading);
    }
    
    {
        // buttons
        _btnClose = MenuItemImage::create("btn_close.png", "btn_close_on.png", CC_CALLBACK_0(ItemFIlterLayer::onBtnClosePressed, this));
        _btnClose->setAnchorPoint({0.5, 0});
        _btnClose->setPosition({_mntHeading->getContentSize().width * 0.5f, 0});
        
        Menu *closeMenu = Menu::create(_btnClose, nullptr);
        closeMenu->setPosition({0, 0});
        
        _mntHeading->addChild(closeMenu);
    }
    
    return true;
}

void ItemFIlterLayer::onBtnClosePressed() {
    this->removeFromParent();
}

void ItemFIlterLayer::onResutFetched(const MealGroup &g) {
    // reload tables here
}