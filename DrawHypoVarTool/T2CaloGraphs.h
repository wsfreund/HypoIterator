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

    TH1F *trCore;
    TH1F *teRatio;
    TH1F *tEt;
    TH1F *tHadEt;

    unsigned rCoreCuts;
    unsigned eRatioCuts;
    unsigned etCuts;
    unsigned hadEtCuts;
    unsigned totalData;

    TPaveStats *psrCore;
    TPaveStats *pseRatio;
    TPaveStats *psEt; 
    TPaveStats *psHadEt;

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

    CODE drawCut(const std::string &cut);
    CODE drawCut(const std::string &cut, const std::string &mode);
    double getMaximum(const std::string &cut);


    ~T2CaloGraphs();

};


#endif
