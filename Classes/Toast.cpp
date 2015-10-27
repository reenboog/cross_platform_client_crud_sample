
#include "Toast.h"

#define kToastFadeInTime 0.2f
#define kToastFadeOutTime 0.2f
#define kToastTag 6364

#define zToast 100

using namespace cocos2d;
using namespace std;

void Toast::show(Layer *layer, const string &str, float delay) {
    
    
    Toast *toast = static_cast<Toast*>(layer->getChildByTag(kToastTag));
    if(toast) {
        layer->removeChild(toast);
    }
    
    toast = new Toast();
    toast->init(str, delay);
    
    layer->addChild(toast, zToast, kToastTag);
    
    toast->autorelease();
}

bool Toast::init(const string &str, float delay) {
    if(!Node::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    Sprite *mount = Sprite::create("toast.png");
    this->addChild(mount);
    
    mount->setScaleX(visibleSize.width / mount->getContentSize().width);
    //mount->setAnchorPoint({0.5, 0});
    mount->setPosition({visibleSize.width * 0.5f, visibleSize.height + mount->getContentSize().height * 0.5f});
    mount->setOpacity(0);
    
    // add label
    Label *label = Label::createWithTTF(str, "helvetica.ttf", 20);
    label->setColor({255, 255, 255});
    
    this->addChild(label);
    
    label->setPosition(mount->getPosition());
    label->setOpacity(0);
    
    mount->runAction(Sequence::create(Spawn::create(FadeTo::create(kToastFadeInTime, 255),
                                                    MoveBy::create(kToastFadeInTime, -Vec2(0, mount->getContentSize().height)),
                                                    NULL),
                                      DelayTime::create(delay),
                                      Spawn::create(MoveBy::create(kToastFadeInTime, Vec2(0, mount->getContentSize().height)),
                                                    NULL),
                                      NULL));
    
    label->runAction(Sequence::create(Spawn::create(FadeTo::create(kToastFadeInTime, 255),
                                                    MoveBy::create(kToastFadeInTime, -Vec2(0, mount->getContentSize().height)),
                                                    NULL),
                                      DelayTime::create(delay),
                                      Spawn::create(MoveBy::create(kToastFadeInTime, Vec2(0, mount->getContentSize().height)),
                                                    NULL),
                                      NULL));
    
    this->runAction(Sequence::create(DelayTime::create(delay + kToastFadeInTime + kToastFadeOutTime),
                                     CallFunc::create([this]() {
        this->removeFromParent();
    }), NULL));
    
    return true;
}