//
//  Header.h
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 29.10.15.
//
//

#ifndef ttt_c_tracker_Header_h
#define ttt_c_tracker_Header_h

#include "Meal.h"

class IOnItemCreated {
public:
    virtual void onItemCreated(const Meal &m) = 0;
    virtual void onItemCreationCanceled() = 0;
};

#endif