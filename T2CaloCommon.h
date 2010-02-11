#include "HypoBase.h"
#include "T2CaloConfig.h"
#include <vector>
#include "TChain.h"
#include "TH1F.h"
#include "TTree.h"

#ifndef T2CALO_COMMON
#define T2CALO_COMMON


class T2CaloCommon : public HypoBase {

    protected:

    //Variables
    enum PCUTS {LVL2E =-1 , TRIG, dETA, dPHI, rCORE, eRATIO, et_EM, et_HAD, c_F1, AP};

    virtual CODE ordenateRoi(const std::vector<float> *eta, const std::vector<float> *phi);
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

    std::vector<float> *ringer_eta;
    std::vector<float> *ringer_phi;

    //Vector with T2Calo Cuts;
    std::vector<int> *t2CaAns;

    //Tree holding extraVariables:
    TTree *extraVariables;

    //Functions

    virtual CODE calcTransverseFraction();

    virtual CODE fillDecision(PCUTS entry);

    //Corte
    virtual PCUTS applyCuts(const float eta, const float rCore, const float F1, const float eRatio, const float eT_T2Calo, const float hadET_T2Calo);

    virtual bool cutEta(const float dEta);
    virtual bool cutPhi(const float dPhi);
    virtual bool cutrCore(const float rCore, const size_t etaBin);
    virtual bool cuteRatio(const float eRatio, const float F1, const float eta, const size_t etaBin);
    virtual bool cuteT_T2Calo(const float eT_T2Calo, const size_t etaBin);
    virtual bool cuthadET_T2Calo(const float hadET_T2Calo, const float eT_T2Calo, const size_t etaBin);
    virtual bool cutF1(const float F1);

    public:

    T2CaloCommon(const std::string &chainPath);

    virtual CODE exec();
    virtual CODE drawCutCounter();


    ~T2CaloCommon();

};


#endif
