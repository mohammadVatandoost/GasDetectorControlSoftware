#ifndef MYUTITLITY_H
#define MYUTITLITY_H

#include <iostream>
#include <sstream>      // std::stringstream

using namespace std;

class MyUtitlity {
public:
    MyUtitlity() {}
    string numberToString(double num) {
        ostringstream ss;
        ss << num;
        return ss.str();
    }
    string numberToString(uint8_t num){
        ostringstream ss;
        ss << num;
        return ss.str();
    }
    string numberToString(uint16_t num){
        ostringstream ss;
        ss << num;
        return ss.str();
    }
    string numberToString(uint32_t num){
        ostringstream ss;
        ss << num;
        return ss.str();
    }
    string numberToString(int num){
        ostringstream ss;
        ss << num;
        return ss.str();
    }
    string numberToString(float num){
        ostringstream ss;
        ss << num;
        return ss.str();
    }
};



#endif // MYUTITLITY_H
