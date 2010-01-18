#include"T2CaloGraphs.h"


T2CaloGraphs::T2CaloGraphs(const std::string &stringPath, const std::string &userDataLabel):
Graphs(stringPath, userDataLabel){

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

    psrCore = new TPaveStats();
    pseRatio = new TPaveStats();
    psEt = new TPaveStats();
    psHiHadEt = new TPaveStats();
    psLowHadEt = new TPaveStats();


	hadET_T2Calo	=	new std::vector<float>;
	rCore			=	new std::vector<float>;
	energyRatio		=	new std::vector<float>;
	F1			    =	new std::vector<float>;
	energy			=	new std::vector<float>;
	ehad1			=	new std::vector<float>;
	energyS1		=	new std::vector<float>;
    lvl2_eta	    = 	new std::vector<float>;
    lvl2_phi	    = 	new std::vector<float>;
    et      	    = 	new std::vector<float>;
    t2CaAns         =   new std::vector<int>;


	readChain->SetBranchStatus("T2CaEta", 	    true);
    readChain->SetBranchStatus("T2CaPhi",	    true);
	readChain->SetBranchStatus("T2CaRcore", 	true);
	readChain->SetBranchStatus("T2CaEratio",	true);
	readChain->SetBranchStatus("T2CaEmES1", 	true);
	readChain->SetBranchStatus("T2CaEmE", 	    true);
	readChain->SetBranchStatus("T2CaHadES0",    true);


	readChain->SetBranchAddress("T2CaEta", 	 &lvl2_eta);
	readChain->SetBranchAddress("T2CaPhi",	 &lvl2_phi);
	readChain->SetBranchAddress("T2CaRcore", &rCore);
	readChain->SetBranchAddress("T2CaEratio",&energyRatio);
	readChain->SetBranchAddress("T2CaEmES1", &energyS1);
	readChain->SetBranchAddress("T2CaEmE", 	 &energy);
	readChain->SetBranchAddress("T2CaHadES0",&ehad1);

    if (DEBUG) std::cout<<"Calculando limite para os histogramas"<<std::endl;

	int nEvents	= static_cast<int>(readChain->GetEntries());

	for(int i = 0; i<nEvents; ++i){
  
        if (DEBUG) std::cout<<"------------"<<std::endl;

		readChain->GetEntry(i);
 
        if (DEBUG) std::cout<<"Lida a entrada "<<i<<std::endl;

        if (DEBUG) std::cout<<"Calculando parametros"<<std::endl;
     
	    calcTransverseFraction();//calculate the Transverse Energy and Energy Fraction F1 for its ROI j;

        if (DEBUG) std::cout<<"lvl2_eta size = "<<lvl2_eta->size()<<std::endl;


	    for(size_t j=0; j<lvl2_eta->size(); ++j){       
            if (DEBUG) std::cout<<j<<std::endl;
             findGraphsLimits(lvl2_eta->at(j), rCore->at(j), F1->at(j), energyRatio->at(j), et->at(j), hadET_T2Calo->at(j)); // apply cut for each ROI j;
	    }//for j


        if (DEBUG) std::cout<<"Esvaziando parametros"<<std::endl;
        clearVectors();

        if (DEBUG) std::cout<<"Entrada "<<i<<" concluida com sucesso"<<std::endl;

        if (DEBUG) std::cout<<"------------"<<std::endl;

    }


}
   


