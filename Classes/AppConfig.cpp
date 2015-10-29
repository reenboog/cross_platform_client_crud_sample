//
//  AppConfig.cpp
//  solveMe
//
//  Created by Alex Gievsky on 11.11.13.
//
//

#include "AppConfig.h"
#include "Constants.h"
#include "Shared.h"
#include "Localized.h"
#include "User.h"

#include "json/document.h"

#include <string>

#define kUserGoalKey "userGoal"

using namespace std;
using namespace cocos2d;

AppConfig* AppConfig::__sharedInstance = nullptr;

AppConfig::~AppConfig() {
    
}

AppConfig::AppConfig() {
}

AppConfig* AppConfig::sharedInstance() {
    if(__sharedInstance == nullptr) {
        __sharedInstance = new AppConfig();
    }
    
    return __sharedInstance;
}

void AppConfig::purge() {
    delete __sharedInstance;
    __sharedInstance = nullptr;
    
    FileUtils::getInstance()->destroyInstance();
}

void AppConfig::load() {
    int goal = UserDefault::getInstance()->getIntegerForKey(kUserGoalKey, 0);
    
    if(goal != 0) {
        User::sharedInstance()->setGoal(goal);
    }
}

void AppConfig::save() {
    UserDefault::getInstance()->setIntegerForKey(kUserGoalKey, User::sharedInstance()->getGoal().getCalories());
}

void AppConfig::loadFilePaths() {
    // load file paths
    ssize_t configDataSize = 0;
    unsigned char *t = (FileUtils::getInstance()->getFileData("Res/config.json", "r", &configDataSize));
    
    char *configData = new char[configDataSize + 1];
    memcpy(configData, t, configDataSize);
    configData[configDataSize] = NULL;
    
    delete[] t;
    t = NULL;
    
    
    LanguageType currentLanguage = Application::getInstance()->getCurrentLanguage();
    
    string languagePrefix = Localized::languageShortNameForType(currentLanguage);
    
    auto addResourcePath = [=](const string &path) {
        FileUtils::getInstance()->addSearchPath((path + languagePrefix).c_str());
        FileUtils::getInstance()->addSearchPath(path.c_str());
    };
    
    Size frameSize = Director::getInstance()->getOpenGLView()->getFrameSize();
    
    rapidjson::Document configDoc;
    configDoc.Parse<0>(configData);
    
    string layoutBaseDimensionType = configDoc["layoutBaseDimension"].GetString();
    
    float frameBaseDimension = frameSize.height;
    
    if(layoutBaseDimensionType.compare("width") == 0) {
        frameBaseDimension = frameSize.width;
    }

    const auto &designEntriesArray = configDoc["designResolutionEntries"];
    if(designEntriesArray.IsArray()) {
        for(int i = designEntriesArray.Size() - 1; i >= 0; --i) {
            const auto &currentDeviceEntry = designEntriesArray[i];
            
            if(currentDeviceEntry.IsObject()) {
                double currentResolutionBaseDimension = currentDeviceEntry[layoutBaseDimensionType.c_str()].GetDouble();
                
                if(frameBaseDimension > currentResolutionBaseDimension) {
                    int requiredEntryIndex = MIN(i + 1, designEntriesArray.Size() - 1);
                    const auto &requiredEntry = designEntriesArray[requiredEntryIndex];
                    double requiredBaseDimension = requiredEntry[layoutBaseDimensionType.c_str()].GetDouble();
                    
                    //
                    double layoutWidth = requiredEntry["designWidth"].GetDouble();
                    double layoutHeight = requiredEntry["designHeight"].GetDouble();
                    
                    this->setDesignLayoutSize({static_cast<float>(layoutWidth), static_cast<float>(layoutHeight)});
                    
                    float designLayoutBaseDimension = layoutHeight;
                    ResolutionPolicy policy = ResolutionPolicy::FIXED_HEIGHT;
                    
                    if(layoutBaseDimensionType.compare("width") == 0) {
                        designLayoutBaseDimension = layoutWidth;
                        //frameBaseDimension = frameSize.width;
                        policy = ResolutionPolicy::FIXED_WIDTH;
                    }
                    
                    Director::getInstance()->getOpenGLView()->setDesignResolutionSize(layoutWidth, layoutHeight, policy);
                    Director::getInstance()->setContentScaleFactor(requiredBaseDimension / designLayoutBaseDimension);
                    
                    Size visibleSize = Director::getInstance()->getVisibleSize();
                    this->setVisibleOrigin({static_cast<float>((visibleSize.width - layoutWidth) / 2.0), static_cast<float>((visibleSize.height - layoutHeight) / 2.0)});
                    //

                    // load required entry and all the entries above
                    for(; requiredEntryIndex >= 0; --requiredEntryIndex) {
                        const auto &entryToLoad = designEntriesArray[requiredEntryIndex];
                        
                        if(entryToLoad.IsObject()) {
                            for(auto it = entryToLoad["paths"].onBegin(); it != entryToLoad["paths"].onEnd(); ++it) {
                                string path = it->GetString();
                                addResourcePath(path);
                            }
                        }
                    }
                    
                    // stop iterating all the rest entries
                    break;
                }
            }
        }
    }

    // load shared paths
    
    const auto &sharedPathsArray = configDoc["sharedPaths"];
    if(sharedPathsArray.IsArray()) {
        for(auto it = sharedPathsArray.onBegin(); it != sharedPathsArray.onEnd(); ++it) {
            string path = it->GetString();
            addResourcePath(path);
        }
    }
    
    delete[] configData;
}

Size AppConfig::getDesignLayoutSize() {
    return this->_designLayoutSize;
}

Point AppConfig::getVisibleOrigin() {
    return this->_visibleOrigin;
}

void AppConfig::setDesignLayoutSize(const Size &size) {
    this->_designLayoutSize = size;
}

void AppConfig::setVisibleOrigin(const Point &point) {
    this->_visibleOrigin = point;
}