#include "HypoVarCanvas.h"
HypoVarCanvas::HypoVarCanvas(HypoVarBase *userHypoVar1, HypoVarBase *userHypoVar2):
hypoVarCanvas(0)
{
  t2Var1 = 0;
  t2Var2 = 0;
  neuralVar1 = 0;
  neuralVar2 = 0;
  grCoreCut = 0;
  geRatioCut = 0;
  gEtCut = 0;
  gHadEtCut = 0;
  gNeural = 0;
  if ( ( (t2Var1 = dynamic_cast<T2CaVarGraph*>(userHypoVar1)) && ( t2Var2 = dynamic_cast<T2CaVarGraph*>(userHypoVar2)) ) ){
    if (!t2Var1->getTotalData() || !t2Var2->getTotalData()){
      t2Var1->exec();
      t2Var2->exec();
    }
  } else if (( (neuralVar1 = dynamic_cast<NeuralVarGraph*>(userHypoVar1)) && ( neuralVar2 = dynamic_cast<NeuralVarGraph*>(userHypoVar2)) )){
    if (!neuralVar1->getTotalData() || !neuralVar2->getTotalData()){
      neuralVar1->exec();
      neuralVar2->exec();
    }
  } else {
    std::cout<<"You should use the same kind of data. Terminating!"<<std::endl;
    throw;
  }
}   


int HypoVarCanvas::Draw(bool scaled){

    if (hypoVarCanvas){
      if (gROOT->GetListOfCanvases()->FindObject("Hypo Variables Analysis")){
        hypoVarCanvas->Closed();
        delete hypoVarCanvas;
        hypoVarCanvas = 0;
      }
    }
    hypoVarCanvas = new TCanvas("Hypo Variables Analysis", "Hypo Variables Analysis");

    if (t2Var1 && t2Var2){
      if (!t2Var1->getTotalData() || !t2Var2->getTotalData()){
        t2Var1->exec();
        t2Var2->exec();
      }
      hypoVarCanvas->Divide(2,2);
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
    } else if (neuralVar2 && neuralVar1){
        float neuralThreshold[2] = {neuralVar1->getThreshold(), neuralVar2->getThreshold()};
        float neuralHeight[2] = {0.};
        if (neuralVar2->getHist()->GetMaximum()/ neuralVar2->getHist()->GetEntries()> neuralVar1->getHist()->GetMaximum()/neuralVar1->getHist()->GetEntries()){
        neuralVar1->DrawOutput("",scaled);
        neuralVar2->DrawOutput("sames",scaled);
        neuralHeight[1] = neuralVar2->getHist()->GetMaximum();
      } else {
        neuralVar2->DrawOutput("",scaled);
        neuralVar1->DrawOutput("sames",scaled);
        neuralHeight[1] = neuralVar1->getHist()->GetMaximum();
      }
      gNeural = new TGraph(2,neuralThreshold,neuralHeight);
      gNeural->Draw();
      gNeural->SetLineStyle(kDashed);
      gPad->SetFillColor(33);
    }
    return 0;
}


int HypoVarCanvas::setRange(const std::string &var, const float x1, const float x2, const std::string &axis){
  if (t2Var1 && t2Var2){
    t2Var1->setRange(var,x1,x2,axis);
    t2Var2->setRange(var,x1,x2,axis);
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
  }
  return 0;
}

int HypoVarCanvas::setRange(const int padNumber, const float x1, const float x2, const std::string &axis){
  if (t2Var1 && t2Var2){
    t2Var1->setRange(padNumber,x1,x2,axis);
    t2Var2->setRange(padNumber,x1,x2,axis);
    hypoVarCanvas->cd(padNumber)->Modified();
    hypoVarCanvas->cd(padNumber)->Update();
    hypoVarCanvas->cd();
  }
  return 0;
}

int HypoVarCanvas::setRange(const std::string &var, const float x1, const float x2, const float y1, const float y2){
  if (t2Var1 && t2Var2){
    t2Var1->setRange(var,x1,x2,y1,y2);
    t2Var2->setRange(var,x1,x2,y1,y2);
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
  }
  return 0;
}

int HypoVarCanvas::setRange(const int padNumber, const float x1, const float x2, const float y1, const float y2){
  if (t2Var1 && t2Var2){
    t2Var1->setRange(padNumber,x1,x2,y1,y2);
    t2Var2->setRange(padNumber,x1,x2,y1,y2);
    hypoVarCanvas->cd(padNumber)->Modified();
    hypoVarCanvas->cd(padNumber)->Update();
    hypoVarCanvas->cd();
  }
  return 0;
}