Graphs::CODE T2CaloGraphs::exec(){

	int nEvents	= static_cast<int>(readChain->GetEntries());

    if (DEBUG) std::cout<<"Iniciado execute"<<std::endl;

    if (DEBUG) std::cout<<"nEvents = "<<nEvents<<std::endl;

    if (DEBUG) std::cout<<"Preenxendo os histogramas"<<std::endl; 

    if (dataLabel == "electrons") {

        trCore = new TH1F("Elc rCore", "rCore Cut", 100, minrCore, maxrCore);
        teRatio = new TH1F("Elc eRatio", "eRatio Cut", 100, mineRatio, maxeRatio);
        tEt = new TH1F("Elc EM Et", "Et Cut", 100, minEt, maxEt);
        tHadECutHiEnergy = new TH1F("Elc Had Hi-Et", "Had Et Cut", 100, minHadEt, maxHadEt);
        tHadECutLowEnergy = new TH1F("Elc Had Low-Et", "Had Et Cut", 100, minHadEt, maxHadEt);
        tF1 = new TH1F("Elc F1", "F1 Cut", 100, minF1, maxF1);

        trCore->SetLineColor(kBlue);
        teRatio->SetLineColor(kBlue);
        tEt->SetLineColor(kBlue);
        tHadECutHiEnergy->SetLineColor(kBlue);
        tHadECutLowEnergy->SetLineColor(kTeal);


    } else {

        trCore = new TH1F("Jet rCore", "rCore Cut", 100, minrCore, maxrCore);
        teRatio = new TH1F("Jet eRatio", "eRatio Cut", 100, mineRatio, maxeRatio);
        tEt = new TH1F("Jet EM Et", "Et Cut", 100, minEt, maxEt);
        tHadECutHiEnergy = new TH1F("Jet Had Hi-Et", "Had Et Cut", 100, minHadEt, maxHadEt);
        tHadECutLowEnergy = new TH1F("Jet Had Low-Et", "Had Et Cut", 100, minHadEt, maxHadEt);
        tF1 = new TH1F("Jet F1", "F1 Cut", 100, minF1, maxF1);

        trCore->SetLineColor(kRed);
        teRatio->SetLineColor(kRed);
        tEt->SetLineColor(kRed);
        tHadECutHiEnergy->SetLineColor(kRed);
        tHadECutLowEnergy->SetLineColor(kMagenta);


    }

    trCore->SetBit(TH1::kCanRebin);
    teRatio->SetBit(TH1::kCanRebin);
    tEt->SetBit(TH1::kCanRebin);
    tHadECutHiEnergy->SetBit(TH1::kCanRebin);
    tHadECutLowEnergy->SetBit(TH1::kCanRebin);
    tF1->SetBit(TH1::kCanRebin);


	for(int i = 0; i<nEvents; ++i){
  
        if (DEBUG) std::cout<<"------------"<<std::endl;

		readChain->GetEntry(i);
 
        if (DEBUG) std::cout<<"Lida a entrada "<<i<<std::endl;

        if (DEBUG) std::cout<<"Calculando parametros"<<std::endl;
     
	    calcTransverseFraction();//calculate the Transverse Energy and Energy Fraction F1 for its ROI j;

        if (DEBUG) std::cout<<"lvl2_eta size = "<<lvl2_eta->size()<<std::endl;


	    for(size_t j=0; j<lvl2_eta->size(); ++j){       
            if (DEBUG) std::cout<<j<<std::endl;
            fill_Cuts( lvl2_eta->at(j) , rCore->at(j), F1->at(j), energyRatio->at(j), et->at(j), hadET_T2Calo->at(j)); // apply cut for each ROI j;
	    }//for j


        if (DEBUG) std::cout<<"Esvaziando parametros"<<std::endl;
        clearVectors();

        if (DEBUG) std::cout<<"Entrada "<<i<<" concluida com sucesso"<<std::endl;

        if (DEBUG) std::cout<<"------------"<<std::endl;

    }

    if (DEBUG) std::cout<<"min rCore = "<<minrCore<<std::endl; 
    if (DEBUG) std::cout<<"max rCore = "<<maxrCore<<std::endl; 
    if (DEBUG) std::cout<<"min eRatio = "<<mineRatio<<std::endl;
    if (DEBUG) std::cout<<"max rCore = "<<maxeRatio<<std::endl; 
    if (DEBUG) std::cout<<"min et = "<<minEt<<std::endl; 
    if (DEBUG) std::cout<<"max et = "<<maxEt<<std::endl; 
    if (DEBUG) std::cout<<"min hadEt = "<<minHadEt<<std::endl; 
    if (DEBUG) std::cout<<"max hadEt = "<<maxHadEt<<std::endl;
    if (DEBUG) std::cout<<"min F1 = "<<minF1<<std::endl; 
    if (DEBUG) std::cout<<"max F1 = "<<maxF1<<std::endl;  


    if (DEBUG) std::cout<<"Execute terminado com sucesso"<<std::endl;     

	return Graphs::OK;
    
}

