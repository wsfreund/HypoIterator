#include "RelEfficCanvas.h"

RelEfficCanvas::RelEfficCanvas(RelEfficBase *userRelEfficData){
    relCanvas = new TCanvas("Relative Efficiency", "Relative Efficiency");
    relEfficData = userRelEfficData;
    relEfficElc = 0;
    relEfficJet = 0;
}

RelEfficCanvas::RelEfficCanvas(RelEfficBase *userRelEfficElc, RelEfficBase *userRelEfficJet){
    relCanvas = new TCanvas("Relative Efficiency", "Relative Efficiency");
    relEfficData = 0;
    relEfficElc = userRelEfficElc;
    relEfficJet = userRelEfficJet;
}   


int RelEfficCanvas::Draw(){

    if (typeid(*relEfficData) == typeid(T2CaRelEffic))
        cout<<"Ponteiro para T2CaRelEffic"<<endl;

    T2CaRelEffic *t2relEfficData = dynamic_cast<T2CaRelEffic*>(relEfficData);
    T2CaRelEffic *t2relEfficElc = dynamic_cast<T2CaRelEffic*>(relEfficElc);
    T2CaRelEffic *t2relEfficJet = dynamic_cast<T2CaRelEffic*>(relEfficJet);
    
    relCanvas->Divide(2,2);
    relCanvas->cd(1);
    if (t2relEfficData)
        t2relEfficData->DrawEfficVs("eta", "ACP");
    if (t2relEfficElc && t2relEfficJet){
        t2relEfficElc->DrawEfficVs("eta","ACP");
        t2relEfficJet->DrawEfficVs("eta","CP,SAME");
    }else{
    gPad->SetEditable(kFALSE);
    relCanvas->cd(2);
    if (t2relEfficData)
        t2relEfficData->DrawEfficVs("phi", "ACP");
    if (t2relEfficElc && t2relEfficJet){
        t2relEfficElc->DrawEfficVs("phi","ACP");
        t2relEfficJet->DrawEfficVs("phi","CP,SAME");
    }
    relCanvas->cd(3);
    if (t2relEfficData)
        t2relEfficData->DrawEfficVs("et", "ACP");
    if (t2relEfficElc && t2relEfficJet){
        t2relEfficElc->DrawEfficVs("et", "ACP");
        t2relEfficElc->DrawEfficVs("et", "CP,SAME");
    }
    relCanvas->cd(4);
    TPaveText *pt = new TPaveText(.05,.05,.95,.95);
    if (t2relEfficData){
        TString line1, line2, line3, line4, line5, line6;
        unsigned totalData = t2relEfficData->getTotalData();
        float detRate = t2relEfficData->getDetRate();
        std::string dataLabel;
        t2relEfficData->getDataLabel(dataLabel);
        if (dataLabel == "elc")
            dataLabel = "Electrons";
        if (dataLabel == "jet")
            dataLabel == "Jets";
        line1.Form("Total Data:%s = %d", dataLabel.c_str(), totalData);
        float detrCoreRate = t2relEfficData->getDetrCoreRate();
        float deteRatioRate = t2relEfficData->getDeteRatioRate();
        float detEtRate = t2relEfficData->getDetEtRate();
        float detHadEtRate = t2relEfficData->getDetEtRate();
        line2.Form("T2Calo Detection Rate = %.4f", detRate);
        line3.Form("rCore Cut Detection Rate = %.4f", detrCoreRate);
        line4.Form("eRatio Cut Detection Rate = %.4f", deteRatioRate);
        line5.Form("Et_{Em} Cut Detection Rate = %.4f", detEtRate);
        line6.Form("Et_{Had} Cut Detection Rate = %.4f", detHadEtRate);
        pt->AddText("");
        pt->AddText(line1);
        pt->AddText("");
        pt->AddText(line2);
        pt->AddText("");
        pt->AddText("T2Calo Cuts:");
        pt->AddText(line3);
        pt->AddText(line4);
        pt->AddText(line5);
        pt->AddText(line6);
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
        float detHadEtRateElc = t2relEfficData->getDetEtRate();
        float detrCoreRateJet = t2relEfficData->getDetrCoreRate();
        float deteRatioRateJet = t2relEfficData->getDeteRatioRate();
        float detEtRateJet = t2relEfficData->getDetEtRate();
        float detHadEtRateJet = t2relEfficData->getDetEtRate();
        float rCoreEffic = calcSP(detrCoreRateElc, detrCoreRateJet);
        float eRatioEffic = calcSP(deteRatioRateElc, deteRatioRateJet);
        float etEffic = calcSP(detEtRateElc, detEtRateJet);
        float hadEtEffic = calcSP(detHadEtRateElc, detHadEtRateJet);
        line2.Form("T2Calo Efficience = %.4f", effic);
        line3.Form("Electrons Efficience = %.4f", detRateElc);
        line4.Form("Jets Efficience = %.4f", detRateJet);
        line4.Form("rCore Cut Efficience = %.4f", rCoreEffic);
        line5.Form("rCore Electron Rate = %.4f", detrCoreRateElc);
        line6.Form("rCore Jet Rate = %.4f", detrCoreRateJet);
        line7.Form("eRatio Cut Efficience = %.4f", eRatioEffic);
        line8.Form("eRatio Electron Rate = %.4f", deteRatioRateElc);
        line9.Form("eRatio Jet Rate = %.4f", deteRatioRateJet);
        line10.Form("Et_{Em} Cut Efficience = %.4f", etEffic);
        line11.Form("Et_{Em} Electron Rate = %.4f", detEtRateElc);
        line12.Form("Et_{Em} Jet Rate = %.4f", detEtRateJet);
        line13.Form("Et_{Had} Cut Efficience = %.4f", hadEtEffic);
        line14.Form("Et_{Had} Electron Rate = %.4f", detHadEtRateElc);
        line15.Form("Et_{Had} Jet Rate = %.4f", detHadEtRateJet);
        pt->AddText("");
        pt->AddText(line1);
        pt->AddText("");
        TText* p1 = pt->AddText(line2);
        TText* p2 = pt->AddText(line3);
        p1->SetTextColor(4);
        p2->SetTextColor(2);
        pt->AddText("");
        pt->AddText(line4);
        p1 = pt->AddText(line5);
        p2 = pt->AddText(line6);
        p1->SetTextColor(4);
        p2->SetTextColor(2);
        pt->AddText("");
        pt->AddText(line7);
        p1 = pt->AddText(line8);
        p2 = pt->AddText(line9);
        p1->SetTextColor(4);
        p2->SetTextColor(2);
        pt->AddText("");
        pt->AddText(line10);
        p1 = pt->AddText(line11);
        p2 = pt->AddText(line12);
        p1->SetTextColor(4);
        p2->SetTextColor(2);
        pt->AddText("");
        pt->AddText(line13);
        p1 = pt->AddText(line14);
        p2 = pt->AddText(line15);
        p1->SetTextColor(4);
        p2->SetTextColor(2);
    }
    TText *p1 = pt->AddText(0.5, 0.98, "Signal Processing Laboratory - COPPE/UFRJ");
    p1->SetTextSize(0.01);
    pt->SetFillColor(30);
    pt->SetTextAlign(12);

    pt->SetLabel("HypoIterator v4.0.0");

    pt->Draw();
    
    return 0;

}

inline float RelEfficCanvas::calcSP(float detelc, float detjet){
    return TMath::Sqrt(TMath::Sqrt(detelc*detjet)*((detelc+detjet)/2));
}

