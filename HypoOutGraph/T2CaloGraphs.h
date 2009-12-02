#include"T2CaloEfic.h"
#include "TH1F"

#ifndef T2CALO_GRAPHS
#define T2CALO_GRAPHS

class T2CaloGraphs : public T2CaloEfic {

    //Cut Histograms:
    TH1F *trCore;
    TH1F *teRatio;
    TH1F *tEt;
    TH1F *tHadE;
    TH1F *tF1;

    bool cutrCore(const float rCore, const size_t etaBin);
    bool cuteRatio(const float eRatio, const float eta, const size_t etaBin);
    bool cuteT_T2Calo(const float eT_T2Calo, const size_t etaBin);
    bool cuthadET_T2Calo(const float hadET_T2Calo, const float eT_T2Calo, const size_t etaBin);
    bool cutF1(const float F1);

    public:
    T2CaloGraphs(TChain *&T2CaChain, TTree *&T2CaFillingTree):T2CaloEfic(T2CaChain, T2CaFillingTree){

    trCore = new TH1F("NeuralNetworkOutput", "L2 Calo Neural Network Output", 220, -1.1, 1.1);

    }
 
    //functions
    CODE drawGraphs();



};


#endif