Graphs::CODE T2CaloGraphs::exec(const float setMinrCore, const float setMaxrCore, const float setMineRatio, const float setMaxeRatio, const float setMinEt, const float setMaxEt, const float setMinHadEt, const float setMaxHadEt){

	int nEvents	= static_cast<int>(readChain->GetEntries());

    if (DEBUG) std::cout<<"Iniciado execute"<<std::endl;

    if (DEBUG) std::cout<<"nEvents = "<<nEvents<<std::endl;

    if (DEBUG) std::cout<<"Preenxendo os histogramas"<<std::endl; 

    if (dataLabel == "electrons") {

        trCore = new TH1F("Elc rCore", "rCore Cut", 100, setMinrCore, setMaxrCore);
        teRatio = new TH1F("Elc eRatio", "eRatio Cut", 100, setMineRatio, setMaxeRatio);
        tEt = new TH1F("Elc EM Et", "Et Cut", 100, setMinEt, setMaxEt);
        tHadECutHiEnergy = new TH1F("Elc Had Hi-Et", "Had Et Cut", 100, setMinHadEt, setMaxHadEt);
        tHadECutLowEnergy = new TH1F("Elc Had Low-Et", "Had Et Cut", 100, setMinHadEt, setMaxHadEt);
        tF1 = new TH1F("Elc F1", "F1 Cut", 100, minF1, maxF1);

        trCore->SetLineColor(kBlue);
        teRatio->SetLineColor(kBlue);
        tEt->SetLineColor(kBlue);
        tHadECutHiEnergy->SetLineColor(kBlue);
        tHadECutLowEnergy->SetLineColor(kTeal);


    } else {

        trCore = new TH1F("Jet rCore", "rCore Cut", 100, setMinrCore, setMaxrCore);
        teRatio = new TH1F("Jet eRatio", "eRatio Cut", 100, setMineRatio, setMaxeRatio);
        tEt = new TH1F("Jet EM Et", "Et Cut", 100, setMinEt, setMaxEt);
        tHadECutHiEnergy = new TH1F("Jet Had Hi-Et", "Had Et Cut", 100, setMinHadEt, setMaxHadEt);
        tHadECutLowEnergy = new TH1F("Jet Had Low-Et", "Had Et Cut", 100, setMinHadEt, setMaxHadEt);
        tF1 = new TH1F("Jet F1", "F1 Cut", 100, minF1, maxF1);

        trCore->SetLineColor(kRed);
        teRatio->SetLineColor(kRed);
        tEt->SetLineColor(kRed);
        tHadECutHiEnergy->SetLineColor(kRed);
        tHadECutLowEnergy->SetLineColor(kMagenta);


    }

    trCore->SetBit(TH1::kCanRebin);
    teRatio->SetBit(TH1::kCanRebin);
    tEt->SetBit(TH1::kCanRebin);
    tHadECutHiEnergy->SetBit(TH1::kCanRebin);
    tHadECutLowEnergy->SetBit(TH1::kCanRebin);
    tF1->SetBit(TH1::kCanRebin);


	for(int i = 0; i<nEvents; ++i){
  
        if (DEBUG) std::cout<<"------------"<<std::endl;

		readChain->GetEntry(i);
 
        if (DEBUG) std::cout<<"Lida a entrada "<<i<<std::endl;

        if (DEBUG) std::cout<<"Calculando parametros"<<std::endl;
     
	    calcTransverseFraction();//calculate the Transverse Energy and Energy Fraction F1 for its ROI j;

        if (DEBUG) std::cout<<"lvl2_eta size = "<<lvl2_eta->size()<<std::endl;


	    for(size_t j=0; j<lvl2_eta->size(); ++j){       
            if (DEBUG) std::cout<<j<<std::endl;
            fill_Cuts( lvl2_eta->at(j) , rCore->at(j), F1->at(j), energyRatio->at(j), et->at(j), hadET_T2Calo->at(j)); // apply cut for each ROI j;
	    }//for j


        if (DEBUG) std::cout<<"Esvaziando parametros"<<std::endl;
        clearVectors();

        if (DEBUG) std::cout<<"Entrada "<<i<<" concluida com sucesso"<<std::endl;

        if (DEBUG) std::cout<<"------------"<<std::endl;

    }

    if (DEBUG) std::cout<<"min rCore = "<<setMinrCore<<std::endl; 
    if (DEBUG) std::cout<<"max rCore = "<<maxrCore<<std::endl; 
    if (DEBUG) std::cout<<"min eRatio = "<<mineRatio<<std::endl;
    if (DEBUG) std::cout<<"max rCore = "<<maxeRatio<<std::endl; 
    if (DEBUG) std::cout<<"min et = "<<minEt<<std::endl; 
    if (DEBUG) std::cout<<"max et = "<<maxEt<<std::endl; 
    if (DEBUG) std::cout<<"min hadEt = "<<minHadEt<<std::endl; 
    if (DEBUG) std::cout<<"max hadEt = "<<maxHadEt<<std::endl;
    if (DEBUG) std::cout<<"min F1 = "<<minF1<<std::endl; 
    if (DEBUG) std::cout<<"max F1 = "<<maxF1<<std::endl;  


    if (DEBUG) std::cout<<"Execute terminado com sucesso"<<std::endl;     

	return Graphs::OK;
    
}



