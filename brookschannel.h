#ifndef BROOKSCHANNEL_H
#define BROOKSCHANNEL_H

#include <iostream>

#define Normal 0
#define Closed 1
#define Opened 2


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
    void setVOR(double vor);
};

#endif // BROOKSCHANNEL_H
