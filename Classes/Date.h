//
//  Date.h
//  ttt_c_tracker
//
//  Created by Alex Gievsky on 28.10.15.
//
//

#ifndef __ttt_c_tracker__Date__
#define __ttt_c_tracker__Date__

class Date {
public:
    virtual ~Date() {}
    Date(int year, int month, int day, int hours = 0, int minutes = 0, int seconds = 0);
    
    bool isLeapYear();
    bool isValid();
    
    unsigned int getYear() const {
        return _year;
    }
    
    unsigned int getMonth() const {
        return _month;
    }
    
    unsigned int getDay() const {
        return _day;
    }
    
    unsigned int getHours() const {
        return _hours;
    }
    
    unsigned int getMinutes() const {
        return _minutes;
    }
    
    unsigned int getSeconds() const {
        return _seconds;
    }
private:
    Date() {}
private:
    unsigned int _year;
    unsigned int _month;
    unsigned int _day;
    unsigned int _hours;
    unsigned int _minutes;
    unsigned int _seconds;
};

#endif /* defined(__ttt_c_tracker__Date__) */
