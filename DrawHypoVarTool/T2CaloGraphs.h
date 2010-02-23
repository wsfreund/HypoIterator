#ifndef T2CAVARGRAPH_H
#define T2CAVARGRAPH_H

#include "../T2CaCommon.h"
#include "HypoVarHist.h"
#include <cstring>
#include <iostream>
#include <TPad.h>

class T2CaVarGraph : public T2CaCommon {

    protected:

    HypoVarHist *trCore;
    HypoVarHist *teRatio;
    HypoVarHist *tEt;
    HypoVarHist *tHadEt;

    PCUTS applyCuts(const float eta, const float rCore, const float F1, const float eRatio, const float eT_T2Calo, const float hadET_T2Calo);

    bool cutEta(const float dEta);
    bool cutPhi(const float dPhi);
    bool cutrCore(const float rCore, const size_t etaBin);
    bool cuteRatio(const float eRatio, const float F1, const float eta, const size_t etaBin);
    bool cuteT_T2Calo(const float eT_T2Calo, const size_t etaBin);
    bool cuthadET_T2Calo(const float hadET_T2Calo, const float eT_T2Calo, const size_t etaBin);
    bool cutF1(const float F1);

    public:

    T2CaVarGraph();
    ~T2CaVarGraph();

};


#endif
