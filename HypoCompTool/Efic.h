#ifndef EFIC

#define EFIC

#include<vector>
#include<iostream>
#include<cmath>
#include<TChain.h>
#include<TH1I.h>
#include<TTree.h>


class Efic {

	protected:

	enum CODE {ERROR=0, OK};

	std::vector<float>	*lvl2_eta;
	std::vector<float>	*lvl2_phi;
	std::vector<int>	*decision;
	std::vector<float>	*et;

    TTree   *eficFillingTree;
    TChain  *eficReadingChain;

	public:

	enum DECISION {JET = -1, ELECTRON = 1};


	Efic(TChain *outsideChain, TTree *outsideFillingTree){

        eficReadingChain = outsideChain;

        eficFillingTree = outsideFillingTree;

	    lvl2_eta	= 	new std::vector<float>;
	    lvl2_phi	= 	new std::vector<float>;
	    decision	= 	new std::vector<int>;
	    et      	= 	new std::vector<float>;


	}

    const std::vector<float> *getEta(){  return lvl2_eta; }
    const std::vector<float> *getPhi(){  return lvl2_phi; }
    const std::vector<int>   *getDec(){  return decision; }
    const std::vector<float> *getEt() {  return et;       }

    virtual CODE clearVectors() = 0;
    virtual CODE exec() = 0;
    virtual CODE swapVectors(const size_t index1, const size_t index2) = 0;
    virtual CODE eraseVectors(const size_t index) = 0;

	CODE ordenateRoi(const std::vector<float> *eta, const std::vector<float> *phi);

	~Efic(){ 


		delete lvl2_eta;
		delete lvl2_phi;
		delete decision;
		delete et;

	}

};

#endif
