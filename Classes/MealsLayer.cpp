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
#include "User.h"
#include "CreateMealItemLayer.h"
#include "EditMealItemLayer.h"
#include "LayerBlocker.h"
#include "Toast.h"
#include "ItemFilterLayer.h"

#define zBack 0
#define zSettings 10
#define zCreateItem 10
#define zEditItem 10
#define zFilter 10

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
    
    _currentCalories = 0;
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
        _labelMail = Label::createWithTTF(User::sharedInstance()->getName(), "helvetica.ttf", 18);
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
        _labelDate = Label::createWithTTF("0", "helvetica.ttf", 18);
        _labelDate->setColor({255, 255, 255});
        _labelDate->setPosition({_mntDate->getContentSize().width * 0.5f, _mntDate->getContentSize().height * 0.5f});
        
        _mntDate->addChild(_labelDate);
        
        this->setCurrentDateLabel(Date::now());
        
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
            
            ///////////////////////////////////////////////////////////////////////////////////////////////////////////
            // just for tests
            UserSettingsLayer *s = UserSettingsLayer::create(this);
            this->addChild(s);
        }
    }
    
    this->fetchAvailableMeals();
    this->setTotalCaloriesConsumed(0);
    
    return true;
}

#pragma mark - UI

void MealsLayer::setCurrentDateLabel(const Date &date) {
    _labelDate->setString(StringUtils::format("%i.%i.%i", date.getYear(), date.getMonth(), date.getDay()));
}

#pragma mark - UI callbacks

void MealsLayer::onBtnSettingsPressed() {
    UserSettingsLayer *settings = UserSettingsLayer::create(this);
    
    this->addChild(settings, zSettings);
}

void MealsLayer::onBtnDateSelectPressed() {
    ItemFIlterLayer *l = ItemFIlterLayer::create(this);
    
    this->addChild(l, zFilter);
}

void MealsLayer::onBtnAddItemPressed() {
    // pop up CreateMealItemLayer
    CreateMealItemLayer *layer = CreateMealItemLayer::create(this);
    
    this->addChild(layer, zCreateItem);
}

#pragma mark - Meals

void MealsLayer::setMealsUpToDate() {
    _selectedDate = Date::now();
    this->setCurrentDateLabel(_selectedDate);
    
    _meals = User::sharedInstance()->getAllMeal().selectForDate(_selectedDate);
    
    this->setTotalCaloriesConsumed(_meals.getTotalCalories());
    
    _mealsTableView->reloadData();
}

#pragma mark - Meal CRUD

void MealsLayer::fetchAvailableMeals() {
    LayerBlocker::block(this);
    
    Toast::show(this, "Fetching meals...", 2);
    
    // call server
    auto onMealsFetched = [this](const MealGroup &meals) {
        LayerBlocker::unblock(this);
        
        this->setMealsUpToDate();
    };
    
    auto onFailedToFetchMeals = [=](const string &error, const string &description) {
        LayerBlocker::unblock(this);
        
        Toast::show(this, "Network error");
    };

    LayerBlocker::block(this);
    
    ServerAPI::fetchAvailableMeals(onMealsFetched, onFailedToFetchMeals);
}

void MealsLayer::setTotalCaloriesConsumed(int calories) {
    int goal = User::sharedInstance()->getGoal().getCalories();
    _currentCalories = calories;

    _progressCaloriesConsumed->setPercentage(100.0f * _currentCalories / goal);
    _labelCaloriesConsumed->setString(StringUtils::format("%i / %i", _currentCalories, goal));
    
    if(_currentCalories > goal) {
        _labelCaloriesConsumed->setColor({219, 44, 44});
    } else {
        _labelCaloriesConsumed->setColor({53, 172, 225});
    }
}

void MealsLayer::onItemCreated(const Meal &item) {
    this->setMealsUpToDate();
}

void MealsLayer::onItemCreationCanceled() {
    // In fact, do nothing
}

void MealsLayer::onItemDeleted(const string &itemId) {
    this->setMealsUpToDate();
}

void MealsLayer::onItemUpdated(const string &itemId, const string &newCaption, int newCalories) {
    this->setMealsUpToDate();
}

#pragma mark - IOnGoalChanged

void MealsLayer::onGoalChanged(int newGoal) {
    // recalc the data here
    // move the progress
    this->setTotalCaloriesConsumed(_currentCalories);
}

#pragma mark - filtering

void MealsLayer::onFilterApplied(IOnDateFilterResultFetched *fetcher, const Date &dateFrom, const Date &dateTo, int timeFrom, int timeTo) {
    MealGroup filtered = User::sharedInstance()->getAllMeal().selectBetweenDates(dateFrom, dateTo, timeFrom, timeTo);
    
    fetcher->onResutFetched(filtered);
}

#pragma mark - Table delegates

void MealsLayer::scrollViewDidScroll(cocos2d::extension::ScrollView *view) {
}

void MealsLayer::scrollViewDidZoom(ScrollView *view) {
}

void MealsLayer::tableCellTouched(TableView *table, TableViewCell *cell) {
    // a button pressed?
    unsigned int idx = cell->getTag();
    CCLOG("touched: %i", idx);
    
    EditMealItemLayer *editLayer = EditMealItemLayer::create(this, _meals.get(idx).getId());
    
    this->addChild(editLayer, zEditItem);
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