inline Graphs::CODE T2CaloGraphs::calcTransverseFraction(){

    //Electrons
    for(size_t j=0; j<lvl2_eta->size(); ++j){
	    et->push_back( ( energy->at(j) ) / ( cosh ( fabs ( lvl2_eta->at(j) ) ) ) );
	    hadET_T2Calo->push_back( ( ehad1->at(j) ) / ( cosh ( fabs ( lvl2_eta->at(j) ) ) ) / (et->at(j)) );
	    F1->push_back( ( energyS1->at(j) ) / ( energy->at(j) ) );
    }


	return	Graphs::OK;

}

Graphs::CODE T2CaloGraphs::findGraphsLimits(const float eta, const float rCore, const float F1, const float eRatio, const float eT_T2Calo, const float hadET_T2Calo){

    minrCore=(minrCore>rCore)?rCore:minrCore;
    maxrCore=(maxrCore<rCore)?rCore:maxrCore;

    bool inCrack = ( fabs (eta) > 2.37 || ( fabs (eta) > 1.37 && fabs (eta) < 1.52 ) );

    if ( (!inCrack) || ( F1 < m_F1thr)) {
        mineRatio=(mineRatio>eRatio)?eRatio:mineRatio;
        maxeRatio=(maxeRatio<eRatio)?eRatio:maxeRatio;
    }

    minEt=(minEt>eT_T2Calo)?eT_T2Calo:minEt;
    maxEt=(minEt<eT_T2Calo)?eT_T2Calo:maxEt;

    minHadEt=(minHadEt>hadET_T2Calo)?hadET_T2Calo:minHadEt;
    maxHadEt=(maxHadEt<hadET_T2Calo)?hadET_T2Calo:maxHadEt;

    minF1=(minF1>F1)?F1:minF1;
    maxF1=(maxF1<F1)?F1:maxF1;

    return Graphs::OK;

}

