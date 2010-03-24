#ifndef RELEFFICBASE_H
#define RELEFFICBASE_H

#include <cstring>
#include "TGraphAsymmErrors.h"
#include "HypoErrorsGraph.h"
#include "TMath.h"
#include "TCanvas.h"
#include <iostream>


class RelEfficBase : virtual public HypoBase {

    protected:
    HypoErrorsGraph *etaxEfficGraph;
    HypoErrorsGraph *phixEfficGraph;
    HypoErrorsGraph *etxEfficGraph;
    unsigned NREGIONS;
    public:
    RelEfficBase(unsigned userNREGIONS)
    {
      NREGIONS = userNREGIONS; // do not touch it.
      etaxEfficGraph = 0; 
      phixEfficGraph = 0; 
      etxEfficGraph = 0;
    }
    virtual int DrawEfficVs(const std::string &vsWho, const std::string &opt = "") = 0;
    TGraphAsymmErrors* getGraph(const std::string &dataType){
        cout<<"on "<<dataType<<" getGraph!"<<endl;
        if(dataType == "eta"){
            return etaxEfficGraph->getGraph();
        }
        if(dataType == "phi")
            return phixEfficGraph->getGraph();
        if(dataType == "et")
            return etxEfficGraph->getGraph(); 
        return 0;
    }

    virtual ~RelEfficBase(){};

};

#endif
