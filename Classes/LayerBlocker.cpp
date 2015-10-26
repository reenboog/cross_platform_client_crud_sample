
#include "LayerBlocker.h"

#define kLayerBlockerTag 3564
#define zLayerBlocker 200

using namespace cocos2d;

void LayerBlocker::block(Layer *target, float delay) {
    LayerBlocker::unblock(target);
    
    LayerBlocker *blocker = new LayerBlocker();

    blocker->init(target, delay);
    blocker->setPosition({0, 0});
    
    target->addChild(blocker, zLayerBlocker, kLayerBlockerTag);
    
    blocker->autorelease();
}

bool LayerBlocker::init(Layer *target, float delay) {
    if(!Node::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    MenuItemImage *btn = MenuItemImage::create("blank.png", "blank.png", [](Ref *){});
    btn->setScale(visibleSize.width / btn->getContentSize().width, visibleSize.height / btn->getContentSize().height);
    btn->setOpacity(0);
    
    Menu *blockMenu = Menu::create(btn, nullptr);
    blockMenu->setPosition({visibleSize.width * 0.5f, visibleSize.height * 0.5f});
    
    this->addChild(blockMenu);
    
    if(delay != -1) {
        blockMenu->runAction(Sequence::create(DelayTime::create(delay),
                                              CallFunc::create([=]() {
            LayerBlocker::unblock(target);
        }), nullptr));
    }
    
    return true;
}


void LayerBlocker::unblock(cocos2d::Layer *target) {
    LayerBlocker *blocker = static_cast<LayerBlocker*>(target->getChildByTag(kLayerBlockerTag));

    if(blocker) {
        target->removeChild(blocker);
    }
}