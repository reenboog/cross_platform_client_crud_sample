//
//  IOnFilterApplied.h
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 30.10.15.
//
//

#ifndef ttt_c_tracker_IOnFilterApplied_h
#define ttt_c_tracker_IOnFilterApplied_h

#include "Date.h"
#include "MealGroup.h"

class IOnDateFilterResultFetched {
public:
    virtual void onResutFetched(const MealGroup &g) = 0;
};

class IOnFilterApplied {
public:
    virtual void onFilterApplied(IOnDateFilterResultFetched *fetcher, const Date &dateFrom, const Date &dateTo, int timeFrom = 0, int timeTo = 24 * 3600) = 0;
};

#endif