Graphs::CODE T2CaloGraphs::fill_Cuts(const float eta, const float rCore, const float F1, const float eRatio, const float eT_T2Calo, const float hadET_T2Calo){
	
	size_t	etaBin = 0;
	for (size_t iBin = 0; iBin < (( sizeof(m_etabin) / sizeof(float) ) -1) ; ++iBin) {
		if ( fabs (eta) > m_etabin[iBin] && fabs (eta) < m_etabin[iBin+1] ) etaBin = iBin; 
	}

	//Corte Eta
	//if (cutEta(dEta)) return T2CaloGraphs::dETA;
 
	//Corte Phi
	//if (cutPhi(dPhi)) return T2CaloGraphs::dPHI;

    if (DEBUG) std::cout<<"Preenxendo os gráficos"<<std::endl;


    bool pass = true;

	//Corte rCore
    if (fill_rCore(rCore, etaBin)) {
        t2CaAns->push_back(T2CaloGraphs::rCORE);
        pass = false;
    }

	//Corte eRatio
    if (fill_eRatio(eRatio, F1, eta, etaBin) && pass) {
        t2CaAns->push_back(T2CaloGraphs::eRATIO);
        pass = false;
    }

	//Corte Energia Tranversa EM
    if (fill_eT_T2Calo(eT_T2Calo, etaBin) && pass) {
        t2CaAns->push_back(T2CaloGraphs::et_EM);
        pass = false;
    }
    
	//Corte Energia Tranversa HAD
    if (fill_hadET_T2Calo(hadET_T2Calo, eT_T2Calo, etaBin) && pass) {
        t2CaAns->push_back(T2CaloGraphs::et_HAD);
        pass = false;
    }

	//Corte Fração de energia
/*	if (fill_F1(F1, eta) && pass) {
        t2CaAns->push_back(T2CaloGraphs::et_HAD);
        pass = false;
    }
*/

    if (pass) {
        t2CaAns->push_back(T2CaloGraphs::AP);
    }

    return Graphs::OK;

}


inline bool T2CaloGraphs::fill_rCore(const float rCore, const size_t etaBin){


    if (DEBUG) std::cout<<"Dando fill no rCore, rCore = "<<rCore<<std::endl;
    trCore->Fill(rCore);

    if ( rCore < m_carcorethr[etaBin] )  {
        return true;
    }
    return false;

}

inline bool T2CaloGraphs::fill_eRatio(const float eRatio, const float F1, const float eta, const size_t etaBin){

    bool inCrack = ( fabs (eta) > 2.37 || ( fabs (eta) > 1.37 && fabs (eta) < 1.52 ) );
     


	if ( (!inCrack) || ( F1 < m_F1thr) ){
        if (DEBUG) std::cout<<"Dando fill no eRatio, eRatio = "<<eRatio<<std::endl;
        teRatio->Fill(eRatio);
        if (eRatio < m_caeratiothr[etaBin]) { // Two ifs just to be simmilar to T2Calo implementation
		    return true;
        }
	}
 
    return false;

}

inline bool T2CaloGraphs::fill_eT_T2Calo(const float eT_T2Calo, const size_t etaBin){


    if (DEBUG) std::cout<<"Dando fill no EM Et, eT = "<<eT_T2Calo<<std::endl;
    tEt->Fill(eT_T2Calo);

    if ( eT_T2Calo < m_eTthr[etaBin] ){
        return true;
    }
    return false;
}

inline bool T2CaloGraphs::fill_hadET_T2Calo(const float hadET_T2Calo, const float eT_T2Calo, const size_t etaBin){


    float hadET_cut;


    if ( eT_T2Calo >  m_eT2thr[etaBin] ) {
        if (DEBUG) std::cout<<"Dando fill no HAD Hi-Et, HADeT = "<<hadET_T2Calo<<std::endl;
        hadET_cut = m_hadeT2thr[etaBin];
        tHadECutHiEnergy->Fill(hadET_T2Calo);
    }
    else{
        if (DEBUG) std::cout<<"Dando fill no HAD Low-Et, HADeT = "<<hadET_T2Calo<<std::endl;
        hadET_cut = m_hadeTthr[etaBin];
        tHadECutLowEnergy->Fill(hadET_T2Calo);
    }
    if ( hadET_T2Calo > hadET_cut ) {
        return true;
    }
    return false;
}

