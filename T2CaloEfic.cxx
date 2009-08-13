#include "T2CaloEfic.h"
#include "T2CaloConfig.h"

T2CaloEfic::T2CaloEfic(TChain *&T2CaChain, TTree *&T2CaFillingTree):Efic(T2CaChain, T2CaFillingTree){

	hadET_T2Calo		=	new vector<float>;
	rCore			=	new vector<float>;
	energyRatio		=	new vector<float>;
	F1			=	new vector<float>;
	energy			=	new vector<float>;
	ehad1			=	new vector<float>;
	energyS1		=	new vector<float>;
	t2CaAns		        =	new vector<int>;

	eficReadingChain->SetBranchStatus("T2CaEta", 		true);
	eficReadingChain->SetBranchStatus("T2CaPhi",		true);
	eficReadingChain->SetBranchStatus("T2CaRcore", 	        true);
	eficReadingChain->SetBranchStatus("T2CaEratio",	        true);
	eficReadingChain->SetBranchStatus("T2CaEmES1", 	        true);
	eficReadingChain->SetBranchStatus("T2CaEmE", 		true);
	eficReadingChain->SetBranchStatus("T2CaHadES0", 	true);
//	eficReadingChain->SetBranchStatus("LVL1ID",	        true);


	eficReadingChain->SetBranchAddress("T2CaEta", 		&lvl2_eta);
	eficReadingChain->SetBranchAddress("T2CaPhi",		&lvl2_phi);
	eficReadingChain->SetBranchAddress("T2CaRcore", 	&rCore);
	eficReadingChain->SetBranchAddress("T2CaEratio",	&energyRatio);
	eficReadingChain->SetBranchAddress("T2CaEmES1", 	&energyS1);
	eficReadingChain->SetBranchAddress("T2CaEmE", 		&energy);
	eficReadingChain->SetBranchAddress("T2CaHadES0", 	&ehad1);
//	eficReadingChain->SetBranchAddress("LVL1ID",	        &lvl1_id);



	eficFillingTree->		Branch("T2CaOut",	&t2CaAns);
	eficFillingTree->		Branch("T2CaDec",	&decision);
//	eficFillingTree->		Branch("T2Calvl1_id",	&lvl1_id);
//	eficFillingTree->		Branch("T2CaRoi_id",	&roi_id);
	eficFillingTree->		Branch("T2CaEta",	&lvl2_eta);
	eficFillingTree->		Branch("T2CaPhi",	&lvl2_phi);
	eficFillingTree->		Branch("T2CaET",	&et);


}


Efic::CODE T2CaloEfic::exec(){


	for(size_t j=0; j<lvl2_eta->size(); ++j){
                
		calcTransverseFraction(j);//calculate the Transverse Energy and Energy Fraction F1 for it ROI j;

		T2CaloEfic::PCUTS	roiAns	=	applyCuts( lvl2_eta->at(j) , lvl2_phi->at(j), rCore->at(j), F1->at(j), energyRatio->at(j), et->at(j), hadET_T2Calo->at(j) ); // apply cut for each ROI j;

		t2CaAns->push_back(roiAns); //Fill passed cuts with the event answer given by T2Calo.

		fillDecision(roiAns); //Fill vector telling if the event was a electron or a jet;

	}//for j

	return Efic::OK;

}

inline Efic::CODE T2CaloEfic::calcTransverseFraction(const size_t j){

	et->push_back( ( energy->at(j) ) / ( cosh ( fabs ( lvl2_eta->at(j) ) ) ) );
	hadET_T2Calo->push_back( ( ehad1->at(j) ) / ( cosh ( fabs ( lvl2_eta->at(j) ) ) ) );
	F1->push_back( ( energyS1->at(j) ) / ( energy->at(j) ) );

	return	Efic::OK;

}

Efic::CODE T2CaloEfic::fillDecision(T2CaloEfic::PCUTS	entry){

	switch (entry){
		case T2CaloEfic::AP:
			decision->push_back(Efic::ELECTRON);
			break;
		case T2CaloEfic::dETA:
		case T2CaloEfic::dPHI:
		case T2CaloEfic::rCORE:
		case T2CaloEfic::eRATIO:
		case T2CaloEfic::et_EM:
		case T2CaloEfic::et_HAD:
		case T2CaloEfic::c_F1:
			decision->push_back(Efic::JET);
			break;
		default:
			return Efic::ERROR;
	}

	return Efic::OK;

}

