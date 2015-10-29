//
//  MealItemCell.h
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 29.10.15.
//
//

#ifndef __ttt_c_tracker__MealItemCell__
#define __ttt_c_tracker__MealItemCell__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"

class MealsLayer;

class MealItemCell: public cocos2d::extension::TableViewCell {
public:
    MealItemCell();
    virtual ~MealItemCell();
    
    virtual bool init(const std::string &caption,
                      int calories,
                      int time,
                      MealsLayer *table);
    
    static MealItemCell* create(const std::string &caption,
                                int calories,
                                int time,
                                MealsLayer *table);
private:
    cocos2d::Sprite *_back;
    
    cocos2d::Label *_labelTime;
    cocos2d::Label *_labelCaption;
    cocos2d::Label *_labelCalories;
    
    cocos2d::Sprite *_expandArrow;
    
    MealsLayer *_table;
};

#endif /* defined(__ttt_c_tracker__MealItemCell__) */
