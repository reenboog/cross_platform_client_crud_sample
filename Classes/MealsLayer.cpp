//
//  MealsLayer.cpp
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 27.10.15.
//
//

#include "MealsLayer.h"
#include "ServerAPI.h"
#include "MealItemCell.h"
#include "UserSettingsLayer.h"

#define zBack 0

using namespace cocos2d;
using namespace cocos2d::extension;
//using namespace ui;
using namespace std;


MealsLayer::~MealsLayer() {
    
}

MealsLayer::MealsLayer(): Layer() {
    _back = nullptr;
    
    _layout = nullptr;
    _mntHead = nullptr;
    _headingNode = nullptr;
    _btnSettings = nullptr;
    _labelMail = nullptr;
    _labelCaloriesConsumed = nullptr;
    _bgProgressCalories = nullptr;
    _progressCaloriesConsumed = nullptr;
    _mntDate = nullptr;
    _btnDateSelect = nullptr;
    _btnAddItem = nullptr;
    _labelDate = nullptr;
    
    _mealsTableView = nullptr;
}

Scene* MealsLayer::scene() {
    auto scene = Scene::create();
    auto layer = MealsLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool MealsLayer::init() {
    if(!Layer::init()) {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    // back
    {
        _back = Sprite::create("back.png");
        _back->setPosition({static_cast<float>(visibleSize.width / 2.0), static_cast<float>(visibleSize.height / 2.0)});
        
        Size backSize = _back->getContentSize();
        
        _back->setScale(visibleSize.width / backSize.width, visibleSize.height / backSize.height);
        
        this->addChild(_back, zBack);
    }
    
    {
        // main layout
        
        _layout = Layer::create();
        this->addChild(_layout);
    }
    
    {
        // heading
        _headingNode = Node::create();
        _headingNode->setPosition({0, 0});

        this->addChild(_headingNode);
        
        _mntHead = Sprite::create("mnt_meals_list_head.png");
        _mntHead->setAnchorPoint({0.0f, 1.0f});
        _mntHead->setPosition({0, visibleSize.height});
        
        _headingNode->addChild(_mntHead);
        
        // settings button
        _btnSettings = MenuItemImage::create("btn_settings.png", "btn_settings_on.png", CC_CALLBACK_0(MealsLayer::onBtnSettingsPressed, this));
        _btnSettings->setAnchorPoint({1, 1});
        _btnSettings->setPosition({visibleSize.width, visibleSize.height});
        
        Menu *settingsMenu = Menu::create(_btnSettings, nullptr);
        settingsMenu->setPosition({0, 0});

        _headingNode->addChild(settingsMenu);
        
        // mail label
        _labelMail = Label::createWithTTF("alex.gievsky@gmail.com", "helvetica.ttf", 18);
        _labelMail->setOpacity(255 * 0.5f);
        _labelMail->setColor({93, 93, 93});
        _labelMail->setAnchorPoint({0, 1});
        _labelMail->setPosition({visibleSize.width * 0.03f, visibleSize.height * 0.98f});
        
        _headingNode->addChild(_labelMail);
        
        // calories consumed
        _labelCaloriesConsumed = Label::createWithTTF("2300 / 4500", "helvetica.ttf", 40);
        _labelCaloriesConsumed->setColor({53, 172, 225});
        _labelCaloriesConsumed->setAnchorPoint({0, 1});
        _labelCaloriesConsumed->setPosition({visibleSize.width * 0.03f, visibleSize.height * 0.98f - _labelMail->getContentSize().height});
        
        _headingNode->addChild(_labelCaloriesConsumed);
        
        // calories progress
        _bgProgressCalories = Sprite::create("bg_progress_calories.png");
        _bgProgressCalories->setAnchorPoint({0, 1});
        _bgProgressCalories->setPosition({0.0f, visibleSize.height - _mntHead->getContentSize().height});
        
        _headingNode->addChild(_bgProgressCalories);
        
        // calories progress
        _progressCaloriesConsumed = ProgressTimer::create(Sprite::create("progress_calories.png"));
        
        _progressCaloriesConsumed->setPosition(_bgProgressCalories->getContentSize().width / 2.0, _bgProgressCalories->getContentSize().height / 2.0);
        _progressCaloriesConsumed->setType(ProgressTimer::Type::BAR);
        _progressCaloriesConsumed->setMidpoint({0, 0});
        _progressCaloriesConsumed->setBarChangeRate({1, 0});
        
        _progressCaloriesConsumed->setPercentage(70);
        
        _bgProgressCalories->addChild(_progressCaloriesConsumed);
        
        // date mount
        _mntDate = Sprite::create("mnt_meals_list_date.png");
        _mntDate->setAnchorPoint({0, 1});
        _mntDate->setPosition({0, _bgProgressCalories->getPositionY() - _bgProgressCalories->getContentSize().height});
        
        _headingNode->addChild(_mntDate);
        
        // date select btn
        _btnDateSelect = MenuItemImage::create("btn_date_select.png", "btn_date_select_on.png", CC_CALLBACK_0(MealsLayer::onBtnDateSelectPressed, this));
        _btnDateSelect->setAnchorPoint({0, 1});
        _btnDateSelect->setPosition({0, _mntDate->getContentSize().height});
        
        Menu *dateSelectMenu = Menu::create(_btnDateSelect, nullptr);
        dateSelectMenu->setPosition({0, 0});
        
        _mntDate->addChild(dateSelectMenu);

        // new item button
        _btnAddItem = MenuItemImage::create("btn_new_item.png", "btn_new_item_on.png", CC_CALLBACK_0(MealsLayer::onBtnAddItemPressed, this));
        _btnAddItem->setAnchorPoint({1, 1});
        _btnAddItem->setPosition({_mntDate->getContentSize().width, _mntDate->getContentSize().height});

        Menu *addItemMenu = Menu::create(_btnAddItem, nullptr);
        addItemMenu->setPosition({0, 0});
        
        _mntDate->addChild(addItemMenu);
        
        // date label
        _labelDate = Label::createWithTTF("28.10.2015", "helvetica.ttf", 18);
        _labelDate->setColor({255, 255, 255});
        _labelDate->setPosition({_mntDate->getContentSize().width * 0.5f, _mntDate->getContentSize().height * 0.5f});
        
        _mntDate->addChild(_labelDate);
        
        //
        {
            // table view
            Sprite *mealCell = Sprite::create("bg_item.png");

            _mealCellSize = Size(mealCell->getContentSize().width, mealCell->getContentSize().height);
            _mealsTableView = TableView::create(this, Size(_mealCellSize.width,
                                                           visibleSize.height - _mntHead->getContentSize().height -
                                                           _bgProgressCalories->getContentSize().height - _mntDate->getContentSize().height));
            _mealsTableView->setDirection(ScrollView::Direction::VERTICAL);
            _mealsTableView->setPosition(Point(0, 0));
            _mealsTableView->setDelegate(this);
            _mealsTableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
            
            this->addChild(_mealsTableView);
            
            
            // fake data
            ///////////
            
            Meal m1(Date(2015, 10, 28), 13, "Some soup", "111", 999, "111");
            Meal m2(Date(2015, 10, 29), 0, "A glass of orange juice", "112", 450, "222");
            Meal m3(Date(2015, 10, 29), 63, "Fried chicken", "113", 120, "333");
            Meal m4(Date(2015, 10, 29), 5520, "Veggi pizza", "114", 1000, "444");
            Meal m5(Date(2015, 10, 29), 39720, "m5", "115", 70, "555");
            Meal m6(Date(2015, 10, 29), 13, "Glass of milk", "116", 111, "666");
            Meal m7(Date(2015, 10, 29), 39725, "m7", "117", 111, "777");
            
            _meals.add(m1);
            _meals.add(m2);
            _meals.add(m3);
            _meals.add(m4);
            _meals.add(m5);
            _meals.add(m6);
            _meals.add(m7);
            
            _mealsTableView->reloadData();
            ///////////
            
            // add settings layer
            // just for tests
            UserSettingsLayer *s = UserSettingsLayer::create();
            this->addChild(s);
            //
        }
    }
    
    
    ///////////
    
    //this->createMeal("test", CCRANDOM_0_1() * 100);
    
    return true;
}

void MealsLayer::createMeal(const std::string &caption, int calories) {
    auto onMealCreated = [=]() {
        CCLOG("created!");
    };
    
    auto onFailedToCreateMEal = [=](const string &error, const string &description) {
        CCLOG("failed to create!");
    };
    
    ServerAPI::createMeal(caption, calories, onMealCreated, onFailedToCreateMEal);
}

#pragma mark - UI callbacks

void MealsLayer::onBtnSettingsPressed() {
    
}

void MealsLayer::onBtnDateSelectPressed() {
    
}

void MealsLayer::onBtnAddItemPressed() {
    
}

#pragma mark - Table delegates

void MealsLayer::scrollViewDidScroll(cocos2d::extension::ScrollView *view) {
}

void MealsLayer::scrollViewDidZoom(ScrollView *view) {
}

void MealsLayer::tableCellTouched(TableView *table, TableViewCell *cell) {
    // a button pressed?
    CCLOG("touched: %i", cell->getTag());
}

ssize_t MealsLayer::numberOfCellsInTableView(TableView *table) {
    //return _requests.size();
    return _meals.size();
}

Size MealsLayer::tableCellSizeForIndex(TableView *table, ssize_t idx) {
    return this->_mealCellSize;
}

extension::TableViewCell* MealsLayer::tableCellAtIndex(TableView *table, ssize_t idx) {
    TableViewCell *cell = table->cellAtIndex(idx);
    
    if(cell == nullptr) {
        string caption = _meals.get(idx).getCaption();
        int calories = _meals.get(idx).getCalories();
        int time = _meals.get(idx).getConsumptionTime();
        
        cell = MealItemCell::create(caption, calories, time, this);
        cell->setTag(idx);
    }
    
    return cell;
}