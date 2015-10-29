//
//  IOnItemModified.h
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 29.10.15.
//
//

#ifndef ttt_c_tracker_IOnItemModified_h
#define ttt_c_tracker_IOnItemModified_h

class IOnItemModified {
public:
    virtual void onItemDeleted(const std::string &itemId) = 0;
    virtual void onItemUpdated(const std::string &itemId, const std::string &newCaption, int newCalories) = 0;
};

#endif
