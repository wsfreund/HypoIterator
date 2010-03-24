#include "RelEfficCanvas.h"

RelEfficCanvas::RelEfficCanvas(RelEfficBase *userRelEfficData){
    relCanvas = 0;
    relEfficData = userRelEfficData;
    relEffic1 = 0;
    relEffic2 = 0;
}

RelEfficCanvas::RelEfficCanvas(RelEfficBase *userRelEffic1, RelEfficBase *userRelEffic2){
    relCanvas = 0;
    relEfficData = 0;
    relEffic1 = userRelEffic1;
    relEffic2 = userRelEffic2;
}   


int RelEfficCanvas::Draw(const int numPads){

    relCanvas = new TCanvas("Relative Efficiency", "Relative Efficiency");
    T2CaRelEffic *t2relEfficData = dynamic_cast<T2CaRelEffic*>(relEfficData);
    
    std::string id;

    if (relEfficData)
      id = t2relEfficData->getId(); 
    
    T2CaRelEffic *t2relEfficElc = 0; 
    T2CaRelEffic *t2relEfficJet = 0;
    if (relEffic1 && relEffic2){
      if (dynamic_cast<HypoBase*>(relEffic1)->getId().find("elc") != std::string::npos)
        t2relEfficElc = dynamic_cast<T2CaRelEffic*>(relEffic1);
      else
        t2relEfficJet = dynamic_cast<T2CaRelEffic*>(relEffic1);
      if (dynamic_cast<HypoBase*>(relEffic2)->getId().find("elc") != std::string::npos)
        t2relEfficElc = dynamic_cast<T2CaRelEffic*>(relEffic2);
      else
        t2relEfficJet = dynamic_cast<T2CaRelEffic*>(relEffic2);
      if ( !t2relEfficJet || !t2relEfficElc)
        throw;
    }

    if (numPads ==4){
      relCanvas->Divide(2,2);

      // ETA  
      TVirtualPad *etaPad = relCanvas->cd(1);
      TH1F *th1EtaPad;
      if (t2relEfficData){
          if ( id.find("elc") != std::string::npos){
              th1EtaPad = etaPad->DrawFrame(-2.5, 80, 2.5, 100);
              th1EtaPad->GetYaxis()->SetTitle("Detection (%)");
          }
          if ( id.find("jet") != std::string::npos){
              th1EtaPad = etaPad->DrawFrame(-2.5, 10, 2.5, 40);
              th1EtaPad->GetYaxis()->SetTitle("False Alarm (%)");
          }
          t2relEfficData->DrawEfficVs("eta", "LP");
      } else if (t2relEfficElc && t2relEfficJet){
          th1EtaPad = etaPad->DrawFrame(-2.5, 0, 2.5, 100);
          th1EtaPad->GetYaxis()->SetTitle("Rating (%)");
          t2relEfficElc->DrawEfficVs("eta","LP");
          t2relEfficJet->DrawEfficVs("eta","LP,SAME");
          t2relEfficJet->getGraph("eta")->SetLineStyle(kDashed);
      } else {
          cout<<"Not know T2Calo or Ringer Type"<<endl;
          return 1;
      }

      th1EtaPad->SetTitle("T2Calo Rate x #eta");
      th1EtaPad->GetXaxis()->SetTitle("#eta");
      th1EtaPad->GetXaxis()->SetTitleSize(0.08);
      th1EtaPad->GetYaxis()->SetTitleSize(0.06);
      th1EtaPad->GetYaxis()->CenterTitle();
      th1EtaPad->GetXaxis()->SetTitleOffset(.5);
      th1EtaPad->GetYaxis()->SetTitleOffset(.6);
      etaPad->SetFillColor(33);
      etaPad->SetGrid();
      etaPad->Modified();
      etaPad->SetEditable(kFALSE);

      // PHI 

      TVirtualPad *phiPad = relCanvas->cd(2);
      TH1F *th1PhiPad;
      
      /*TLatex phiAxisLabel;
      phiAxisLabel.SetTextSize(0.04);
      phiAxisLabel.SetTextAlign(23);
      double yl = -3;
      phiAxisLabel.DrawLatex(-TMath::Pi(),yl,"-#pi");
      phiAxisLabel.DrawLatex(-TMath::Pi()/2,yl,"-#frac{#pi}{2}");
      phiAxisLabel.DrawLatex(0,yl,"0");
      phiAxisLabel.DrawLatex(TMath::Pi()/2,yl,"#frac{#pi}{2}");
      phiAxisLabel.DrawLatex(TMath::Pi(),yl,"#pi");*/ 
      if (t2relEfficData){
          if ( id.find("elc") != std::string::npos ){
              th1PhiPad = phiPad->DrawFrame(-TMath::Pi(), 90, TMath::Pi(), 100);
              th1PhiPad->GetYaxis()->SetTitle("Detection (%)");
          }
          if ( id.find("jet") != std::string::npos ){
              th1PhiPad = phiPad->DrawFrame(-TMath::Pi(), 10, TMath::Pi(), 30);
              th1PhiPad->GetYaxis()->SetTitle("False Alarm (%)");
          }
          t2relEfficData->DrawEfficVs("phi", "LP");
      } else if (t2relEfficElc && t2relEfficJet){
          th1PhiPad = phiPad->DrawFrame(-TMath::Pi(), 0, TMath::Pi(), 100);
          th1PhiPad->GetYaxis()->SetTitle("Rating (%)");
          t2relEfficElc->DrawEfficVs("phi","LP");
          t2relEfficJet->DrawEfficVs("phi","LP,SAME");
          t2relEfficJet->getGraph("phi")->SetLineStyle(kDashed);
      } else {
          cout<<"Not know T2Calo or Ringer Type"<<endl;
          return 1;
      }
      th1PhiPad->SetTitle("T2Calo Rate x #phi");
      th1PhiPad->GetXaxis()->SetTitle("#phi");
      th1PhiPad->GetXaxis()->SetTitleSize(0.08);
      th1PhiPad->GetYaxis()->SetTitleSize(0.06);
      th1PhiPad->GetYaxis()->CenterTitle();
      th1PhiPad->GetXaxis()->SetTitleOffset(.55);
     // th1PhiPad->GetXaxis()->SetLabelOffset(999);
      th1PhiPad->GetXaxis()->SetNdivisions(-4);
      th1PhiPad->GetYaxis()->SetTitleOffset(.6);
      phiPad->SetFillColor(33);
      phiPad->SetGrid();
      phiPad->Modified();
      phiPad->SetEditable(kFALSE);
      
      // ET
      
      TVirtualPad *etPad = relCanvas->cd(3);
      TH1F *th1EtPad;
      if (t2relEfficData){
          if ( id.find("elc") != std::string::npos ){
              th1EtPad = etPad->DrawFrame(15, 90, 80, 100);
              th1EtPad->GetYaxis()->SetTitle("Detection (%)");
          }
          else if ( id.find("jet") != std::string::npos ){
              th1EtPad = etPad->DrawFrame(15, 0, 80, 100);
              th1EtPad->GetYaxis()->SetTitle("False Alarm (%)");
          }
          t2relEfficData->DrawEfficVs("et", "LP");
      }
      else if (t2relEfficElc && t2relEfficJet){
          th1EtPad = etPad->DrawFrame(15, 0, 80, 100);
          th1EtPad->GetYaxis()->SetTitle("Rating (%)");
          t2relEfficElc->DrawEfficVs("et", "LP");
          t2relEfficJet->DrawEfficVs("et", "LP,SAME");
          t2relEfficJet->getGraph("et")->SetLineStyle(kDashed);
      } else {
          cout<<"Unknown T2Calo or Ringer Type"<<endl;
          return 1;
      }
      th1EtPad->SetTitle("T2Calo Rate x E_{T}");
      th1EtPad->GetXaxis()->SetTitle("Transverse Energy (GeV)");
      th1EtPad->GetXaxis()->SetTitleSize(0.045);
      th1EtPad->GetYaxis()->SetTitleSize(0.06);
      th1EtPad->GetYaxis()->CenterTitle();
      th1EtPad->GetXaxis()->SetTitleOffset(.75);
      th1EtPad->GetYaxis()->SetTitleOffset(.6);
      etPad->SetFillColor(33);
      etPad->SetGrid();
      etPad->Modified();
      etPad->SetEditable(kFALSE);

      // Info Stats

      relCanvas->cd(4);
      gPad->SetFillColor(33);
      TPaveText *pt = new TPaveText(.05,.05,.95,.95);
      TPaveText *ptT2Calo;
      if (t2relEfficData){
          if ( id.find("elc") != std::string::npos ){
              ptT2Calo = new TPaveText(.06,.12,.94,.60,"T2Calo Cuts Detection Rate");
          }
          else if ( id.find("jet") != std::string::npos ){
              ptT2Calo = new TPaveText(.06,.12,.94,.60,"T2Calo Cuts False Alarm Rate");
          }
      }else
          ptT2Calo = new TPaveText(.06,.12,.94,.60,"T2Calo Cuts");
      ptT2Calo->SetLabel("T2Calo Cuts");
      pt->SetFillColor(18);
      ptT2Calo->SetTextAlign(12);
      pt->SetLabel("HypoIterator v4.0.0");
      ptT2Calo->SetFillColor(18);
      // ONE DATA:
      if (t2relEfficData){
          TString line1, line2, line3, line4, line5, line6;
          unsigned totalData = t2relEfficData->getTotalData();
          float detRate = t2relEfficData->getDetRate();
          if ( id.find("elc") != std::string::npos )
              line1.Form("Total Data : Electrons = %d", totalData);
          if ( id.find("jet") != std::string::npos ) 
              line1.Form("Total Data : Jets = %d", totalData);
          float detrCoreRate = t2relEfficData->getDetrCoreRate();
          float deteRatioRate = t2relEfficData->getDeteRatioRate();
          float detEtRate = t2relEfficData->getDetEtRate();
          float detHadEtRate = t2relEfficData->getDetHadEtRate();
          if ( id.find("elc") != std::string::npos){
              line2.Form("#scale[1.2]{T2Calo Detection Rate = %.4f%%}", detRate);
              line3.Form("rCore Detection Rate = %.4f%%", detrCoreRate);
              line4.Form("eRatio Detection Rate  = %.4f%%", deteRatioRate);
              line5.Form("Et_{Em} Detection Rate = %.4f%%", detEtRate);
              line6.Form("Et_{Had} Detection Rate = %.4f%%", detHadEtRate);
          }
          if ( id.find("jet") != std::string::npos ){
              line2.Form("#scale[1.2]{T2Calo False Alarm Rate = %.4f%%}", (100. - detRate));
              line3.Form("rCore False Alarm Rate = %.4f%%", (100. - detrCoreRate));
              line4.Form("eRatio False Alarm Rate = %.4f%%", (100. - deteRatioRate));
              line5.Form("Et_{Em} False Alarm Rate = %.4f%%", (100. - detEtRate));
              line6.Form("Et_{Had} False Alarm Rate = %.4f%%", (100. -detHadEtRate));
          }
          pt->SetTextAlign(12);
          pt->AddText("");
          pt->AddText(line1);
          pt->AddText("");
          pt->AddText(line2);
          pt->AddText(""); pt->AddText(""); pt->AddText(""); pt->AddText(""); pt->AddText("");pt->AddText("");pt->AddText("");pt->AddText("");pt->AddText("");
          ptT2Calo->AddText("");
          ptT2Calo->AddText(line3);
          ptT2Calo->AddText(line4);
          ptT2Calo->AddText(line5);
          ptT2Calo->AddText(line6);
          TString line666("Signal Processing Laboratory - COPPE/UFRJ");
          TText *p1 = pt->AddText(0.40, 0.02, line666);
          p1->SetTextSize(0.04);
      //TWO DATA
      }else if (t2relEfficElc && t2relEfficJet){
          TString line1, line2, line3, line4, line5, line6, line7, line8, line9, line10, line11, line12, line13, line14, line15, line16;
          unsigned totalDataElc = t2relEfficElc->getTotalData();
          unsigned totalDataJet = t2relEfficJet->getTotalData();
          float detRateElc = t2relEfficElc->getDetRate();
          float detRateJet = t2relEfficJet->getDetRate();
          unsigned totalData = totalDataElc + totalDataJet;
          float effic = calcSP(detRateElc, detRateJet);
          line1.Form("Total Data = %d : #color[4]{Electrons = %d} : #color[2]{Jets = %d}",totalData, totalDataElc,totalDataJet);
          float detrCoreRateElc = t2relEfficElc->getDetrCoreRate();
          float deteRatioRateElc = t2relEfficElc->getDeteRatioRate();
          float detEtRateElc = t2relEfficElc->getDetEtRate();
          float detHadEtRateElc = t2relEfficElc->getDetHadEtRate();
          float detrCoreRateJet = t2relEfficJet->getDetrCoreRate();
          float deteRatioRateJet = t2relEfficJet->getDeteRatioRate();
          float detEtRateJet = t2relEfficJet->getDetEtRate();
          float detHadEtRateJet = t2relEfficJet->getDetHadEtRate();
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
          pt->SetTextAlign(21);
          pt->AddText(0.5,0.9,line1);
          pt->AddText(0.5,0.8,line2);
          pt->AddText(0.3,0.70,line3);
          pt->AddText(0.7,0.70,line4);
          pt->SetTextAlign(22);
          float y = 0.90; const float yDecrement = (.95 - .05)/8; float x1 = 0.2; float x2 = 0.4; float x3 = 0.6; 
          ptT2Calo->AddText(x2, y, line5);  y-=yDecrement;
          ptT2Calo->AddText(x1, y, line6);
          ptT2Calo->AddText(x3, y, line7);  y-=yDecrement;
          ptT2Calo->AddText(x2, y, line8);  y-=yDecrement;
          ptT2Calo->AddText(x1, y, line9);   
          ptT2Calo->AddText(x3, y, line10);  y-=yDecrement;
          ptT2Calo->AddText(x2, y, line11); y-=yDecrement;
          ptT2Calo->AddText(x1, y, line12);
          ptT2Calo->AddText(x3, y, line13); y-=yDecrement;
          ptT2Calo->AddText(x2, y, line14); y-=yDecrement;
          ptT2Calo->AddText(x1, y, line15);
          ptT2Calo->AddText(x3, y, line16);
          TString line666("Signal Processing Laboratory - COPPE/UFRJ");
          TText *p1 = pt->AddText(0.7, 0.02, line666);
          p1->SetTextSize(0.04);
      } else {
          cout<<"Unknown T2Calo or Ringer Type"<<endl;
          return 1;
      }

      pt->Draw();
      ptT2Calo->Draw();
      gPad->Modified();
      gPad->SetEditable(kFALSE);

      relCanvas->cd();
      gPad->SetFillColor(18);
      relCanvas->Modified();
      relCanvas->Update();

    } else if (numPads ==3){ // Three PADS!!!!

      relCanvas->Divide(1,2);

      // ET
      
      TVirtualPad *etPad = relCanvas->cd(1);
      TH1F *th1EtPad;
      legend = new TLegend(.90,.83,.995,.98);
      if (t2relEfficData){
          if ( id.find("elc") != std::string::npos ){
              th1EtPad = etPad->DrawFrame(15, 90, 80, 100);
              th1EtPad->GetYaxis()->SetTitle("Detection (%)");
          }
          else if ( id.find("jet") != std::string::npos ){
              th1EtPad = etPad->DrawFrame(15, 0, 80, 100);
              th1EtPad->GetYaxis()->SetTitle("False Alarm (%)");
          }
          t2relEfficData->DrawEfficVs("et", "LP");
          if ( id.find("elc") != std::string::npos )
            legend->AddEntry(t2relEfficData->getGraph("et"),t2relEfficData->getDataLabel().c_str());
          else if ( id.find("jet") != std::string::npos )
            legend->AddEntry(t2relEfficData->getGraph("et"), t2relEfficData->getDataLabel().c_str());
      }
      else if (t2relEfficElc && t2relEfficJet){
          th1EtPad = etPad->DrawFrame(15, 0, 80, 100);
          th1EtPad->GetYaxis()->SetTitle("Rating (%)");
          t2relEfficElc->DrawEfficVs("et", "LP");
          t2relEfficJet->DrawEfficVs("et", "LP,SAME");
          t2relEfficJet->getGraph("et")->SetLineStyle(kDashed);
          legend->AddEntry(t2relEfficElc->getGraph("et"),t2relEfficData->getDataLabel().c_str());
          legend->AddEntry(t2relEfficJet->getGraph("et"),t2relEfficData->getDataLabel().c_str());
      } else {
          cout<<"Unknown T2Calo or Ringer Type"<<endl;
          return 1;
      }
      legend->Draw();
      th1EtPad->SetTitle("T2Calo Rate x E_{T}");
      th1EtPad->GetXaxis()->SetTitle("Transverse Energy (GeV)");
      th1EtPad->GetXaxis()->SetTitleSize(0.045);
      th1EtPad->GetYaxis()->SetTitleSize(0.06);
      th1EtPad->GetYaxis()->CenterTitle();
      th1EtPad->GetXaxis()->SetTitleOffset(.75);
      th1EtPad->GetYaxis()->SetTitleOffset(.6);
      etPad->SetFillColor(33);
      etPad->SetGrid();
      etPad->Modified();
      etPad->SetEditable(kFALSE);


      //Coord Pads:
      TVirtualPad *coordPad = relCanvas->cd(2);
      coordPad->SetFillColor(18);
      coordPad->Divide(2,1);

      // ETA 

      TVirtualPad *etaPad = coordPad->cd(1);
      TH1F *th1EtaPad;
      if (t2relEfficData){
          if ( id.find("elc") != std::string::npos ){
              th1EtaPad = etaPad->DrawFrame(-2.5, 80, 2.5, 100);
              th1EtaPad->GetYaxis()->SetTitle("Detection (%)");
          }
          if ( id.find("jet") != std::string::npos ){
              th1EtaPad = etaPad->DrawFrame(-2.5, 10, 2.5, 40);
              th1EtaPad->GetYaxis()->SetTitle("False Alarm (%)");
          }
          t2relEfficData->DrawEfficVs("eta", "LP");
      } else if (t2relEfficElc && t2relEfficJet){
          th1EtaPad = etaPad->DrawFrame(-2.5, 0, 2.5, 100);
          th1EtaPad->GetYaxis()->SetTitle("Rating (%)");
          t2relEfficElc->DrawEfficVs("eta","LP");
          t2relEfficJet->DrawEfficVs("eta","LP,SAME");
          t2relEfficJet->getGraph("eta")->SetLineStyle(kDashed);
      } else {
          cout<<"Not know T2Calo or Ringer Type"<<endl;
          return 1;
      }

      th1EtaPad->SetTitle("T2Calo Rate x #eta");
      th1EtaPad->GetXaxis()->SetTitle("#eta");
      th1EtaPad->GetXaxis()->SetTitleSize(0.08);
      th1EtaPad->GetYaxis()->SetTitleSize(0.06);
      th1EtaPad->GetYaxis()->CenterTitle();
      th1EtaPad->GetXaxis()->SetTitleOffset(.5);
      th1EtaPad->GetYaxis()->SetTitleOffset(.6);
      etaPad->SetFillColor(33);
      etaPad->SetGrid();
      etaPad->Modified();
      etaPad->SetEditable(kFALSE);

      // PHI 

      TVirtualPad *phiPad = coordPad->cd(2);
      TH1F *th1PhiPad;
      
      /*TLatex phiAxisLabel;
      phiAxisLabel.SetTextSize(0.04);
      phiAxisLabel.SetTextAlign(23);
      double yl = -2;
      phiAxisLabel.DrawLatex(-TMath::Pi(),yl,"-#pi");
      phiAxisLabel.DrawLatex(-TMath::Pi()/2,yl,"-#frac{#pi}{2}");
      phiAxisLabel.DrawLatex(0,yl,"0");
      phiAxisLabel.DrawLatex(TMath::Pi()/2,yl,"#frac{#pi}{2}");
      phiAxisLabel.DrawLatex(TMath::Pi(),yl,"#pi"); */
      if (t2relEfficData){
          if ( id.find("elc") != std::string::npos ){
              th1PhiPad = phiPad->DrawFrame(-TMath::Pi(), 90, TMath::Pi(), 100);
              th1PhiPad->GetYaxis()->SetTitle("Detection (%)");
          }
          if ( id.find("jet") != std::string::npos ){
              th1PhiPad = phiPad->DrawFrame(-TMath::Pi(), 10, TMath::Pi(), 30);
              th1PhiPad->GetYaxis()->SetTitle("False Alarm (%)");
          }
          t2relEfficData->DrawEfficVs("phi", "LP");
      } else if (t2relEfficElc && t2relEfficJet){
          th1PhiPad = phiPad->DrawFrame(-TMath::Pi(), 0, TMath::Pi(), 100);
          th1PhiPad->GetYaxis()->SetTitle("Rating (%)");
          t2relEfficElc->DrawEfficVs("phi","LP");
          t2relEfficJet->DrawEfficVs("phi","LP,SAME");
          t2relEfficJet->getGraph("phi")->SetLineStyle(kDashed);
      } else {
          cout<<"Not know T2Calo or Ringer Type"<<endl;
          return 1;
      }
      th1PhiPad->SetTitle("T2Calo Rate x #phi");
      th1PhiPad->GetXaxis()->SetTitle("#phi");
      th1PhiPad->GetXaxis()->SetTitleSize(0.08);
      th1PhiPad->GetYaxis()->SetTitleSize(0.06);
      th1PhiPad->GetYaxis()->CenterTitle();
      th1PhiPad->GetXaxis()->SetTitleOffset(.55);
      //th1PhiPad->GetXaxis()->SetLabelOffset(999);
      th1PhiPad->GetXaxis()->SetNdivisions(-4);
      th1PhiPad->GetYaxis()->SetTitleOffset(.6);
      phiPad->SetFillColor(33);
      phiPad->SetGrid();
      phiPad->Modified();
      phiPad->SetEditable(kFALSE);
      

      // Info Stats

      infoCanvas = new TCanvas("Analysis Information","Analysis Information");
      infoCanvas->cd();
      infoCanvas->SetFillColor(33);
      TPaveText *pt = new TPaveText(.05,.05,.95,.95);
      TPaveText *ptT2Calo;
      if (t2relEfficData){
          if ( id.find("elc") != std::string::npos ){
              ptT2Calo = new TPaveText(.06,.12,.94,.60,"T2Calo Cuts Detection Rate");
          }
          else if ( id.find("jet") != std::string::npos ){
              ptT2Calo = new TPaveText(.06,.12,.94,.60,"T2Calo Cuts False Alarm Rate");
          }
      }else
          ptT2Calo = new TPaveText(.06,.12,.94,.60,"T2Calo Cuts");
      ptT2Calo->SetLabel("T2Calo Cuts");
      pt->SetFillColor(18);
      ptT2Calo->SetTextAlign(12);
      pt->SetLabel("HypoIterator v4.0.0");
      ptT2Calo->SetFillColor(18);
      // ONE DATA:
      if (t2relEfficData){
          TString line1, line2, line3, line4, line5, line6;
          unsigned totalData = t2relEfficData->getTotalData();
          float detRate = t2relEfficData->getDetRate();
          if ( id.find("elc") != std::string::npos )
              line1.Form("Total Data : Electrons = %d", totalData);
          if ( id.find("jet") != std::string::npos )
              line1.Form("Total Data : Jets = %d", totalData);
          float detrCoreRate = t2relEfficData->getDetrCoreRate();
          float deteRatioRate = t2relEfficData->getDeteRatioRate();
          float detEtRate = t2relEfficData->getDetEtRate();
          float detHadEtRate = t2relEfficData->getDetHadEtRate();
          if ( id.find("elc") != std::string::npos ){
              line2.Form("#scale[1.2]{T2Calo Detection Rate = %.4f%%}", detRate);
              line3.Form("rCore Detection Rate = %.4f%%", detrCoreRate);
              line4.Form("eRatio Detection Rate  = %.4f%%", deteRatioRate);
              line5.Form("Et_{Em} Detection Rate = %.4f%%", detEtRate);
              line6.Form("Et_{Had} Detection Rate = %.4f%%", detHadEtRate);
          }
          if ( id.find("jet") != std::string::npos ){
              line2.Form("#scale[1.2]{T2Calo False Alarm Rate = %.4f%%}", (100. - detRate));
              line3.Form("rCore False Alarm Rate = %.4f%%", (100. - detrCoreRate));
              line4.Form("eRatio False Alarm Rate = %.4f%%", (100. - deteRatioRate));
              line5.Form("Et_{Em} False Alarm Rate = %.4f%%", (100. - detEtRate));
              line6.Form("Et_{Had} False Alarm Rate = %.4f%%", (100. -detHadEtRate));
          }
          pt->SetTextAlign(12);
          pt->AddText("");
          pt->AddText(line1);
          pt->AddText("");
          pt->AddText(line2);
          pt->AddText(""); pt->AddText(""); pt->AddText(""); pt->AddText(""); pt->AddText("");pt->AddText("");pt->AddText("");pt->AddText("");pt->AddText("");
          ptT2Calo->AddText("");
          ptT2Calo->AddText(line3);
          ptT2Calo->AddText(line4);
          ptT2Calo->AddText(line5);
          ptT2Calo->AddText(line6);
          TString line666("Signal Processing Laboratory - COPPE/UFRJ");
          TText *p1 = pt->AddText(0.35, 0.02, line666);
          p1->SetTextSize(0.04);
      //TWO DATA
      }else if (t2relEfficElc && t2relEfficJet){
          TString line1, line2, line3, line4, line5, line6, line7, line8, line9, line10, line11, line12, line13, line14, line15, line16;
          unsigned totalDataElc = t2relEfficElc->getTotalData();
          unsigned totalDataJet = t2relEfficJet->getTotalData();
          float detRateElc = t2relEfficElc->getDetRate();
          float detRateJet = t2relEfficJet->getDetRate();
          unsigned totalData = totalDataElc + totalDataJet;
          float effic = calcSP(detRateElc, detRateJet);
          line1.Form("Total Data = %d : #color[4]{Electrons = %d} : #color[2]{Jets = %d}",totalData, totalDataElc,totalDataJet);
          float detrCoreRateElc = t2relEfficElc->getDetrCoreRate();
          float deteRatioRateElc = t2relEfficElc->getDeteRatioRate();
          float detEtRateElc = t2relEfficElc->getDetEtRate();
          float detHadEtRateElc = t2relEfficElc->getDetHadEtRate();
          float detrCoreRateJet = t2relEfficJet->getDetrCoreRate();
          float deteRatioRateJet = t2relEfficJet->getDeteRatioRate();
          float detEtRateJet = t2relEfficJet->getDetEtRate();
          float detHadEtRateJet = t2relEfficJet->getDetHadEtRate();
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
          pt->SetTextAlign(21);
          pt->AddText(0.5,0.9,line1);
          pt->AddText(0.5,0.8,line2);
          pt->AddText(0.3,0.70,line3);
          pt->AddText(0.7,0.70,line4);
          pt->SetTextAlign(22);
          float y = 0.90; const float yDecrement = (.95 - .05)/8; float x1 = 0.2; float x2 = 0.4; float x3 = 0.6; 
          ptT2Calo->AddText(x2, y, line5);  y-=yDecrement;
          ptT2Calo->AddText(x1, y, line6);
          ptT2Calo->AddText(x3, y, line7);  y-=yDecrement;
          ptT2Calo->AddText(x2, y, line8);  y-=yDecrement;
          ptT2Calo->AddText(x1, y, line9);   
          ptT2Calo->AddText(x3, y, line10);  y-=yDecrement;
          ptT2Calo->AddText(x2, y, line11); y-=yDecrement;
          ptT2Calo->AddText(x1, y, line12);
          ptT2Calo->AddText(x3, y, line13); y-=yDecrement;
          ptT2Calo->AddText(x2, y, line14); y-=yDecrement;
          ptT2Calo->AddText(x1, y, line15);
          ptT2Calo->AddText(x3, y, line16);
          TString line666("Signal Processing Laboratory - COPPE/UFRJ");
          TText *p1 = pt->AddText(0.7, 0.02, line666);
          p1->SetTextSize(0.04);
      } else {
          cout<<"Unknown T2Calo or Ringer Type"<<endl;
          return 1;
      }

      pt->Draw();
      ptT2Calo->Draw();
      infoCanvas->Modified();
      infoCanvas->SetEditable(kFALSE);

      relCanvas->cd();
      gPad->SetFillColor(18);
      relCanvas->Modified();
      relCanvas->Update();

    }

    return 0;

}

inline float RelEfficCanvas::calcSP(float detelc, float detjet){
    return TMath::Sqrt(TMath::Sqrt(detelc*detjet)*((detelc+detjet)/2));
}

