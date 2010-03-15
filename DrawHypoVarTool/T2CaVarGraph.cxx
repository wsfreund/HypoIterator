#include "T2CaVarGraph.h"

T2CaVarGraph::T2CaVarGraph(const std::string &chainPath, bool shunt):T2CaCommon(chainPath){
    /*trCore = new TH1F((dataLabel + " rCore").c_str(), "rCore Cut", 100, 0, .1);
    teRatio = new TH1F((dataLabel + " eRatio").c_str(), "eRatio Cut", 100, 0, .1);
    tEt = new TH1F((dataLabel + " Et").c_str(), "Et_em Cut", 100, 0, .1);
    tHadEt = new TH1F((dataLabel + " HadEt").c_str(),"Et_had Cut", 100, 0, .1);
    trCore->SetBit(TH1::kCanRebin);
    teRatio->SetBit(TH1::kCanRebin);
    tEt->SetBit(TH1::kCanRebin);
    tHadEt->SetBit(TH1::kCanRebin);*/

    useShunt = shunt;
    
    size_t comp = chainPath.find("pile");
    if (comp != std::string::npos){
        dataLabel = "pile " + dataLabel;
    } else {
        std::string input;
        while( (input != "yes") && (input != "no") ){
            cout<<"Data input should be treated as pile-up?[yes/no]"<<endl;
            std::getline(std::cin, input);
        }
        if (input == "yes")
            dataLabel = "pile " + dataLabel;
    }

    if (dataLabel == "elc" || dataLabel == "pile elc" ){
      trCore = new HypoVarHist(100, 0.9, 1.02, dataLabel, std::string("rCore"));
      teRatio = new HypoVarHist(100, 0.82, 1., dataLabel, std::string("eRatio"));
      tEt = new HypoVarHist(100, 5., 85., dataLabel, std::string("E_{T}"));
      tHadEt = new HypoVarHist(100, -0.01, .01, dataLabel, std::string("HAD E_{T}"));
    }
    else {
      trCore = new HypoVarHist(100, 0.5, 1.02, dataLabel, std::string("rCore"));
      teRatio = new HypoVarHist(100, -0.02, 1.02, dataLabel, std::string("eRatio"));
      tEt = new HypoVarHist(100, 0., 50, dataLabel, std::string("E_{T}"));
      tHadEt = new HypoVarHist(100, -0.02, .1, dataLabel, std::string("HAD E_{T}"));
    }
}

HypoBase::CODE T2CaVarGraph::exec(){
    int n_entries = static_cast<int>(hypoChain->GetEntries());
    for(int i=0; i<n_entries; ++i){
        hypoChain->GetEntry(i);
        calcTransverseFraction();//calculate the Transverse Energy and Energy Fraction F1 for its ROI i;

        for(size_t j=0; j<lvl2_eta->size(); ++j){
            T2CaCommon::PCUTS  roiAns = applyCuts( lvl2_eta->at(j) , rCore->at(j), F1->at(j), energyRatio->at(j), et->at(j), hadET_T2Calo->at(j) ); // apply cut for each ROI j;
            t2CaAns->push_back(roiAns); //Fill passed cuts with the event answer given by T2Calo.
            fillDecision(roiAns); //Fill vector telling if the event was a electron or a jet;
        }//for j
        matchAndOrdenate(ringer_eta, ringer_phi);
        extraVariables->Fill();
        clearVectors();
    }
    fillHypoRate();
    fillT2Rate();
    return HypoBase::OK;
}

