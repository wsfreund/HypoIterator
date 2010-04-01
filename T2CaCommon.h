#ifndef T2CA_COMMON_H
#define T2CA_COMMON_H

#include "T2CaBase.h"
#include "T2CaConfig.h"
#include <vector>
#include <string>
#include "TChain.h"
#include "TH1F.h"
#include "TH1I.h"
#include "TPad.h"
#include "TTree.h"
#include "TPaveStats.h"

class T2CaCommon : public T2CaBase { // FIXME enhiretance should be virtual here.

    protected:

    //Constants:

    t2ca_00_07_85_conf l2chain;

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
    CODE calcTransverseFraction();
    CODE fillDecision(PCUTS entry);
    CODE fillT2CaRate();
    CODE initialize();
    //Cuts
    PCUTS applyCuts(const float eta, const float rCore, const float F1, const float eRatio, const float eT_T2Calo, const float hadET_T2Calo);
    bool cutEta(const float dEta);
    bool cutPhi(const float dPhi);
    bool cutrCore(const float rCore, const size_t etaBin);
    bool cuteRatio(const float eRatio, const float F1, const float eta, const size_t etaBin);
    bool cuteT_T2Calo(const float eT_T2Calo, const size_t etaBin);
    bool cuthadET_T2Calo(const float hadET_T2Calo, const float eT_T2Calo, const size_t etaBin);
    bool cutF1(const float F1);


    public:
    T2CaCommon(const std::string &chainPath, const t2ca_00_07_85_conf userL2chain, const std::string &userDataLabel);
    T2CaCommon(const std::string &chainPath, const t2ca_00_07_85_conf userL2chain, const std::string &userDataLabel, const std::string &id);
    CODE exec();
    //Draw functions:
    CODE DrawCutCounter(const std::string &opt = "");
    CODE DrawCutStats();
    CODE WriteTree();
    //Get functions:
    unsigned getrCoreCuts()const {return rCoreCuts;}
    unsigned geteRatioCuts()const {return eRatioCuts;}
    unsigned getEmCuts()const {return etCuts;}
    unsigned getHadEtCuts()const {return hadEtCuts;}
    float getDetrCoreRate()const {return detrCoreRate;}
    float getDeteRatioRate()const {return deteRatioRate;}
    float getDetEtRate()const {return detEtRate;}
    float getDetHadEtRate()const {return detHadEtRate;}
    const t2ca_00_07_85_conf& getl2chain()const {return l2chain;}

    virtual ~T2CaCommon();

};


#endif
