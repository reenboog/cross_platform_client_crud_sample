//
//  MainLayer.cpp
//  skill_market
//
//  Created by Alex Gievsky on 23.07.15.
//
//

#include "MainLayer.h"

//#include "ProfileLayer.h"
//#include "HomeLayer.h"

using namespace cocos2d;

#define zBack 0

MainLayer::~MainLayer() {
    
}

MainLayer::MainLayer() {
    _bottomMenuMount = nullptr;
    _back = nullptr;
    _menu = nullptr;
}

Scene* MainLayer::scene() {
    auto scene = Scene::create();
    auto layer = MainLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool MainLayer::init() {
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
        _back->setVisible(false);
        
        this->addChild(_back, zBack);
    }
    
    {
        _bottomMenuMount = Sprite::create("ui_bottom_panel.png");
        this->addChild(_bottomMenuMount);
        
        _bottomMenuMount->setPosition({visibleSize.width * 0.5f, _bottomMenuMount->getContentSize().height * 0.5f});
    }
    
    // menu
    {
        _btnHome = MenuItemImage::create("btn_home.png", "btn_home_on.png", CC_CALLBACK_0(MainLayer::onHomeBtnPressed, this));
        _btnHome->setAnchorPoint({0, 0});
        _btnHome->setPosition({0, 0});
        
        _btnProfile = MenuItemImage::create("btn_profile.png", "btn_profile_on.png", CC_CALLBACK_0(MainLayer::onProfileBtnPressed, this));
        _btnProfile->setAnchorPoint({1, 0});
        _btnProfile->setPosition({visibleSize.width, 0});
        
        _btncreate = MenuItemImage::create("btn_create.png", "btn_create_on.png", CC_CALLBACK_0(MainLayer::onCreateNewsBtnPressed, this));
        _btncreate->setAnchorPoint({0.5f, 0});
        _btncreate->setPosition({visibleSize.width * 0.5f, 0});
        
        _btnSearch = MenuItemImage::create("btn_search.png", "btn_search_on.png", CC_CALLBACK_0(MainLayer::onSearchBtnPressed, this));
        _btnSearch->setAnchorPoint({1, 0});
        _btnSearch->setPosition({_btncreate->getPositionX() - _btncreate->getContentSize().width * 0.5f, 0});
        
        _btnStar = MenuItemImage::create("btn_star.png", "btn_star_on.png", CC_CALLBACK_0(MainLayer::onStarBtnPressed, this));
        _btnStar->setAnchorPoint({0, 0});
        _btnStar->setPosition({_btncreate->getPositionX() + _btncreate->getContentSize().width * 0.5f, 0});
        
        _menu = Menu::create(_btnHome, _btnSearch, _btncreate, _btnStar, _btnProfile, nullptr);
        _menu->setPosition({0, 0});
        
        this->addChild(_menu);
    }
    
    // set up layers
    // profile
    //_profileLayer = ProfileLayer::create();
    //this->addChild(_profileLayer, -1);
    
    _layers.push_back(_profileLayer);
    
    // home layer
    //_homeLayer = HomeLayer::create();
    //this->addChild(_homeLayer, -1);
    
    //_layers.push_back(_homeLayer);
    //
    
    this->closeAllLayers();
    
    this->showProfile();
    
    return true;
}

void MainLayer::onHomeBtnPressed() {
    this->closeAllLayers();
    
    this->showHome();
}

void MainLayer::onSearchBtnPressed() {
    this->closeAllLayers();
    
    this->showSearch();
}

void MainLayer::onCreateNewsBtnPressed() {
    this->closeAllLayers();
    
    // do nothing yet
}

void MainLayer::onStarBtnPressed() {
    this->closeAllLayers();
    
    this->showStar();
}

void MainLayer::onProfileBtnPressed() {
    this->closeAllLayers();
    
    this->showProfile();
}

void MainLayer::closeAllLayers() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    for(Layer *layer: _layers) {
        layer->setPosition({visibleSize.width * 4, visibleSize.height * 4});
    }
}

void MainLayer::showHome() {
    this->closeAllLayers();
    
    _homeLayer->setPosition({0, 0});
}

void MainLayer::showSearch() {
    this->closeAllLayers();
}

void MainLayer::showStar() {
    this->closeAllLayers();
}

void MainLayer::showProfile() {
    this->closeAllLayers();
    
    _profileLayer->setPosition({0, 0});
}