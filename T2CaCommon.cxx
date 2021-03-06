#include "T2CaCommon.h"

T2CaCommon::T2CaCommon(const std::string &chainPath, const t2ca_00_07_85_conf userL2chain, const std::string &userDataLabel):
T2CaBase(chainPath, userDataLabel)
{
  l2chain = userL2chain,
  hCuts = 0;
  rCoreCuts = 0;
  eRatioCuts = 0;
  etCuts = 0;
  hadEtCuts = 0;
  detrCoreRate = 0;
  deteRatioRate = 0;
  detEtRate = 0;
  detHadEtRate = 0;
  initialize();
}

T2CaCommon::T2CaCommon(const std::string &chainPath, const t2ca_00_07_85_conf userL2chain, const std::string &userDataLabel, const std::string &id):
T2CaBase(chainPath, userDataLabel, id)
{
  l2chain = userL2chain;
  hCuts = 0;
  rCoreCuts = 0;
  eRatioCuts = 0;
  etCuts = 0;
  hadEtCuts = 0;
  detrCoreRate = 0;
  deteRatioRate = 0;
  detEtRate = 0;
  detHadEtRate = 0;
  initialize();
}

HypoBase::CODE T2CaCommon::initialize(){

    file->cd();
    file->mkdir(("T2Calo Analysis_" + dataLabel).c_str());
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

    extraVariables = new TTree(("T2Calo Tree_" + dataLabel).c_str(), "Tree with T2Calo data");

    extraVariables->Branch("T2CaEta", &lvl2_eta);
    extraVariables->Branch("T2CaPhi", &lvl2_phi);
    extraVariables->Branch("T2CaDec", &decision);
    extraVariables->Branch("T2CaOut", &t2CaAns);
    extraVariables->Branch("T2CaEt",  &et);
    extraVariables->Branch("T2CaF1",  &F1);
    extraVariables->Branch("T2CaHadEt", &hadET_T2Calo);

    return HypoBase::OK;
}

HypoBase::CODE T2CaCommon::ResetBranchAddresses(){

    extraVariables->ResetBranchAddresses();
    extraVariables->SetBranchStatus("*",true);
    extraVariables->SetBranchAddress("T2CaEta", &lvl2_eta);
    extraVariables->SetBranchAddress("T2CaPhi", &lvl2_phi);
    extraVariables->SetBranchAddress("T2CaDec", &decision);
    extraVariables->SetBranchAddress("T2CaOut", &t2CaAns);
    extraVariables->SetBranchAddress("T2CaEt",  &et);
    extraVariables->SetBranchAddress("T2CaF1",  &F1);
    extraVariables->SetBranchAddress("T2CaHadEt", &hadET_T2Calo);

    return HypoBase::OK;

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
        matchAndOrdenate(ringer_eta, ringer_phi);
        extraVariables->Fill();
        clearVectors();
    }
    fillHypoRate();
    fillT2CaRate();
    return HypoBase::OK;

}

HypoBase::CODE T2CaCommon::fillT2CaRate(){
    if (totalData!=0){
        if ( id.find("elc") != std::string::npos ){
            detrCoreRate = (float)(totalData - rCoreCuts)/(float)totalData*100;
            deteRatioRate = (float)(totalData - eRatioCuts - rCoreCuts)/(float)(totalData -rCoreCuts)*100;
            detEtRate = (float)(totalData - eRatioCuts - rCoreCuts - etCuts)/(float)(totalData -rCoreCuts - eRatioCuts)*100;
            detHadEtRate = (float)(totalData - hadEtCuts - eRatioCuts - etCuts - rCoreCuts)/(float)(totalData -rCoreCuts - eRatioCuts - etCuts)*100;
        }
        if ( id.find("jet") != std::string::npos ){
            detrCoreRate = ((float)(rCoreCuts)/(float)totalData)*100;
            deteRatioRate = ((float)(eRatioCuts)/(float)(totalData - rCoreCuts))*100;
            detEtRate = ((float)(etCuts)/(float)(totalData - rCoreCuts - eRatioCuts))*100;
            detHadEtRate = ((float)(hadEtCuts)/(float)(totalData - rCoreCuts - eRatioCuts - etCuts) )*100;
        }
    }

    return HypoBase::OK;
}

