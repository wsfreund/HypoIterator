#ifndef T2CARELEFFIC_H
#define T2CARELEFFIC_H
#include "../T2CaCommon.h"
#include "RelEfficBase.h"
#include <cstring>
#include "HypoErrorsGraph.h"
#include "TMath.h"
#include "TCanvas.h"
#include <iostream>
using std::cout;
using std::endl;

class T2CaRelEffic : public T2CaCommon, public RelEfficBase{

    public:
    T2CaRelEffic(const std::string &rPath, unsigned user_nRegions);
    int DrawEfficVs(const std::string &vsWho, const std::string &opt);
    virtual ~T2CaRelEffic();

};


#endif
