//
//  MealsLayer.cpp
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 27.10.15.
//
//

#include "MealsLayer.h"

#define zBack 0

using namespace cocos2d;
//using namespace ui;
using namespace std;


MealsLayer::~MealsLayer() {
    
}

MealsLayer::MealsLayer(): Layer() {
    _back = nullptr;
    
    _layout = nullptr;
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
    
    return true;
}
