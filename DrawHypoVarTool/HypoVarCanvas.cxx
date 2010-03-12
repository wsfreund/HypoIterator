#include "HypoVarCanvas.h"
HypoVarCanvas::HypoVarCanvas(HypoVarBase *hypoVar1, HypoVarBase *hypoVar2){
    hypoVarCanvas = 0;
    HypoBase *hypoBase1 = dynamic_cast<HypoBase*>(hypoVar1);
    HypoBase *hypoBase2 = dynamic_cast<HypoBase*>(hypoVar2);
    if (hypoBase1){
        std::string dataLabel;
        hypoBase1->getDataLabel(dataLabel);
        size_t comp = dataLabel.find("pile");
        if (comp != std::string::npos)
             hypoVarPile = hypoVar1;
        else if (dataLabel == "elc" || dataLabel == "jet")
             hypoVarCommon = hypoVar1;
    }
    if (hypoBase2){
        std::string dataLabel;
        hypoBase2->getDataLabel(dataLabel);
        size_t comp = dataLabel.find("pile");
        if (comp != std::string::npos)
             hypoVarPile = hypoVar2;
        else if (dataLabel == "elc" || dataLabel == "jet")
             hypoVarCommon = hypoVar2;
    }
    if ( !(hypoVarCommon) || !(hypoVarPile)){
        cout<<"Wrong parameters"<<endl;
        delete this;
    }

}   


int HypoVarCanvas::Draw(bool scaled){

    hypoVarCanvas = new TCanvas("Hypo Variables Analysis", "Hypo Variables Analysis");
    T2CaVarGraph *t2varPile   = dynamic_cast<T2CaVarGraph*>(hypoVarPile);
    T2CaVarGraph *t2varCommon = dynamic_cast<T2CaVarGraph*>(hypoVarCommon);

    hypoVarCanvas->Divide(2,2);

    if (t2varPile && t2varCommon){
        //RCORE
        float rCoreCutPoint[2] = {m_carcorethr[0], m_carcorethr[0]};
        float rCoreCutHeight[2] = {0.};
        TVirtualPad *rcorePad = hypoVarCanvas->cd(1);
        if (t2varCommon->getHist("rcore")->GetMaximum()/ t2varCommon->getHist("rcore")->GetEntries()> t2varPile->getHist("rcore")->GetMaximum()/t2varPile->getHist("rcore")->GetEntries()){
          t2varCommon->DrawVar("rcore", "", scaled);
          t2varPile->DrawVar("rcore","sames", scaled);
          rCoreCutHeight[1] = t2varCommon->getHist("rcore")->GetMaximum();
        } else {
          t2varPile->DrawVar("rcore", "", scaled);
          t2varCommon->DrawVar("rcore","sames",scaled);
          rCoreCutHeight[1] = t2varPile->getHist("rcore")->GetMaximum();
        }
        grCoreCut = new TGraph(2,rCoreCutPoint,rCoreCutHeight);
        grCoreCut->Draw();
        grCoreCut->SetLineStyle(kDashed);
        rcorePad->SetFillColor(33);
        rcorePad->Modified();
        //ERATIO
        float eRatioCutPoint[2] = {m_caeratiothr[0], m_caeratiothr[0]};
        float eRatioCutHeight[2] = {0.};
        TVirtualPad *eratioPad = hypoVarCanvas->cd(2);
        if (t2varCommon->getHist("eratio")->GetMaximum()/t2varCommon->getHist("eratio")->GetEntries() > t2varPile->getHist("eratio")->GetMaximum()/t2varPile->getHist("eratio")->GetEntries()){
          t2varCommon->DrawVar("eratio", "", scaled);
          t2varPile->DrawVar("eratio","sames", scaled);
          eRatioCutHeight[1] = t2varCommon->getHist("eratio")->GetMaximum();
        } else {
          t2varPile->DrawVar("eratio", "", scaled);
          t2varCommon->DrawVar("eratio","sames", scaled);
          eRatioCutHeight[1] = t2varPile->getHist("eratio")->GetMaximum();
        }
        geRatioCut = new TGraph(2,eRatioCutPoint,eRatioCutHeight);
        geRatioCut->Draw();
        geRatioCut->SetLineStyle(kDashed);
        eratioPad->SetFillColor(33);
        eratioPad->Modified();
        TVirtualPad *etPad = hypoVarCanvas->cd(3);
        //ET
        float etCutPoint[2] = {m_eTthr[0]*.001, m_eTthr[0]*.001};
        float etCutHeight[2] = {0.};
        if (t2varCommon->getHist("et")->GetMaximum()/t2varCommon->getHist("et")->GetEntries()> t2varPile->getHist("et")->GetMaximum()/t2varPile->getHist("et")->GetEntries()){
          t2varCommon->DrawVar("et");
          t2varPile->DrawVar("et","sames");
          etCutHeight[1] = t2varCommon->getHist("et")->GetMaximum();
        } else {
          t2varPile->DrawVar("et", "", scaled);
          t2varCommon->DrawVar("et","sames", scaled);
          etCutHeight[1] = t2varPile->getHist("et")->GetMaximum();
        }
        gEtCut = new TGraph(2,etCutPoint,etCutHeight);
        gEtCut->Draw();
        gEtCut->SetLineStyle(kDashed);
        etPad->SetFillColor(33);
        etPad->Modified();
        TVirtualPad *hadEtPad = hypoVarCanvas->cd(4);
        //HADET
        float hadEtCutPoint[2] = {m_hadeTthr[0]*.001, m_hadeTthr[0]*.001};
        float hadEtCutHeight[2] = {0.};
        if (t2varCommon->getHist("hadet")->GetMaximum()/t2varCommon->getHist("hadet")->GetEntries() > t2varPile->getHist("hadet")->GetMaximum()/t2varPile->getHist("hadet")->GetEntries()){
          t2varCommon->DrawVar("hadet", "", scaled);
          t2varPile->DrawVar("hadet","sames", scaled);
          hadEtCutHeight[1] = t2varCommon->getHist("hadet")->GetMaximum();
        } else {
          t2varPile->DrawVar("hadet", "", scaled);
          t2varCommon->DrawVar("hadet","sames", scaled);
          hadEtCutHeight[1] = t2varPile->getHist("hadet")->GetMaximum();
        }
        gHadEtCut = new TGraph(2,hadEtCutPoint,hadEtCutHeight);
        gHadEtCut->Draw();
        gHadEtCut->SetLineStyle(kDashed);
        hadEtPad->SetFillColor(33);
        hadEtPad->Modified();
        TVirtualPad *t2caVarPad = hypoVarCanvas->cd();
        t2caVarPad->SetFillColor(18);
    }
    return 0;

}


