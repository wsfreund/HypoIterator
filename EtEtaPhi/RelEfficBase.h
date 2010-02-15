#ifndef RELEFFICBASE_H
#define RELEFFICBASE_H

#include <cstring>
#include "HypoErrorsGraph.h"
#include "TMath.h"
#include "TCanvas.h"
#include <iostream>


class RelEfficBase {

    protected:
    HypoErrorsGraph *etaxEficGraph;
    HypoErrorsGraph *phixEficGraph;
    HypoErrorsGraph *etxEficGraph;
    unsigned NREGIONS;
    public:
    RelEfficBase(unsigned userNREGIONS):
        NREGIONS(userNREGIONS){
        etaxEficGraph = 0; phixEficGraph = 0; etxEficGraph = 0;}
    virtual int DrawEfficVs(const std::string &vsWho, const std::string &opt) = 0;
    virtual ~RelEfficBase(){};

};

#endif
