//
//  ManagerSettingsLayer.h
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 30.10.15.
//
//

#ifndef __ttt_c_tracker__ManagerSettingsLayer__
#define __ttt_c_tracker__ManagerSettingsLayer__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"


class ManagerSettingsLayer: public cocos2d::Layer {
public:
    ManagerSettingsLayer();
    ~ManagerSettingsLayer();
    
    virtual bool init();
    
    void onBtnBackPressed();
    void onBtnLogoutPressed();
    
    CREATE_FUNC(ManagerSettingsLayer);
private:
    cocos2d::Sprite *_back;
    cocos2d::Sprite *_mntHeading;
    cocos2d::MenuItemImage *_btnBack;
    cocos2d::MenuItemImage *_btnLogout;
};


#endif /* defined(__ttt_c_tracker__ManagerSettingsLayer__) */
