#include"T2CaloGraphs.h"


T2CaloGraphs::T2CaloGraphs(std::string &electronsPath, std::string &jetsPath){

    minrCore=999999999.;
    maxrCore=-999999999.;
    mineRatio=999999999.;
    maxeRatio=-999999999.;
    minEt=999999999.;
    maxEt=-999999999.;
    minHadEt=999999999.;
    maxHadEt=-999999999.;
    minF1=9999999999.;
    maxF1=-999999999.;

	elc_hadET_T2Calo	=	new std::vector<float>;
	elc_rCore			=	new std::vector<float>;
	elc_energyRatio		=	new std::vector<float>;
	elc_F1			    =	new std::vector<float>;
	elc_energy			=	new std::vector<float>;
	elc_ehad1			=	new std::vector<float>;
	elc_energyS1		=	new std::vector<float>;
    elc_lvl2_eta	    = 	new std::vector<float>;
    elc_lvl2_phi	    = 	new std::vector<float>;
    elc_et      	    = 	new std::vector<float>;


	elc_readChain = new TChain("CollectionTree");
	elc_readChain->Add(electronsPath.c_str());
	elc_readChain->SetBranchStatus("*",	false);


	elc_readChain->SetBranchStatus("T2CaEta", 	    true);
    elc_readChain->SetBranchStatus("T2CaPhi",	    true);
	elc_readChain->SetBranchStatus("T2CaRcore", 	true);
	elc_readChain->SetBranchStatus("T2CaEratio",	true);
	elc_readChain->SetBranchStatus("T2CaEmES1", 	true);
	elc_readChain->SetBranchStatus("T2CaEmE", 	    true);
	elc_readChain->SetBranchStatus("T2CaHadES0",    true);


	elc_readChain->SetBranchAddress("T2CaEta", 	 &elc_lvl2_eta);
	elc_readChain->SetBranchAddress("T2CaPhi",	 &elc_lvl2_phi);
	elc_readChain->SetBranchAddress("T2CaRcore", &elc_rCore);
	elc_readChain->SetBranchAddress("T2CaEratio",&elc_energyRatio);
	elc_readChain->SetBranchAddress("T2CaEmES1", &elc_energyS1);
	elc_readChain->SetBranchAddress("T2CaEmE", 	 &elc_energy);
	elc_readChain->SetBranchAddress("T2CaHadES0",&elc_ehad1);


	jet_readChain = new TChain("CollectionTree");
	jet_readChain->Add(jetsPath.c_str());
	jet_readChain->SetBranchStatus("*",	false);


	jet_hadET_T2Calo	=	new std::vector<float>;
	jet_rCore			=	new std::vector<float>;
	jet_energyRatio	    =	new std::vector<float>;
	jet_F1		        =	new std::vector<float>;
	jet_energy		    =	new std::vector<float>;
	jet_ehad1			=	new std::vector<float>;
	jet_energyS1		=	new std::vector<float>;
    jet_lvl2_eta	    = 	new std::vector<float>;
    jet_lvl2_phi	    = 	new std::vector<float>;
    jet_et      	    = 	new std::vector<float>;


	jet_readChain->SetBranchStatus("T2CaEta", 	true);
	jet_readChain->SetBranchStatus("T2CaPhi",	true);
	jet_readChain->SetBranchStatus("T2CaRcore", true);
	jet_readChain->SetBranchStatus("T2CaEratio",true);
	jet_readChain->SetBranchStatus("T2CaEmES1", true);
	jet_readChain->SetBranchStatus("T2CaEmE", 	true);
	jet_readChain->SetBranchStatus("T2CaHadES0",true);


	jet_readChain->SetBranchAddress("T2CaEta", 		&jet_lvl2_eta);
	jet_readChain->SetBranchAddress("T2CaPhi",		&jet_lvl2_phi);
	jet_readChain->SetBranchAddress("T2CaRcore", 	&jet_rCore);
	jet_readChain->SetBranchAddress("T2CaEratio",	&jet_energyRatio);
	jet_readChain->SetBranchAddress("T2CaEmES1", 	&jet_energyS1);
	jet_readChain->SetBranchAddress("T2CaEmE", 		&jet_energy);
	jet_readChain->SetBranchAddress("T2CaHadES0", 	&jet_ehad1);

    elc_trCore = new TH1F("T2Calo_rCore Cut", "Electrons", 100, 0, 0);
    elc_teRatio = new TH1F("T2Calo_eRatio Cut", "Electrons", 100, 0, 0);
    elc_tEt = new TH1F("T2Calo_eT Cut", "Electrons", 100, 0, 0);
    elc_tHadECutHiEnergy = new TH1F("T2Calo_had_eT Cut", "Electrons", 100, 0, 0);
    elc_tHadECutLowEnergy = new TH1F("T2Calo_had_eT Cut", "Electrons", 100, 0, 0);

    elc_trCore->SetLineColor(kBlue);
    elc_teRatio->SetLineColor(kBlue);
    elc_tEt->SetLineColor(kBlue);
    elc_tHadECutHiEnergy->SetLineColor(kBlue);
    elc_tHadECutLowEnergy->SetLineColor(kTeal);

    jet_trCore = new TH1F("T2Calo_rCore Cut", "Jets", 100, 0, 0);
    jet_teRatio = new TH1F("T2Calo_eRatio Cut", "Jets", 100, 0, 0);
    jet_tEt = new TH1F("T2Calo_eT Cut", "Jets", 100, 0, 0);
    jet_tHadECutHiEnergy = new TH1F("T2Calo_had_eT Cut", "Jets", 100, 0, 0);
    jet_tHadECutLowEnergy = new TH1F("T2Calo_had_eT Cut", "Jets", 100, 0, 0);

    jet_trCore->SetLineColor(kRed);
    jet_teRatio->SetLineColor(kRed);
    jet_tEt->SetLineColor(kRed);
    jet_tHadECutHiEnergy->SetLineColor(kRed);
    jet_tHadECutLowEnergy->SetLineColor(kMagenta);


}
   


