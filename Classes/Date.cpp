//
//  Date.cpp
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 28.10.15.
//
//

#include "Date.h"

Date::Date(int year, int month, int day, int hours, int minutes, int seconds) {
    _year = year;
    _month = month;
    _day = day;
    _hours = hours;
    _minutes = minutes;
    _seconds = seconds;
}

bool Date::isLeapYear() {
    return (!((_year % 4) && (_year % 100)) || !(_year % 400));
}

bool Date::isValid() {
    if(_hours > 24 || _minutes > 60 || _seconds > 60) {
        return false;
    }
    
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