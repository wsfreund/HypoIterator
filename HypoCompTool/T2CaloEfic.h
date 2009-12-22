#include"Efic.h"
#include "../T2CaloConfig.h"
using namespace t2CaloConfig;

#ifndef T2CALO_EFIC
#define T2CALO_EFIC


class T2CaloEfic : public Efic {

    protected:

        //Variables
    enum PCUTS {LVL2E =-1 , TRIG, dETA, dPHI, rCORE, eRATIO, et_EM, et_HAD, c_F1, AP};

    std::vector<float>	*hadET_T2Calo;
    std::vector<float> 	*rCore;
    std::vector<float> 	*energyRatio;
    std::vector<float>	*F1;
    std::vector<float>	*energy;
    std::vector<float>	*ehad1;
    std::vector<float>	*energyS1;
    std::vector<float>	*eta0;
    std::vector<float>	*phi0;


    //Vector with T2Calo Cuts;
    std::vector<int>	*t2CaAns;

    //Functions

    CODE calcTransverseFraction();

    CODE fillDecision(PCUTS	entry);

    //Corte
    PCUTS applyCuts(const float eta, const float rCore, const float F1, const float eRatio, const float eT_T2Calo, const float hadET_T2Calo);

    bool cutEta(const float dEta);
    bool cutPhi(const float dPhi);
    bool cutrCore(const float rCore, const size_t etaBin);
    bool cuteRatio(const float eRatio, const float F1, const float eta, const size_t etaBin);
    bool cuteT_T2Calo(const float eT_T2Calo, const size_t etaBin);
    bool cuthadET_T2Calo(const float hadET_T2Calo, const float eT_T2Calo, const size_t etaBin);
    bool cutF1(const float F1);

    public:

    T2CaloEfic(TChain *T2CaChain, TTree *T2CaFillingTree);

    const vector<int> *getT2CaAns() { return t2CaAns; }

    CODE exec();
    CODE drawCutCounter();
    CODE clearVectors();
    CODE swapVectors(const size_t index1, const size_t index2);
    CODE eraseVectors(const size_t index);


    ~T2CaloEfic();

};


#endif
