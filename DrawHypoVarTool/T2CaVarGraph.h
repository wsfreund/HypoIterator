#ifndef T2CAVARGRAPH_H
#define T2CAVARGRAPH_H

#include "../HypoBase.h"
#include "../T2CaCommon.h"
#include "HypoVarBase.h"
#include "HypoVarHist.h"
#include <cstring>
#include <iostream>
#include <TPad.h>
#include "TString.h"
#include "TPaveText.h"

class T2CaVarGraph : public T2CaCommon, public HypoVarBase {

    protected:

    HypoVarHist *trCore;
    HypoVarHist *teRatio;
    HypoVarHist *tEt;
    HypoVarHist *tHadEt;

    bool useShunt;

    PCUTS applyCuts(const float eta, const float rCore, const float F1, const float eRatio, const float eT_T2Calo, const float hadET_T2Calo);

    bool cutrCore(const float rCore, const size_t etaBin);
    bool cuteRatio(const float eRatio, const float F1, const float eta, const size_t etaBin);
    bool cuteT_T2Calo(const float eT_T2Calo, const size_t etaBin);
    bool cuthadET_T2Calo(const float hadET_T2Calo, const float eT_T2Calo, const size_t etaBin);
    bool cutF1(const float F1);

    public:

    T2CaVarGraph(const std::string &chainPath, bool shunt = false);
    CODE DrawCutStats();
    int DrawVar(const std::string &var, const std::string &mode="");
    ~T2CaVarGraph();

};


#endif
