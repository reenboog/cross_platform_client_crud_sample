
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
    
    _btnLoginWithVK = MenuItemImage::create("btn_login_vk.png", "btn_login_vk_on.png", CC_CALLBACK_0(LoginLayer::onLoginWithVKBtnPresed, this));

    _loginMenu = Menu::create(_btnLoginWithVK, nullptr);
    _loginMenu->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
    
    this->addChild(_loginMenu);
    
    this->restoreSessionIfAny();
    
    return true;
}

void LoginLayer::restoreSessionIfAny() {
    LayerBlocker::block(this);
    
    auto onWakeUp = [this]() {
        this->onLoggedIn();
    };
    
    auto onFailedToWakeUp = [this](const string &error, const string &message) {
        LayerBlocker::unblock(this);
    };
    
    ServerAPI::wakeUp(onWakeUp, onFailedToWakeUp);
}

void LoginLayer::onLoginWithVKBtnPresed() {
    LayerBlocker::block(this, 10);
    Toast::show(this, "Logging in...");
    
    auto onLoggedIn = [=]() {
        this->onLoggedIn();
    };
    
    auto onFailedToLogIn = [=](const string &error, const string &description) {
        this->onFailedToLogIn(error, description);
    };
    
    ServerAPI::logIn(onLoggedIn, onFailedToLogIn);
}

void LoginLayer::onLoggedIn() {
    Toast::show(this, "Logged in.");
    
    this->fetchUserNameAndLastName();
}

void LoginLayer::onFailedToLogIn(const string &error, const string &description) {
    Toast::show(this, description);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    if(error.compare(kResponseStatusUserDoesNotExist) == 0) {
        _loginMenu->removeFromParent();
        
        _btnLoginWithVK = MenuItemImage::create("btn_signup_vk.png",
                                                "btn_signup_vk_on.png",
                                                CC_CALLBACK_0(LoginLayer::onSignupWithVKBtnPressed, this));
        
        _loginMenu = Menu::create(_btnLoginWithVK, nullptr);
        _loginMenu->setPosition(visibleSize.width * 0.5f, visibleSize.height * 0.5f);
        
        this->addChild(_loginMenu);
        
        LayerBlocker::unblock(this);
    } else {
        LayerBlocker::unblock(this);
        
        CCLOG("Failed to log in.\n%s\n%s", error.c_str(), description.c_str());
        
        Toast::show(this, description);
    }
}

void LoginLayer::onSignupWithVKBtnPressed() {
    // sign up
    LayerBlocker::block(this, 10);
    Toast::show(this, "Signing up...");
    
    auto onSignedUp = [this]() {
        this->onSignedUp();
    };
    
    auto onFailedToSignUp = [this](const string &error, const string &description) {
        LayerBlocker::unblock(this);
        
        CCLOG("Failed to sign up.\n%s\n%s", error.c_str(), description.c_str());
        
        Toast::show(this, description);
    };
    
    ServerAPI::signUp(onSignedUp, onFailedToSignUp);
}

void LoginLayer::onSignedUp() {
    Toast::show(this, "Signed up.");
    
    this->fetchUserNameAndLastName();
}

void LoginLayer::onFailedToSignUp(const string &error, const string &description) {
    LayerBlocker::unblock(this);
    
    CCLOG("Failed to sign up.\n%s\n%s", error.c_str(), description.c_str());
    
    Toast::show(this, description);
}

void LoginLayer::fetchUserNameAndLastName() {
    auto onUserNameFetched = [=](const string &name, const string &lastName) {
        User::sharedInstance()->setName(name);
        User::sharedInstance()->setLastName(lastName);
        
        // fetch all the skills from db and then, replace scene
        
        auto onSkillsFetched = []() {
            //Director::getInstance()->replaceScene(ProfileLayer::scene());
        };
        
        auto onFailedToFetchSkills = [this](const string &error, const string &description) {
            CCLOG("Failed to fetch skills. Trying once again...");
            
            this->fetchUserNameAndLastName();
        };
        
        ServerAPI::fetchAllSkills(onSkillsFetched, onFailedToFetchSkills);
    };
    
    // would be nice to count attempts and react somehow in case of connetion lost or similar
    auto onFailedToFetchUserName = [this](const string &error, const string &description) {
        // say something bad and try again until succeed
        CCLOG("Failed to fetch user name.\n%s\n%s", error.c_str(), description.c_str());
        
        this->fetchUserNameAndLastName();
    };
    
    ServerAPI::fetchUserNameAndLastName(onUserNameFetched, onFailedToFetchUserName);
}