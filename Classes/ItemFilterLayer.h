//
//  ItemFilterLayer.h
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 30.10.15.
//
//

#ifndef __ttt_c_tracker__ItemFilterLayer__
#define __ttt_c_tracker__ItemFilterLayer__

#include "Meal.h"

#include "IOnFilterApplied.h"

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"

class ItemFIlterLayer: public cocos2d::Layer, public IOnDateFilterResultFetched, public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate {
public:
    ItemFIlterLayer();
    ~ItemFIlterLayer();
    
    virtual bool init(IOnFilterApplied *delegate);
    
    // table
    void scrollViewDidScroll(cocos2d::extension::ScrollView *view);
    void scrollViewDidZoom(cocos2d::extension::ScrollView *view);
    
    void onMealIemPressed(const std::string &reqId);
    
    void tableCellTouched(cocos2d::extension::TableView *table, cocos2d::extension::TableViewCell *cell);
    
    cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);
    cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
    ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
    //
    
    void onResutFetched(const MealGroup &g);
    
    void onBtnClosePressed();
    
    void onTextEvent(cocos2d::Ref *sender, cocos2d::ui::TextField::EventType event);
    
    static ItemFIlterLayer* create(IOnFilterApplied *delegate);
private:
    // table
    cocos2d::extension::TableView *_tableView;
    cocos2d::Size _cellSize;
    
    cocos2d::Sprite *_back;
    cocos2d::Sprite *_mntHeading;
    cocos2d::MenuItemImage *_btnClose;
    
    cocos2d::ui::TextField *_textFrom;
    cocos2d::ui::TextField *_textTo;
    
    IOnFilterApplied *_delegate;
    
    std::vector<CaloriesPerDay> _items;
};


#endif /* defined(__ttt_c_tracker__ItemFilterLayer__) */