T2CaloEfic::PCUTS T2CaloEfic::applyCuts(const float eta, const float phi, const float rCore, const float F1, const float eRatio, const float eT_T2Calo, const float hadET_T2Calo){
	
	size_t	etaBin = 0;
	for (size_t iBin = 0; iBin < (( sizeof(m_etabin) / sizeof(float) ) -1) ; ++iBin) {
		if ( fabs (eta) > m_etabin[iBin] && fabs (eta) < m_etabin[iBin+1] ) etaBin = iBin; 
	}

	//Corte Eta
	//if (cutEta(dEta)) return T2CaloEfic::dETA;
 
	//Corte Phi
	//if (cutPhi(dPhi)) return T2CaloEfic::dPHI;

	//Corte rCore
	if (cutrCore(rCore, etaBin)) return T2CaloEfic::rCORE;

	//Corte eRatio
	if (cuteRatio(eRatio, eta, etaBin)) return T2CaloEfic::eRATIO;

	//Corte Energia Tranversa EM
	if (cuteT_T2Calo(eT_T2Calo, etaBin)) return T2CaloEfic::et_EM;

	//Corte Energia Tranversa HAD
	if (cuthadET_T2Calo(hadET_T2Calo, eT_T2Calo, etaBin)) return T2CaloEfic::et_HAD;

	//Corte Fração de energia
	if (cutF1(F1)) return T2CaloEfic::c_F1;

	//Chegou até aqui passou yeah
	return T2CaloEfic::AP;

}

inline bool T2CaloEfic::cutEta(const float dEta){

	if ( dEta > m_detacluster ) {
		return true;
	}	
	return false;
}


inline bool T2CaloEfic::cutPhi(const float dPhi){

	if ( dPhi > m_dphicluster ){
		return true;
	}	
	return false;

}

inline bool T2CaloEfic::cutrCore(const float rCore, const size_t etaBin){

	if ( rCore < m_carcorethr[etaBin] )  {
		return true;
	}
	return false;

}

inline bool T2CaloEfic::cuteRatio(const float eRatio, const float eta, const size_t etaBin){

	bool inCrack = ( fabs (eta) > 2.37 || ( fabs (eta) > 1.37 && fabs (eta) < 1.52 ) );
	 
	if ( (!inCrack) && (eRatio < m_caeratiothr[etaBin])) {
		return true;
	}
 
	return false;

}

inline bool T2CaloEfic::cuteT_T2Calo(const float eT_T2Calo, const size_t etaBin){


	if ( eT_T2Calo < m_eTthr[etaBin] ){
		return true;
	}
	return false;
}

inline bool T2CaloEfic::cuthadET_T2Calo(const float hadET_T2Calo, const float eT_T2Calo, const size_t etaBin){


	float hadET_cut;
	if ( eT_T2Calo >  m_eT2thr[etaBin] ) hadET_cut = m_hadeT2thr[etaBin] ;
	else hadET_cut = m_hadeTthr[etaBin];

	if ( hadET_T2Calo > hadET_cut ) {
		return true;
	}
	return false;
}

inline bool T2CaloEfic::cutF1(const float F1){

	if ( F1 < m_F1thr){
		return true;
	}
	return false;

}


Efic::CODE T2CaloEfic::eraseVectors(const size_t index){

        vector<float>::iterator p;
        vector<int>::iterator p2;
        size_t j;

        for( j=0, p = lvl2_eta->begin(); j<index; ++j, ++p) {};
        lvl2_eta->erase(p,lvl2_eta->end());

        for( j=0, p = lvl2_phi->begin(); j<index; ++j, ++p) {};
        lvl2_phi->erase(p,lvl2_phi->end());

        for( j=0, p = et->begin(); j<index; ++j, ++p) {};
        et->erase(p,et->end());

        for( j=0, p2 = t2CaAns->begin(); j<index; ++j, ++p2) {};
        t2CaAns->erase(p2,t2CaAns->end());

        for( j=0, p2 = decision->begin(); j<index; ++j, ++p2) {};
        decision->erase(p2,decision->end());


        return Efic::OK;

}

