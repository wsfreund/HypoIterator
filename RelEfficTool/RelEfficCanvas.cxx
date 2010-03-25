#include "RelEfficCanvas.h"

RelEfficCanvas::RelEfficCanvas(RelEfficBase *userRelEfficData){
    relCanvas = 0;
    relEfficData = userRelEfficData;
    relEffic1 = 0;
    relEffic2 = 0;
    infoCanvas = 0;
    pt = 0;
    hypoPt = 0;
    legend = 0;
    if (!dynamic_cast<T2CaRelEffic*>(relEfficData) && (!dynamic_cast<NeuralRelEffic*>(relEfficData)))
      std::cout<<"Cannot use type entered "<< typeid(userRelEfficData).name()<<std::endl;

}

RelEfficCanvas::RelEfficCanvas(RelEfficBase *userRelEffic1, RelEfficBase *userRelEffic2){
    relCanvas = 0;
    relEfficData = 0;
    relEffic1 = userRelEffic1;
    relEffic2 = userRelEffic2;
    infoCanvas = 0;
    pt = 0;
    hypoPt = 0;
    legend = 0;
    if (dynamic_cast<T2CaRelEffic*>(relEffic1)){
      if (dynamic_cast<NeuralRelEffic*>(relEffic2)){
        if (relEffic1->getId().find("elc")!=std::string::npos){
          if (relEffic2->getId().find("elc")==std::string::npos){
            std::cout<<"When comparing different Hypos both of them must have the same kind of data"<<std::endl;
            throw;
          }
        } else if (relEffic2->getId().find("jet")==std::string::npos){
          std::cout<<"When comparing different Hypos both of them must have the same kind of data"<<std::endl;
          throw;
        }
      } else if (dynamic_cast<T2CaRelEffic*>(relEffic2)){
        if (relEffic1->getId().find("elc")!=std::string::npos){
          if (relEffic2->getId().find("elc")!=std::string::npos){
            std::cout<<"When comparing same Hypo data must be different"<<std::endl;
            throw;
          }
        } else if (relEffic2->getId().find("jet")!=std::string::npos){
          std::cout<<"When comparing same Hypo data must be different"<<std::endl;
          throw;
        }
      } else {
        std::cout<<"Cannot use type entered "<< typeid(userRelEffic2).name()<<std::endl;
        throw;
      }
    } else if (dynamic_cast<NeuralRelEffic*>(relEffic1)){
      if (dynamic_cast<T2CaRelEffic*>(relEffic2)){
        if (relEffic1->getId().find("elc")!=std::string::npos){
          if (relEffic2->getId().find("elc")==std::string::npos){
            std::cout<<"When comparing different Hypos both of them must have the same kind of data"<<std::endl;
            throw;
          }
        } else if (relEffic2->getId().find("jet")==std::string::npos){
          std::cout<<"When comparing different Hypos both of them must have the same kind of data"<<std::endl;
          throw;
        }
      } else if (dynamic_cast<NeuralRelEffic*>(relEffic2)){
        if (relEffic1->getId().find("elc")!=std::string::npos){
          if (relEffic2->getId().find("elc")!=std::string::npos){
            std::cout<<"When comparing same Hypo data must be different"<<std::endl;
            throw;
          }
        } else if (relEffic2->getId().find("jet")!=std::string::npos){
          std::cout<<"When comparing same Hypo data must be different"<<std::endl;
          throw;
        }
      } else {
        std::cout<<"Cannot use type entered "<< typeid(userRelEffic2).name()<<std::endl;
        throw;
      }
    } else {
      std::cout<<"Cannot use type entered "<< typeid(userRelEffic1).name()<<std::endl;
      throw;
    }

}   