T2CaloGraphs::CODE T2CaloGraphs::exec(){


	calcTransverseFraction();//calculate the Transverse Energy and Energy Fraction F1 for its ROI j;

	for(size_t j=0; j<elc_lvl2_eta->size(); ++j){       
        fill_Cuts( elc_lvl2_eta->at(j) , elc_rCore->at(j), elc_F1->at(j), elc_energyRatio->at(j), elc_et->at(j), elc_hadET_T2Calo->at(j), 1 ); // apply cut for each ROI j for electrons;
	}//for j

	for(size_t j=0; j<jet_lvl2_eta->size(); ++j){       
        fill_Cuts( jet_lvl2_eta->at(j) , jet_rCore->at(j), jet_F1->at(j), jet_energyRatio->at(j), jet_et->at(j), jet_hadET_T2Calo->at(j), 0 ); // apply cut for each ROI j for electrons;
	}//for j

	return T2CaloGraphs::OK;

}


inline T2CaloGraphs::CODE T2CaloGraphs::calcTransverseFraction(){

    //Electrons
    for(size_t j=0; j<elc_lvl2_eta->size(); ++j){
	    elc_et->push_back( ( elc_energy->at(j) ) / ( cosh ( fabs ( elc_lvl2_eta->at(j) ) ) ) );
	    elc_hadET_T2Calo->push_back( ( elc_ehad1->at(j) ) / ( cosh ( fabs ( elc_lvl2_eta->at(j) ) ) ) / (elc_et->at(j)) );
	    elc_F1->push_back( ( elc_energyS1->at(j) ) / ( elc_energy->at(j) ) );
    }
    //Jets
    for(size_t j=0; j<jet_lvl2_eta->size(); ++j){
	    jet_et->push_back( ( jet_energy->at(j) ) / ( cosh ( fabs ( jet_lvl2_eta->at(j) ) ) ) );
	    jet_hadET_T2Calo->push_back( ( jet_ehad1->at(j) ) / ( cosh ( fabs ( jet_lvl2_eta->at(j) ) ) ) / (jet_et->at(j)));
	    jet_F1->push_back( ( jet_energyS1->at(j) ) / ( jet_energy->at(j) ) );
    }

	return	T2CaloGraphs::OK;

}

