#ifndef HYPOERRORSGRAPH_H
#define HYPOERRORSGRAPH_H

#include <vector>
#include <typeinfo>
#include "TTree.h"
#include "TMath.h"
#include <cstring>
#include "TGraphAsymmErrors.h"
#include <iostream>
using std::cout;
using std::endl;

class HypoErrorsGraph {

    protected:
    enum PARTICLES {JET = -1, ELECTRON = 1};
    enum CODE {ERROR = 0, OK};
    /*const*/ unsigned NREGIONS;
    /*const*/ unsigned NPOINTS;
    /*const*/ float LOWEDGE;
    /*const*/ float HIEDGE;
    /*const*/ std::vector<float> *vectorInput;
    /*const*/ std::string title;
    /*const*/ std::string dataLabel;
    TTree* dataTree;


    TGraphAsymmErrors *graph;

    CODE genGraph();
    CODE genEdges(float* edges);
    CODE incrementEdges(const float*  edges, float* centerBin);
    CODE genEficErrors(const float* edges, float* efic, float* lowErrors, float* hiErrors) ;
    bool isAtRegion(const float lowEdge, const float data, const float hiEdge);

    public:

    HypoErrorsGraph();
    HypoErrorsGraph(const float userLOWEDGE, const float userHIEDGE, TTree *&userDataTree, const std::string &branchName, const unsigned userNREGIONS, const std::string &dataLabel, const std::string &userTitle);
    HypoErrorsGraph(const float userLOWEDGE, const float userHIEDGE, std::vector<float> *&dataVector, const unsigned userNREGIONS, const std::string &dataLabel, const std::string &userTitle);

    HypoErrorsGraph &operator=(const HypoErrorsGraph &graph2);
    HypoErrorsGraph* operator=(const HypoErrorsGraph* &graph2);
    
    TGraphAsymmErrors *& getGraph(){ return graph; };
    CODE Draw(const std::string &input);

    ~HypoErrorsGraph();

};


#endif
