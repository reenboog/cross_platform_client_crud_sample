//
//  ManagerLayer.h
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 30.10.15.
//
//

#ifndef __ttt_c_tracker__ManagerLayer__
#define __ttt_c_tracker__ManagerLayer__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "MealGroup.h"
#include "User.h"

class ManagerLayer: public cocos2d::Layer, public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate {
public:
    ManagerLayer();
    virtual ~ManagerLayer();
    
    static cocos2d::Scene* scene();
    virtual bool init();
    
    // table view
    void scrollViewDidScroll(cocos2d::extension::ScrollView *view);
    void scrollViewDidZoom(cocos2d::extension::ScrollView *view);
    
    void onMealIemPressed(const std::string &reqId);
    
    void tableCellTouched(cocos2d::extension::TableView *table, cocos2d::extension::TableViewCell *cell);
    
    cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);
    cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
    ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
    //
    
    void fetchUsers();
    
    void onBtnSettingsPressed();
    
    CREATE_FUNC(ManagerLayer);
private:
    cocos2d::Sprite *_back;
    
    cocos2d::extension::TableView *_usersTableView;
    cocos2d::Size _userCellSize;
    
    cocos2d::Node *_headingNode;
    cocos2d::Sprite *_mntHead;
    cocos2d::MenuItemImage *_btnSettings;
    cocos2d::Label *_labelMail;
    cocos2d::Label *_labelRole;
    
    std::vector<User> _users;
};

#endif /* defined(__ttt_c_tracker__ManagerLayer__) */