T2CaloGraphs::CODE T2CaloGraphs::fill_Cuts(const float eta, const float rCore, const float F1, const float eRatio, const float eT_T2Calo, const float hadET_T2Calo, const int dataId){
	
	size_t	etaBin = 0;
	for (size_t iBin = 0; iBin < (( sizeof(m_etabin) / sizeof(float) ) -1) ; ++iBin) {
		if ( fabs (eta) > m_etabin[iBin] && fabs (eta) < m_etabin[iBin+1] ) etaBin = iBin; 
	}

	//Corte Eta
	//if (cutEta(dEta)) return T2CaloGraphs::dETA;
 
	//Corte Phi
	//if (cutPhi(dPhi)) return T2CaloGraphs::dPHI;

    bool pass = true;

	//Corte rCore
    if (fill_rCore(rCore, etaBin,dataId)) {
        t2CaAns->push_back(T2CaloGraphs::rCORE);
        pass = false;
    }

	//Corte eRatio
    if (fill_eRatio(eRatio, F1, eta, etaBin,dataId)) {
        t2CaAns->push_back(T2CaloGraphs::eRATIO);
        pass = false;
    }

	//Corte Energia Tranversa EM
    if (fill_eT_T2Calo(eT_T2Calo, etaBin, dataId)) {
        t2CaAns->push_back(T2CaloGraphs::et_EM);
        pass = false;
    }
    
	//Corte Energia Tranversa HAD
    if (fill_hadET_T2Calo(hadET_T2Calo, eT_T2Calo, etaBin, dataId)) {
        t2CaAns->push_back(T2CaloGraphs::et_HAD);
        pass = false;
    }

	//Corte Fração de energia
/*	if (fill_F1(F1, eta, dataId)) {
        t2CaAns->push_back(T2CaloGraphs::et_HAD);
        pass = false;
    }
*/

    if (pass) t2CaAns->push_back(T2CaloGraphs::AP);

    return T2CaloGraphs::OK;

}


inline bool T2CaloGraphs::fill_rCore(const float rCore, const size_t etaBin, const int dataId){

    minrCore=(minrCore>rCore)?rCore:minrCore;
    minrCore=(maxrCore<rCore)?rCore:maxrCore;

    if (dataId) elc_trCore->Fill(rCore);
    else jet_trCore->Fill(rCore);

    if ( rCore < m_carcorethr[etaBin] )  {
        return true;
    }
    return false;

}

inline bool T2CaloGraphs::fill_eRatio(const float eRatio, const float F1, const float eta, const size_t etaBin, const int dataId){

    bool inCrack = ( fabs (eta) > 2.37 || ( fabs (eta) > 1.37 && fabs (eta) < 1.52 ) );
     
    mineRatio=(mineRatio>eRatio)?eRatio:mineRatio;
    maxeRatio=(maxeRatio<eRatio)?eRatio:maxeRatio;

    if (dataId) elc_teRatio->Fill(eRatio);
    else jet_teRatio->Fill(eRatio);

	if ( (!inCrack) || ( F1 < m_F1thr) ){
        if (eRatio < m_caeratiothr[etaBin]) { // Two ifs just to be simmilar to T2Calo implementation
		    return true;
        }
	}
 
    return false;

}

inline bool T2CaloGraphs::fill_eT_T2Calo(const float eT_T2Calo, const size_t etaBin, const int dataId){

    minEt=(minEt>eT_T2Calo)?eT_T2Calo:minEt;
    maxEt=(minEt<eT_T2Calo)?eT_T2Calo:maxEt;

    if (dataId) elc_tEt->Fill(eT_T2Calo);
    else jet_tEt->Fill(eT_T2Calo);

    if ( eT_T2Calo < m_eTthr[etaBin] ){
        return true;
    }
    return false;
}

inline bool T2CaloGraphs::fill_hadET_T2Calo(const float hadET_T2Calo, const float eT_T2Calo, const size_t etaBin, const int dataId){

    minHadEt=(minHadEt>hadET_T2Calo)?hadET_T2Calo:minHadEt;
    maxHadEt=(maxHadEt<hadET_T2Calo)?hadET_T2Calo:maxHadEt;

    float hadET_cut;


    if ( eT_T2Calo >  m_eT2thr[etaBin] ) {
        hadET_cut = m_hadeT2thr[etaBin];
        if (dataId) elc_tHadECutHiEnergy->Fill(hadET_T2Calo);
        else jet_tHadECutHiEnergy->Fill(hadET_T2Calo);
    }
    else{
        hadET_cut = m_hadeTthr[etaBin];
        if (dataId) elc_tHadECutLowEnergy->Fill(hadET_T2Calo);
        else jet_tHadECutLowEnergy->Fill(hadET_T2Calo);
    
    }
    if ( hadET_T2Calo > hadET_cut ) {
        return true;
    }
    return false;
}

