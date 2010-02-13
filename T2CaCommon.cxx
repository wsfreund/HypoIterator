#include "T2CaCommon.h"

T2CaCommon::T2CaCommon(const std::string &chainPath):
    HypoBase(chainPath){

    hadET_T2Calo = new std::vector<float>;
    rCore = new std::vector<float>;
    energyRatio = new std::vector<float>;
    F1 = new std::vector<float>;
    energy = new std::vector<float>;
    ehad1 = new std::vector<float>;
    energyS1 = new std::vector<float>;
    t2CaAns = new std::vector<int>;
    ringer_eta = new std::vector<float>;
    ringer_phi = new std::vector<float>;

    hypoChain->SetBranchStatus("T2CaEta",        true);
    hypoChain->SetBranchStatus("T2CaPhi",        true);
    hypoChain->SetBranchStatus("T2CaRcore",      true);
    hypoChain->SetBranchStatus("T2CaEratio",     true);
    hypoChain->SetBranchStatus("T2CaEmES1",      true);
    hypoChain->SetBranchStatus("T2CaEmE",        true);
    hypoChain->SetBranchStatus("T2CaHadES0",     true);

    hypoChain->SetBranchStatus("Ringer_LVL2_Eta",true);
    hypoChain->SetBranchStatus("Ringer_LVL2_Phi",true);

    hypoChain->SetBranchAddress("T2CaEta",       &lvl2_eta);
    hypoChain->SetBranchAddress("T2CaPhi",       &lvl2_phi);
    hypoChain->SetBranchAddress("T2CaRcore",     &rCore);
    hypoChain->SetBranchAddress("T2CaEratio",    &energyRatio);
    hypoChain->SetBranchAddress("T2CaEmES1",     &energyS1);
    hypoChain->SetBranchAddress("T2CaEmE",       &energy);
    hypoChain->SetBranchAddress("T2CaHadES0",    &ehad1);
    hypoChain->SetBranchAddress("Ringer_LVL2_Eta",&ringer_eta);
    hypoChain->SetBranchAddress("Ringer_LVL2_Phi",&ringer_phi);

    extraVariables = new TTree("HypoData", "Tree with Hypo data");

    cout<<extraVariables<<endl;
    extraVariables->Branch("T2CaEta", &lvl2_eta);
    extraVariables->Branch("T2CaPhi", &lvl2_phi);
    extraVariables->Branch("T2CaDec", &decision);
    extraVariables->Branch("T2CaOut", &t2CaAns);
    extraVariables->Branch("T2CaEt",  &et);
    extraVariables->Branch("T2CaF1",  &F1);
    extraVariables->Branch("T2CaHadEt", &hadET_T2Calo);

    exec();
}




HypoBase::CODE T2CaCommon::exec(){

    int n_entries = static_cast<int>(hypoChain->GetEntries());

    for(int i=0; i<n_entries; ++i){
     
        hypoChain->GetEntry(i);
        calcTransverseFraction();//calculate the Transverse Energy and Energy Fraction F1 for its ROI i;

        for(size_t j=0; j<lvl2_eta->size(); ++j){
            T2CaCommon::PCUTS       roiAns  =       applyCuts( lvl2_eta->at(j) , rCore->at(j), F1->at(j), energyRatio->at(j), et->at(j), hadET_T2Calo->at(j) ); // apply cut for each ROI j;
            t2CaAns->push_back(roiAns); //Fill passed cuts with the event answer given by T2Calo.
            fillDecision(roiAns); //Fill vector telling if the event was a electron or a jet;
        }//for j
        ordenateRoi(ringer_eta, ringer_phi);
        extraVariables->Fill();
        clearVectors();
    }

    return HypoBase::OK;

}

