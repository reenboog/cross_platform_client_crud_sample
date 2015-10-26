
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
    
    void onLoginWithVKBtnPresed();
    void onSignupWithVKBtnPressed();
    
private:
    void restoreSessionIfAny();
private:
    cocos2d::Sprite *_back;
    
    cocos2d::Menu *_loginMenu;
    cocos2d::MenuItemImage *_btnLoginWithVK;
};

#endif