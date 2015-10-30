//
//  Date.cpp
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 28.10.15.
//
//

#include "Date.h"
#include "cocos2d.h"

#include <ctime>
#include <iomanip>

using namespace std;
using namespace cocos2d;

bool operator==(const Date &l, const Date &r) {
    if(&l == &r) {
        return true;
    }
    
    return l._year == r._year && l._month == r._month && l._day == r._day;
}

bool operator<=(const Date &l, const Date &r) {
    if(&l == &r) {
        return true;
    }
    
    return l._year <= r._year || l._month <= r._month || l._day <= r._day;
}

bool operator>=(const Date &l, const Date &r) {
    if(&l == &r) {
        return true;
    }
    
    return l._year >= r._year || l._month >= r._month || l._day >= r._day;
}

bool operator <(const Date &l, const Date &r) {
    return l._year < r._year || l._month < r._month || l._day < r._day;
}

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

Date Date::now() {
    /*
     time_t rawtime;
     struct tm * timeinfo;
     
     time ( &rawtime );
     timeinfo = localtime ( &rawtime );
     
     */
    
    
    time_t t = std::time(nullptr);
    struct tm timeInfo = *std::localtime(&t);
    
    Date d(0, 0, 0);
    
    d._year = timeInfo.tm_year + 1900;
    d._month = timeInfo.tm_mon + 1;
    d._day = timeInfo.tm_mday;
    
    return d;
}

Date Date::dateFromString(const string &str) {
    Date d;
    
    d._year = 0;
    d._month = 0;
    d._day = 0;
    
    struct tm tm;
    //time_t t;
    
    // "6 Dec 2001 12:33:45"
    if(strptime(str.c_str(), "%d %b %Y %H:%M", &tm) != NULL) {
        d._year = tm.tm_year + 1900;
        d._month = tm.tm_mon + 1;
        d._day = tm.tm_mday;
    }
    
    return d;
}

int Date::timeFromDateString(const string &str) {
    int time = 0;
    
    struct tm tm;
    //time_t t;
    
    // "6 Dec 2001 12:33:45"
    if(strptime(str.c_str(), "%d %b %Y %H:%M", &tm) != NULL) {
        time += tm.tm_hour * 3600;
        time += tm.tm_min * 60;
    }
    
    return time;
}

int Date::time() {
    int time = 0;
    
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    
    time += tm.tm_hour * 3600;
    time += tm.tm_min * 60;
    time += tm.tm_sec;
    
    return time;
}