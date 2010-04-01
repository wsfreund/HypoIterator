#include "HypoVarHist.h"

HypoVarHist::HypoVarHist(const unsigned nBins, const float xLow, const float xHi, const Color_t userColor, const std::string &userDataLabel, const std::string varName, const float userStatsPosBegin, const float userStatsPosEnd):
dataLabel(userDataLabel),
color(userColor),
statsPosBegin(userStatsPosBegin),
statsPosEnd(userStatsPosEnd)
{
    std::string legend = varName;
    if (varName == "E_{T}")
      legend = "Transverse Energy (GeV)";
    if (varName == "HAD E_{T}")
      legend = "Hadronic Transverse Energy";
    
    hist = new TH1F(dataLabel.c_str(), (varName + " Distribution;"+legend).c_str(), nBins, xLow, xHi);
    hist->SetLineColor(color);
    
    hist->SetStats(true);
}

int HypoVarHist::Draw(const std::string method, bool scaled){
    if(scaled){  
        hist->Scale(1/hist->Integral()*100);
    }
    hist->Draw(method.c_str());
    gPad->Update();
    histStats = (TPaveStats*)hist->GetListOfFunctions()->FindObject("stats");
    if (histStats){
      histStats->SetX1NDC(statsPosBegin); histStats->SetX2NDC(statsPosEnd);
      histStats->SetTextColor(color);
      histStats->Draw();
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
