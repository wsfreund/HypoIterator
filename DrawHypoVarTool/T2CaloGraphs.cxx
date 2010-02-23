#include "T2CaloGraphs.h"


T2CaloGraphs::T2CaloGraphs(const std::string &dataPath, const std::string &userDataLabel):Graphs(dataPath, userDataLabel){
    /*    

          trCore = new TH1F((dataLabel + " rCore").c_str(), "rCore Cut", 100, 0, .1);
          teRatio = new TH1F((dataLabel + " eRatio").c_str(), "eRatio Cut", 100, 0, .1);
          tEt = new TH1F((dataLabel + " Et").c_str(), "Et_em Cut", 100, 0, .1);
          tHadEt = new TH1F((dataLabel + " HadEt").c_str(),"Et_had Cut", 100, 0, .1);

          trCore->SetBit(TH1::kCanRebin);
          teRatio->SetBit(TH1::kCanRebin);
          tEt->SetBit(TH1::kCanRebin);
          tHadEt->SetBit(TH1::kCanRebin);

*/

    trCore = new TH1F((dataLabel + " rCore").c_str(), "rCore Cut", 100, 0.5, 1.02);
    teRatio = new TH1F((dataLabel + " eRatio").c_str(), "eRatio Cut", 100, -0.02, 1.02);
    tEt = new TH1F((dataLabel + " Et").c_str(), "Et_em Cut", 100, 0., 50.e3);
    tHadEt = new TH1F((dataLabel + " HadEt").c_str(),"Et_had Cut", 100, -0.01, .1);

    psrCore = new TPaveStats();
    pseRatio = new TPaveStats();
    psEt = new TPaveStats();
    psHadEt= new TPaveStats();

    size_t comp = dataLabel.find("common");
    if (comp != std::string::npos){ 
        trCore->SetLineColor(kBlue);
        teRatio->SetLineColor(kBlue);
        tEt->SetLineColor(kBlue);
        tHadEt->SetLineColor(kBlue);
    }

    comp = dataLabel.find("pile");

    if (comp != std::string::npos){
        trCore->SetLineColor(kRed);
        teRatio->SetLineColor(kRed);
        tEt->SetLineColor(kRed);
        tHadEt->SetLineColor(kRed);
    }
}


Graphs::CODE T2CaloGraphs::scale(){
    trCore->Scale(1/trCore->Integral());
    teRatio->Scale(1/teRatio->Integral());
    tEt->Scale(1/tEt->Integral());
    tHadEt->Scale(1/tHadEt->Integral());
    return Graphs::OK;
}

