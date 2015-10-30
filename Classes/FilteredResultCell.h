//
//  FilteredResultCell.h
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 30.10.15.
//
//

#ifndef __ttt_c_tracker__FilteredResultCell__
#define __ttt_c_tracker__FilteredResultCell__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

class MealsLayer;

class FilteredResultCell: public cocos2d::extension::TableViewCell {
public:
    FilteredResultCell();
    virtual ~FilteredResultCell();
    
    virtual bool init(const std::string &date, int calories);
    
    static FilteredResultCell* create(const std::string &date, int calories);
private:
    cocos2d::Sprite *_back;
    
    cocos2d::Label *_labelDate;
    cocos2d::Label *_labelCalories;
};

    

#endif /* defined(__ttt_c_tracker__FilteredResultCell__) */
