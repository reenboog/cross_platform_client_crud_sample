//
//  ItemFilterLayer.cpp
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 30.10.15.
//
//

#include "ItemFilterLayer.h"
#include "FilteredResultCell.h"

#include <map>

#define zBack 0

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace ui;
using namespace std;

ItemFIlterLayer::~ItemFIlterLayer() {
    
}

ItemFIlterLayer::ItemFIlterLayer() {
    _back = nullptr;
    _mntHeading = nullptr;
    _btnClose = nullptr;
    
    _textFrom = nullptr;
    _textTo = nullptr;
    
    _delegate = nullptr;
}

ItemFIlterLayer* ItemFIlterLayer::create(IOnFilterApplied *delegate) {
    ItemFIlterLayer *pRet = new ItemFIlterLayer();
    
    if(pRet && pRet->init(delegate)) {
        pRet->autorelease();
        return pRet;
    } else {
        delete pRet;
        pRet = NULL;
        return NULL;
    }
}

bool ItemFIlterLayer::init(IOnFilterApplied *delegate) {
    if(!Layer::init()) {
        return false;
    }
    
    _delegate = delegate;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // back
    {
        Sprite *mntHead = Sprite::create("mnt_meals_list_head.png");
        Sprite *mntProgress = Sprite::create("bg_progress_calories.png");
        Sprite *mntDate = Sprite::create("mnt_meals_list_date.png");
        
        _back = Sprite::create("back.png");
        
        _back->setOpacity(0.9f * 255);
        _back->setAnchorPoint({0, 1});
        _back->setPosition({0.0f, visibleSize.height - mntHead->getContentSize().height - mntProgress->getContentSize().height - mntDate->getContentSize().height});
        
        Size backSize = _back->getContentSize();
        
        _back->setScale(visibleSize.width / backSize.width, visibleSize.height / backSize.height);
        
        this->addChild(_back, zBack);
    }
    
    {
        // parent blocker
        MenuItemImage *btn = MenuItemImage::create("blank.png", "blank.png", [](Ref *){});
        btn->setScale(visibleSize.width / btn->getContentSize().width, visibleSize.height / btn->getContentSize().height);
        btn->setOpacity(0);
        
        Menu *blockMenu = Menu::create(btn, nullptr);
        blockMenu->setPosition({visibleSize.width * 0.5f, visibleSize.height * 0.5f});
        
        this->addChild(blockMenu);
    }
    
    {
        // heading
        _mntHeading = Sprite::create("mnt_filter_heading.png");
        _mntHeading->setAnchorPoint({0, 1});
        _mntHeading->setPosition(_back->getPosition());
        
        this->addChild(_mntHeading);
    }
    
    {
        // buttons
        _btnClose = MenuItemImage::create("btn_close.png", "btn_close_on.png", CC_CALLBACK_0(ItemFIlterLayer::onBtnClosePressed, this));
        _btnClose->setAnchorPoint({0.5, 0});
        _btnClose->setPosition({_mntHeading->getContentSize().width * 0.5f, 0});
        
        Menu *closeMenu = Menu::create(_btnClose, nullptr);
        closeMenu->setPosition({0, 0});
        
        _mntHeading->addChild(closeMenu);
    }
    
    {
        // "%d %b %Y %H:%M"
        _textFrom = TextField::create("30 Oct 2015 00:00", "helvetica.ttf", 21);
        _mntHeading->addChild(_textFrom);
        
        _textFrom->addEventListener(CC_CALLBACK_2(ItemFIlterLayer::onTextEvent, this));
        _textFrom->setPosition({_mntHeading->getContentSize().width * 0.04f, _mntHeading->getContentSize().height * 0.73f});
        _textFrom->setMaxLength(20);
        _textFrom->setMaxLengthEnabled(true);
        _textFrom->setAnchorPoint({0, 0.5});
        _textFrom->setColor({93, 93, 93});
        _textFrom->setPlaceHolderColor({93, 93, 93, 100});
        
        //
        // "%d %b %Y %H:%M"
        _textTo = TextField::create("30 Oct 2015 00:00", "helvetica.ttf", 20);
        _mntHeading->addChild(_textTo);
        
        _textTo->addEventListener(CC_CALLBACK_2(ItemFIlterLayer::onTextEvent, this));
        _textTo->setPosition({_mntHeading->getContentSize().width * 0.52f, _mntHeading->getContentSize().height * 0.73f});
        _textTo->setMaxLength(20);
        _textTo->setMaxLengthEnabled(true);
        _textTo->setAnchorPoint({0, 0.5});
        _textTo->setColor({93, 93, 93});
        _textTo->setPlaceHolderColor({93, 93, 93, 100});
    }
    
    //
    {
        // table view
        Sprite *cell = Sprite::create("bg_item.png");
        
        _cellSize = Size(cell->getContentSize().width, cell->getContentSize().height);
        _tableView = TableView::create(this, Size(_cellSize.width, _mntHeading->getPositionY() - _mntHeading->getContentSize().height));
        _tableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);
        _tableView->setPosition(Point(0, 0));
        _tableView->setDelegate(this);
        _tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
        
        this->addChild(_tableView);
        
//        _items.push_back(CaloriesPerDay(Date(2015, 10, 29), 3000));
//        _items.push_back(CaloriesPerDay(Date(2015, 10, 30), 3000));
//        _items.push_back(CaloriesPerDay(Date(2015, 10, 31), 200));
//        _items.push_back(CaloriesPerDay(Date(2015, 10, 30), 3000));
        
        _tableView->reloadData();
    }
    
    return true;
}

