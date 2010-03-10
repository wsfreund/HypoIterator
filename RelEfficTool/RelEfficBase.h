#ifndef RELEFFICBASE_H
#define RELEFFICBASE_H

#include <cstring>
#include "TGraphAsymmErrors.h"
#include "HypoErrorsGraph.h"
#include "TMath.h"
#include "TCanvas.h"
#include <iostream>


class RelEfficBase {

    protected:
    HypoErrorsGraph *etaxEfficGraph;
    HypoErrorsGraph *phixEfficGraph;
    HypoErrorsGraph *etxEfficGraph;
    unsigned NREGIONS;
    public:
    RelEfficBase(unsigned userNREGIONS):
        NREGIONS(userNREGIONS){
        etaxEfficGraph = 0; phixEfficGraph = 0; etxEfficGraph = 0;}
    virtual int DrawEfficVs(const std::string &vsWho, const std::string &opt) = 0;
    virtual TGraphAsymmErrors* getGraph(const std::string &dataType){
        if(dataType == "eta")
            return etaxEfficGraph->getGraph();
        if(dataType == "phi")
            return phixEfficGraph->getGraph();
        if(dataType == "et")
            return etxEfficGraph->getGraph(); 
        return 0;
    }

    virtual ~RelEfficBase(){};

};

#endif
