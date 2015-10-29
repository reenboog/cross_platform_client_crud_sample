//
//  Date.cpp
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 28.10.15.
//
//

#include "Date.h"
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;

Date::Date(int year, int month, int day) {
    _year = year;
    _month = month;
    _day = day;
}

bool Date::isLeapYear() {
    return (!((_year % 4) && (_year % 100)) || !(_year % 400));
}

bool Date::isValid() {
    unsigned short monthLen[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if(_year <= 0|| _month <= 0 || _day <= 0 || _day > 31 || _month > 12) {
        return false;
    }
    
    if(isLeapYear() && _month == 2) {
        monthLen[1]++;
    }
    
    if(_day > monthLen[_month - 1]) {
        return false;
    }
    
    return true;
}

string Date::timeStrForSeconds(int s) {
    string time;
    
    int hours = s / 3600;
    int minutes = (s - (hours * 3600)) / 60;
    
    time += StringUtils::format("%i", hours);

    time += ':';
    
    if(minutes < 10) {
        time += '0';
    }
    
    time += StringUtils::format("%i", minutes);
    
    return time;
}