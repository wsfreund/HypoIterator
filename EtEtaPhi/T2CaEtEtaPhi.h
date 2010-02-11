#ifndef T2CAETETAPHI_H
#define T2CAETETAPHI_H

#include "../T2CaloCommon.h"
#include <vector>
#include <cstring>
#include "HypoErrorsGraph.h"
#include "TMath.h"


class T2CaEtEtaPhi : public T2CaloCommon {
    

    protected:

    HypoErrorsGraph *etaxEficGraph;
    HypoErrorsGraph *phixEficGraph;
    HypoErrorsGraph *etxEficGraph;

    unsigned NREGIONS;
    std::string dataLabel;

    public:

    T2CaEtEtaPhi(std::string &rPath, unsigned user_nRegions, std::string &dataLabel);
    CODE DrawEficVs(const std::string &vsWho, const std::string &opt);

};


#endif