HypoBase::CODE T2CaCommon::calcTransverseFraction(){
    for(size_t j=0; j<lvl2_eta->size(); ++j){
        et->push_back( ( energy->at(j) ) / ( cosh ( fabs ( lvl2_eta->at(j) ) ) ) );
        //hadET_T2Calo->push_back( ( ehad1->at(j) ) / ( cosh ( fabs ( lvl2_eta->at(j) ) ) ) ); // old
        hadET_T2Calo->push_back( ( ehad1->at(j) ) / ( cosh ( fabs ( lvl2_eta->at(j) ) ) ) / (et->at(j)) );
        F1->push_back( ( energyS1->at(j) ) / ( energy->at(j) ) );
    }
    return  HypoBase::OK;
}

HypoBase::CODE T2CaCommon::fillDecision(T2CaCommon::PCUTS entry){
    ++totalData;
    switch (entry){
        case T2CaCommon::AP:
            decision->push_back(HypoBase::ELECTRON);
            ++detElc;
            break;
        case T2CaCommon::dETA:
        case T2CaCommon::dPHI:
        case T2CaCommon::rCORE:
        case T2CaCommon::eRATIO:
        case T2CaCommon::et_EM:
        case T2CaCommon::et_HAD:
        case T2CaCommon::c_F1:
            decision->push_back(HypoBase::JET);
            ++detJet;
            break;
        default:
            return HypoBase::ERROR;
    }
    return HypoBase::OK;
}

T2CaCommon::PCUTS T2CaCommon::applyCuts(const float eta, const float rCore, const float F1, const float eRatio, const float eT_T2Calo, const float hadET_T2Calo){
    size_t  etaBin = 0;
    for (size_t iBin = 0; iBin < (( sizeof(l2chain.m_etabin) / sizeof(float) ) -1) ; ++iBin) {
        if ( fabs (eta) > l2chain.m_etabin[iBin] && fabs (eta) < l2chain.m_etabin[iBin+1] ) etaBin = iBin; 
    }
    //if (cutEta(dEta)) return T2CaCommon::dETA;
    //if (cutPhi(dPhi)) return T2CaCommon::dPHI;
    if (cutrCore(rCore, etaBin)){
        ++rCoreCuts;
        return T2CaCommon::rCORE;
    }

    if (cuteRatio(eRatio, F1, eta, etaBin)){
        ++eRatioCuts;   
        return T2CaCommon::eRATIO;
    }
    if (cuteT_T2Calo(eT_T2Calo, etaBin)){
        ++etCuts;
        return T2CaCommon::et_EM;
    }
    if (cuthadET_T2Calo(hadET_T2Calo, eT_T2Calo, etaBin)){
        ++hadEtCuts;
        return T2CaCommon::et_HAD;
    }
    //if (cutF1(F1)) return T2CaCommon::c_F1; //T2Ca dont cut here anymore
    return T2CaCommon::AP;
}

inline bool T2CaCommon::cutEta(const float dEta){
    if ( dEta > l2chain.m_detacluster )
        return true;
    return false;
}


inline bool T2CaCommon::cutPhi(const float dPhi){
    if ( dPhi > l2chain.m_dphicluster )
        return true;
    return false;
}

inline bool T2CaCommon::cutrCore(const float rCore, const size_t etaBin){
    if ( rCore < l2chain.m_carcorethr[etaBin] )
        return true;
    return false;
}

inline bool T2CaCommon::cuteRatio(const float eRatio, const float F1, const float eta, const size_t etaBin){
    bool inCrack = ( fabs (eta) > 2.37 || ( fabs (eta) > 1.37 && fabs (eta) < 1.52 ) );
    if ( !(inCrack || F1 < l2chain.m_F1thr) )
        if (eRatio < l2chain.m_caeratiothr[etaBin])// Two ifs just to be simmilar to T2Calo implementation
            return true;
    return false;
}

inline bool T2CaCommon::cuteT_T2Calo(const float eT_T2Calo, const size_t etaBin){
    if ( eT_T2Calo < l2chain.m_eTthr[etaBin] )
        return true;
    return false;
}