inline bool T2CaloGraphs::fill_F1(const float F1){

    tF1->Fill(F1);

    if ( F1 < m_F1thr){
        return true;
    }
    return false;
}


Graphs::CODE T2CaloGraphs::draw_rCore(){

    trCore->Draw();

    gPad->Update();

    if (dataLabel == "electrons") {
    
        psrCore = (TPaveStats*)trCore->GetListOfFunctions()->FindObject("stats");
        psrCore->SetX1NDC(0.8); psrCore->SetX2NDC(0.98);
        psrCore->SetTextColor(kBlue);
    }else{
        psrCore = (TPaveStats*)trCore->GetListOfFunctions()->FindObject("stats");
        psrCore->SetX1NDC(0.55); psrCore->SetX2NDC(0.75);
        psrCore->SetTextColor(kRed);
    }

    psrCore->Draw();

    gPad->Update();


    return Graphs::OK;

}

Graphs::CODE T2CaloGraphs::draw_eRatio(){


    teRatio->Draw();

    gPad->Update();

    if (dataLabel == "electrons") {
    
        pseRatio = (TPaveStats*)teRatio->GetListOfFunctions()->FindObject("stats");
        pseRatio->SetX1NDC(0.8); pseRatio->SetX2NDC(0.98);
        pseRatio->SetTextColor(kBlue);
    }else{
        pseRatio = (TPaveStats*)teRatio->GetListOfFunctions()->FindObject("stats");
        pseRatio->SetX1NDC(0.55); pseRatio->SetX2NDC(0.75);
        pseRatio->SetTextColor(kRed);
    }

    pseRatio->Draw();

    gPad->Update();

    return Graphs::OK;

}

Graphs::CODE T2CaloGraphs::draw_et(){

    tEt->Draw();

    gPad->Update();

    if (dataLabel == "electrons") {
    
        psEt = (TPaveStats*)tEt->GetListOfFunctions()->FindObject("stats");
        psEt->SetX1NDC(0.8); psEt->SetX2NDC(0.98);
        psEt->SetTextColor(kBlue);
    }else{
        psEt = (TPaveStats*)tEt->GetListOfFunctions()->FindObject("stats");
        psEt->SetX1NDC(0.55); psEt->SetX2NDC(0.75);
        psEt->SetTextColor(kRed);
    }

    psEt->Draw();

    gPad->Update();

    return Graphs::OK;

}

Graphs::CODE T2CaloGraphs::draw_hadEt(){

	int max1=tHadECutHiEnergy->GetMaximum();
	int max2=tHadECutLowEnergy->GetMaximum();

    if (max1>max2){
	    tHadECutHiEnergy->SetAxisRange(0,1.1*max1, "Y");
        tHadECutLowEnergy->SetAxisRange(0,1.1*max1,"Y");
    }else{
	    tHadECutHiEnergy->SetAxisRange(0,1.1*max2, "Y");
        tHadECutLowEnergy->SetAxisRange(0,1.1*max2,"Y");
    }
        

    tHadECutHiEnergy->Draw();
    tHadECutLowEnergy->Draw("sames");

    gPad->Update();

    if (dataLabel == "electrons") {

        psHiHadEt = (TPaveStats*)tHadECutHiEnergy->GetListOfFunctions()->FindObject("stats");
        psHiHadEt->SetX1NDC(0.84); psHiHadEt->SetX2NDC(0.99);
        psHiHadEt->SetTextColor(kBlue);

        psLowHadEt = (TPaveStats*)tHadECutLowEnergy->GetListOfFunctions()->FindObject("stats");
        psLowHadEt->SetX1NDC(0.68); psLowHadEt->SetX2NDC(0.83);
        psLowHadEt->SetTextColor(kTeal);

    }else{

        psHiHadEt = (TPaveStats*)tHadECutHiEnergy->GetListOfFunctions()->FindObject("stats");
        psHiHadEt->SetX1NDC(0.52); psHiHadEt->SetX2NDC(0.67);
        psHiHadEt->SetTextColor(kRed);

        psLowHadEt = (TPaveStats*)tHadECutLowEnergy->GetListOfFunctions()->FindObject("stats");
        psLowHadEt->SetX1NDC(0.36); psLowHadEt->SetX2NDC(0.51);
        psLowHadEt->SetTextColor(kMagenta);

    }

    psHiHadEt->Draw();
    psLowHadEt->Draw();

    gPad->Update();

    return Graphs::OK;

}

