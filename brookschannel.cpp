#include "brookschannel.h"

BrooksChannel::BrooksChannel()
{

}

void BrooksChannel::setSpRate(double spR)
{
    spRate = spR;
}

void BrooksChannel::setVOR(int vor)
{
    VOR = vor;
}

void BrooksChannel::setName(string name)
{
    this->name = name;
}
