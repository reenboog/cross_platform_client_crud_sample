//
//  FilteredResultCell.cpp
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 30.10.15.
//
//

#include "FilteredResultCell.h"

using namespace cocos2d;
using namespace std;

FilteredResultCell::FilteredResultCell() {
    _back = nullptr;
    _labelCalories = nullptr;
    _labelDate = nullptr;
}

FilteredResultCell::~FilteredResultCell() {
}

bool FilteredResultCell::init(const string &date, int calories) {
    if(!TableViewCell::init()) {
        return false;
    }
    
    {
        // back
        _back = Sprite::create("bg_item.png");
        addChild(_back);
        
        _back->setPosition(Point::ZERO);
        _back->setAnchorPoint(Point::ZERO);
    }
    
    {
        // caption
        _labelDate = Label::createWithTTF(date, "helvetica.ttf", 18);
        _labelDate->setColor({93, 93, 93});
        _labelDate->setOpacity(0.7 * 255);
        _labelDate->setAnchorPoint({0, 0.0});
        _labelDate->setPosition({_back->getContentSize().width * 0.04f, _back->getContentSize().height * 0.12f});
        
        _back->addChild(_labelDate);
    }
    
    {
        // calories
        _labelCalories = Label::createWithTTF(StringUtils::format("%i", calories), "helvetica.ttf", 31);
        _labelCalories->setColor({53, 172, 225});
        _labelCalories->setAnchorPoint({0, 1.0});
        _labelCalories->setPosition({_back->getContentSize().width * 0.04f, _back->getContentSize().height * 0.94f});
        
        _back->addChild(_labelCalories);
    }
    
    return true;
}

FilteredResultCell* FilteredResultCell::create(const string &date, int calories) {
    
    FilteredResultCell *result = new FilteredResultCell();
    
    if(result && result->init(date, calories)) {
        result->autorelease();
        return result;
    } else {
        delete result;
        result = NULL;
        return NULL;
    }
}