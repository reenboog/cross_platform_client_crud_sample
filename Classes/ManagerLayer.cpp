//
//  ManagerLayer.cpp
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 30.10.15.
//
//

#include "ManagerLayer.h"
#include "User.h"
#include "UserItemCell.h"
#include "LayerBlocker.h"
#include "Toast.h"
#include "ServerAPI.h"

#define zBack 0

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace std;

ManagerLayer::ManagerLayer() {
    _back = nullptr;
    _mntHead = nullptr;
    _headingNode = nullptr;
    _btnSettings = nullptr;
    _labelMail = nullptr;
    _labelRole = nullptr;
    _usersTableView = nullptr;
}

ManagerLayer::~ManagerLayer() {
    
}

bool ManagerLayer::init() {
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
        // heading
        _headingNode = Node::create();
        _headingNode->setPosition({0, 0});
        
        this->addChild(_headingNode);
        
        _mntHead = Sprite::create("mnt_meals_list_head.png");
        _mntHead->setAnchorPoint({0.0f, 1.0f});
        _mntHead->setPosition({0, visibleSize.height});
        
        _headingNode->addChild(_mntHead);
        
        // settings button
        _btnSettings = MenuItemImage::create("btn_settings.png", "btn_settings_on.png", CC_CALLBACK_0(ManagerLayer::onBtnSettingsPressed, this));
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
        _labelRole = Label::createWithTTF("manager", "helvetica.ttf", 40);
        _labelRole->setColor({53, 172, 225});
        _labelRole->setAnchorPoint({0, 1});
        _labelRole->setPosition({visibleSize.width * 0.03f, visibleSize.height * 0.98f - _labelMail->getContentSize().height});
        
        _headingNode->addChild(_labelRole);
    }
    
    {
        Sprite *cell = Sprite::create("bg_item.png");
        
        _userCellSize = Size(cell->getContentSize().width, cell->getContentSize().height);
        _usersTableView = TableView::create(this, Size(_userCellSize.width, visibleSize.height - _mntHead->getContentSize().height));
        _usersTableView->setDirection(ScrollView::Direction::VERTICAL);
        _usersTableView->setPosition(Point(0, 0));
        _usersTableView->setDelegate(this);
        _usersTableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
        
        this->addChild(_usersTableView);
    }
    
    this->fetchUsers();
    
    return true;
}

Scene* ManagerLayer::scene() {
    auto scene = Scene::create();
    auto layer = ManagerLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

void ManagerLayer::fetchUsers() {
    LayerBlocker::block(this);
    
    Toast::show(this, "Fetching users...", 2);
    
    // call server
    auto onUsersFetched = [this](const vector<User> &users) {
        LayerBlocker::unblock(this);
        
        Toast::show(this, "Fetched", 1);
        
        _users = users;
        _usersTableView->reloadData();
    };
    
    auto onFailedToFetchUsers = [=](const string &error, const string &description) {
        LayerBlocker::unblock(this);
        
        Toast::show(this, "Network error");
    };
    
    LayerBlocker::block(this);
    
    // call api
    ServerAPI::fetchUsers(onUsersFetched, onFailedToFetchUsers);
}

#pragma mark - ui callbacks

void ManagerLayer::onBtnSettingsPressed() {
    //
}

#pragma mark - Table delegates

void ManagerLayer::scrollViewDidScroll(cocos2d::extension::ScrollView *view) {
}

void ManagerLayer::scrollViewDidZoom(ScrollView *view) {
}

void ManagerLayer::tableCellTouched(TableView *table, TableViewCell *cell) {
    // a button pressed?
    unsigned int idx = cell->getTag();
    CCLOG("touched: %i", idx);

    // show user goal's page
//    EditMealItemLayer *editLayer = EditMealItemLayer::create(this, _meals.get(idx).getId());
//    
//    this->addChild(editLayer, zEditItem);
}

ssize_t ManagerLayer::numberOfCellsInTableView(TableView *table) {
    //return _requests.size();
    return _users.size();
}

Size ManagerLayer::tableCellSizeForIndex(TableView *table, ssize_t idx) {
    return this->_userCellSize;
}

extension::TableViewCell* ManagerLayer::tableCellAtIndex(TableView *table, ssize_t idx) {
    TableViewCell *cell = table->cellAtIndex(idx);
    
    if(cell == nullptr) {
        string name = _users[idx].getName();

        cell = UserItemCell::create(name, this);
        cell->setTag(idx);
    }
    
    return cell;
}