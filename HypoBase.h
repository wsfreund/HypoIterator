#ifndef HYPOBASE_H
#define HYPOBASE_H

#include<vector>
#include<cmath>
#include<TChain.h>
#include<TH1I.h>
#include<TTree.h>
#include<cstring>
#include<iostream>
using std::cout;
using std::endl;

class HypoBase {

    static const float MAXDPHI = 0.1;
    static const float MAXDETA = 0.1;
    protected:

    enum CODE {ERROR=0, OK};
    CODE matchAndOrdenate(const std::vector<float> *eta, const std::vector<float> *phi);
    virtual CODE swapVectors(const size_t index1, const size_t index2) = 0;
    virtual CODE eraseVectors(const size_t index) = 0;
    virtual CODE exec() = 0;
    CODE fillHypoRate();
    std::vector<float>      *lvl2_eta;
    std::vector<float>      *lvl2_phi;
    std::vector<int>        *decision;
    std::vector<float>      *et;
    //Some analysis data:
    unsigned totalData;
    unsigned detElc;
    unsigned detJet;
    float detRate;
    std::string dataLabel;

    TChain *hypoChain;
    TTree *extraVariables;

    public:
    enum DECISION {JET = -1, ELECTRON = 1};

    HypoBase(const std::string &chainPath);

    virtual void getExtraVariables(TTree*& refExtraVariables) const{refExtraVariables = extraVariables;}
    unsigned getTotalData() const{ return totalData;}
    unsigned getDetElc() const{return detElc;}
    unsigned getDetJet() const{return detJet;}
    float    getDetRate() const{return detRate;}
    virtual void getDataLabel(std::string &hypoDataLabel) const{hypoDataLabel = dataLabel;}


    virtual ~HypoBase();
};

#endif
