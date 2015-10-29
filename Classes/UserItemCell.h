//
//  UserItemCell.h
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 30.10.15.
//
//

#ifndef __ttt_c_tracker__UserItemCell__
#define __ttt_c_tracker__UserItemCell__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"


class ManagerLayer;

class UserItemCell: public cocos2d::extension::TableViewCell {
public:
    UserItemCell();
    virtual ~UserItemCell();
    
    virtual bool init(const std::string &name, ManagerLayer *table);
    
    static UserItemCell* create(const std::string &name, ManagerLayer *table);
private:
    cocos2d::Sprite *_back;
    cocos2d::Label *_labelName;
    
    cocos2d::Sprite *_expandArrow;
    
    ManagerLayer *_table;
};

#endif /* defined(__ttt_c_tracker__UserItemCell__) */
