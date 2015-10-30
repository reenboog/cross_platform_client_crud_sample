//
//  ItemFilterLayer.h
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 30.10.15.
//
//

#ifndef __ttt_c_tracker__ItemFilterLayer__
#define __ttt_c_tracker__ItemFilterLayer__

#include "IOnFilterApplied.h"

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

class ItemFIlterLayer: public cocos2d::Layer, public IOnDateFilterResultFetched {
public:
    ItemFIlterLayer();
    ~ItemFIlterLayer();
    
    virtual bool init(IOnFilterApplied *delegate);
    
    void onResutFetched(const MealGroup &g);
    
    void onBtnClosePressed();
    
    void onTextEvent(cocos2d::Ref *sender, cocos2d::ui::TextField::EventType event);
    
    static ItemFIlterLayer* create(IOnFilterApplied *delegate);
private:
    cocos2d::Sprite *_back;
    cocos2d::Sprite *_mntHeading;
    cocos2d::MenuItemImage *_btnClose;
    
    cocos2d::ui::TextField *_textFrom;
    cocos2d::ui::TextField *_textTo;
    
    IOnFilterApplied *_delegate;
};


#endif /* defined(__ttt_c_tracker__ItemFilterLayer__) */
