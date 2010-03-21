#include "HypoVarCanvas.h"
HypoVarCanvas::HypoVarCanvas(HypoVarBase *userHypoVar1, HypoVarBase *userHypoVar2):
hypoVarCanvas(0),
hypoVar1(userHypoVar1),
hypoVar2(userHypoVar2)
{

}   


int HypoVarCanvas::Draw(bool scaled){

    hypoVarCanvas = new TCanvas("Hypo Variables Analysis", "Hypo Variables Analysis");
    T2CaVarGraph *t2Var1 = dynamic_cast<T2CaVarGraph*>(dynamic_cast<HypoBase*>(hypoVar1));
    T2CaVarGraph *t2Var2 = dynamic_cast<T2CaVarGraph*>(dynamic_cast<HypoBase*>(hypoVar2));


    hypoVarCanvas->Divide(2,2);

    if (t2Var1 && t2Var2){
        if ( t2Var1->getTotalData() == 0)
          t2Var1->exec();
        if ( t2Var2->getTotalData() == 0)
          t2Var2->exec();
        //RCORE
        float rCoreCutPoint[2] = {t2Var1->getl2chain().m_carcorethr[0], t2Var1->getl2chain().m_carcorethr[0]};
        float rCoreCutHeight[2] = {0.};
        TVirtualPad *rcorePad = hypoVarCanvas->cd(1);
        if (t2Var2->getHist("rcore")->GetMaximum()/ t2Var2->getHist("rcore")->GetEntries()> t2Var1->getHist("rcore")->GetMaximum()/t2Var1->getHist("rcore")->GetEntries()){
          t2Var2->DrawVar("rcore", "", scaled);
          t2Var1->DrawVar("rcore","sames", scaled);
          rCoreCutHeight[1] = t2Var2->getHist("rcore")->GetMaximum();
        } else {
          t2Var1->DrawVar("rcore", "", scaled);
          t2Var2->DrawVar("rcore","sames",scaled);
          rCoreCutHeight[1] = t2Var1->getHist("rcore")->GetMaximum();
        }
        grCoreCut = new TGraph(2,rCoreCutPoint,rCoreCutHeight);
        grCoreCut->Draw();
        grCoreCut->SetLineStyle(kDashed);
        rcorePad->SetFillColor(33);
        rcorePad->Modified();
        //ERATIO
        float eRatioCutPoint[2] = {t2Var1->getl2chain().m_caeratiothr[0], t2Var1->getl2chain().m_caeratiothr[0]};
        float eRatioCutHeight[2] = {0.};
        TVirtualPad *eratioPad = hypoVarCanvas->cd(2);
        if (t2Var2->getHist("eratio")->GetMaximum()/t2Var2->getHist("eratio")->GetEntries() > t2Var1->getHist("eratio")->GetMaximum()/t2Var1->getHist("eratio")->GetEntries()){
          t2Var2->DrawVar("eratio", "", scaled);
          t2Var1->DrawVar("eratio","sames", scaled);
          eRatioCutHeight[1] = t2Var2->getHist("eratio")->GetMaximum();
        } else {
          t2Var1->DrawVar("eratio", "", scaled);
          t2Var2->DrawVar("eratio","sames", scaled);
          eRatioCutHeight[1] = t2Var1->getHist("eratio")->GetMaximum();
        }
        geRatioCut = new TGraph(2,eRatioCutPoint,eRatioCutHeight);
        geRatioCut->Draw();
        geRatioCut->SetLineStyle(kDashed);
        eratioPad->SetFillColor(33);
        eratioPad->Modified();
        TVirtualPad *etPad = hypoVarCanvas->cd(3);
        //ET
        float etCutPoint[2] = {t2Var1->getl2chain().m_eTthr[0]*.001, t2Var1->getl2chain().m_eTthr[0]*.001};
        float etCutHeight[2] = {0.};
        if (t2Var2->getHist("et")->GetMaximum()/t2Var2->getHist("et")->GetEntries()> t2Var1->getHist("et")->GetMaximum()/t2Var1->getHist("et")->GetEntries()){
          t2Var2->DrawVar("et");
          t2Var1->DrawVar("et","sames");
          etCutHeight[1] = t2Var2->getHist("et")->GetMaximum();
        } else {
          t2Var1->DrawVar("et", "", scaled);
          t2Var2->DrawVar("et","sames", scaled);
          etCutHeight[1] = t2Var1->getHist("et")->GetMaximum();
        }
        gEtCut = new TGraph(2,etCutPoint,etCutHeight);
        gEtCut->Draw();
        gEtCut->SetLineStyle(kDashed);
        etPad->SetFillColor(33);
        etPad->Modified();
        TVirtualPad *hadEtPad = hypoVarCanvas->cd(4);
        //HADET
        float hadEtCutPoint[2] = {t2Var1->getl2chain().m_hadeTthr[0], t2Var1->getl2chain().m_hadeTthr[0]};
        float hadEtCutHeight[2] = {0.};
        if (t2Var2->getHist("hadet")->GetMaximum()/t2Var2->getHist("hadet")->GetEntries() > t2Var1->getHist("hadet")->GetMaximum()/t2Var1->getHist("hadet")->GetEntries()){
          t2Var2->DrawVar("hadet", "", scaled);
          t2Var1->DrawVar("hadet","sames", scaled);
          hadEtCutHeight[1] = t2Var2->getHist("hadet")->GetMaximum();
        } else {
          t2Var1->DrawVar("hadet", "", scaled);
          t2Var2->DrawVar("hadet","sames", scaled);
          hadEtCutHeight[1] = t2Var1->getHist("hadet")->GetMaximum();
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
  hypoVar1->setRange(var,x1,x2,axis);
  hypoVar2->setRange(var,x1,x2,axis);
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
  hypoVarCanvas->cd();
  return 0;
}

int HypoVarCanvas::setRange(const int padNumber, const float x1, const float x2, const std::string &axis){
  hypoVar1->setRange(padNumber,x1,x2,axis);
  hypoVar2->setRange(padNumber,x1,x2,axis);
  hypoVarCanvas->cd(padNumber)->Modified();
  hypoVarCanvas->cd(padNumber)->Update();
  hypoVarCanvas->cd();
  return 0;
}

int HypoVarCanvas::setRange(const std::string &var, const float x1, const float x2, const float y1, const float y2){
  hypoVar1->setRange(var,x1,x2,y1,y2);
  hypoVar2->setRange(var,x1,x2,y1,y2);
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
  hypoVarCanvas->cd();
  return 0;
}

int HypoVarCanvas::setRange(const int padNumber, const float x1, const float x2, const float y1, const float y2){
  hypoVar1->setRange(padNumber,x1,x2,y1,y2);
  hypoVar2->setRange(padNumber,x1,x2,y1,y2);
  hypoVarCanvas->cd(padNumber)->Modified();
  hypoVarCanvas->cd(padNumber)->Update();
  hypoVarCanvas->cd();
  return 0;
}
