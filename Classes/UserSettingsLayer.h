//
//  UserSettingsLayer.h
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 29.10.15.
//
//

#ifndef __ttt_c_tracker__UserSettingsLayer__
#define __ttt_c_tracker__UserSettingsLayer__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

class UserSettingsLayer: public cocos2d::Layer {
public:
    UserSettingsLayer();
    ~UserSettingsLayer();
    
    virtual bool init();
    
    void onBtnBackPressed();
    void onBtnSavePressed();
    
    CREATE_FUNC(UserSettingsLayer);
private:
    cocos2d::Sprite *_back;
    cocos2d::Sprite *_mntHeading;
    cocos2d::MenuItemImage *_btnBack;
};

#endif /* defined(__ttt_c_tracker__UserSettingsLayer__) */