#include "HypoVarHist.h"

HypoVarHist::HypoVarHist(const unsigned nBins, const float xLow, const float xHi, const std::string &userDataLabel, const std::string varName):
dataLabel(userDataLabel){
    
    std::string label;

    if (dataLabel == "elc")
        label = "Electrons";
    else if (dataLabel == "pile elc")
        label = "Electrons (Pile-up)";
    else if (dataLabel == "jet")
        label = "Jets";
    else if (dataLabel == "pile elc")
        label = "Jets (Pile-up)";

    hist = new TH1F(label.c_str(), (varName + " Hist").c_str(), nBins, xLow, xHi);
    if ( dataLabel == "elc" || dataLabel == "jet")
        hist->SetLineColor(kBlue);
    if ( dataLabel == "pile elc" || dataLabel == "pile jet")
        hist->SetLineColor(kRed);
    hist->SetStats(true);
}

int HypoVarHist::Draw(const std::string method, bool scaled){
    if(scaled){  
        hist->Scale(1/hist->Integral());
    }
    hist->Draw(method.c_str());
    gPad->Update();
    histStats = (TPaveStats*)hist->GetListOfFunctions()->FindObject("stats");
    if ( dataLabel == "elc" || dataLabel == "jet"){
        if (histStats){
          histStats->SetX1NDC(0.8); histStats->SetX2NDC(0.98);
          histStats->SetTextColor(kBlue);
          histStats->Draw();
        }
    }
    else if ( dataLabel == "pile elc" || dataLabel == "pile jet"){
        if (histStats){
          histStats->SetX1NDC(0.55); histStats->SetX2NDC(0.75);
          histStats->SetTextColor(kRed);
          histStats->Draw();
        }
    }
    gPad->Update();
    return 0;
}

int HypoVarHist::Fill(float fillValue) { 
    hist->Fill(fillValue); 
    return 0;
}

HypoVarHist::~HypoVarHist(){
    delete hist;
}
