#include "T2CaRelEfficCanvas.h"

HypoBase::CODE T2CaRelEfficCanvas::Draw(){

    relCanvas->Divide(2,2);
    relCanvas->cd(1);
    if (relEfficData)
        relEfficData->DrawEfficVs("eta", );
    if (relEfficElc && relEfficJet){
        relEfficElc->DrawEfficVs("eta",);
        relEfficJet->DrawEfficVs("eta",)
    }
    gPad->SetEditable(kFALSE);
    relCanvas->cd(2);
    if (relEfficData)
        relEfficData->DrawEfficVs("phi", );
    if (relEfficElc && relEfficJet){
        relEfficElc->DrawEfficVs("phi",);
        relEfficJet->DrawEfficVs("phi",);
    }
    relCanvas->cd(3);
    if (relEfficData)
        relEfficData->DrawEfficVs("et", );
    if (relEfficElc && relEfficJet){
        relEfficElc->DrawEfficVs("et", );
        relEfficElc->DrawEfficVs("et", );
    }
    relCanvas->cd(4);
    TPaveText *pt = new TPaveText(.05,.05,.95,.95);
    if (relEfficData){
        TString line1;
        unsigned totalData = relEfficData->getTotalData();
        float detRate = relEfficData->getDetRate();
        HypoBase* pHypo = dynamic_cast<T2CaRelEfic*>(relEfficData);
        line1.Form("Total Data = %d",totalData);
        if (pHypo){
            TString line1, line2, line3, line4, line5, line6;
            float detrCoreRate = pHypo->getDetrCoreRate();
            float deteRatioRate = pHypo->getDeteRatioRate();
            float detEtRate = pHypo->getDetEtRate();
            float detHadEtRate = pHypo->getDetEtRate();
            std::string dataLabel 
            pHypo->getDataLabel(dataLabel);
            line2.Form("T2Calo Detection Rate = %.4f", detRate);
            line3.Form("rCore Cut Detection Rate = %.4f", detrCoreRate);
            line4.Form("eRatio Cut Detection Rate = %.4f", deteRatioRate);
            line5.Form("Et_{Em} Cut Detection Rate = %.4f", detEtRate);
            line6.Form("Et_{Had} Cut Detection Rate = %.4f", detHadEtRate;);
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
        }
    }else if (relEfficElc && relEfficJet){
        TString line1;
        unsigned totalDataElc = relEfficElc->getTotalData();
        unsigned totalDataJet = relEfficJet->getTotalData();
        float detRateElc = relEfficElc->getDetRate();
        float detRateJet = relEfficJet->getDetRate();
        float totalData = totalDataElc + totalDataJet;
        float effic = calcSP(detRateElc, detRateJet);
        HypoBase* pHypoElc = dynamic_cast<T2CaRelEfic*>(relEfficElc);
        HypoBase* pHypoJet = dynamic_cast<T2CaRelEfic*>(relEfficJet);
        line1.Form("Total Data = %d:Electrons = %d:Jets = %d",totalData, totalDataElc,totalDataJet);
        if (pHypo){
            TString line2, line3, line4, line5, line6, line7;
            float detrCoreRateElc = pHypoElc->getDetrCoreRate();
            float deteRatioRateElc = pHypoElc->getDeteRatioRate();
            float detEtRateElc = pHypoElc->getDetEtRate();
            float detHadEtRateElc = pHypoElc->getDetEtRate();
            float detrCoreRateJet = pHypoJet->getDetrCoreRate();
            float deteRatioRateJet = pHypoJet->getDeteRatioRate();
            float detEtRateJet = pHypoJet->getDetEtRate();
            float detHadEtRateJet = pHypoJet->getDetEtRate();
            float rCoreEffic = calcSP(detrCoreRateElc, detrCoreRateJet);
            float eRatioEffic = calcSP(deteRatioRateElc, deteRatioRateJet);
            float etEffic = calcSP(detEtRateElc, detEtRateJet);
            float hadEtEffic = calcSP(detHadEtRateElc, detHadEtRateJet);
            std::string dataLabel 
            pHypo->getDataLabel(dataLabel);
            line2.Form("T2Calo Efficience = %.4f", effic);
            line3.Form("Electrons Efficience = %.4f", detRateElc);
            TText *p2 = line4.Form("Jets Efficience = %.4f", detRateJet);
            p1->SetTextColor(4);
            p2->SetTextColor(2);
            line4.Form("rCore Cut Efficience = %.4f", rCoreEffic);
            line5.Form("rCore Electron Rate = %.4f", detrCoreRateElc);
            line6.Form("rCore Jet Rate = %.4f", detrCoreRateJet);
            line7.Form("eRatio Cut Efficience = %.4f", deteRatioRate);
            line5.Form("eRatio Electron Rate = %.4f", detrCoreRateElc);
            line6.Form("rCore Jet Rate = %.4f", detrCoreRateJet);
            line5.Form("Et_{Em} Cut Efficience = %.4f", detEtRate);
            line6.Form("Et_{Had} Cut Efficience = %.4f", detHadEtRate;);
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



}

inline float calcSP(float detelc, float detjet){
    return TMath::Sqrt(TMath::Sqrt(detelc*detjet)*((detelc+detjet)/2));
}