inline TH1F* RelEfficCanvas::drawWithProperties(const std::string &var, RelEfficBase *&relEfficData, 
    const std::string &title, const float &xLow, const float &xHi,  
    const std::string &xlabel, const std::string &ylabel, const float &xOffSet, const float &xSize, 
    const float &yOffSet, const float &ySize, const float &yLow, const float &yHi){

  TH1F *th1axis = gPad->DrawFrame(xLow, yLow, xHi, yHi);
  th1axis->GetYaxis()->SetTitle(ylabel.c_str());
  th1axis->SetTitle(title.c_str());
  th1axis->GetXaxis()->SetTitle(xlabel.c_str());
  th1axis->GetXaxis()->SetTitleSize(xSize);
  th1axis->GetYaxis()->SetTitleSize(ySize);
  th1axis->GetYaxis()->CenterTitle();
  th1axis->GetXaxis()->SetTitleOffset(xOffSet);
  th1axis->GetYaxis()->SetTitleOffset(yOffSet);
  if (var == "phi")
    th1axis->GetXaxis()->SetNdivisions(-4);
  gPad->SetFillColor(33);
  gPad->SetGrid();
  T2CaRelEffic* t2CaRel = 0;
  NeuralRelEffic* neuralRel = 0;
  if ( (t2CaRel = dynamic_cast<T2CaRelEffic*>(relEfficData)))
    t2CaRel->DrawEfficVs(var,"LP");
  else if ( (neuralRel = dynamic_cast<NeuralRelEffic*>(relEfficData)))
    neuralRel->DrawEfficVs(var,"LP");
  

  gPad->Modified();
  return th1axis;

}

inline TH1F* RelEfficCanvas::drawWithProperties(const std::string &var, RelEfficBase *&relEffic1, RelEfficBase *&relEffic2, 
    Color_t color1, Color_t color2, const std::string &title, const float &xLow, const float &xHi,  
    const std::string &xlabel, const std::string &ylabel, const float &xOffSet, const float &xSize, 
    const float &yOffSet, const float &ySize, const float &yLow, const float &yHi){

  TH1F *th1axis = gPad->DrawFrame(xLow, yLow, xHi, yHi);
  th1axis->GetYaxis()->SetTitle(ylabel.c_str());
  th1axis->SetTitle(title.c_str());
  th1axis->GetXaxis()->SetTitle(xlabel.c_str());
  th1axis->GetXaxis()->SetTitleSize(xSize);
  th1axis->GetYaxis()->SetTitleSize(ySize);
  th1axis->GetYaxis()->CenterTitle();
  th1axis->GetXaxis()->SetTitleOffset(xOffSet);
  th1axis->GetYaxis()->SetTitleOffset(yOffSet);
  if (var == "phi")
    th1axis->GetXaxis()->SetNdivisions(-4);
  gPad->SetFillColor(33);
  gPad->SetGrid();
  T2CaRelEffic* t2CaRel = 0;
  NeuralRelEffic* neuralRel = 0;
  const std::string &rvar = var;
  if ( (t2CaRel = dynamic_cast<T2CaRelEffic*>(relEffic1) ) ){
    t2CaRel->DrawEfficVs(rvar,"LP",color1);
  }else if ( (neuralRel = dynamic_cast<NeuralRelEffic*>(relEffic1))){
    neuralRel->DrawEfficVs(rvar,"LP",color1);
  }if ( (t2CaRel = dynamic_cast<T2CaRelEffic*>(relEffic2))){
    t2CaRel->DrawEfficVs(rvar,"LP,SAME", color2);
    t2CaRel->getGraph(rvar)->SetLineStyle(kDashed);
  } else if ( (neuralRel = dynamic_cast<NeuralRelEffic*>(relEffic2))){
    neuralRel->DrawEfficVs(rvar,"LP,SAME",color2);
    neuralRel->getGraph(rvar)->SetLineStyle(kDashed);
  }
  gPad->Modified();
  return th1axis;

}

