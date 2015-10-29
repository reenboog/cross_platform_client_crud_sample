//
//  MealsLayer.h
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 27.10.15.
//
//

#ifndef __ttt_c_tracker__MealsLayer__
#define __ttt_c_tracker__MealsLayer__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include "MealGroup.h"

#include "IOnGoalChanged.h"
#include "IOnItemCreated.h"

class MealsLayer: public cocos2d::Layer, public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate, public IOnGoalChanged, public IOnItemCreated {
public:
    MealsLayer();
    ~MealsLayer();
    
    static cocos2d::Scene* scene();
    
    virtual bool init();
        
    void onBtnSettingsPressed();
    void onBtnDateSelectPressed();
    void onBtnAddItemPressed();
    
    void setTotalCaloriesConsumed(int calories);
    
    // items CRUD
    void onItemCreated(const Meal &m);
    void onItemCreationCanceled();
    
    // IOnGOalCHanged delegates
    void onGoalChanged(int newGoal);
    
    // table view
    // table view methods
    void scrollViewDidScroll(cocos2d::extension::ScrollView *view);
    void scrollViewDidZoom(cocos2d::extension::ScrollView *view);
    
    void onMealIemPressed(const std::string &reqId);
    
    void tableCellTouched(cocos2d::extension::TableView *table, cocos2d::extension::TableViewCell *cell);
    
    cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx);
    cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
    ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
    //
    
    CREATE_FUNC(MealsLayer);
private:
    cocos2d::Sprite *_back;
    cocos2d::Layer *_layout;
    
    // table
    cocos2d::extension::TableView *_mealsTableView;
    cocos2d::Size _mealCellSize;
    
    // heading
    cocos2d::Node *_headingNode;
    cocos2d::Sprite *_mntHead;
    cocos2d::MenuItemImage *_btnSettings;
    cocos2d::Label *_labelMail;
    cocos2d::Label *_labelCaloriesConsumed;
    cocos2d::Sprite *_bgProgressCalories;
    cocos2d::ProgressTimer *_progressCaloriesConsumed;
    cocos2d::Sprite *_mntDate;
    cocos2d::MenuItemImage *_btnDateSelect;
    cocos2d::MenuItemImage *_btnAddItem;
    cocos2d::Label *_labelDate;
    
    // selection data
    int _currentCalories;
    Date _selectedDate;
    
    // local model
    MealGroup _meals;
};

#endif /* defined(__ttt_c_tracker__MealsLayer__) */
