#ifndef T2CA_COMMON_H
#define T2CA_COMMON_H

#include "HypoBase.h"
#include "T2CaConfig.h"
#include <vector>
#include "TChain.h"
#include "TH1F.h"
#include "TH1I.h"
#include "TTree.h"
#include "TPaveStats.h"
#include <iostream>
using std::cout;
using std::endl;

class T2CaCommon : public HypoBase {

    protected:

    //Variables
    enum PCUTS {LVL2E =-1 , TRIG, dETA, dPHI, rCORE, eRATIO, et_EM, et_HAD, c_F1, AP};

    virtual CODE clearVectors();
    virtual CODE swapVectors(const size_t index1, const size_t index2);
    virtual CODE eraseVectors(const size_t index);

    std::vector<float>  *hadET_T2Calo;
    std::vector<float>  *rCore;
    std::vector<float>  *energyRatio;
    std::vector<float>  *F1;
    std::vector<float>  *energy;
    std::vector<float>  *ehad1;
    std::vector<float>  *energyS1;
    std::vector<float>  *eta0;
    std::vector<float>  *phi0;
    //Ringer eta and phi for matching:
    std::vector<float> *ringer_eta;
    std::vector<float> *ringer_phi;
    //Vector with T2Calo Cuts;
    std::vector<int> *t2CaAns;
    //Tree holding extraVariables:
    TTree *extraVariables;
    //Analysis Variables:
    unsigned rCoreCuts;
    unsigned eRatioCuts;
    unsigned etCuts;
    unsigned hadEtCuts;
    float detrCoreRate;
    float deteRatioRate;
    float detEtRate;
    float detHadEtRate;

    //Functions
    virtual CODE calcTransverseFraction();
    virtual CODE fillDecision(PCUTS entry);
    //Cuts
    virtual PCUTS applyCuts(const float eta, const float rCore, const float F1, const float eRatio, const float eT_T2Calo, const float hadET_T2Calo);
    virtual bool cutEta(const float dEta);
    virtual bool cutPhi(const float dPhi);
    virtual bool cutrCore(const float rCore, const size_t etaBin);
    virtual bool cuteRatio(const float eRatio, const float F1, const float eta, const size_t etaBin);
    virtual bool cuteT_T2Calo(const float eT_T2Calo, const size_t etaBin);
    virtual bool cuthadET_T2Calo(const float hadET_T2Calo, const float eT_T2Calo, const size_t etaBin);
    virtual bool cutF1(const float F1);

    public:
    T2CaCommon(const std::string &chainPath);
    CODE exec();
    CODE DrawCutCounter();
    virtual CODE DrawCutStats();
    void getExtraVariables(TTree*& refExtraVariables)const { refExtraVariables = extraVariables; }
    unsigned getrCoreCuts()const {return rCoreCuts;}
    unsigned geteRatioCuts()const {return eRatioCuts;}
    unsigned getEmCuts()const {return etCuts;}
    unsigned getHadEtCuts()const {return hadEtCuts;}
    float getDetrCoreRate()const {return detrCoreRate;}
    float getDeteRatioRate()const {return deteRatioRate;}
    float getDetEtRate()const {return detEtRate;}
    float getDetHadEtRate()const {return detHadEtRate;}
    ~T2CaCommon();

};


#endif
