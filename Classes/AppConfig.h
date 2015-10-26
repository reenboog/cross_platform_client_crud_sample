//
//  GameConfig.h
//  solveMe
//
//  Created by Alex Gievsky on 11.11.13.
//
//

#ifndef TTT_AppConfig__H
#define TTT_AppConfig__H

#include "cocos2d.h"
#include "Constants.h"

class AppConfig {
private:
    AppConfig();
    void setDesignLayoutSize(const cocos2d::Size &size);
    void setVisibleOrigin(const cocos2d::Point &point);
public:
    ~AppConfig();
    
    void load();
    void save();
    
    cocos2d::Size getDesignLayoutSize();
    cocos2d::Point getVisibleOrigin();
    
    void loadFilePaths();
    
    static AppConfig* sharedInstance();
    static void purge();
private:
    static AppConfig *__sharedInstance;
    
    cocos2d::Point _visibleOrigin;
    cocos2d::Size _designLayoutSize;
};

#endif /* defined(__solveMe__GameConfig__) */