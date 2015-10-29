//
//  MealItemCell.cpp
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 29.10.15.
//
//

#include "MealItemCell.h"

#include "Date.h"

// table_cell_expand_arrow
using namespace cocos2d;
using namespace std;

MealItemCell::MealItemCell() {
    _back = nullptr;
    _labelCalories = nullptr;
    _labelCaption = nullptr;
    _labelTime = nullptr;
    
    _expandArrow = nullptr;
}

MealItemCell::~MealItemCell() {
}

bool MealItemCell::init(const string &caption,
                        int calories,
                        int time,
                        MealsLayer *table) {
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
        _labelCaption = Label::createWithTTF(caption, "helvetica.ttf", 18);
        _labelCaption->setColor({93, 93, 93});
        _labelCaption->setOpacity(0.7 * 255);
        _labelCaption->setAnchorPoint({0, 0.0});
        _labelCaption->setPosition({_back->getContentSize().width * 0.04f, _back->getContentSize().height * 0.12f});
        
        _back->addChild(_labelCaption);
    }
    
    {
        // calories
        _labelCalories = Label::createWithTTF(StringUtils::format("%i", calories), "helvetica.ttf", 31);
        _labelCalories->setColor({53, 172, 225});
        _labelCalories->setAnchorPoint({0, 1.0});
        _labelCalories->setPosition({_back->getContentSize().width * 0.04f, _back->getContentSize().height * 0.94f});
        
        _back->addChild(_labelCalories);
    }
    
    {
        // expand arrow
        _expandArrow = Sprite::create("table_cell_expand_arrow.png");
        _expandArrow->setAnchorPoint({1, 1});
        _expandArrow->setPosition({_back->getContentSize().width, _back->getContentSize().height});
        
        _back->addChild(_expandArrow);
    }
    
    {
        // time label
        _labelTime = Label::createWithTTF(Date::timeStrForSeconds(time), "helvetica.ttf", 14);
        _labelTime->setColor({93, 93, 93});
        _labelTime->setOpacity(0.4f * 255);
        _labelTime->setAnchorPoint({1, 0.5f});
        _labelTime->setPosition({0, _expandArrow->getContentSize().height * 0.45f});
        
        _expandArrow->addChild(_labelTime);
    }
    
    return true;
}

MealItemCell* MealItemCell::create(const string &caption,
                                   int calories,
                                   int time,
                                   MealsLayer *table) {

    MealItemCell *result = new MealItemCell();
    
    if(result && result->init(caption, calories, time, table)) {
        result->autorelease();
        return result;
    } else {
        delete result;
        result = NULL;
        return NULL;
    }
}