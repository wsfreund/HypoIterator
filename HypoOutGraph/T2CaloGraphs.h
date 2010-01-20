#ifndef T2CALO_GRAPHS
#define T2CALO_GRAPHS


#include"Graphs.h"
#include"../T2CaloConfig.h"
#include"TPaveStats.h"
#include"TH1F.h"
#include<cstring>
#include"TList.h"
#include<iostream>
#include<TPad.h>



class T2CaloGraphs : public Graphs {

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

    std::vector<float>  *ringer_lvl2_eta;
    std::vector<float>  *ringer_lvl2_phi;

    TH1F *trCore;
    TH1F *teRatio;
    TH1F *tEt;
    TH1F *tHadEt;

    TPaveStats *psrCore;
    TPaveStats *pseRatio;
    TPaveStats *psEt; 
    TPaveStats *psHadEt;


    //Vector with T2Calo Cuts;
    std::vector<int>	*t2CaAns;

    //Functions

    CODE calcTransverseFraction();

    CODE swapVectors(const size_t index1, const size_t index2);
    CODE eraseVectors(const size_t index);

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

    T2CaloGraphs(const std::string &dataPath, const std::string &userDataLabel);

    CODE exec();
    CODE drawCutCounter();
    CODE clearVectors();

    CODE drawCut(const std::string &cut);
    CODE drawCut(const std::string &cut, const std::string &mode);
    double getMaximum(const std::string &cut);


    ~T2CaloGraphs();

};


#endif
