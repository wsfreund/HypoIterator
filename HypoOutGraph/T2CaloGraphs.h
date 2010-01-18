#include "Graphs.h"
#include "../T2CaloConfig.h"
#include "TH1F.h"
#include "TChain.h"
#include "TPaveStats.h"
#include "TList.h"
#include "TPad.h"
#include <cstring>
#include <cmath>
#include <iostream>



#ifndef T2CALO_GRAPHS
#define T2CALO_GRAPHS

class T2CaloGraphs : public Graphs {

    protected:

    enum PCUTS {LVL2E =-1 , TRIG, dETA, dPHI, rCORE, eRATIO, et_EM, et_HAD, c_F1, AP};


    //Cut Histograms:
    TH1F *trCore;
    TH1F *teRatio;
    TH1F *tEt;
    TH1F *tHadECutHiEnergy;
    TH1F *tHadECutLowEnergy;
    TH1F *tF1;

    TPaveStats *psrCore;
    TPaveStats *pseRatio;
    TPaveStats *psEt;
    TPaveStats *psHiHadEt;
    TPaveStats *psLowHadEt;


    //Variables for Histograms axis:
    float minrCore;
    float maxrCore;
    float mineRatio;
    float maxeRatio;
    float minEt;
    float maxEt;
    float minHadEt;
    float maxHadEt;
    float minF1;
    float maxF1;

    //Chain variables
	std::vector<float>	*hadET_T2Calo;
	std::vector<float> 	*rCore;
	std::vector<float> 	*energyRatio;
	std::vector<float>	*F1;
	std::vector<float>	*energy;
	std::vector<float>	*ehad1;
	std::vector<float>	*energyS1;
	std::vector<float>	*eta0;
	std::vector<float>	*phi0;
    std::vector<float>	*lvl2_eta;
    std::vector<float>	*lvl2_phi;
    std::vector<float>	*et;


    //Variable used for t2calo expert monitoring histogram
    std::vector<int> *t2CaAns;

    bool fill_rCore(const float rCore, const size_t etaBin);
    bool fill_eRatio(const float eRatio, const float F1, const float eta, const size_t etaBin);
    bool fill_eT_T2Calo(const float eT_T2Calo, const size_t etaBin);
    bool fill_hadET_T2Calo(const float hadET_T2Calo, const float eT_T2Calo, const size_t etaBin);
    bool fill_F1(const float F1);

    CODE calcTransverseFraction();
    CODE findGraphsLimits(const float eta, const float rCore, const float F1, const float eRatio, const float eT_T2Calo, const float hadET_T2Calo);
    CODE fill_Cuts(const float eta, const float rCore, const float F1, const float eRatio, const float eT_T2Calo, const float hadET_T2Calo);
    CODE clearVectors();

    
    public:
    T2CaloGraphs(const std::string &stringPath, const std::string &userDataLabel);

    //Functions
    CODE exec();
    CODE exec(const float setMinrCore, const float setMaxrCore, const float setMineRatio, const float setMaxeRatio, const float setMinEt, const float setMaxEt, const float setMinHadEt, const float setMaxHadEt);


    CODE draw_rCore();
    CODE draw_eRatio();
    CODE draw_et();
    CODE draw_hadEt();
    CODE draw_F1();
    CODE draw_cutCounter();

    CODE draw_rCore(std::string input);
    CODE draw_eRatio(std::string input);
    CODE draw_et(std::string input);
    CODE draw_hadEt(std::string input);
    CODE draw_F1(std::string input);

    CODE setRange(const std::string &cutName, const float yMax);
//    float getminX(const std::string &dataType);
//    float getmaxX(const std::string &dataType);

    float getY(const std::string &dataType);


    float getMinrCore() { return minrCore;}
    float getMaxrCore() { return maxrCore;}
    float getMineRatio(){ return mineRatio;}
    float getMaxeRatio(){ return maxeRatio;}
    float getMinEt() { return minEt;}
    float getMaxEt() { return maxEt;}
    float getMinHadEt(){ return minHadEt;}
    float getMaxHadEt(){ return maxHadEt;}

    ~T2CaloGraphs(){

        //Deleting all variables created by electrons Tchain:
	    delete 	hadET_T2Calo;
	    delete	rCore;
	    delete	energyRatio;
	    delete	F1;
	    delete	energy;
	    delete	ehad1;
	    delete	energyS1;
        delete  t2CaAns;



    }

};


#endif
