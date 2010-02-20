#include "RelEfficCanvas.h"

RelEfficCanvas::RelEfficCanvas(RelEfficBase *userRelEfficData){
    relCanvas = 0;
    relEfficData = userRelEfficData;
    relEfficElc = 0;
    relEfficJet = 0;
}

RelEfficCanvas::RelEfficCanvas(RelEfficBase *userRelEfficElc, RelEfficBase *userRelEfficJet){
    relCanvas = 0;
    relEfficData = 0;
    relEfficElc = userRelEfficElc;
    relEfficJet = userRelEfficJet;
}   


int RelEfficCanvas::Draw(){

    relCanvas = new TCanvas("Relative Efficiency", "Relative Efficiency");
    T2CaRelEffic *t2relEfficData = dynamic_cast<T2CaRelEffic*>(relEfficData);
    T2CaRelEffic *t2relEfficElc = dynamic_cast<T2CaRelEffic*>(relEfficElc);
    T2CaRelEffic *t2relEfficJet = dynamic_cast<T2CaRelEffic*>(relEfficJet);
    
    std::string dataLabel;
   if (t2relEfficData){ 
        t2relEfficData->getDataLabel(dataLabel);
   }
    relCanvas->Divide(2,2);
    
    // ETA 
    
    TVirtualPad *etaPad = relCanvas->cd(1);
    etaPad->SetFillColor(33);
    TH1F *th1EtaPad;
    if (t2relEfficData){
        if (dataLabel == "elc")
            th1EtaPad = etaPad->DrawFrame(-2.5, 80, 2.5, 100);
        if (dataLabel == "jet")
            th1EtaPad = etaPad->DrawFrame(-2.5, 10, 2.5, 40);
        t2relEfficData->DrawEfficVs("eta", "LP");
    }
    if (t2relEfficElc && t2relEfficJet){
        t2relEfficElc->DrawEfficVs("eta","LP");
        t2relEfficJet->DrawEfficVs("eta","LP,SAME");
    }
    th1EtaPad->SetTitle("T2Calo Rate x #eta");
    th1EtaPad->GetXaxis()->SetTitle("#eta");
    th1EtaPad->GetYaxis()->SetTitle("Rating(%)");
    th1EtaPad->GetXaxis()->SetTitleSize(0.08);
    th1EtaPad->GetYaxis()->SetTitleSize(0.06);
    th1EtaPad->GetYaxis()->CenterTitle();
    th1EtaPad->GetXaxis()->SetTitleOffset(.5);
    th1EtaPad->GetYaxis()->SetTitleOffset(.6);
    etaPad->Modified();
    etaPad->SetGrid();
    etaPad->Modified();
    etaPad->SetEditable(kFALSE);

    // PHI 

    TVirtualPad *phiPad = relCanvas->cd(2);
    TH1F *th1PhiPad;
    
    if (t2relEfficData){
        if (dataLabel == "elc"){
            th1PhiPad = phiPad->DrawFrame(-TMath::Pi(), 90, TMath::Pi(), 100);
            th1PhiPad->GetYaxis()->SetTitle("Detection (%)");
        }
        else if (dataLabel == "jet"){
            th1PhiPad = phiPad->DrawFrame(-TMath::Pi(), 10, TMath::Pi(), 30);
            th1PhiPad->GetYaxis()->SetTitle("False Alarm (%)");
        }
        t2relEfficData->DrawEfficVs("phi", "LP");
    }
    if (t2relEfficElc && t2relEfficJet){
        t2relEfficElc->DrawEfficVs("phi","LP");
        t2relEfficJet->DrawEfficVs("phi","LP,SAME");
    }
    TLatex phiAxisLabel;
    phiAxisLabel.SetTextSize(0.04);
    phiAxisLabel.SetTextAlign(23);
    double yl = -2;
    phiAxisLabel.DrawLatex(-TMath::Pi(),yl,"-#pi");
    phiAxisLabel.DrawLatex(-TMath::Pi()/2,yl,"-#frac{#pi}{2}");
    phiAxisLabel.DrawLatex(0,yl,"0");
    phiAxisLabel.DrawLatex(TMath::Pi()/2,yl,"#frac{#pi}{2}");
    phiAxisLabel.DrawLatex(TMath::Pi(),yl,"#pi"); 
    th1PhiPad->SetTitle("T2Calo Rate x #phi");
    th1PhiPad->GetXaxis()->SetTitle("#phi");
    th1PhiPad->GetXaxis()->SetTitleSize(0.08);
    th1PhiPad->GetYaxis()->SetTitleSize(0.06);
    th1PhiPad->GetYaxis()->CenterTitle();
    th1PhiPad->GetXaxis()->SetTitleOffset(.55);
    th1PhiPad->GetXaxis()->SetLabelOffset(999);
    th1PhiPad->GetXaxis()->SetNdivisions(-4);
    th1PhiPad->GetYaxis()->SetTitleOffset(.6);
    phiPad->SetFillColor(33);
    phiPad->Modified();
    phiPad->SetGrid();
    phiPad->Modified();
    phiPad->SetEditable(kFALSE);
    
    // ET
    
    TVirtualPad *etPad = relCanvas->cd(3);
    TH1F *th1EtPad;
    if (t2relEfficData){
        if (dataLabel == "elc"){
            th1EtPad = gPad->DrawFrame(15000, 90, 80000, 100);
            th1EtPad->GetYaxis()->SetTitle("Detection (%)");
        }
        else if (dataLabel == "jet"){
            th1EtPad = gPad->DrawFrame(15000, 0, 80000, 100);
            th1EtPad->GetYaxis()->SetTitle("False Alarm (%)");
        }
        t2relEfficData->DrawEfficVs("et", "LP");
    }
    if (t2relEfficElc && t2relEfficJet){
        t2relEfficElc->DrawEfficVs("et", "LP");
        t2relEfficElc->DrawEfficVs("et", "LP,SAME");
    }
    th1EtPad->SetTitle("T2Calo Rate x Et");
    th1EtPad->GetXaxis()->SetTitle("Transverse Energy");
    th1EtPad->GetXaxis()->SetTitleSize(0.045);
    th1EtPad->GetYaxis()->SetTitleSize(0.06);
    th1EtPad->GetYaxis()->CenterTitle();
    th1EtPad->GetXaxis()->SetTitleOffset(.75);
    th1EtPad->GetYaxis()->SetTitleOffset(.6);
    etPad->SetFillColor(33);
    etPad->Modified();
    etPad->SetGrid();
    etPad->Modified();
    etPad->SetEditable(kFALSE);

    // Info Stats

    relCanvas->cd(4);
    gPad->SetFillColor(33);
    TPaveText *pt = new TPaveText(.05,.05,.95,.95);
    TPaveText *ptT2Calo;
    if (t2relEfficData){
        if (dataLabel == "elc"){
            ptT2Calo = new TPaveText(.06,.12,.94,.60,"T2Calo Cuts Detection Rate:");
            ptT2Calo->SetLabel("T2Calo Cuts Detection Rate Rate");
        }
        else if (dataLabel == "elc"){
            ptT2Calo = new TPaveText(.06,.12,.94,.60,"T2Calo Cuts False Alarm Rate:");
            ptT2Calo->SetLabel("T2Calo Cuts False Alarm Rate");
        }
    }
    //pt->SetFillColor(34);
    pt->SetTextAlign(12);
    ptT2Calo->SetTextAlign(12);
    pt->SetLabel("HypoIterator v4.0.0");
    //ptT2Calo->SetFillColor(34);
    // ONE DATA:
    if (t2relEfficData){
        TString line1, line2, line3, line4, line5, line6;
        unsigned totalData = t2relEfficData->getTotalData();
        float detRate = t2relEfficData->getDetRate();
        if (dataLabel == "elc")
            dataLabel = "Electrons";
        if (dataLabel == "jet")
            dataLabel = "Jets";
        line1.Form("Total Data : %s = %d", dataLabel.c_str(), totalData);
        float detrCoreRate = t2relEfficData->getDetrCoreRate();
        float deteRatioRate = t2relEfficData->getDeteRatioRate();
        float detEtRate = t2relEfficData->getDetEtRate();
        float detHadEtRate = t2relEfficData->getDetHadEtRate();
        if (dataLabel == "elc"){
            line2.Form("T2Calo Detection Rate = %.4f%", detRate);
            line3.Form("rCore = %.4f%", detrCoreRate);
            line4.Form("eRatio = %.4f%", deteRatioRate);
            line5.Form("Et_{Em} = %.4f%", detEtRate);
            line6.Form("Et_{Had} = %.4f%", detHadEtRate);
        }
        if (dataLabel == "jet"){
            line2.Form("T2Calo False Alarm Rate = %.4f%", (100. - detRate));
            line3.Form("rCore = %.4f%", (100. - detrCoreRate));
            line4.Form("eRatio = %.4f%", (100. - deteRatioRate));
            line5.Form("Et_{Em} = %.4f%", (100. - detEtRate));
            line6.Form("Et_{Had} = %.4f%", (100. -detHadEtRate));
        }
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
    //TWO DATA
    }else if (t2relEfficElc && t2relEfficJet){
        TString line1, line2, line3, line4, line5, line6, line7, line8, line9, line10, line11, line12, line13, line14, line15;
        unsigned totalDataElc = t2relEfficElc->getTotalData();
        unsigned totalDataJet = t2relEfficJet->getTotalData();
        float detRateElc = t2relEfficElc->getDetRate();
        float detRateJet = t2relEfficJet->getDetRate();
        float totalData = totalDataElc + totalDataJet;
        float effic = calcSP(detRateElc, detRateJet);
        line1.Form("Total Data = %d:Electrons = %d:Jets = %d",totalData, totalDataElc,totalDataJet);
        float detrCoreRateElc = t2relEfficData->getDetrCoreRate();
        float deteRatioRateElc = t2relEfficData->getDeteRatioRate();
        float detEtRateElc = t2relEfficData->getDetEtRate();
        float detHadEtRateElc = t2relEfficData->getDetHadEtRate();
        float detrCoreRateJet = t2relEfficData->getDetrCoreRate();
        float deteRatioRateJet = t2relEfficData->getDeteRatioRate();
        float detEtRateJet = t2relEfficData->getDetEtRate();
        float detHadEtRateJet = t2relEfficData->getDetHadEtRate();
        float rCoreEffic = calcSP(detrCoreRateElc, detrCoreRateJet);
        float eRatioEffic = calcSP(deteRatioRateElc, deteRatioRateJet);
        float etEffic = calcSP(detEtRateElc, detEtRateJet);
        float hadEtEffic = calcSP(detHadEtRateElc, detHadEtRateJet);
        line2.Form("T2Calo Efficience = %.4f", effic);
        line3.Form("Electrons Efficience = %.4f", detRateElc);
        line4.Form("Jets Efficience = %.4f", detRateJet);
        line4.Form("rCore Efficience = %.4f", rCoreEffic);
        line5.Form("rCore Electron Rate = %.4f", detrCoreRateElc);
        line6.Form("rCore Jet Rate = %.4f", detrCoreRateJet);
        line7.Form("eRatio Efficience = %.4f", eRatioEffic);
        line8.Form("eRatio Electron Rate = %.4f", deteRatioRateElc);
        line9.Form("eRatio Jet Rate = %.4f", deteRatioRateJet);
        line10.Form("Et_{Em} Efficience = %.4f", etEffic);
        line11.Form("Et_{Em} Electron Rate = %.4f", detEtRateElc);
        line12.Form("Et_{Em} Jet Rate = %.4f", detEtRateJet);
        line13.Form("Et_{Had} Efficience = %.4f", hadEtEffic);
        line14.Form("Et_{Had} Electron Rate = %.4f", detHadEtRateElc);
        line15.Form("Et_{Had} Jet Rate = %.4f", detHadEtRateJet);
        pt->AddText("");
        pt->AddText(line1);
        pt->AddText("");
        TText* p1 = pt->AddText(line2);
        TText* p2 = pt->AddText(line3);
        p1->SetTextColor(4);
        p2->SetTextColor(2);
        pt->AddText(""); pt->AddText(""); pt->AddText(""); pt->AddText(""); pt->AddText(""); pt->AddText("");
        ptT2Calo->AddText("");
        ptT2Calo->AddText("T2Calo Cuts:");
        ptT2Calo->AddText(line4);
        p1 = ptT2Calo->AddText(line5);
        p2 = ptT2Calo->AddText(line6);
        p1->SetTextColor(4);
        p2->SetTextColor(2);
        ptT2Calo->AddText("");
        ptT2Calo->AddText(line7);
        p1 = ptT2Calo->AddText(line8);
        p2 = ptT2Calo->AddText(line9);
        p1->SetTextColor(4);
        p2->SetTextColor(2);
        ptT2Calo->AddText("");
        ptT2Calo->AddText(line10);
        p1 = ptT2Calo->AddText(line11);
        p2 = ptT2Calo->AddText(line12);
        p1->SetTextColor(4);
        p2->SetTextColor(2);
        ptT2Calo->AddText("");
        ptT2Calo->AddText(line13);
        p1 = ptT2Calo->AddText(line14);
        p2 = ptT2Calo->AddText(line15);
        p1->SetTextColor(4);
        p2->SetTextColor(2);
    }
    TString line666("Signal Processing Laboratory - COPPE/UFRJ");
    TText *p1 = pt->AddText(0.43, 0.02, line666);
    p1->SetTextSize(0.04);

    pt->Draw();
    ptT2Calo->Draw();
    gPad->Modified();
    gPad->SetEditable(kFALSE);

    relCanvas->cd();
    gPad->SetFillColor(18);
    relCanvas->Modified();
    relCanvas->Update();

    return 0;

}

inline float RelEfficCanvas::calcSP(float detelc, float detjet){
    return TMath::Sqrt(TMath::Sqrt(detelc*detjet)*((detelc+detjet)/2));
}

