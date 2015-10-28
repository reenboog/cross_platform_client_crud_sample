
#include "AppDelegate.h"
#include "LoginLayer.h"
#include "SimpleAudioEngine.h"
#include "AppConfig.h"
#include "Localized.h"
#include "User.h"
#include "ServerAPI.h"
#include "MealsLayer.h"

// tests
#include "Tests.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate()  {
    ServerAPI::purge();
    Localized::purge();
    AppConfig::purge();
    User::purge();
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("ttt_c_tracker");
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    AppConfig::sharedInstance()->loadFilePaths();
    AppConfig::sharedInstance()->load();
    
    Localized::load();
    
//    auto onWakeUp = [=]() {
//        director->runWithScene(MealsLayer::scene());
//    };
//    
//    auto onFailedToWakeUp = [=](const string &error, const string &message) {
//        director->runWithScene(LoginLayer::scene());
//    };
//    
//    ServerAPI::wakeUp(onWakeUp, onFailedToWakeUp);
    
    // *************************************************
    // run some models tests
    test();
    // *************************************************
    
    director->runWithScene(MealsLayer::scene());

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
