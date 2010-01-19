#include "T2CaloGraphs.h"


T2CaloGraphs::T2CaloGraphs(const std::string &dataPath, const std::string &userDataLabel):Graphs(dataPath, userDataLabel){

	hadET_T2Calo	=	new std::vector<float>;
	rCore			=	new std::vector<float>;
	energyRatio		=	new std::vector<float>;
	F1			    =	new std::vector<float>;
	energy			=	new std::vector<float>;
	ehad1			=	new std::vector<float>;
	energyS1		=	new std::vector<float>;
	t2CaAns		    =	new std::vector<int>;

    ringer_lvl2_eta =   new std::vector<float>;
    ringer_lvl2_phi =   new std::vector<float>;

    trCore = new TH1F((dataLabel + " rCore").c_str(), "rCore Cut", 100, 0, .1);
    teRatio = new TH1F((dataLabel + " eRatio").c_str(), "eRatio Cut", 100, 0, .1);
    tEt = new TH1F((dataLabel + " Et").c_str(), "Et_em Cut", 100, 0, .1);
    tHadEt = new TH1F((dataLabel + " HadEt").c_str(),"Et_had Cut", 100, 0, .1);

    trCore->SetBit(TH1::kCanRebin);
    teRatio->SetBit(TH1::kCanRebin);
    tEt->SetBit(TH1::kCanRebin);
    tHadEt->SetBit(TH1::kCanRebin);

    psrCore = new TPaveStats();
    pseRatio = new TPaveStats();
    psEt = new TPaveStats();
    psHadEt= new TPaveStats();


    if (dataLabel == "nopile"){ 
        trCore->SetLineColor(kBlue);
        teRatio->SetLineColor(kBlue);
        tEt->SetLineColor(kBlue);
        tHadEt->SetLineColor(kBlue);
    }else if(dataLabel == "pile"){
        trCore->SetLineColor(kRed);
        teRatio->SetLineColor(kRed);
        tEt->SetLineColor(kRed);
        tHadEt->SetLineColor(kRed);
    }


	readChain->SetBranchStatus("T2CaEta", 		true);
	readChain->SetBranchStatus("T2CaPhi", 		true);
	readChain->SetBranchStatus("T2CaRcore", 	true);
	readChain->SetBranchStatus("T2CaEratio",	true);
	readChain->SetBranchStatus("T2CaEmES1", 	true);
	readChain->SetBranchStatus("T2CaEmE", 		true);
	readChain->SetBranchStatus("T2CaHadES0", 	true);

	readChain->SetBranchStatus("Ringer_LVL2_Eta", 	true);
	readChain->SetBranchStatus("Ringer_LVL2_Phi",   true);


	readChain->SetBranchAddress("T2CaEta", 		&lvl2_eta);
	readChain->SetBranchAddress("T2CaPhi", 		&lvl2_phi);
	readChain->SetBranchAddress("T2CaRcore", 	&rCore);
	readChain->SetBranchAddress("T2CaEratio",	&energyRatio);
	readChain->SetBranchAddress("T2CaEmES1", 	&energyS1);
	readChain->SetBranchAddress("T2CaEmE", 		&energy);
	readChain->SetBranchAddress("T2CaHadES0", 	&ehad1);

    readChain->SetBranchAddress("Ringer_LVL2_Eta",   &ringer_lvl2_eta);       
    readChain->SetBranchAddress("Ringer_LVL2_Phi",   &ringer_lvl2_phi); 

    if (DEBUG) std::cout<<"Fim Construtor"<<std::endl;

}


Graphs::CODE T2CaloGraphs::exec(){

    if (DEBUG) std::cout<<"Execute()"<<std::endl;

    size_t nEntries = static_cast<size_t>(readChain->GetEntries());

    if (DEBUG) std::cout<<"nEntries "<<nEntries<<std::endl;

    for(size_t i=0; i<nEntries; ++i){

        readChain->GetEntry(i);

	    calcTransverseFraction();//calculate the Transverse Energy and Energy Fraction F1 for its ROI j;

        ordenateRoi(ringer_lvl2_eta, ringer_lvl2_phi);

	    for(size_t j=0; j<lvl2_eta->size(); ++j){
                    
		    T2CaloGraphs::PCUTS	roiAns	=	applyCuts( lvl2_eta->at(j) , rCore->at(j), F1->at(j), energyRatio->at(j), et->at(j), hadET_T2Calo->at(j) ); // apply cut for each ROI j;
		    t2CaAns->push_back(roiAns); //Fill passed cuts with the event answer given by T2Calo.

	    }//for j
        clearVectors();

    }

    if (DEBUG) std::cout<<"Fim do execute"<<std::endl;

	return Graphs::OK;

}

