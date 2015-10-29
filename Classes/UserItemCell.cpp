//
//  UserItemCell.cpp
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 30.10.15.
//
//

#include "UserItemCell.h"

using namespace cocos2d;
using namespace std;

UserItemCell::UserItemCell() {
    _back = nullptr;
    _labelName = nullptr;
    
    _expandArrow = nullptr;
    _table = nullptr;
}

UserItemCell::~UserItemCell() {
}

bool UserItemCell::init(const string &name, ManagerLayer *table) {
    if(!TableViewCell::init()) {
        return false;
    }
    
    _table = table;
    //Size visibleSize = Director::getInstance()->getVisibleSize();
    
    {
        // back
        _back = Sprite::create("bg_item.png");
        addChild(_back);
        
        _back->setPosition(Point::ZERO);
        _back->setAnchorPoint(Point::ZERO);
    }
    
    {
        // caption
        _labelName = Label::createWithTTF(name, "helvetica.ttf", 18);
        _labelName->setColor({93, 93, 93});
        _labelName->setOpacity(0.7 * 255);
        _labelName->setAnchorPoint({0, 0.5});
        _labelName->setPosition({_back->getContentSize().width * 0.04f, _back->getContentSize().height * 0.45f});
        
        _back->addChild(_labelName);
    }
    
    {
        // expand arrow
        _expandArrow = Sprite::create("table_cell_expand_arrow.png");
        _expandArrow->setAnchorPoint({1, 1});
        _expandArrow->setPosition({_back->getContentSize().width, _back->getContentSize().height});
        
        _back->addChild(_expandArrow);
    }
    
    return true;
}

UserItemCell* UserItemCell::create(const string &name, ManagerLayer *table) {
    UserItemCell *result = new UserItemCell();
    
    if(result && result->init(name, table)) {
        result->autorelease();
        return result;
    } else {
        delete result;
        result = NULL;
        return NULL;
    }
}