inline bool T2CaCommon::cuthadET_T2Calo(const float hadET_T2Calo, const float eT_T2Calo, const size_t etaBin){
    float hadET_cut;
    if ( eT_T2Calo >  l2chain.m_eT2thr[etaBin] )
        hadET_cut = l2chain.m_hadeT2thr[etaBin] ;
    else hadET_cut = l2chain.m_hadeTthr[etaBin];
    if ( hadET_T2Calo > hadET_cut )
        return true;
    return false;
}

inline bool T2CaCommon::cutF1(const float F1){
    if ( F1 < l2chain.m_F1thr)
        return true;
    return false;
}


HypoBase::CODE T2CaCommon::eraseVectors(const size_t index){

    std::vector<float>::iterator p;
    std::vector<int>::iterator p2;
    size_t j;

    for( j=0, p = lvl2_eta->begin(); j<index; ++j, ++p) {}; // FIXME can use p+=index probabily, but I wont change that now.
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


//Create T2Calo Graphic for debug comparision
HypoBase::CODE T2CaCommon::DrawCutCounter(const std::string &opt, const bool scaled){

    file->cd();
    file->cd(("T2Calo Analysis_" + dataLabel).c_str());
    hCuts = new TH1I("CutCounter", "L2Calo Hypo Passed Cuts; Cut", 11, -1.5, 9.5);

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
    hCuts->SetLineColor(color);
    hCuts->SetEntries(hCuts->GetBinContent(1));
    if (scaled)
      hCuts->Scale(1./hCuts->GetBinContent(1)*100);
    hCuts->Draw(opt.c_str());
    gPad->Update();
    TPaveStats *histStats = (TPaveStats*)hCuts->GetListOfFunctions()->FindObject("stats");
    float statsPosBegin = 0, statsPosEnd = 0;
    if( id.find("elc") != std::string::npos ){
      statsPosBegin = .83;
      statsPosEnd = .98;
    }else if (id.find("jet") != std::string::npos ){
      statsPosBegin = .63;
      statsPosEnd = .78;
    }
    if (histStats){
      histStats->SetX1NDC(statsPosBegin); histStats->SetX2NDC(statsPosEnd);
      histStats->SetTextColor(color);
      histStats->Draw();
    }

    return HypoBase::OK;

}

HypoBase::CODE T2CaCommon::DrawCutStats(){

    file->cd();
    file->cd(("T2Calo Analysis_" + dataLabel).c_str());
    TPaveText *pt = new TPaveText(.05,.05,.95,.95);
    TString line1, line2, line3, line4, line5, line6, line7, line8, line9; // TODO fazer ifs dependendo se tem os 2 ou 1 soh

    if ( id == "elc")
        line1.Form("#scale[1.2]{Total Data : Electrons = %d}", totalData);
    else if ( id== "jet")
        line1.Form("#scale[1.2]{Total Data : Jets = %d}", totalData);
    line2.Form("rCore Cuts = %d", rCoreCuts);
    line3.Form("rCore Detection Rate = %.4f%%", detrCoreRate);
    line4.Form("eRatio Cuts %d", eRatioCuts);
    line5.Form("eRatio Detection Rate = %.4f%%", deteRatioRate);
    line6.Form("E_{T}^{EM} Cuts = %d", etCuts);
    line7.Form("E_{T}^{EM} Rate = %.4f%%", detEtRate);
    line8.Form("E_{T}^{HAD} Cuts = %d", hadEtCuts);
    line9.Form("E_{T}^{HAD} Rate = %.4f%%", detHadEtRate);

    pt->AddText("");
    pt->AddText(line1);
    pt->AddText("");
    pt->AddText(line2);
    pt->AddText(line3);
    pt->AddText("");
    pt->AddText(line4);
    pt->AddText(line5);
    pt->AddText("");
    pt->AddText(line6);
    pt->AddText(line7);
    pt->AddText("");
    pt->AddText(line8);
    pt->AddText(line9);
    pt->SetFillColor(30);
    pt->SetTextAlign(22);
    pt->SetLabel(dataLabel.c_str());
    pt->Draw();

    return HypoBase::OK;
}


T2CaCommon::~T2CaCommon(){


    if (hCuts)
      delete hCuts;
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