T2CaCommon::PCUTS T2CaVarGraph::applyCuts(const float eta, const float rCore, const float F1, const float eRatio, const float eT_T2Calo, const float hadET_T2Calo){
    T2CaCommon::PCUTS pass = T2CaCommon::AP;
    if (useShunt){
        size_t      etaBin = 0;
        for (size_t iBin = 0; iBin < (( sizeof(m_etabin) / sizeof(float) ) -1) ; ++iBin) {
            if ( fabs (eta) > m_etabin[iBin] && fabs (eta) < m_etabin[iBin+1] ) etaBin = iBin; 
        }
        //if (cutEta(dEta)) return T2CaVarGraph::dETA;
        //if (cutPhi(dPhi)) return T2CaVarGraph::dPHI;
        T2CaCommon::PCUTS pass = T2CaCommon::AP;

        if (cutrCore(rCore, etaBin)) {
            pass = T2CaCommon::rCORE;
        }
        if (cuteRatio(eRatio, F1, eta, etaBin) ){
            pass = T2CaCommon::eRATIO;
        }
        if (cuteT_T2Calo(eT_T2Calo, etaBin) ){
            pass = T2CaCommon::et_EM;
        }
        if (cuthadET_T2Calo(hadET_T2Calo, eT_T2Calo, etaBin) ){
            pass = T2CaCommon::et_HAD;
        }
    }else{
        size_t      etaBin = 0;
        for (size_t iBin = 0; iBin < (( sizeof(m_etabin) / sizeof(float) ) -1) ; ++iBin) {
            if ( fabs (eta) > m_etabin[iBin] && fabs (eta) < m_etabin[iBin+1] ) etaBin = iBin; 
        }
        //if (cutEta(dEta)) return T2CaVarGraph::dETA;
        //if (cutPhi(dPhi)) return T2CaVarGraph::dPHI;
        bool untouched = true;

        if (cutrCore(rCore, etaBin)) {
            pass = T2CaCommon::rCORE;
            ++rCoreCuts;
            untouched = false;
        }
        if (untouched)
            if (cuteRatio(eRatio, F1, eta, etaBin) ){
              pass = T2CaCommon::eRATIO;
              ++eRatioCuts;
              untouched = false;
            }
        if ( untouched )
          if (cuteT_T2Calo(eT_T2Calo, etaBin)){
              pass = T2CaCommon::et_EM;
              ++etCuts;
              untouched = false;
          }
        if ( untouched )
          if ( cuthadET_T2Calo(hadET_T2Calo, eT_T2Calo, etaBin) ){
              ++hadEtCuts;
              pass = T2CaVarGraph::et_HAD;
          }
    }
    return pass;
}

inline bool T2CaVarGraph::cutrCore(const float rCore, const size_t etaBin){
    trCore->Fill(rCore);
    if ( rCore < m_carcorethr[etaBin] )  {
        return true;
    }
    return false;

}

inline bool T2CaVarGraph::cuteRatio(const float eRatio, const float F1, const float eta, const size_t etaBin){
    bool inCrack = ( fabs (eta) > 2.37 || ( fabs (eta) > 1.37 && fabs (eta) < 1.52 ) );
    teRatio->Fill(eRatio);
    if ( (!inCrack) || ( F1 < m_F1thr) ){
        if (eRatio < m_caeratiothr[etaBin]) { // Two ifs just to be simmilar to T2Calo implementation
            return true;
        }
    }
    return false;
}

inline bool T2CaVarGraph::cuteT_T2Calo(const float eT_T2Calo, const size_t etaBin){
    tEt->Fill(eT_T2Calo*.001);//Filling into GeV units
    if ( eT_T2Calo < m_eTthr[etaBin] ){
        return true;
    }
    return false;
}

inline bool T2CaVarGraph::cuthadET_T2Calo(const float hadET_T2Calo, const float eT_T2Calo, const size_t etaBin){
    tHadEt->Fill(hadET_T2Calo);
    float hadET_cut;
    if ( eT_T2Calo >  m_eT2thr[etaBin] ) hadET_cut = m_hadeT2thr[etaBin] ;
    else hadET_cut = m_hadeTthr[etaBin];
    if ( hadET_T2Calo > hadET_cut ) {
        return true;
    }
    return false;
}

inline bool T2CaVarGraph::cutF1(const float F1){
    if ( F1 < m_F1thr){
        return true;
    }
    return false;
}

