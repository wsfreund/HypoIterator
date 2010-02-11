#ifndef T2CAETETAPHI_H
#define T2CAETETAPHI_H

#include "../T2CaloCommon.h"
#include <vector>
#include <cstring>
#include "HypoErrorsGraph.h"
#include "TMath.h"


class T2CaEtEtaPhi : public T2CaloCommon {
    

    protected:

    HypoErrorsGraph etaxEficGraph;
    HypoErrorsGraph phixEficGraph;
    HypoErrorsGraph etxEficGraph;

    const unsigned NREGIONS;
    const std::string dataLabel;

    public:

    T2CaloEtPhi(std::string &rPath, const unsigned int user_nRegions, const std::string &dataLabel);
    CODE drawEficVs(const std::string &opt);

};
