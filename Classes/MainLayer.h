//
//  MainLayer.h
//  skill_market
//
//  Created by Alex Gievsky on 23.07.15.
//
//

#ifndef __TTT__MainLayer__
#define __TTT__MainLayer__

#include "cocos2d.h"

#include <vector>

class MainLayer: public cocos2d::Layer {
public:
    MainLayer();
    virtual ~MainLayer();
    
    static cocos2d::Scene* scene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    void onHomeBtnPressed();
    void onSearchBtnPressed();
    void onCreateNewsBtnPressed();
    void onStarBtnPressed();
    void onProfileBtnPressed();
    
    void showHome();
    void showSearch();
    void showStar();
    void showProfile();
    
    CREATE_FUNC(MainLayer);
private:
    void closeAllLayers();
private:
    // layers
    std::vector<Layer*> _layers;
    
    Layer *_profileLayer;
    Layer *_homeLayer;
    
    // ui
    cocos2d::Sprite *_back;
    cocos2d::Sprite *_bottomMenuMount;
    
    cocos2d::Menu *_menu;
    cocos2d::MenuItemImage *_btnHome;
    cocos2d::MenuItemImage *_btnSearch;
    cocos2d::MenuItemImage *_btncreate;
    cocos2d::MenuItemImage *_btnStar;
    cocos2d::MenuItemImage *_btnProfile;
};

#endif