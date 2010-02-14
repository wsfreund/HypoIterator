#ifndef T2CARELEFIC_H
#define T2CARELEFIC_H
#include "../T2CaCommon.h"
#include <cstring>
#include "HypoErrorsGraph.h"
#include "TMath.h"
#include <iostream>
using std::cout;
using std::endl;

class T2CaRelEfic : public T2CaCommon {

    protected:

    HypoErrorsGraph *etaxEficGraph;
    HypoErrorsGraph *phixEficGraph;
    HypoErrorsGraph *etxEficGraph;

    unsigned NREGIONS;
    const std::string dataLabel;

    public:

    T2CaRelEfic(const std::string &rPath, unsigned user_nRegions, const std::string &dataLabel);
    CODE DrawEficVs(const std::string &vsWho, const std::string &opt);
    virtual ~T2CaRelEfic();

};


#endif
