//
//  LoginLayerOnKeyboardEnterExit.h
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 27.10.15.
//
//

#ifndef ttt_c_tracker_LoginLayerOnKeyboardEnterExit_h
#define ttt_c_tracker_LoginLayerOnKeyboardEnterExit_h

#include "LoginLayer.h"

using namespace cocos2d;

void LoginLayer::onKeyboardEnter() {
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    _layout->setPositionY((visibleSize.height - _mntCridentials->getPositionY()) / 2.0f);
}

void LoginLayer::onKeyboardExit() {
    _layout->setPositionY(0);
}

#endif