T2CaloGraphs::PCUTS T2CaloGraphs::applyCuts(const float eta, const float rCore, const float F1, const float eRatio, const float eT_T2Calo, const float hadET_T2Calo){

    size_t      etaBin = 0;
    for (size_t iBin = 0; iBin < (( sizeof(m_etabin) / sizeof(float) ) -1) ; ++iBin) {
        if ( fabs (eta) > m_etabin[iBin] && fabs (eta) < m_etabin[iBin+1] ) etaBin = iBin; 
    }

    //Corte Eta
    //if (cutEta(dEta)) return T2CaloGraphs::dETA;

    //Corte Phi
    //if (cutPhi(dPhi)) return T2CaloGraphs::dPHI;

    //Corte rCore

    bool untouched = true;

    ++totalData;

    T2CaloGraphs::PCUTS pass = T2CaloGraphs::AP;

    if (cutrCore(rCore, etaBin)) {
        pass = T2CaloGraphs::rCORE;
        ++rCoreCuts;
        //        untouched = false;
    }

    //Corte eRatio
    if (cuteRatio(eRatio, F1, eta, etaBin) && untouched){
        pass = T2CaloGraphs::eRATIO;
        ++eRatioCuts;
        //        untouched = false;
    }

    //Corte Energia Tranversa EM
    if (cuteT_T2Calo(eT_T2Calo, etaBin) && untouched){
        pass = T2CaloGraphs::et_EM;
        ++etCuts;
        //        untouched = false;
    }

    //Corte Energia Tranversa HAD
    if (cuthadET_T2Calo(hadET_T2Calo, eT_T2Calo, etaBin) &&untouched){
        pass = T2CaloGraphs::et_HAD;
        ++hadEtCuts;
        //        untouched = false;
    }

    //Corte Fração de energia
    //if (cutF1(F1)) return T2CaloGraphs::c_F1; //Não tem esse corte na nova versão do T2Calo, ele fica dentro do  eRatio.

    //Chegou até aqui passou yeah
    return pass;

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

Graphs::CODE T2CaloGraphs::cutStats(){

    TPaveText *pt = new TPaveText(.05,.05,.95,.95);
    TString line1, line2, line3, line4, line5, line6, line7, line8, line9;

    line1.Form("Total Data = %.0d", totalData);
    line2.Form("rCore Cuts = %.0d", rCoreCuts);
    line3.Form("rCore Rate = %.4f", static_cast<float>(rCoreCuts)/static_cast<float>(totalData)*100.);
    line4.Form("eRatio Cuts %.0d", eRatioCuts);
    line5.Form("eRatio Rate = %.4f", static_cast<float>(eRatioCuts)/static_cast<float>(totalData)*100.);
    line6.Form("Et_em Cuts = %.0d", etCuts);
    line7.Form("Et_em Rate = %.4f", static_cast<float>(etCuts)/static_cast<float>(totalData)*100.);
    line8.Form("Et_had Cuts = %.0d", hadEtCuts);
    line9.Form("Et_had Rate = %.4f", static_cast<float>(hadEtCuts)/static_cast<float>(totalData)*100.);

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
    pt->SetTextAlign(12);

    pt->SetLabel(dataLabel.c_str());

    pt->Draw();

    return Graphs::OK;

}

Graphs::CODE T2CaloGraphs::drawCut(const std::string &cut){
    size_t cond;
    if (cut == "rcore"){
        trCore->Draw();
        gPad->Update();
        cond = dataLabel.find("common");
        if (cond != std::string::npos){
            psrCore = (TPaveStats*)trCore->GetListOfFunctions()->FindObject("stats");
            psrCore->SetX1NDC(0.8); psrCore->SetX2NDC(0.98);
            psrCore->SetTextColor(kBlue);
            psrCore->Draw();
        }
        cond = dataLabel.find("pile");
        if(cond != std::string::npos){
            psrCore = (TPaveStats*)trCore->GetListOfFunctions()->FindObject("stats");
            psrCore->SetX1NDC(0.55); psrCore->SetX2NDC(0.75);
            psrCore->SetTextColor(kRed);
            psrCore->Draw();
        }
        gPad->Update();
    }else if (cut == "eratio"){
        teRatio->Draw();
        gPad->Update();
        cond = dataLabel.find("common");
        if (cond != std::string::npos){
            pseRatio = (TPaveStats*)teRatio->GetListOfFunctions()->FindObject("stats");
            pseRatio->SetX1NDC(0.8); pseRatio->SetX2NDC(0.98);
            pseRatio->SetTextColor(kBlue);
            pseRatio->Draw();
        }
        cond = dataLabel.find("pile");
        if (cond != std::string::npos){
            pseRatio = (TPaveStats*)teRatio->GetListOfFunctions()->FindObject("stats");
            pseRatio->SetX1NDC(0.55); pseRatio->SetX2NDC(0.75);
            pseRatio->SetTextColor(kRed);
            pseRatio->Draw();
        }
        gPad->Update();
    }else if (cut == "et"){
        tEt->Draw();
        gPad->Update();
        cond = dataLabel.find("common");
        if (cond != std::string::npos){
            psEt = (TPaveStats*)tEt->GetListOfFunctions()->FindObject("stats");
            psEt->SetX1NDC(0.8); psEt->SetX2NDC(0.98);
            psEt->SetTextColor(kBlue);
            psEt->Draw();
        }
        cond = dataLabel.find("pile");
        if (cond != std::string::npos){
            psEt = (TPaveStats*)tEt->GetListOfFunctions()->FindObject("stats");
            psEt->SetX1NDC(0.55); psEt->SetX2NDC(0.75);
            psEt->SetTextColor(kRed);
            psEt->Draw();
        }
        gPad->Update();
    }else if (cut == "hadet"){
        tHadEt->Draw();
        gPad->Update();
        cond = dataLabel.find("common");
        if (cond != std::string::npos){
            psHadEt = (TPaveStats*)tHadEt->GetListOfFunctions()->FindObject("stats");
            psHadEt->SetX1NDC(0.8); psHadEt->SetX2NDC(0.98);
            psHadEt->SetTextColor(kBlue);
            psHadEt->Draw();
        }
        cond = dataLabel.find("pile");
        if (cond != std::string::npos){
            psHadEt = (TPaveStats*)tHadEt->GetListOfFunctions()->FindObject("stats");
            psHadEt->SetX1NDC(0.55); psHadEt->SetX2NDC(0.75);
            psHadEt->SetTextColor(kRed);
            psHadEt->Draw();
        }
        gPad->Update();
    }
    return Graphs::OK;
}


Graphs::CODE T2CaloGraphs::drawCut(const std::string &cut, const std::string &mode){
    size_t cond;
    if (cut == "rcore"){
        trCore->Draw(mode.c_str());
        gPad->Update();
        cond = dataLabel.find("common");
        if (cond != std::string::npos){
            psrCore = (TPaveStats*)trCore->GetListOfFunctions()->FindObject("stats");
            psrCore->SetX1NDC(0.8); psrCore->SetX2NDC(0.98);
            psrCore->SetTextColor(kBlue);
            psrCore->Draw();
        }
        cond = dataLabel.find("pile");
        if (cond != std::string::npos){
            psrCore = (TPaveStats*)trCore->GetListOfFunctions()->FindObject("stats");
            psrCore->SetX1NDC(0.55); psrCore->SetX2NDC(0.75);
            psrCore->SetTextColor(kRed);
            psrCore->Draw();
        }
        gPad->Update();
    }else if (cut == "eratio"){
        teRatio->Draw(mode.c_str());
        gPad->Update();
        cond = dataLabel.find("common");
        if (cond != std::string::npos){
            pseRatio = (TPaveStats*)teRatio->GetListOfFunctions()->FindObject("stats");
            pseRatio->SetX1NDC(0.8); pseRatio->SetX2NDC(0.98);
            pseRatio->SetTextColor(kBlue);
            pseRatio->Draw();
        }
        cond = dataLabel.find("pile");
        if (cond != std::string::npos){
            pseRatio = (TPaveStats*)teRatio->GetListOfFunctions()->FindObject("stats");
            pseRatio->SetX1NDC(0.55); pseRatio->SetX2NDC(0.75);
            pseRatio->SetTextColor(kRed);
            pseRatio->Draw();
        }
        gPad->Update();
    }else if (cut == "et"){
        tEt->Draw(mode.c_str());
        gPad->Update();
        cond = dataLabel.find("common");
        if (cond != std::string::npos){
            psEt = (TPaveStats*)tEt->GetListOfFunctions()->FindObject("stats");
            psEt->SetX1NDC(0.8); psEt->SetX2NDC(0.98);
            psEt->SetTextColor(kBlue);
            psEt->SetTextColor(kBlue);
        }
        cond = dataLabel.find("pile");
        if (cond != std::string::npos){
            psEt = (TPaveStats*)tEt->GetListOfFunctions()->FindObject("stats");
            psEt->SetX1NDC(0.55); psEt->SetX2NDC(0.75);
            psEt->SetTextColor(kRed);
            psEt->Draw();
        }
        gPad->Update();
    }else if (cut == "hadet"){
        tHadEt->Draw(mode.c_str());
        gPad->Update();
        cond = dataLabel.find("common");
        if (cond != std::string::npos){
            psHadEt = (TPaveStats*)tHadEt->GetListOfFunctions()->FindObject("stats");
            psHadEt->SetX1NDC(0.8); psHadEt->SetX2NDC(0.98);
            psHadEt->SetTextColor(kBlue);
            psHadEt->Draw();
        }
        cond = dataLabel.find("pile");
        if (cond != std::string::npos){
            psHadEt = (TPaveStats*)tHadEt->GetListOfFunctions()->FindObject("stats");
            psHadEt->SetX1NDC(0.55); psHadEt->SetX2NDC(0.75);
            psHadEt->SetTextColor(kRed);
            psHadEt->Draw();
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
    delete hadET_T2Calo;
    delete rCore;
    delete energyRatio;
    delete F1;
    delete energy;
    delete ehad1;
    delete energyS1;
    delete t2CaAns;
    delete ringer_lvl2_eta;
    delete ringer_lvl2_phi;

}