int HypoVarCanvas::setRange(const std::string &var, const float x1, const float x2, const std::string &axis){
  hypoVarPile->setRange(var,x1,x2,axis);
  hypoVarCommon->setRange(var,x1,x2,axis);
  if (var == "rcore"){
    hypoVarCanvas->cd(1)->Modified();
    hypoVarCanvas->cd(1)->Update();
  }else if (var == "eratio"){
    hypoVarCanvas->cd(2)->Modified();
    hypoVarCanvas->cd(2)->Update();
  }else if (var == "et"){
    hypoVarCanvas->cd(3)->Modified();
    hypoVarCanvas->cd(3)->Update();
  }else if (var == "hadet"){
    hypoVarCanvas->cd(4)->Modified();
    hypoVarCanvas->cd(4)->Update();
  }
  return 0;
}

int HypoVarCanvas::setRange(const int padNumber, const float x1, const float x2, const std::string &axis){
  hypoVarPile->setRange(padNumber,x1,x2,axis);
  hypoVarCommon->setRange(padNumber,x1,x2,axis);
  hypoVarCanvas->cd(padNumber)->Modified();
  hypoVarCanvas->cd(padNumber)->Update();
  return 0;
}

int HypoVarCanvas::setRange(const std::string &var, const float x1, const float x2, const float y1, const float y2){
  hypoVarPile->setRange(var,x1,x2,y1,y2);
  hypoVarCommon->setRange(var,x1,x2,y1,y2);
  if (var == "rcore"){
    hypoVarCanvas->cd(1)->Modified();
    hypoVarCanvas->cd(1)->Update();
  }else if (var == "eratio"){
    hypoVarCanvas->cd(2)->Modified();
    hypoVarCanvas->cd(2)->Update();
  }else if (var == "et"){
    hypoVarCanvas->cd(3)->Modified();
    hypoVarCanvas->cd(3)->Update();
  }else if (var == "hadet"){
    hypoVarCanvas->cd(4)->Modified();
    hypoVarCanvas->cd(4)->Update();
  }
  return 0;
}

int HypoVarCanvas::setRange(const int padNumber, const float x1, const float x2, const float y1, const float y2){
  hypoVarPile->setRange(padNumber,x1,x2,y1,y2);
  hypoVarCommon->setRange(padNumber,x1,x2,y1,y2);
  hypoVarCanvas->cd(padNumber)->Modified();
  hypoVarCanvas->cd(padNumber)->Update();
  return 0;
}
