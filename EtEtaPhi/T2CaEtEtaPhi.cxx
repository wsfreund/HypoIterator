#include "T2CaEtEtaPhi.h"

T2CaEtEtaPhi::T2CaEtEtaPhi(std::string &rPath, unsigned user_nRegions, std::string &userDataLabel):
    T2CaloCommon(rPath),
    NREGIONS(user_nRegions),
    dataLabel(userDataLabel){

    etaxEficGraph = new HypoErrorsGraph(-2.5, 2.5, extraVariables, "T2CaEta", "T2CaDec", NREGIONS, dataLabel, "T2CaEfic x Eta");
    phixEficGraph = new HypoErrorsGraph(-TMath::Pi(), TMath::Pi(), extraVariables, "T2CaPhi", "T2CaDec", NREGIONS, dataLabel, "T2CaEfic x Phi");
    etxEficGraph = new HypoErrorsGraph(10e3, 80e3, extraVariables, "T2CaEt", "T2CaDec", NREGIONS, dataLabel, "T2CaEfic x Et");

}

HypoBase::CODE T2CaEtEtaPhi::DrawEficVs(const std::string &vsWho, const std::string &opt){

    if ( vsWho == "eta")
        etaxEficGraph->Draw(opt);
    else if (vsWho == "phi")
        phixEficGraph->Draw(opt);
    else if (vsWho == "et")
        etxEficGraph->Draw(opt);

    return HypoBase::OK;

}