void ItemFIlterLayer::onBtnClosePressed() {
    this->removeFromParent();
}

void ItemFIlterLayer::onResutFetched(const MealGroup &g) {
    // reload tables here
    // recalc items
    // reload table
    
    map<Date, int> totalCaloriesPerDays;
    
    for(int i = 0; i < g.size(); ++i) {
        Meal m = g.get(i);
        Date currentDate = m.getConsumptioDate();
        auto it = totalCaloriesPerDays.find(currentDate);
        
        if(it == totalCaloriesPerDays.end()) {
            totalCaloriesPerDays.insert({currentDate, m.getCalories()});
        } else {
            it->second += m.getCalories();
        }
    }
    
    _items.clear();
    
    for(auto it = totalCaloriesPerDays.begin(); it != totalCaloriesPerDays.end(); ++it) {
        _items.push_back(CaloriesPerDay(it->first, it->second));
    }
    
    _tableView->reloadData();
}

#pragma mark - Text dates

void ItemFIlterLayer::onTextEvent(cocos2d::Ref *sender, TextField::EventType event) {
//    switch(event) {
//        case TextField::EventType::ATTACH_WITH_IME:
//            this->onKeyboardEnter(); break;
//        case TextField::EventType::DETACH_WITH_IME:
//            this->onKeyboardExit(); break;
//    }
    // INSERT_TEXT,
//    DELETE_BACKWARD,
    if(event == TextField::EventType::INSERT_TEXT || event == TextField::EventType::DELETE_BACKWARD) {
        Date dateFrom = Date::dateFromString(_textFrom->getString());
        int timeFrom = Date::timeFromDateString(_textFrom->getString());
        
        Date dateTo = Date::dateFromString(_textTo->getString());
        int timeTo = Date::timeFromDateString(_textTo->getString());
        
        _delegate->onFilterApplied(this, dateFrom, dateTo, timeFrom, timeTo);
    }
    
}

#pragma mark - Table delegates

void ItemFIlterLayer::scrollViewDidScroll(cocos2d::extension::ScrollView *view) {
}

void ItemFIlterLayer::scrollViewDidZoom(cocos2d::extension::ScrollView *view) {
}

void ItemFIlterLayer::tableCellTouched(TableView *table, TableViewCell *cell) {
    // a button pressed?
    unsigned int idx = cell->getTag();
    CCLOG("touched: %i", idx);
}

ssize_t ItemFIlterLayer::numberOfCellsInTableView(TableView *table) {
    //return _requests.size();
    return _items.size();
}

Size ItemFIlterLayer::tableCellSizeForIndex(TableView *table, ssize_t idx) {
    return this->_cellSize;
}

extension::TableViewCell* ItemFIlterLayer::tableCellAtIndex(TableView *table, ssize_t idx) {
    TableViewCell *cell = table->cellAtIndex(idx);
    
    if(cell == nullptr) {
        Date d = _items[idx]._date;

        string strDate = StringUtils::format("%i.%i.%i", d.getDay(), d.getMonth(), d.getYear());
        int calories = _items[idx]._calories;
        
        cell = FilteredResultCell::create(strDate, calories);
        cell->setTag(idx);
    }
    
    return cell;
}