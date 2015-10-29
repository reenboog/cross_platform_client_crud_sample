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
    Date(int year, int month, int day);
    
    static std::string timeStrForSeconds(int s);
    
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
private:
    Date() {}
private:
    unsigned int _year;
    unsigned int _month;
    unsigned int _day;
};

#endif /* defined(__ttt_c_tracker__Date__) */
