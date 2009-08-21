#ifndef EFIC

#define EFIC

#include<vector>
#include<iostream>
#include<cmath>
#include<TChain.h>
#include<TH1I.h>
#include<TTree.h>

using namespace std;

export class Efic {

	protected:

	vector<float>	*lvl2_eta;
	vector<float>	*lvl2_phi;
//	vector<float>	*lvl1_id;
	vector<int>	    *decision;
	vector<float>	*et;
//	vector<float>	*roi_id;

        TTree   *eficFillingTree;
        TChain  *eficReadingChain;

	public:

	enum DECISION {JET = -1, ELECTRON = 1};
	enum CODE {ERROR=0, OK};

	Efic(TChain *outsideChain, TTree *outsideFillingTree){

                eficReadingChain = outsideChain;

                eficFillingTree = outsideFillingTree;

		lvl2_eta	= 	new vector<float>;
		lvl2_phi	= 	new vector<float>;
//		lvl1_id		= 	new vector<float>;
		decision	= 	new vector<int>;
		et      	= 	new vector<float>;
//		roi_id		= 	new vector<float>;


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

		delete lvl2_eta;
		delete lvl2_phi;
//		delete lvl1_id;
		delete decision;
		delete et;
//		delete roi_id;

	}

};

#endif
