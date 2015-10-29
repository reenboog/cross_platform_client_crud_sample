//
//  Header.h
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 30.10.15.
//
//

#ifndef ttt_c_tracker_Layers_h
#define ttt_c_tracker_Layers_h

#include "cocos2d.h"

#include "User.h"

#include "MealsLayer.h"
#include "ManagerLayer.h"

using namespace cocos2d;

class LayerManager {
public:
    static void showScreenForRole(User::Role role, bool replace = true) {
        switch(role) {
            case User::Role::UR_User:
                if(replace) {
                    Director::getInstance()->replaceScene(MealsLayer::scene());
                } else {
                    Director::getInstance()->runWithScene(MealsLayer::scene());
                }
                break;
            case User::Role::UR_Manager:
                if(replace) {
                    Director::getInstance()->replaceScene(ManagerLayer::scene());
                } else {
                    Director::getInstance()->runWithScene(ManagerLayer::scene());
                }
                break;
            default:
                break;
        }
    }

private:
    LayerManager() {}
};

#endif
