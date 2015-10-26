
#include "LoginLayer.h"
#include "SimpleAudioEngine.h"

#include "ServerAPI.h"

#include "Toast.h"
#include "LayerBlocker.h"

#include "User.h"

#define zBack 0

using namespace cocos2d;
using namespace std;

LoginLayer::~LoginLayer() {
    
}

LoginLayer::LoginLayer(): Layer() {
    _back = nullptr;
 
    _btnLoginWithVK = nullptr;
    _loginMenu = nullptr;
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
    
//    _btnLoginWithVK = MenuItemImage::create("btn_login_vk.png", "btn_login_vk_on.png", CC_CALLBACK_0(LoginLayer::onLoginWithVKBtnPresed, this));
//
//    _loginMenu = Menu::create(_btnLoginWithVK, nullptr);
//    _loginMenu->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
//    
//    this->addChild(_loginMenu);
    
    this->restoreSessionIfAny();
    
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

void LoginLayer::onLoginWithVKBtnPresed() {
    LayerBlocker::block(this, 10);
    Toast::show(this, "Logging in...");
    
    auto onLoggedIn = [=]() {
        //this->onLoggedIn();
    };
    
    auto onFailedToLogIn = [=](const string &error, const string &description) {
        //this->onFailedToLogIn(error, description);
    };
    
    // todo
    //ServerAPI::logIn(onLoggedIn, onFailedToLogIn);
}