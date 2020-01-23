﻿#ifndef BROOKSCHANNEL_H
#define BROOKSCHANNEL_H

#include <iostream>

#define VORNormal 0
#define VORClosed 1
#define VOROpened 2


using namespace std;

class BrooksChannel
{
public:
    BrooksChannel();
    double spRate;
    int VOR = 0;
    string name;
    double rateReaded;

    void setSpRate(double spR);
    void setVOR(int vor);
    void setName(string name);
};

#endif // BROOKSCHANNEL_H
