#include"Efic.h"

#ifndef T2CALO_EFIC
#define T2CALO_EFIC

export class T2CaloEfic : public Efic {


        //Variables
	enum PCUTS {LVL2E =-1 , TRIG, dETA, dPHI, rCORE, eRATIO, et_EM, et_HAD, c_F1, AP};

	vector<float>	*hadET_T2Calo;
	vector<float> 	*rCore;
	vector<float> 	*energyRatio;
	vector<float>	*F1;
	vector<float>	*energy;
	vector<float>	*ehad1;
	vector<float>	*energyS1;
	vector<float>	*eta0;
	vector<float>	*phi0;


	//Vector with T2Calo Cuts;
	vector<int>	*t2CaAns;

        //Functions

	CODE calcTransverseFraction(const size_t j);

	CODE fillDecision(PCUTS	entry);

	//Corte
	PCUTS applyCuts(const float eta, const float rCore, const float F1, const float eRatio, const float eT_T2Calo, const float hadET_T2Calo);

	bool cutEta(const float dEta);
	bool cutPhi(const float dPhi);
	bool cutrCore(const float rCore, const size_t etaBin);
	bool cuteRatio(const float eRatio, const float eta, const size_t etaBin);
	bool cuteT_T2Calo(const float eT_T2Calo, const size_t etaBin);
	bool cuthadET_T2Calo(const float hadET_T2Calo, const float eT_T2Calo, const size_t etaBin);
	bool cutF1(const float F1);


	static const float 	m_eTthr[];
	static const float 	m_eT2thr[];
	static const float 	m_hadeTthr[];
	static const float 	m_hadeT2thr[];
	static const float 	m_etabin[];
	static const float 	m_carcorethr[];
	static const float 	m_caeratiothr[];
	static const float 	m_F1thr;
	static const float 	m_detacluster;
	static const float 	m_dphicluster;



	public:

	T2CaloEfic(TChain *&T2CaChain, TTree *&T2CaFillingTree);

        const vector<int> *getT2CaAns() { return t2CaAns; }

	CODE exec();
	CODE drawCutCounter();
	CODE clearVectors();
        CODE swapVectors(const size_t index1, const size_t index2);
        CODE eraseVectors(const size_t index);


	~T2CaloEfic();



};

#endif