inline Graphs::CODE T2CaloGraphs::calcTransverseFraction(){


	for(size_t j=0; j<lvl2_eta->size(); ++j){
	    et->push_back( ( energy->at(j) ) / ( cosh ( fabs ( lvl2_eta->at(j) ) ) ) );
//	    hadET_T2Calo->push_back( ( ehad1->at(j) ) / ( cosh ( fabs ( lvl2_eta->at(j) ) ) ) ); //Antiga implementação no T2Calo
        hadET_T2Calo->push_back( ( ehad1->at(j) ) / ( cosh ( fabs ( lvl2_eta->at(j) ) ) ) / (et->at(j)) );
	    F1->push_back( ( energyS1->at(j) ) / ( energy->at(j) ) );
    }

	return	Graphs::OK;

}

T2CaloGraphs::PCUTS T2CaloGraphs::applyCuts(const float eta, const float rCore, const float F1, const float eRatio, const float eT_T2Calo, const float hadET_T2Calo){
	
	size_t	etaBin = 0;
	for (size_t iBin = 0; iBin < (( sizeof(m_etabin) / sizeof(float) ) -1) ; ++iBin) {
		if ( fabs (eta) > m_etabin[iBin] && fabs (eta) < m_etabin[iBin+1] ) etaBin = iBin; 
	}

	//Corte Eta
	//if (cutEta(dEta)) return T2CaloGraphs::dETA;
 
	//Corte Phi
	//if (cutPhi(dPhi)) return T2CaloGraphs::dPHI;

	//Corte rCore

    bool untouched = true;

    T2CaloGraphs::PCUTS pass = T2CaloGraphs::AP;

	if (cutrCore(rCore, etaBin)) {
        pass = T2CaloGraphs::rCORE;
        untouched = false;
    }

	//Corte eRatio
	if (cuteRatio(eRatio, F1, eta, etaBin) && untouched){
        pass = T2CaloGraphs::eRATIO;
        untouched = false;
    }

	//Corte Energia Tranversa EM
	if (cuteT_T2Calo(eT_T2Calo, etaBin) && untouched){
        pass = T2CaloGraphs::et_EM;
        untouched = false;
    }

	//Corte Energia Tranversa HAD
	if (cuthadET_T2Calo(hadET_T2Calo, eT_T2Calo, etaBin) &&untouched){
        pass = T2CaloGraphs::et_HAD;
        untouched = false;
    }

	//Corte Fração de energia
    //if (cutF1(F1)) return T2CaloGraphs::c_F1; //Não tem esse corte na nova versão do T2Calo, ele fica dentro do  eRatio.

	//Chegou até aqui passou yeah
	return pass;

}

inline bool T2CaloGraphs::cutEta(const float dEta){

	if ( dEta > m_detacluster ) {
		return true;
	}	
	return false;
}


inline bool T2CaloGraphs::cutPhi(const float dPhi){

	if ( dPhi > m_dphicluster ){
		return true;
	}	
	return false;

}

inline bool T2CaloGraphs::cutrCore(const float rCore, const size_t etaBin){

    trCore->Fill(rCore);
	if ( rCore < m_carcorethr[etaBin] )  {
		return true;
	}
	return false;

}

inline bool T2CaloGraphs::cuteRatio(const float eRatio, const float F1, const float eta, const size_t etaBin){

	bool inCrack = ( fabs (eta) > 2.37 || ( fabs (eta) > 1.37 && fabs (eta) < 1.52 ) );
	 
    teRatio->Fill(eRatio);

	if ( (!inCrack) || ( F1 < m_F1thr) ){
        if (eRatio < m_caeratiothr[etaBin]) { // Two ifs just to be simmilar to T2Calo implementation
		    return true;
        }
	}
 
	return false;

}

inline bool T2CaloGraphs::cuteT_T2Calo(const float eT_T2Calo, const size_t etaBin){

    tEt->Fill(eT_T2Calo);

	if ( eT_T2Calo < m_eTthr[etaBin] ){
		return true;
	}
	return false;
}

inline bool T2CaloGraphs::cuthadET_T2Calo(const float hadET_T2Calo, const float eT_T2Calo, const size_t etaBin){

    tHadEt->Fill(hadET_T2Calo);

	float hadET_cut;
	if ( eT_T2Calo >  m_eT2thr[etaBin] ) hadET_cut = m_hadeT2thr[etaBin] ;
	else hadET_cut = m_hadeTthr[etaBin];

	if ( hadET_T2Calo > hadET_cut ) {
		return true;
	}
	return false;
}

