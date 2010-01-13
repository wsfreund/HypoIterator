#include "../T2CaloConfig.h"
#include "TH1F.h"
#include "TChain.h"
#include <cstring>
#include <cmath>
#include <iostream>


#ifndef T2CALO_GRAPHS
#define T2CALO_GRAPHS

class T2CaloGraphs{

    protected:

	enum CODE {ERROR=0, OK};
    enum PCUTS {LVL2E =-1 , TRIG, dETA, dPHI, rCORE, eRATIO, et_EM, et_HAD, c_F1, AP};

    //Cut Histograms:
    TH1F *elc_trCore;
    TH1F *elc_teRatio;
    TH1F *elc_tEt;
    TH1F *elc_tHadECutHiEnergy;
    TH1F *elc_tHadECutLowEnergy;
    TH1F *elc_tF1;

    TH1F *jet_trCore;
    TH1F *jet_teRatio;
    TH1F *jet_tEt;
    TH1F *jet_tHadECutHiEnergy;
    TH1F *jet_tHadECutLowEnergy;
    TH1F *jet_tF1;

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

    //Electron Chain variables
	std::vector<float>	*elc_hadET_T2Calo;
	std::vector<float> 	*elc_rCore;
	std::vector<float> 	*elc_energyRatio;
	std::vector<float>	*elc_F1;
	std::vector<float>	*elc_energy;
	std::vector<float>	*elc_ehad1;
	std::vector<float>	*elc_energyS1;
	std::vector<float>	*elc_eta0;
	std::vector<float>	*elc_phi0;
    std::vector<float>	*elc_lvl2_eta;
    std::vector<float>	*elc_lvl2_phi;
    std::vector<float>	*elc_et;

    //Jet Chain variables
    std::vector<float>  *jet_hadET_T2Calo;
    std::vector<float>  *jet_rCore;
    std::vector<float>  *jet_energyRatio;
    std::vector<float>  *jet_F1;
    std::vector<float>  *jet_energy;
    std::vector<float>  *jet_ehad1;
    std::vector<float>  *jet_energyS1;
    std::vector<float>  *jet_eta0;
    std::vector<float>  *jet_phi0;
	std::vector<float>	*jet_lvl2_eta;
    std::vector<float>	*jet_lvl2_phi;
	std::vector<float>	*jet_et;

    //Variable used for t2calo expert monitoring histogram
    std::vector<int> *t2CaAns;

    //Chain for Electrons:
    TChain  *elc_readChain;
    //Chain for Jets
    TChain  *jet_readChain;


    bool fill_rCore(const float rCore, const size_t etaBin, const int dataId);
    bool fill_eRatio(const float eRatio, const float F1, const float eta, const size_t etaBin, const int dataId);
    bool fill_eT_T2Calo(const float eT_T2Calo, const size_t etaBin, const int dataId);
    bool fill_hadET_T2Calo(const float hadET_T2Calo, const float eT_T2Calo, const size_t etaBin, const int dataId);
    bool fill_F1(const float F1, const int dataId);

    CODE calcTransverseFraction();
    CODE fill_Cuts(const float eta, const float rCore, const float F1, const float eRatio, const float eT_T2Calo, const float hadET_T2Calo, const int dataId);
    CODE drawCutCounter();
    
    public:
    T2CaloGraphs(std::string &electronsPath, std::string &jetsPath);
 
    //functions
    CODE exec();

    CODE draw_rCore();
    CODE draw_eRatio();
    CODE draw_et();
    CODE draw_hadEt();
    CODE draw_F1();

    ~T2CaloGraphs(){

        //Deleting all variables created by electrons Tchain:
	    delete 	elc_hadET_T2Calo;
	    delete	elc_rCore;
	    delete	elc_energyRatio;
	    delete	elc_F1;
	    delete	elc_energy;
	    delete	elc_ehad1;
	    delete	elc_energyS1;
		delete  elc_lvl2_eta;
		delete  elc_lvl2_phi;
		delete  elc_et;


        //Deleting all variables created by jets Tchain:
	    delete 	jet_hadET_T2Calo;
	    delete	jet_rCore;
	    delete	jet_energyRatio;
	    delete	jet_F1;
	    delete	jet_energy;
	    delete	jet_ehad1;
	    delete	jet_energyS1;
		delete  jet_lvl2_eta;
		delete  jet_lvl2_phi;
		delete  jet_et;

        //Deleting histograms:
        delete elc_trCore;
        delete elc_teRatio;
        delete elc_tEt;
        delete elc_tHadECutHiEnergy;
        delete elc_tHadECutLowEnergy;

        delete jet_trCore;
        delete jet_teRatio;
        delete jet_tEt;
        delete jet_tHadECutHiEnergy;
        delete jet_tHadECutLowEnergy;

        //Deleting TChains:
        delete  elc_readChain;
        delete  jet_readChain;

    }

};


#endif
