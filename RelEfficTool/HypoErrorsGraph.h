#ifndef HYPOERRORSGRAPH_H
#define HYPOERRORSGRAPH_H

#include <vector>
#include <typeinfo>
#include "TTree.h"
#include "TMath.h"
#include <string>
#include "TGraphAsymmErrors.h"
#include "../HypoBase.h"
#include "../T2CaCommon.h"
#include "../NeuralCommon.h"
#include <iostream>
using std::cout;
using std::endl;

class HypoErrorsGraph {

    protected:
    enum CODE {ERROR = 0, OK};

    Color_t color;
    unsigned NREGIONS;
    unsigned NPOINTS;
    float LOWEDGE;
    float HIEDGE;
    std::string title;
    std::string id;
    HypoBase *dataHypo;
    TTree *dataTree;
    bool mev2gev;

    std::vector<float>* vectorInput;
    std::vector<int>* vectorDec;


    TGraphAsymmErrors *graph;

    CODE genGraph();
    CODE genEdges(float* edges);
    CODE incrementEdges(const float*  edges, float* centerBin);
    CODE genEfficErrors(float* edges, float* pX, float* effic, float* lowErrors, float* hiErrors);
    bool isAtRegion(const float lowEdge, const float data, const float hiEdge);
    CODE checkAndGenErrors(const float &efic, float &error, float &lowError, float &hiError);

    public:

    HypoErrorsGraph(const float userLOWEDGE, const float userHIEDGE, HypoBase *dataHypo, const std::string &branchName, const unsigned userNREGIONS, const std::string &userTitle);

    HypoErrorsGraph(const float userLOWEDGE, const float userHIEDGE, std::vector<float> *&dataVector, std::vector<int> *&inputDec, const unsigned userNREGIONS, const std::string &userId, const Color_t userColor, const std::string &userTitle);

    HypoErrorsGraph &operator=(const HypoErrorsGraph& graph2);
    HypoErrorsGraph* operator=(const HypoErrorsGraph*& graph2);
    
    TGraphAsymmErrors *getGraph(){ return graph; }
    CODE Draw(const std::string &input);

    void SetColor(Color_t userColor) { color = userColor; } 

    virtual ~HypoErrorsGraph();

};


#endif
