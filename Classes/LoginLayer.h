
#ifndef __GAME_LAYER_H__
#define __GAME_LAYER_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

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
    
    void onTextMailEvent(cocos2d::Ref *sender, cocos2d::ui::TextField::EventType event);
    void onTextPasswordEvent(cocos2d::Ref *sender, cocos2d::ui::TextField::EventType event);
    
    void onKeyboardEnter();
    void onKeyboardExit();
    
    // server API callbacks
private:
    void onSignedUp();
    void onFailedToSignUp(const std::string &error, const std::string &description);
    
    void onLoggedIn();
    void onFailedToLogIn(const std::string &error, const std::string &description);
    
private:
    cocos2d::Sprite *_back;
    
    cocos2d::Menu *_menuLogin;
    
    cocos2d::MenuItemImage *_btnLinkSignup;
    cocos2d::MenuItemImage *_btnLinkLogin;
    
    cocos2d::MenuItemImage *_btnSignup;
    cocos2d::MenuItemImage *_btnLogin;
    
    cocos2d::Sprite *_mntCridentials;
    cocos2d::Sprite *_unknownAvatar;
    
    cocos2d::ui::TextField *_textMail;
    cocos2d::ui::TextField *_textPassword;
    
    cocos2d::Layer *_layout;
};

#endif