int RelEfficCanvas::genInfoPad(){
  gPad->SetFillColor(33);
  TPaveText *pt = new TPaveText(.05,.05,.95,.95);
  pt->SetLabel("HypoIterator v4.0.0");
  pt->SetFillColor(18);
  // ONE DATA:
  if (relEfficData){
      std::string id = relEfficData->getId();
      TString line1, line2, line3, line4, line5, line6;
      unsigned totalData = relEfficData->getTotalData();
      float detRate = relEfficData->getDetRate();
      if ( id.find("elc") != std::string::npos )
          line1.Form("Total Data : Electrons = %d", totalData);
      if ( id.find("jet") != std::string::npos ) 
          line1.Form("Total Data : Jets = %d", totalData);
      T2CaRelEffic *t2CaData;
      if ( (t2CaData = dynamic_cast<T2CaRelEffic*>(relEfficData))){
        if (t2CaData){
            if ( id.find("elc") != std::string::npos ){
                hypoPt = new TPaveText(.06,.12,.94,.60,"T2Calo Detection Rate");
            }
            else if ( id.find("jet") != std::string::npos ){
                hypoPt = new TPaveText(.06,.12,.94,.60,"T2Calo False Alarm");
            }
        }else
            hypoPt = new TPaveText(.06,.12,.94,.60,"T2Calo Cuts");
        hypoPt->SetTextAlign(12);
        hypoPt->SetFillColor(18);
        hypoPt->SetLabel("T2Calo Efficiency");
        float detrCoreRate = t2CaData->getDetrCoreRate();
        float deteRatioRate = t2CaData->getDeteRatioRate();
        float detEtRate = t2CaData->getDetEtRate();
        float detHadEtRate = t2CaData->getDetHadEtRate();
        if ( id.find("elc") != std::string::npos){
            line2.Form("#scale[1.2]{T2Calo Detection Rate = %.4f%%}", detRate);
            line3.Form("rCore Detection Rate = %.4f%%", detrCoreRate);
            line4.Form("eRatio Detection Rate  = %.4f%%", deteRatioRate);
            line5.Form("Et_{Em} Detection Rate = %.4f%%", detEtRate);
            line6.Form("Et_{Had} Detection Rate = %.4f%%", detHadEtRate);
        }
        if ( id.find("jet") != std::string::npos ){
            line2.Form("#scale[1.2]{T2Calo False Alarm = %.4f%%}", (100. - detRate));
            line3.Form("rCore False Alarm = %.4f%%", (100. - detrCoreRate));
            line4.Form("eRatio False Alarm = %.4f%%", (100. - deteRatioRate));
            line5.Form("Et_{Em} False Alarm = %.4f%%", (100. - detEtRate));
            line6.Form("Et_{Had} False Alarm = %.4f%%", (100. -detHadEtRate));
        }
        pt->SetTextAlign(12);
        pt->AddText("");
        pt->AddText(line1);
        pt->AddText("");
        pt->AddText(line2);
        pt->AddText(""); pt->AddText(""); pt->AddText(""); pt->AddText(""); pt->AddText("");pt->AddText("");pt->AddText("");pt->AddText("");pt->AddText("");
        hypoPt->AddText("");
        hypoPt->AddText(line3);
        hypoPt->AddText(line4);
        hypoPt->AddText(line5);
        hypoPt->AddText(line6);
        TString line666("Signal Processing Laboratory - COPPE/UFRJ");
        TText *p1 = pt->AddText(0.30, 0.02, line666);
        p1->SetTextSize(0.04);
        pt->Draw();
        hypoPt->Draw();
        gPad->Modified();
        gPad->SetEditable(kFALSE);
      } else {
        NeuralCommon* neuralData = dynamic_cast<NeuralCommon*>(relEfficData);
        float detRate = neuralData->getDetRate();
        pt->SetTextAlign(12);
        if ( id.find("elc") != std::string::npos)
            line2.Form("#scale[1.2]{NeuralRinger Detection Rate = %.4f%%}", detRate);
        if ( id.find("jet") != std::string::npos)
            line2.Form("#scale[1.2]{NeuralRinger False Alarm = %.4f%%}", detRate);
        pt->AddText("");
        pt->AddText(line1);
        pt->AddText("");
        pt->AddText(line2);
        pt->AddText("");
        TString line666("Signal Processing Laboratory - COPPE/UFRJ");
        TText *p1 = pt->AddText(0.30, 0.02, line666);
        p1->SetTextSize(0.04);
        pt->Draw();
        gPad->Modified();
        gPad->SetEditable(kFALSE);
      }
  //TWO DATA
  }else if (relEffic1 && relEffic2){
    NeuralRelEffic *neural1 = 0;
    NeuralRelEffic *neural2 = 0;
    T2CaRelEffic *t2Ca1 = 0;
    T2CaRelEffic *t2Ca2 = 0;
    if ( (t2Ca1 = dynamic_cast<T2CaRelEffic *>(relEffic1)) && (t2Ca2 = dynamic_cast<T2CaRelEffic *>(relEffic2))){
      if (relEffic1->getId().find("elc")==std::string::npos){ 
        t2Ca1 = t2Ca2;
        t2Ca2 = dynamic_cast<T2CaRelEffic *>(relEffic1);
      }
      if (hypoPt){
        delete hypoPt;
        hypoPt = 0;
      }
      hypoPt = new TPaveText(.06,.12,.94,.60,"T2Calo Efficiency");
      hypoPt->SetLabel("T2Calo Efficiency");
      hypoPt->SetTextAlign(12);
      hypoPt->SetFillColor(18);
      TString line1, line2, line3, line4, line5, line6, line7, line8, line9, line10, line11, line12, line13, line14, line15, line16;
      unsigned totalDataElc = t2Ca1->getTotalData();
      unsigned totalDataJet = t2Ca2->getTotalData();
      float detRateElc = t2Ca1->getDetRate();
      float detRateJet = t2Ca2->getDetRate();
      unsigned totalData = totalDataElc + totalDataJet;
      float effic = calcSP(detRateElc, detRateJet);
      line1.Form("Total Data = %d : #color[4]{Electrons = %d} : #color[2]{Jets = %d}",totalData, totalDataElc,totalDataJet);
      float detrCoreRateElc = t2Ca1->getDetrCoreRate();
      float deteRatioRateElc = t2Ca1->getDeteRatioRate();
      float detEtRateElc = t2Ca1->getDetEtRate();
      float detHadEtRateElc = t2Ca1->getDetHadEtRate();
      float detrCoreRateJet = t2Ca2->getDetrCoreRate();
      float deteRatioRateJet = t2Ca2->getDeteRatioRate();
      float detEtRateJet = t2Ca2->getDetEtRate();
      float detHadEtRateJet = t2Ca2->getDetHadEtRate();
      float rCoreEffic = calcSP(detrCoreRateElc, detrCoreRateJet);
      float eRatioEffic = calcSP(deteRatioRateElc, deteRatioRateJet);
      float etEffic = calcSP(detEtRateElc, detEtRateJet);
      float hadEtEffic = calcSP(detHadEtRateElc, detHadEtRateJet);
      line2.Form("#scale[1.05]{T2Calo Efficience = %.4f%%}", effic);
      line3.Form("#color[4]{#scale[1]{Det Rate = %.4f%%}}", detRateElc);
      line4.Form("#color[2]{#scale[1]{FA = %.4f%%}}", (100. - detRateJet ));
      line5.Form("#scale[1.1]{rCore Efficience = #scale[1.2]{%.4f%%}}", rCoreEffic);
      line6.Form("#scale[1.0]{#color[4]{rCore Det Rate = #scale[1.2]{%.4f%%}}}", detrCoreRateElc);
      line7.Form("#scale[1.0]{#color[2]{rCore FA = #scale[1.2]{%.4f%%}}}", (100. - detrCoreRateJet ));
      line8.Form("#scale[1.1]{eRatio Efficience = #scale[1.2]{%.4f%%}}", eRatioEffic);
      line9.Form("#scale[1.0]{#color[4]{eRatio Det Rate = #scale[1.2]{%.4f%%}}}", deteRatioRateElc);
      line10.Form("#scale[1.0]{#color[2]{eRatio FA = #scale[1.2]{%.4f%%}}}", ( 100. - deteRatioRateJet ));
      line11.Form("#scale[1.1]{Et_{Em} Efficience = #scale[1.2]{%.4f%%}}", etEffic);
      line12.Form("#scale[1.0]{#color[4]{Et_{Em} Det Rate = #scale[1.2]{%.4f%%}}}", detEtRateElc);
      line13.Form("#scale[1.0]{#color[2]{Et_{Em} FA = #scale[1.2]{%.4f%%}}}", ( 100. - detEtRateJet));
      line14.Form("#scale[1.1]{Et_{Had} Efficience = #scale[1.2]{%.4f%%}}", hadEtEffic);
      line15.Form("#scale[1.0]{#color[4]{Et_{Had} Det Rate = #scale[1.2]{%.4f%%}}}", detHadEtRateElc);
      line16.Form("#scale[1.0]{#color[2]{Et_{Had} FA = #scale[1.2]{%.4f%%}}}", ( 100. - detHadEtRateJet));
      pt->AddText(0.5,0.9,line1);
      pt->AddText(0.5,0.8,line2);
      pt->AddText(0.3,0.70,line3);
      pt->AddText(0.7,0.70,line4);
      pt->SetTextAlign(22);
      float y = 0.90; const float yDecrement = (.95 - .05)/8; float x1 = 0.2; float x2 = 0.4; float x3 = 0.6; 
      hypoPt->AddText(x2, y, line5);  y-=yDecrement;
      hypoPt->AddText(x1, y, line6);
      hypoPt->AddText(x3, y, line7);  y-=yDecrement;
      hypoPt->AddText(x2, y, line8);  y-=yDecrement;
      hypoPt->AddText(x1, y, line9);   
      hypoPt->AddText(x3, y, line10);  y-=yDecrement;
      hypoPt->AddText(x2, y, line11); y-=yDecrement;
      hypoPt->AddText(x1, y, line12);
      hypoPt->AddText(x3, y, line13); y-=yDecrement;
      hypoPt->AddText(x2, y, line14); y-=yDecrement;
      hypoPt->AddText(x1, y, line15);
      hypoPt->AddText(x3, y, line16);
      TString line666("Signal Processing Laboratory - COPPE/UFRJ");
      TText *p1 = pt->AddText(0.7, 0.02, line666);
      p1->SetTextSize(0.04);
      pt->Draw();
      hypoPt->Draw();
      gPad->Modified();
      gPad->SetEditable(kFALSE);
    } else if ( (neural1 = dynamic_cast<NeuralRelEffic *>(relEffic1)) && (neural2 = dynamic_cast<NeuralRelEffic *>(relEffic2))){
      if (relEffic1->getId().find("elc")==std::string::npos){ 
        neural1 = neural2;
        neural2 = dynamic_cast<NeuralRelEffic *>(relEffic1);
      }
      TString line1, line2, line3, line4;
      unsigned totalDataElc = neural1->getTotalData();
      unsigned totalDataJet = neural2->getTotalData();
      float detRateElc = neural1->getDetRate();
      float detRateJet = neural2->getDetRate();
      unsigned totalData = totalDataElc + totalDataJet;
      float effic = calcSP(detRateElc, detRateJet);
      line1.Form("Total Data = %d : #color[4]{Electrons = %d} : #color[2]{Jets = %d}",totalData, totalDataElc,totalDataJet);
      line2.Form("#scale[1.05]{NeuralRinger Efficience = %.4f%%}", effic);
      line3.Form("#color[4]{#scale[1]{Det Rate = %.4f%%}}", detRateElc);
      line4.Form("#color[2]{#scale[1]{FA = %.4f%%}}", (100. - detRateJet ));
      pt->AddText(""); pt->AddText(line1);
      pt->AddText(""); pt->AddText(line2);
      pt->AddText(""); pt->AddText(line3);
      pt->AddText(""); pt->AddText(line4);
      pt->AddText("");
      TString line666("Signal Processing Laboratory - COPPE/UFRJ");
      TText *p1 = pt->AddText(0.7, 0.02, line666);
      p1->SetTextSize(0.04);
      pt->Draw();
      gPad->Modified();
      gPad->SetEditable(kFALSE);
    } else {
      neural1 = 0;
      t2Ca1 = 0;
      neural1 = dynamic_cast<NeuralRelEffic *>(relEffic1);
      t2Ca1 = dynamic_cast<T2CaRelEffic *>(relEffic2);
      if (!neural1 && !t2Ca1){
        neural1 = dynamic_cast<NeuralRelEffic *>(relEffic2);
        t2Ca1 = dynamic_cast<T2CaRelEffic *>(relEffic1);
      }
      TString line1, line2, line3, line4;
      unsigned totalDataNe = t2Ca1->getTotalData();
      unsigned totalDataT2 = neural1->getTotalData();
      float detRateT2 = t2Ca1->getDetRate();
      float detRateNe = neural1->getDetRate();
      line1.Form("Total Data NeuralRinger %d", totalDataNe);
      line2.Form("Total Data T2Calo %d", totalDataT2);
      if (relEffic1->getId().find("elc")!=std::string::npos){ 
        line3.Form("#scale[1.05]{#color[4]{NeuralRinger} Detection Rate = %.4f%%}", detRateNe);
        line4.Form("#scale[1.05]{#color[2]{T2Calo} Detection Rate = %.4f%%}", detRateT2);
      } else {
        line3.Form("#scale[1.05]{#color[4]{NeuralRinger} False Alarm = %.4f%%}", (100.-detRateNe));
        line4.Form("#scale[1.05]{#color[2]{T2Calo} False Alarm  = %.4f%%}", (100.-detRateT2));
      }
      pt->AddText(""); pt->AddText(line1);
      pt->AddText(""); pt->AddText(line2);
      pt->AddText(""); pt->AddText(line3);
      pt->AddText(""); pt->AddText(line4);
      pt->AddText("");
      pt->Draw();
      TString line666("Signal Processing Laboratory - COPPE/UFRJ");
      TText *p1 = pt->AddText(0.5, 0.02, line666);
      p1->SetTextSize(0.04);
      gPad->Modified();
      gPad->SetEditable(kFALSE);
    }
  }
  return 0;
}

