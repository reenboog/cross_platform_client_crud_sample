//
//  ManagerLayer.cpp
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 30.10.15.
//
//

#include "ManagerLayer.h"

#define zBack 0

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace std;

ManagerLayer::ManagerLayer() {
    _back = nullptr;
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