inline HypoBase::CODE T2CaCommon::calcTransverseFraction(){


    for(size_t j=0; j<lvl2_eta->size(); ++j){
        et->push_back( ( energy->at(j) ) / ( cosh ( fabs ( lvl2_eta->at(j) ) ) ) );
        //          hadET_T2Calo->push_back( ( ehad1->at(j) ) / ( cosh ( fabs ( lvl2_eta->at(j) ) ) ) ); //Antiga implementação no T2Calo
        hadET_T2Calo->push_back( ( ehad1->at(j) ) / ( cosh ( fabs ( lvl2_eta->at(j) ) ) ) / (et->at(j)) );
        F1->push_back( ( energyS1->at(j) ) / ( energy->at(j) ) );
    }

    return  HypoBase::OK;

}

HypoBase::CODE T2CaCommon::fillDecision(T2CaCommon::PCUTS   entry){

    switch (entry){
        case T2CaCommon::AP:
            decision->push_back(HypoBase::ELECTRON);
            break;
        case T2CaCommon::dETA:
        case T2CaCommon::dPHI:
        case T2CaCommon::rCORE:
        case T2CaCommon::eRATIO:
        case T2CaCommon::et_EM:
        case T2CaCommon::et_HAD:
        case T2CaCommon::c_F1:
            decision->push_back(HypoBase::JET);
            break;
        default:
            return HypoBase::ERROR;
    }

    return HypoBase::OK;

}

T2CaCommon::PCUTS T2CaCommon::applyCuts(const float eta, const float rCore, const float F1, const float eRatio, const float eT_T2Calo, const float hadET_T2Calo){

    size_t  etaBin = 0;
    for (size_t iBin = 0; iBin < (( sizeof(m_etabin) / sizeof(float) ) -1) ; ++iBin) {
        if ( fabs (eta) > m_etabin[iBin] && fabs (eta) < m_etabin[iBin+1] ) etaBin = iBin; 
    }

    //Corte Eta
    //if (cutEta(dEta)) return T2CaCommon::dETA;

    //Corte Phi
    //if (cutPhi(dPhi)) return T2CaCommon::dPHI;

    //Corte rCore
    if (cutrCore(rCore, etaBin)) return T2CaCommon::rCORE;

    //Corte eRatio
    if (cuteRatio(eRatio, F1, eta, etaBin)) return T2CaCommon::eRATIO;

    //Corte Energia Tranversa EM
    if (cuteT_T2Calo(eT_T2Calo, etaBin)) return T2CaCommon::et_EM;

    //Corte Energia Tranversa HAD
    if (cuthadET_T2Calo(hadET_T2Calo, eT_T2Calo, etaBin)) return T2CaCommon::et_HAD;

    //Corte Fração de energia
    //if (cutF1(F1)) return T2CaCommon::c_F1; //Não tem esse corte na nova versão do T2Calo, ele fica dentro do  eRatio.

    //Chegou até aqui passou yeah
    return T2CaCommon::AP;

}

inline bool T2CaCommon::cutEta(const float dEta){

    if ( dEta > m_detacluster ) {
        return true;
    }       
    return false;
}


inline bool T2CaCommon::cutPhi(const float dPhi){

    if ( dPhi > m_dphicluster ){
        return true;
    }       
    return false;

}

inline bool T2CaCommon::cutrCore(const float rCore, const size_t etaBin){

    if ( rCore < m_carcorethr[etaBin] )  {
        return true;
    }
    return false;

}

inline bool T2CaCommon::cuteRatio(const float eRatio, const float F1, const float eta, const size_t etaBin){

    bool inCrack = ( fabs (eta) > 2.37 || ( fabs (eta) > 1.37 && fabs (eta) < 1.52 ) );

    if ( (!inCrack) || ( F1 < m_F1thr) ){
        if (eRatio < m_caeratiothr[etaBin]) { // Two ifs just to be simmilar to T2Calo implementation
            return true;
        }
    }

    return false;

}

inline bool T2CaCommon::cuteT_T2Calo(const float eT_T2Calo, const size_t etaBin){


    if ( eT_T2Calo < m_eTthr[etaBin] ){
        return true;
    }
    return false;
}