int RelEfficCanvas::Draw(const int numPads){

  if(relCanvas){
    if (gROOT->GetListOfCanvases()->FindObject("Relative Efficiency")){
      relCanvas->Closed();
      delete relCanvas;
      relCanvas = 0;
    }
  }
  if(infoCanvas){
    if (gROOT->GetListOfCanvases()->FindObject("Analysis Information")){
      infoCanvas->Closed();
      delete infoCanvas;
      infoCanvas = 0;
    }
  }
  relCanvas = new TCanvas("Relative Efficiency", "Relative Efficiency");
  
  if (relEfficData){
    std::string title;
    std::string ylabel;
    if (dynamic_cast<T2CaRelEffic*>(relEfficData)){
      title = "T2Calo";
    } else 
      title = "NeuralRinger";
    if(relEfficData->getId().find("elc") != std::string::npos) 
      ylabel = "Detection Rate (%)";
    else 
      ylabel = "False Alarm (%)";
    if (numPads==4) {
      relCanvas->Divide(2,2);
      relCanvas->cd(1);
      th1EtaPad = drawWithProperties("eta", relEfficData, title+" x #eta", 
         -2.5,2.5,"#eta", ylabel);
      relCanvas->cd(2);
      th1PhiPad = drawWithProperties("phi", relEfficData, title+" x #phi", 
         -TMath::Pi(),TMath::Pi(),"#phi", ylabel);
      relCanvas->cd(3);
      th1EtPad = drawWithProperties("et", relEfficData, title+" x E_{T}", 
         15,80,"Transverse Energy (GeV)", ylabel, .6, 0.045);
      relCanvas->cd(4);
      genInfoPad();
    } else if (numPads==3){
      relCanvas->Divide(1,2);
      relCanvas->cd(1);
      th1EtPad = drawWithProperties("et", relEfficData, title+" x E_{T}", 
         15,80,"Transverse Energy (GeV)", ylabel, .75);
      TVirtualPad *coordPad = relCanvas->cd(2);
      coordPad->SetFillColor(18);
      coordPad->Divide(2,1);
      coordPad->cd(1);
      th1EtaPad = drawWithProperties("eta", relEfficData, title+" x #eta", 
         -2.5,2.5,"#eta", ylabel);
      coordPad->cd(2);
      th1PhiPad = drawWithProperties("phi", relEfficData, title+" x #phi", 
         -TMath::Pi(),TMath::Pi(),"#phi", ylabel, 0.045);
      infoCanvas = new TCanvas("Analysis Information","Analysis Information");
      infoCanvas->cd();
      infoCanvas->SetFillColor(33);
      genInfoPad();
    }
    relCanvas->cd();
  } else if (relEffic1 && relEffic2){
    Color_t color1 = kBlack;
    Color_t color2 = kBlack;
    std::string title;
    std::string ylabel;
    std::string legend1;
    std::string legend2;
    if (dynamic_cast<T2CaRelEffic*>(relEffic1)){
      if (dynamic_cast<NeuralRelEffic*>(relEffic2)){ // T2Calo x Ringer
        color1 = kRed;
        color2 = kBlue;
        title = "L2Hypo";
        legend1 = "T2Calo "+ relEffic1->getDataLabel();
        legend2 = "NeuralRinger "+ relEffic2->getDataLabel();
        if(relEffic1->getId().find("elc") != std::string::npos){ // both elc
          ylabel = "Detection Rate (%)";
        }if(relEffic1->getId().find("jet") != std::string::npos){ // both jet
          ylabel = "False Alarm (%)";
        }
      } else { // T2Calo x T2Calo
        legend1 = relEffic1->getDataLabel();
        legend2 = relEffic2->getDataLabel();
        title = "T2Calo";
        if(relEffic1->getId().find("elc") != std::string::npos){ // Data 1 is elc, Data 2 is jet
          if (relEffic2->getId().find("jet") != std::string::npos){
            color1 = kBlue;
            color2 = kRed;
          }
        } else { // Data 1 is jet, Data 2 is elc
          color1 = kRed;
          color2 = kBlue;
        }
      } 
    } else if (dynamic_cast<NeuralRelEffic*>(relEffic2)){ // Ringer x Ringer
      title = "NeuralRinger";
      legend1 = relEffic1->getDataLabel();
      legend2 = relEffic2->getDataLabel();
      if(relEffic1->getId().find("elc") != std::string::npos){
        if (relEffic2->getId().find("jet") != std::string::npos){ // Data 1 is elc, Data 2 is jet
          color1 = kBlue;
          color2 = kRed;
        }
      } else { // Data 1 is jet, Data 2 is elc
        color1 = kRed;
        color2 = kBlue;
      }
    } else { // Ringer x T2Calo 
      legend1 = "NeuralRinger "+ relEffic1->getDataLabel();
      legend2 = "T2Calo "+ relEffic2->getDataLabel();
      color1 = kBlue;
      color2 = kRed;
      title = "L2Hypo";
      if(relEffic1->getId().find("elc") != std::string::npos) // both elc
          ylabel = "Detection Rate (%)";
      if(relEffic1->getId().find("jet") != std::string::npos) // both jet
        ylabel = "False Alarm (%)";
    }
    if (numPads==4) {
      relCanvas->Divide(2,2);
      relCanvas->cd(1);
      th1EtaPad = drawWithProperties("eta", relEffic1, relEffic2, color1, color2, title+" x #eta", 
         -2.5, 2.5, "#eta", ylabel);
      relCanvas->cd(2);
      th1PhiPad = drawWithProperties("phi", relEffic1, relEffic2, color1, color2, title+" x #phi", 
         -TMath::Pi(), TMath::Pi(),"#phi", ylabel);
      relCanvas->cd(3);
      th1EtPad = drawWithProperties("et", relEffic1, relEffic2, color1, color2, title+" x E_{T}", 
         15,80,"Transverse Energy (GeV)", ylabel, .75, 0.045);
      relCanvas->cd(4);
      genInfoPad();
    } else if (numPads==3){
      relCanvas->Divide(1,2);
      relCanvas->cd(1);
      th1EtPad = drawWithProperties("et", relEffic1, relEffic2, color1, color2, title+" x E_{T}", 
         15,80,"Transverse Energy (GeV)", ylabel, .75, 0.045);
      if (legend){
        delete legend;
        legend = 0;
      }
      legend = new TLegend(.90,.83,.995,.98);
      legend->AddEntry(relEffic1->getGraph("et"), legend1.c_str());
      legend->AddEntry(relEffic2->getGraph("et"), legend2.c_str());
      legend->Draw();
      TVirtualPad *coordPad = relCanvas->cd(2);
      coordPad->SetFillColor(18);
      coordPad->Divide(2,1);
      coordPad->cd(1);
      th1EtaPad = drawWithProperties("eta", relEffic1, relEffic2, color1, color2, title+" x #eta", 
         -2.5,2.5,"#eta", ylabel);
      coordPad->cd(2);
      th1PhiPad = drawWithProperties("phi", relEffic1, relEffic2, color1, color2, title+" x #phi", 
         -TMath::Pi(),TMath::Pi(),"#phi", ylabel);
      infoCanvas = new TCanvas("Analysis Information","Analysis Information");
      infoCanvas->cd();
      infoCanvas->SetFillColor(33);
      genInfoPad();
    }
  }
  relCanvas->cd();
  gPad->SetFillColor(18);
  relCanvas->Modified();
  relCanvas->Update();

  return 0;

}

inline float RelEfficCanvas::calcSP(float detelc, float detjet){
    return TMath::Sqrt(TMath::Sqrt(detelc*detjet)*((detelc+detjet)/2));
}