Graphs::CODE T2CaloGraphs::draw_F1(){

    tF1->Draw();

    return Graphs::OK;

}

Graphs::CODE T2CaloGraphs::draw_rCore(std::string input){

    trCore->Draw(input.c_str());

    gPad->Update();

    if (dataLabel == "electrons") {
    
        psrCore = (TPaveStats*)trCore->GetListOfFunctions()->FindObject("stats");
        psrCore->SetX1NDC(0.8); psrCore->SetX2NDC(0.98);
        psrCore->SetTextColor(kBlue);
    }else{
        psrCore = (TPaveStats*)trCore->GetListOfFunctions()->FindObject("stats");
        psrCore->SetX1NDC(0.55); psrCore->SetX2NDC(0.75);
        psrCore->SetTextColor(kRed);
    }

    psrCore->Draw();

    gPad->Update();

    return Graphs::OK;

}

Graphs::CODE T2CaloGraphs::draw_eRatio(std::string input){

    teRatio->Draw(input.c_str());

    gPad->Update();

    if (dataLabel == "electrons") {
    
        pseRatio = (TPaveStats*)teRatio->GetListOfFunctions()->FindObject("stats");
        pseRatio->SetX1NDC(0.8); pseRatio->SetX2NDC(0.98);
        pseRatio->SetTextColor(kBlue);
    }else{
        pseRatio = (TPaveStats*)teRatio->GetListOfFunctions()->FindObject("stats");
        pseRatio->SetX1NDC(0.55); pseRatio->SetX2NDC(0.75);
        pseRatio->SetTextColor(kRed);
    }

    pseRatio->Draw();

    gPad->Update();

    return Graphs::OK;

}

Graphs::CODE T2CaloGraphs::draw_et(std::string input){


    tEt->Draw(input.c_str());

    gPad->Update();

    if (dataLabel == "electrons") {
    
        psEt = (TPaveStats*)tEt->GetListOfFunctions()->FindObject("stats");
        psEt->SetX1NDC(0.8); psEt->SetX2NDC(0.98);
        psEt->SetTextColor(kBlue);
    }else{
        psEt = (TPaveStats*)tEt->GetListOfFunctions()->FindObject("stats");
        psEt->SetX1NDC(0.55); psEt->SetX2NDC(0.75);
        psEt->SetTextColor(kRed);
    }

    psEt->Draw();

    gPad->Update();

    return Graphs::OK;

}