inline bool T2CaloGraphs::cutF1(const float F1){

	if ( F1 < m_F1thr){
		return true;
	}
	return false;

}

Graphs::CODE T2CaloGraphs::swapVectors(const size_t index1, const size_t index2){

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

    temp = hadET_T2Calo->at(index1);
    hadET_T2Calo->at(index1)=hadET_T2Calo->at(index2);
    hadET_T2Calo->at(index2)=temp;

    temp = F1->at(index1);
    F1->at(index1)=F1->at(index2);
    F1->at(index2)=temp;

    temp = rCore->at(index1);
    rCore->at(index1)=rCore->at(index2);
    rCore->at(index2)=temp;

    temp = energyRatio->at(index1);
    energyRatio->at(index1)=energyRatio->at(index2);
    energyRatio->at(index2)=temp;

    return Graphs::OK;

}

Graphs::CODE T2CaloGraphs::eraseVectors(const size_t index){

    std::vector<float>::iterator p;
    size_t j;

    for( j=0, p = lvl2_eta->begin(); j<index; ++j, ++p) {};
    lvl2_eta->erase(p,lvl2_eta->end());

    for( j=0, p = lvl2_phi->begin(); j<index; ++j, ++p) {};
    lvl2_phi->erase(p,lvl2_phi->end());

    for( j=0, p = et->begin(); j<index; ++j, ++p) {};
    et->erase(p,et->end());

    for( j=0, p = hadET_T2Calo->begin(); j<index; ++j, ++p) {};
    hadET_T2Calo->erase(p,hadET_T2Calo->end());

    for( j=0, p = F1->begin(); j<index; ++j, ++p) {};
    F1->erase(p,F1->end());

    for( j=0, p = rCore->begin(); j<index; ++j, ++p) {};
    rCore->erase(p,rCore->end());

    for( j=0, p = energyRatio->begin(); j<index; ++j, ++p) {};
    energyRatio->erase(p,energyRatio->end());

    return Graphs::OK;

}


inline Graphs::CODE T2CaloGraphs::clearVectors(){

	et->clear();
	hadET_T2Calo->clear();
	F1->clear();

	return Graphs::OK;

}


//Create T2Calo Graphic for debug comparision
Graphs::CODE T2CaloGraphs::drawCutCounter(){

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
				return Graphs::ERROR;
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

	hCuts->SetEntries(hCuts->GetBinContent(1));

	hCuts->Draw();

	return Graphs::OK;

}

Graphs::CODE T2CaloGraphs::drawCut(const std::string &cut){

    if (cut == "rcore"){
        trCore->Draw();
        gPad->Update();
        if (dataLabel == "nopile"){
            psrCore = (TPaveStats*)trCore->GetListOfFunctions()->FindObject("stats");
            psrCore->SetX1NDC(0.8); psrCore->SetX2NDC(0.98);
            psrCore->SetTextColor(kBlue);
        }else if(dataLabel == "pile"){
            psrCore = (TPaveStats*)trCore->GetListOfFunctions()->FindObject("stats");
            psrCore->SetX1NDC(0.55); psrCore->SetX2NDC(0.75);
            psrCore->SetTextColor(kRed);
        }
        gPad->Update();
    }else if (cut == "eratio"){
        teRatio->Draw();
        gPad->Update();
        if (dataLabel == "nopile"){
            pseRatio = (TPaveStats*)teRatio->GetListOfFunctions()->FindObject("stats");
            pseRatio->SetX1NDC(0.8); pseRatio->SetX2NDC(0.98);
            pseRatio->SetTextColor(kBlue);
        }else if(dataLabel == "pile"){
            pseRatio = (TPaveStats*)teRatio->GetListOfFunctions()->FindObject("stats");
            pseRatio->SetX1NDC(0.55); pseRatio->SetX2NDC(0.75);
            pseRatio->SetTextColor(kRed);
        }
        gPad->Update();
    }else if (cut == "et"){
        tEt->Draw();
        gPad->Update();
        if(dataLabel =="nopile"){
            psEt = (TPaveStats*)tEt->GetListOfFunctions()->FindObject("stats");
            psEt->SetX1NDC(0.8); psEt->SetX2NDC(0.98);
            psEt->SetTextColor(kBlue);
        }else if(dataLabel =="pile"){
            psEt = (TPaveStats*)tEt->GetListOfFunctions()->FindObject("stats");
            psEt->SetX1NDC(0.55); psEt->SetX2NDC(0.75);
            psEt->SetTextColor(kRed);
        }
        gPad->Update();
    }else if (cut == "hadet"){
        tHadEt->Draw();
        gPad->Update();
        if(dataLabel =="nopile"){
            psHadEt = (TPaveStats*)tHadEt->GetListOfFunctions()->FindObject("stats");
            psHadEt->SetX1NDC(0.8); psHadEt->SetX2NDC(0.98);
            psHadEt->SetTextColor(kBlue);
        }else if(dataLabel =="pile"){
            psHadEt = (TPaveStats*)tHadEt->GetListOfFunctions()->FindObject("stats");
            psHadEt->SetX1NDC(0.55); psHadEt->SetX2NDC(0.75);
            psHadEt->SetTextColor(kRed);
        }
        gPad->Update();
    }

    return Graphs::OK;


}