inline bool T2CaloGraphs::fill_F1(const float F1, const int dataId){

    if (dataId) elc_tF1->Fill(F1);
    else jet_tF1->Fill(F1);

    if ( F1 < m_F1thr){
        return true;
    }
    return false;
}


T2CaloGraphs::CODE T2CaloGraphs::draw_rCore(){

    elc_trCore->SetAxisRange(minrCore,maxrCore);
    jet_trCore->SetAxisRange(minrCore,maxrCore);

    elc_trCore->Draw();
    jet_trCore->Draw("same");

    return T2CaloGraphs::OK;

}

T2CaloGraphs::CODE T2CaloGraphs::draw_eRatio(){

    elc_teRatio->SetAxisRange(mineRatio,maxeRatio);
    jet_teRatio->SetAxisRange(mineRatio,maxeRatio);

    elc_teRatio->Draw();
    jet_teRatio->Draw("same");

    return T2CaloGraphs::OK;

}

T2CaloGraphs::CODE T2CaloGraphs::draw_et(){

    elc_tEt->SetAxisRange(minEt,maxEt);
    jet_tEt->SetAxisRange(minEt,maxEt);


    elc_tEt->Draw();
    jet_tEt->Draw("same");

    return T2CaloGraphs::OK;

}

T2CaloGraphs::CODE T2CaloGraphs::draw_hadEt(){

    elc_tHadECutHiEnergy->SetAxisRange(minHadEt,maxHadEt);
    elc_tHadECutLowEnergy->SetAxisRange(minHadEt,maxHadEt);
    jet_tHadECutHiEnergy->SetAxisRange(minHadEt,maxHadEt);
    jet_tHadECutLowEnergy->SetAxisRange(minHadEt,maxHadEt);

    elc_tHadECutHiEnergy->Draw();
    elc_tHadECutLowEnergy->Draw("same");
    jet_tHadECutHiEnergy->Draw("same");
    jet_tHadECutLowEnergy->Draw("same");

    return T2CaloGraphs::OK;

}

T2CaloGraphs::CODE T2CaloGraphs::draw_F1(){

    elc_tF1->SetAxisRange(minF1,maxF1);
    jet_tF1->SetAxisRange(minF1,maxF1);

    elc_tF1->Draw();
    jet_tF1->Draw("same");
    return T2CaloGraphs::OK;

}


T2CaloGraphs::CODE T2CaloGraphs::drawCutCounter(){

	TH1I *hCuts = new TH1I("CutCounter", "L2Calo Hypo Passed Cuts; Cut", 11, -1.5, 9.5);


	for(size_t j=0; j<t2CaAns->size();++j){
		switch (t2CaAns->at(j)){
			case T2CaloGraphs::AP:
				hCuts->Fill(T2CaloGraphs::c_F1);
			case T2CaloGraphs::c_F1:
				hCuts->Fill(T2CaloGraphs::et_HAD);
			case T2CaloGraphs::et_HAD:
				hCuts->Fill(T2CaloGraphs::et_EM);
			case T2CaloGraphs::et_EM:
				hCuts->Fill(T2CaloGraphs::eRATIO);
			case T2CaloGraphs::eRATIO:
				hCuts->Fill(T2CaloGraphs::rCORE);
			case T2CaloGraphs::rCORE:
				hCuts->Fill(T2CaloGraphs::dPHI);
			case T2CaloGraphs::dPHI:
				hCuts->Fill(T2CaloGraphs::dETA);
			case T2CaloGraphs::dETA:
				hCuts->Fill(T2CaloGraphs::TRIG);
				hCuts->Fill(T2CaloGraphs::LVL2E);
				break;
			default:
				cout<<"Retorno de valor inesperado de corte"<<endl;
				return T2CaloGraphs::ERROR;
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


	hCuts->Draw();

    return T2CaloGraphs::OK;

}