Efic::CODE T2CaloEfic::swapVectors(const size_t index1, const size_t index2){

        float temp;
        temp=lvl2_eta->at(index1);
        lvl2_eta->at(index1)=lvl2_eta->at(index2);
        lvl2_eta->at(index2)=temp;

        temp=lvl2_phi->at(index1);
        lvl2_phi->at(index1)=lvl2_phi->at(index2);
        lvl2_phi->at(index2)=temp;

        temp=et->at(index1);
        et->at(index1)=et->at(index2);
        et->at(index2)=temp;

        temp=t2CaAns->at(index1);
        t2CaAns->at(index1)=t2CaAns->at(index2);
        t2CaAns->at(index2)=temp;

        int temp2;
        temp2=decision->at(index1);
        decision->at(index1)=decision->at(index2);
        decision->at(index2)=temp;

        return Efic::OK;

}

inline Efic::CODE T2CaloEfic::clearVectors(){

	t2CaAns->clear();
	et->clear();
	hadET_T2Calo->clear();
	F1->clear();
	decision->clear();

	return Efic::OK;

}


//Create T2Calo Graphic for debug comparision
Efic::CODE T2CaloEfic::drawCutCounter(){

	TH1I *hCuts = new TH1I("CutCounter", "L2Calo Hypo Passed Cuts; Cut", 11, -1.5, 9.5);

	vector<int> *readOutPut	=	new vector<int>;

	int nEntries	        =       static_cast<int>(eficFillingTree->GetEntries());

	eficFillingTree->SetBranchStatus("T2CaOut",	true);

	eficFillingTree->SetBranchAddress("T2CaOut",	&readOutPut);


	for(int i=0; i<nEntries;++i){
		eficFillingTree->GetEntry(i);
		for(size_t j=0; j<readOutPut->size();++j){
			switch (readOutPut->at(j)){
				case T2CaloEfic::AP:
					hCuts->Fill(T2CaloEfic::c_F1);
				case T2CaloEfic::c_F1:
					hCuts->Fill(T2CaloEfic::et_HAD);
				case T2CaloEfic::et_HAD:
					hCuts->Fill(T2CaloEfic::et_EM);
				case T2CaloEfic::et_EM:
					hCuts->Fill(T2CaloEfic::eRATIO);
				case T2CaloEfic::eRATIO:
					hCuts->Fill(T2CaloEfic::rCORE);
				case T2CaloEfic::rCORE:
					hCuts->Fill(T2CaloEfic::dPHI);
				case T2CaloEfic::dPHI:
					hCuts->Fill(T2CaloEfic::dETA);
				case T2CaloEfic::dETA:
					hCuts->Fill(T2CaloEfic::TRIG);
					hCuts->Fill(T2CaloEfic::LVL2E);
					break;
				default:
					cout<<"Retorno de valor inesperado de corte"<<endl;
					return Efic::ERROR;
			}
		}
	}


	hCuts->GetXaxis()->SetBinLabel(1,"Input");

	hCuts->GetXaxis()->SetBinLabel(2,"has one TrigEMCluster");

	hCuts->GetXaxis()->SetBinLabel(3,"#Delta #eta L2-L1");

	hCuts->GetXaxis()->SetBinLabel(4,"#Delta #phi L2-L1");

	hCuts->GetXaxis()->SetBinLabel(5,"rCore");

	hCuts->GetXaxis()->SetBinLabel(6,"eRatio");

	hCuts->GetXaxis()->SetBinLabel(7,"E_{T}^{EM}");

	hCuts->GetXaxis()->SetBinLabel(8,"E_{T}^{Had}");

	hCuts->GetXaxis()->SetBinLabel(9,"f_{1}");

	hCuts->SetEntries(hCuts->GetBinContent(T2CaloEfic::LVL2E));

	hCuts->Draw();

        delete readOutPut;

        eficFillingTree->ResetBranchAddresses();

	return Efic::OK;

}

T2CaloEfic::~T2CaloEfic(){

	delete 	hadET_T2Calo;
	delete	rCore;
	delete	energyRatio;
	delete	F1;
	delete	energy;
	delete	ehad1;
	delete	energyS1;
	delete	t2CaAns;

}
