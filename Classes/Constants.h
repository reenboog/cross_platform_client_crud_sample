#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#define NC_ADD(name, handler) cocos2d::Director::getInstance()->getEventDispatcher()->\
                                        addCustomEventListener(name, handler)

#define NC_POST(name, data) cocos2d::Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(name, data)

#endif // __CONSTANTS_H__