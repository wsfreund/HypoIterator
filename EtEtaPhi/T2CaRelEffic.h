#ifndef T2CARELEFFIC_H
#define T2CARELEFFIC_H
#include "../T2CaCommon.h"
#include <cstring>
#include "HypoErrorsGraph.h"
#include "TMath.h"
#include <iostream>
using std::cout;
using std::endl;

class T2CaRelEffic : public T2CaCommon {

    protected:

    HypoErrorsGraph *etaxEficGraph;
    HypoErrorsGraph *phixEficGraph;
    HypoErrorsGraph *etxEficGraph;

    unsigned NREGIONS;
    const std::string dataLabel;

    public:

    T2CaRelEffic(const std::string &rPath, unsigned user_nRegions, const std::string &dataLabel);
    CODE DrawEfficVs(const std::string &vsWho, const std::string &opt);
    virtual ~T2CaRelEffic();

};


#endif