HypoBase::CODE T2CaVarGraph::DrawCutStats(){
    TPaveText *pt = new TPaveText(.05,.05,.95,.95);
    TString line1, line2, line3, line4, line5, line6, line7, line8, line9;

    if (dataLabel == "elc")
        line1.Form("#scale[1.2]{Total Data : Electrons = %d}", totalData);
    else if (dataLabel == "jet")
        line1.Form("#scale[1.2]{Total Data : Jets = %d}", totalData);
    else if (dataLabel == "pile elc")
        line1.Form("#scale[1.2]{Total Data : Electrons (pile-up)}= %d", totalData);
    else if (dataLabel == "pile jet")
        line1.Form("#scale[1.2]{Total Data : Jets (pile-up)}= %d", totalData);
    line2.Form("rCore Cuts = %d", rCoreCuts);
    line3.Form("rCore Detection Rate = %.4f%%", detrCoreRate);
    line4.Form("eRatio Cuts %d", eRatioCuts);
    line5.Form("eRatio Detection Rate = %.4f%%", deteRatioRate);
    line6.Form("Et_em Cuts = %d", etCuts);
    line7.Form("Et_em Rate = %.4f%%", detEtRate);
    line8.Form("Et_had Cuts = %d", hadEtCuts);
    line9.Form("Et_had Rate = %.4f%%", detHadEtRate);

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

int T2CaVarGraph::DrawVar(const std::string &var, const std::string &mode, const bool scaled){
    if (var == "rcore"){
        trCore->Draw(mode, scaled);
    }
    else if (var == "eratio"){
        teRatio->Draw(mode, scaled);
    }
    else if (var == "et"){
        tEt->Draw(mode, scaled);
    }
    else if (var == "hadet"){
        tHadEt->Draw(mode, scaled);
    }
    return 0;
}

TH1F* T2CaVarGraph::getHist(const std::string &var){
    if (var == "rcore")
        return trCore->getHist();
    else if (var == "eratio")
        return teRatio->getHist();
    else if (var == "et")
        return tEt->getHist();
    else if (var == "hadet")
        return tHadEt->getHist();
    return 0;
}

int T2CaVarGraph::setRange(const int varNumber, const float x1, const float x2, const std::string &axis){
  if (varNumber == 1){
    trCore->getHist()->SetAxisRange(x1,x2,axis.c_str());
  }else if (varNumber == 2){
    teRatio->getHist()->SetAxisRange(x1,x2,axis.c_str());
  }else if (varNumber == 3){
    tEt->getHist()->SetAxisRange(x1,x2,axis.c_str());
  }else if (varNumber == 4){
    tHadEt->getHist()->SetAxisRange(x1,x2,axis.c_str());
  }
  return HypoBase::OK;

}

int T2CaVarGraph::setRange(const int varNumber, const float x1, const float x2, const float y1, const float y2){
  if (varNumber == 1){
    trCore->getHist()->SetAxisRange(x1,x2);
    trCore->getHist()->SetAxisRange(y1,y2,"Y");
  }else if (varNumber == 2){
    teRatio->getHist()->SetAxisRange(x1,x2);
    teRatio->getHist()->SetAxisRange(y1,y2,"Y");
  }else if (varNumber == 3){
    tEt->getHist()->SetAxisRange(x1,x2);
    tEt->getHist()->SetAxisRange(y1,y2,"Y");
  }else if (varNumber == 4){
    tHadEt->getHist()->SetAxisRange(x1,x2);
    tHadEt->getHist()->SetAxisRange(y1,y2,"Y");
  }
  return HypoBase::OK;
}

int T2CaVarGraph::setRange(const std::string &var, const float x1, const float x2, const std::string &axis){
  if (var == "rcore"){
    trCore->getHist()->SetAxisRange(x1,x2,axis.c_str());
  }else if (var == "eratio"){
    teRatio->getHist()->SetAxisRange(x1,x2,axis.c_str());
  }else if (var == "et"){
    tEt->getHist()->SetAxisRange(x1,x2,axis.c_str());
  }else if (var == "hadet"){
    tHadEt->getHist()->SetAxisRange(x1,x2,axis.c_str());
  }
  return HypoBase::OK;
}

int T2CaVarGraph::setRange(const std::string &var, const float x1, const float x2, const float y1, const float y2){
  if (var == "rcore"){
    trCore->getHist()->SetAxisRange(x1,x2);
    trCore->getHist()->SetAxisRange(y1,y2,"Y");
  }else if (var == "eratio"){
    teRatio->getHist()->SetAxisRange(x1,x2);
    teRatio->getHist()->SetAxisRange(y1,y2,"Y");
  }else if (var == "et"){
    tEt->getHist()->SetAxisRange(x1,x2);
    tEt->getHist()->SetAxisRange(y1,y2,"Y");
  }else if (var == "hadet"){
    tHadEt->getHist()->SetAxisRange(x1,x2);
    tHadEt->getHist()->SetAxisRange(y1,y2,"Y");
  }
  return HypoBase::OK;
}

T2CaVarGraph::~T2CaVarGraph(){
    delete trCore;
    delete teRatio;
    delete tEt;
    delete tHadEt;
}
