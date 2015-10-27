
#include "LoginLayer.h"
#include "LoginLayerOnKeyboardEnterExit.h"
#include "SimpleAudioEngine.h"

#include "ServerAPI.h"

#include "Toast.h"
#include "LayerBlocker.h"

#include "User.h"

#define zBack 0

using namespace cocos2d;
using namespace ui;
using namespace std;

LoginLayer::~LoginLayer() {
    
}

LoginLayer::LoginLayer(): Layer() {
    _back = nullptr;
 
    _menuLogin = nullptr;
    
    _btnLinkLogin = nullptr;
    _btnLinkSignup = nullptr;
    _btnLogin = nullptr;
    _btnSignup = nullptr;
    
    _mntCridentials = nullptr;
    _unknownAvatar = nullptr;
    
    _textMail = nullptr;
    _textPassword = nullptr;
    
    _layout = nullptr;
}

Scene* LoginLayer::scene() {
    auto scene = Scene::create();
    auto layer = LoginLayer::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool LoginLayer::init() {
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
    
    {
        // links
        _btnLinkLogin = MenuItemImage::create("btn_link_login.png", "btn_link_login_on.png", CC_CALLBACK_0(LoginLayer::onBtnLinkLoginPressed, this));
        _btnLinkLogin->setVisible(false);
        _btnLinkLogin->setPosition({visibleSize.width * 0.5f, 0});
        _btnLinkLogin->setAnchorPoint({0.5f, 0});
        
        _btnLinkSignup = MenuItemImage::create("btn_link_signup.png", "btn_link_signup_on.png", CC_CALLBACK_0(LoginLayer::onBtnLinkSignupPressed, this));
        _btnLinkSignup->setPosition(_btnLinkLogin->getPosition());
        _btnLinkSignup->setAnchorPoint(_btnLinkLogin->getAnchorPoint());
    }
    
    {
        // buttons & mounts
        _btnLogin = MenuItemImage::create("btn_login.png", "btn_login_on.png", CC_CALLBACK_0(LoginLayer::onBtnLoginPressed, this));

        _btnSignup = MenuItemImage::create("btn_signup.png", "btn_signup_on.png", CC_CALLBACK_0(LoginLayer::onBtnSignupPressed, this));
        _btnSignup->setVisible(false);
        
        _mntCridentials = Sprite::create("mnt_cridentials.png");
        _mntCridentials->setAnchorPoint({0.5f, 1});
        
        Size cridentialsSize(_mntCridentials->getContentSize().width + _btnLogin->getContentSize().width, _mntCridentials->getContentSize().height + _btnLogin->getContentSize().height);
        
        _mntCridentials->setPosition({visibleSize.width * 0.5f, visibleSize.height * 0.5f + cridentialsSize.height * 0.5f});
        
        _layout->addChild(_mntCridentials);
        
        _btnLogin->setAnchorPoint({0.5f, 1.0f});
        _btnLogin->setPosition({visibleSize.width * 0.5f, _mntCridentials->getPositionY() - _mntCridentials->getContentSize().height});
        
        _btnSignup->setAnchorPoint(_btnLogin->getAnchorPoint());
        _btnSignup->setPosition(_btnLogin->getPosition());
        
        // unknown avatar
        _unknownAvatar = Sprite::create("unknown_avatar.png");
        
        _unknownAvatar->setPosition(visibleSize.width * 0.5f, visibleSize.height - (visibleSize.height - _mntCridentials->getPositionY()) / 2.0f);
        
        _layout->addChild(_unknownAvatar);
        
        // text fields
        // mail
        _textMail = TextField::create("e-mail", "helvetica.ttf", 22);
        _mntCridentials->addChild(_textMail);

        _textMail->addEventListener(CC_CALLBACK_2(LoginLayer::onTextMailEvent, this));
        _textMail->setPosition({_mntCridentials->getContentSize().width * 0.15f, _mntCridentials->getContentSize().height * 0.74f});
        _textMail->setMaxLength(23);
        _textMail->setMaxLengthEnabled(true);
        _textMail->setAnchorPoint({0, 0.5});
        _textMail->setColor({93, 93, 93});
        _textMail->setPlaceHolderColor({93, 93, 93, 100});
        
        // pasword
        _textPassword = TextField::create("password", "helvetica.ttf", 22);
        _mntCridentials->addChild(_textPassword);
        
        _textPassword->addEventListener(CC_CALLBACK_2(LoginLayer::onTextPasswordEvent, this));
        _textPassword->setPosition({_mntCridentials->getContentSize().width * 0.15f, _mntCridentials->getContentSize().height * 0.27f});
        _textPassword->setMaxLength(20);
        _textPassword->setMaxLengthEnabled(true);
        _textPassword->setAnchorPoint({0, 0.5});
        _textPassword->setColor({93, 93, 93});
        _textPassword->setPlaceHolderColor({93, 93, 93, 100});
        _textPassword->setPasswordEnabled(true);
        _textPassword->setPasswordStyleText("*");
    }
    
    _menuLogin = Menu::create(_btnLinkLogin, _btnLinkSignup, _btnLogin, _btnSignup, nullptr);
    _menuLogin->setPosition({0, 0});
    
    _layout->addChild(_menuLogin);
    
    //this->restoreSessionIfAny();
    
    return true;
}

void LoginLayer::restoreSessionIfAny() {
    LayerBlocker::block(this);
    
    auto onWakeUp = [this]() {
        //this->onLoggedIn();
    };
    
    auto onFailedToWakeUp = [this](const string &error, const string &message) {
        LayerBlocker::unblock(this);
    };
    
    // todo
    ServerAPI::wakeUp(onWakeUp, onFailedToWakeUp);
}

void LoginLayer::onBtnLinkLoginPressed() {
    _btnLinkSignup->setVisible(true);
    _btnLinkLogin->setVisible(false);
    
    _btnSignup->setVisible(false);
    _btnLogin->setVisible(true);
}

void LoginLayer::onBtnLinkSignupPressed() {
    _btnLinkSignup->setVisible(false);
    _btnLinkLogin->setVisible(true);
    
    _btnSignup->setVisible(true);
    _btnLogin->setVisible(false);
}

void LoginLayer::onBtnLoginPressed() {
    
}

void LoginLayer::onBtnSignupPressed() {
}

void LoginLayer::onTextMailEvent(cocos2d::Ref *sender, TextField::EventType event) {
    switch(event) {
        case TextField::EventType::ATTACH_WITH_IME:
            this->onKeyboardEnter(); break;
        case TextField::EventType::DETACH_WITH_IME:
            this->onKeyboardExit(); break;
    }
}

void LoginLayer::onTextPasswordEvent(cocos2d::Ref *sender, cocos2d::ui::TextField::EventType event) {
    switch(event) {
        case TextField::EventType::ATTACH_WITH_IME:
            this->onKeyboardEnter(); break;
        case TextField::EventType::DETACH_WITH_IME:
            this->onKeyboardExit(); break;
    }
}

//void LoginLayer::onLoginWithVKBtnPresed() {
//    LayerBlocker::block(this, 10);
//    Toast::show(this, "Logging in...");
//    
//    auto onLoggedIn = [=]() {
//        //this->onLoggedIn();
//    };
//    
//    auto onFailedToLogIn = [=](const string &error, const string &description) {
//        //this->onFailedToLogIn(error, description);
//    };
//    
//    // todo
//    //ServerAPI::logIn(onLoggedIn, onFailedToLogIn);
//}