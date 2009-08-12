#ifndef EFIC

#define EFIC

#include<vector>
#include<iostream>
#include<cmath>
#include<TChain.h>
#include<TH1I.h>
#include<TTree.h>

using namespace std;

class Efic {

	protected:

	enum DECISION {JET = -1, ELECTRON = 1};
	enum CODE {ERROR=0, OK};

	vector<float>	*lvl2_eta;
	vector<float>	*lvl2_phi;
	vector<int>	*decision;
	vector<float>	*et;

        TTree   *eficFillingTree;
        TChain  *eficReadingChain;

	public:

	Efic(){


	}

        const vector<float> *getEta(){  return lvl2_eta; }
        const vector<float> *getPhi(){  return lvl2_phi; }
        const vector<int>   *getDec(){  return decision; }
        const vector<float> *getEt() {  return et;       }

        virtual CODE clearVectors() = 0;
        virtual CODE exec() = 0;
        virtual CODE swapVectors(const size_t index1, const size_t index2) = 0;
        virtual CODE eraseVectors(const size_t index) = 0;

	CODE ordenateRoi(const vector<float> *eta, const vector<float> *phi);

	~Efic(){ 

	}

};

#endif