Graphs::CODE T2CaloGraphs::drawCut(const std::string &cut, const std::string &mode){

    if (cut == "rcore"){
        trCore->Draw(mode.c_str());
        gPad->Update();
        if (dataLabel == "nopile"){
            psrCore = (TPaveStats*)trCore->GetListOfFunctions()->FindObject("stats");
            psrCore->SetX1NDC(0.8); psrCore->SetX2NDC(0.98);
            psrCore->SetTextColor(kBlue);
        }else if(dataLabel == "pile"){
            psrCore = (TPaveStats*)trCore->GetListOfFunctions()->FindObject("stats");
            psrCore->SetX1NDC(0.55); psrCore->SetX2NDC(0.75);
            psrCore->SetTextColor(kRed);
        }
        gPad->Update();
    }else if (cut == "eratio"){
        teRatio->Draw(mode.c_str());
        gPad->Update();
        if(dataLabel == "nopile"){
            pseRatio = (TPaveStats*)teRatio->GetListOfFunctions()->FindObject("stats");
            pseRatio->SetX1NDC(0.8); pseRatio->SetX2NDC(0.98);
            pseRatio->SetTextColor(kBlue);
        }else if(dataLabel =="pile"){
            pseRatio = (TPaveStats*)teRatio->GetListOfFunctions()->FindObject("stats");
            pseRatio->SetX1NDC(0.55); pseRatio->SetX2NDC(0.75);
            pseRatio->SetTextColor(kRed);
        }
        gPad->Update();
    }else if (cut == "et"){
        tEt->Draw(mode.c_str());
        gPad->Update();
        if(dataLabel =="nopile"){
            psEt = (TPaveStats*)tEt->GetListOfFunctions()->FindObject("stats");
            psEt->SetX1NDC(0.8); psEt->SetX2NDC(0.98);
            psEt->SetTextColor(kBlue);
        }else if(dataLabel =="pile"){
            psEt = (TPaveStats*)tEt->GetListOfFunctions()->FindObject("stats");
            psEt->SetX1NDC(0.55); psEt->SetX2NDC(0.75);
            psEt->SetTextColor(kRed);
        }
        gPad->Update();
    }else if (cut == "hadet"){
        tHadEt->Draw(mode.c_str());
        gPad->Update();
        if(dataLabel == "nopile"){
            psHadEt = (TPaveStats*)tHadEt->GetListOfFunctions()->FindObject("stats");
            psHadEt->SetX1NDC(0.8); psHadEt->SetX2NDC(0.98);
            psHadEt->SetTextColor(kBlue);
        }else if(dataLabel == "pile"){
            psHadEt = (TPaveStats*)tHadEt->GetListOfFunctions()->FindObject("stats");
            psHadEt->SetX1NDC(0.55); psHadEt->SetX2NDC(0.75);
            psHadEt->SetTextColor(kRed);
        }
        gPad->Update();
    }

    return Graphs::OK;

}

double T2CaloGraphs::getMaximum(const std::string &cut){


    if (cut == "rcore"){
        return trCore->GetMaximum();
    }else if (cut == "eratio"){
        return teRatio->GetMaximum();
    }else if (cut == "et"){
        return tEt->GetMaximum();
    }else if (cut == "hadet"){
        return tHadEt->GetMaximum();
    }

    return Graphs::OK;

}


T2CaloGraphs::~T2CaloGraphs(){

    delete trCore;
    delete teRatio;
    delete tEt;
    delete tHadEt;

    delete psrCore;
    delete pseRatio;
    delete psEt;
    delete psHadEt;

	delete 	hadET_T2Calo;
	delete	rCore;
	delete	energyRatio;
	delete	F1;
	delete	energy;
	delete	ehad1;
	delete	energyS1;
	delete	t2CaAns;

}
