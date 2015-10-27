
#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"

class LoginLayer: public cocos2d::Layer {
public:
    LoginLayer();
    ~LoginLayer();
    
    static cocos2d::Scene* scene();

    virtual bool init();
    
    CREATE_FUNC(LoginLayer);
    
    void onBtnLinkLoginPressed();
    void onBtnLinkSignupPressed();
    
    void onBtnLoginPressed();
    void onBtnSignupPressed();
    
private:
    void restoreSessionIfAny();
private:
    cocos2d::Sprite *_back;
    
    cocos2d::Menu *_menuLogin;
    
    cocos2d::MenuItemImage *_btnLinkSignup;
    cocos2d::MenuItemImage *_btnLinkLogin;
    
    cocos2d::MenuItemImage *_btnSignup;
    cocos2d::MenuItemImage *_btnLogin;
    
    cocos2d::Sprite *_mntCridentials;
    cocos2d::Sprite *_unknownAvatar;
};

#endif