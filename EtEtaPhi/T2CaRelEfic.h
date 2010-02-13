#ifndef T2CARELEFIC_H
#define T2CARELEFIC_H
#include <iostream>
#include "../T2CaloCommon.h"
#include <vector>
#include <cstring>
#include "HypoErrorsGraph.h"
#include "TMath.h"
using std::cout;
using std::endl;

class T2CaRelEfic : public T2CaloCommon {

    protected:

    HypoErrorsGraph *etaxEficGraph;
    HypoErrorsGraph *phixEficGraph;
    HypoErrorsGraph *etxEficGraph;

    unsigned NREGIONS;
    std::string dataLabel;

    public:

    T2CaRelEfic(std::string &rPath, unsigned user_nRegions, std::string &dataLabel);
    CODE DrawEficVs(const std::string &vsWho, const std::string &opt);
    ~T2CaRelEfic;

};


#endif