Graphs::CODE T2CaloGraphs::draw_hadEt(std::string input){

	int max1=tHadECutHiEnergy->GetMaximum();
	int max2=tHadECutLowEnergy->GetMaximum();

    if (max1>max2){
	    tHadECutHiEnergy->SetAxisRange(0,1.1*max1, "Y");
        tHadECutLowEnergy->SetAxisRange(0,1.1*max1,"Y");
    }else{
	    tHadECutHiEnergy->SetAxisRange(0,1.1*max2, "Y");
        tHadECutLowEnergy->SetAxisRange(0,1.1*max2,"Y");
    }

    tHadECutHiEnergy->Draw(input.c_str());
    tHadECutLowEnergy->Draw(input.c_str());

    gPad->Update();

    if (dataLabel == "electrons") {

        psHiHadEt = (TPaveStats*)tHadECutHiEnergy->GetListOfFunctions()->FindObject("stats");
        psHiHadEt->SetX1NDC(0.84); psHiHadEt->SetX2NDC(0.99);
        psHiHadEt->SetTextColor(kBlue);

        psLowHadEt = (TPaveStats*)tHadECutLowEnergy->GetListOfFunctions()->FindObject("stats");
        psLowHadEt->SetX1NDC(0.68); psLowHadEt->SetX2NDC(0.83);
        psLowHadEt->SetTextColor(kTeal);

    }else{

        psHiHadEt = (TPaveStats*)tHadECutHiEnergy->GetListOfFunctions()->FindObject("stats");
        psHiHadEt->SetX1NDC(0.52); psHiHadEt->SetX2NDC(0.67);
        psHiHadEt->SetTextColor(kRed);

        psLowHadEt = (TPaveStats*)tHadECutLowEnergy->GetListOfFunctions()->FindObject("stats");
        psLowHadEt->SetX1NDC(0.36); psLowHadEt->SetX2NDC(0.51);
        psLowHadEt->SetTextColor(kMagenta);

    }

    psHiHadEt->Draw();
    psLowHadEt->Draw();

    gPad->Update();

    return Graphs::OK;

}

Graphs::CODE T2CaloGraphs::draw_F1(std::string input){

    tF1->Draw(input.c_str());

    return Graphs::OK;

}



inline Graphs::CODE T2CaloGraphs::clearVectors(){

	et->clear();
	hadET_T2Calo->clear();
	F1->clear();

    return Graphs::OK;

}




Graphs::CODE T2CaloGraphs::draw_cutCounter(){

	TH1I *hCuts = new TH1I("CutCounter", "L2Calo Hypo Passed Cuts; Cut", 11, -1.5, 9.5);

    if (DEBUG) std::cout<<"t2CaAns size é de "<<t2CaAns->size()<<std::endl;

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
				std::cout<<"Retorno de valor inesperado de corte"<<std::endl;
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


Graphs::CODE T2CaloGraphs::setRange(const std::string &cutName, const float yMax){

    if (cutName == "rcore"){
        trCore->SetAxisRange(0,1.1*yMax,"Y");
    }else if (cutName == "eratio"){
        teRatio->SetAxisRange(0,1.1*yMax,"Y");
    }else if (cutName == "et"){
        tEt->SetAxisRange(0,1.1*yMax,"Y");
    }else if (cutName == "hadet"){
        tHadECutHiEnergy->SetAxisRange(0,yMax,"Y");
        tHadECutLowEnergy->SetAxisRange(0,yMax,"Y");
    }else if (cutName == "f1"){
        tF1->SetAxisRange(0,1.1*yMax,"Y");
    }

    return Graphs::OK;

}

/*

float T2CaloGraphs::getminX(const std::string &dataType){


    if(dataType == "rcore"){
        return minrCore;
    } else if (dataType == "eratio"){
        return mineRatio;
    } else if (dataType == "et"){
        return minEt;
    } else if (dataType == "hadet"){
        return minHadEt;
    }
    else return 0;

}

float T2CaloGraphs::getmaxX(const std::string &dataType){


    if(dataType == "rcore"){
        return maxrCore;
    } else if (dataType == "eratio"){
        return maxeRatio;
    } else if (dataType == "et"){
        return maxEt;
    } else if (dataType == "hadet"){
        return maxHadEt;
    }
    else return 0;


}

*/

float T2CaloGraphs::getY(const std::string &dataType){

    if(dataType == "rcore"){
        return trCore->GetMaximum();
    } else if (dataType == "eratio"){
        return teRatio->GetMaximum();
    } else if (dataType == "et"){
        return tEt->GetMaximum();
    } else if (dataType == "hadet"){
        if (tHadECutHiEnergy->GetMaximum() > tHadECutLowEnergy->GetMaximum()) return tHadECutHiEnergy->GetMaximum();
        else return tHadECutLowEnergy->GetMaximum();
    }
    else return 0;

}