inline bool T2CaCommon::cuthadET_T2Calo(const float hadET_T2Calo, const float eT_T2Calo, const size_t etaBin){


    float hadET_cut;
    if ( eT_T2Calo >  m_eT2thr[etaBin] ) hadET_cut = m_hadeT2thr[etaBin] ;
    else hadET_cut = m_hadeTthr[etaBin];

    if ( hadET_T2Calo > hadET_cut ) {
        return true;
    }
    return false;
}

inline bool T2CaCommon::cutF1(const float F1){

    if ( F1 < m_F1thr){
        return true;
    }
    return false;

}


HypoBase::CODE T2CaCommon::eraseVectors(const size_t index){

    std::vector<float>::iterator p;
    std::vector<int>::iterator p2;
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


    return HypoBase::OK;

}

HypoBase::CODE T2CaCommon::swapVectors(const size_t index1, const size_t index2){

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

    return HypoBase::OK;

}

inline HypoBase::CODE T2CaCommon::clearVectors(){

    t2CaAns->clear();
    et->clear();
    hadET_T2Calo->clear();
    F1->clear();
    decision->clear();

    return HypoBase::OK;

}

HypoBase::CODE T2CaCommon::ordenateRoi(const std::vector<float> *eta, const std::vector<float> *phi){

    for(size_t j=0; j<lvl2_eta->size();++j){
        if ( j < eta->size() ){
            unsigned matchingPair =     j;
            float    vError  =       sqrt (pow(( eta->at(j) - lvl2_eta->at(j) ),2)+pow(( phi->at(j) - lvl2_phi->at(j) ),2) );
            for(size_t k= (j+1) ; k < (lvl2_eta->size()); ++k){
                float actualError =  sqrt (pow(( eta->at(j) - lvl2_eta->at(k) ),2)+pow(( phi->at(j) - lvl2_phi->at(k) ),2) );
                if ( actualError < vError ) {
                    vError = actualError;
                    matchingPair = k;
                }
            }
            if (j!=matchingPair) {
                swapVectors(j,matchingPair);
            }
        }else{
            eraseVectors(j);
            break;
        }
    }
    return HypoBase::OK;
}


//Create T2Calo Graphic for debug comparision
HypoBase::CODE T2CaCommon::drawCutCounter(){

    TH1I *hCuts = new TH1I("CutCounter", "L2Calo Hypo Passed Cuts; Cut", 11, -1.5, 9.5);

    int nEntries = static_cast<int>(extraVariables->GetEntries());

    for(int i=0; i<nEntries;++i){
        extraVariables->GetEntry(i);
        for(size_t j=0; j<t2CaAns->size();++j){
            switch (t2CaAns->at(j)){
                case T2CaCommon::AP:
                    hCuts->Fill(T2CaCommon::c_F1);
                case T2CaCommon::c_F1:
                    hCuts->Fill(T2CaCommon::et_HAD);
                case T2CaCommon::et_HAD:
                    hCuts->Fill(T2CaCommon::et_EM);
                case T2CaCommon::et_EM:
                    hCuts->Fill(T2CaCommon::eRATIO);
                case T2CaCommon::eRATIO:
                    hCuts->Fill(T2CaCommon::rCORE);
                case T2CaCommon::rCORE:
                    hCuts->Fill(T2CaCommon::dPHI);
                case T2CaCommon::dPHI:
                    hCuts->Fill(T2CaCommon::dETA);
                case T2CaCommon::dETA:
                    hCuts->Fill(T2CaCommon::TRIG);
                    hCuts->Fill(T2CaCommon::LVL2E);
                    break;
                default:
                    return HypoBase::ERROR;
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
    hCuts->SetEntries(hCuts->GetBinContent(1));
    hCuts->Draw();

    return HypoBase::OK;

}

T2CaCommon::~T2CaCommon(){

    delete  hadET_T2Calo;
    delete  rCore;
    delete  energyRatio;
    delete  F1;
    delete  energy;
    delete  ehad1;
    delete  energyS1;
    delete  t2CaAns;
    delete  ringer_eta;
    delete  ringer_phi;

}
