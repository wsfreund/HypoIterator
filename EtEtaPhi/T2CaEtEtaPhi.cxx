#include "T2CaEtEtaPhi.h"

T2CaEtEtaPhi::T2CaEtEtaPhi(const std::string &rPath,const unsigned int user_nRegions, const std::string &userDataLabel):
    T2CaloCommon(rPath),
    NREGIONS(user_nRegions),
    dataLabel(userDataLabel){

    etaxEficGraph(-2.5,2.5,extraVariables,"T2CaEta", NREGIONS, dataLabel, "T2CaEfic x Eta" );
    phixEficGraph(-TMath::pi, TMath::pi,extraVariables,"T2CaPhi", NREGIONS, dataLabel, "T2CaPhi x Phi" );
    etxEficGraph( 10e3, 80e3,extraVariables,"T2CaEt", NREGIONS, dataLabel, "T2CaEfic x Et");

}

HypoBase::CODE T2CaEtEtaPhi::DrawEficVs(const std::string &vsWho, const std::string &opt){

    if ( vsWho == "eta")
        etaxEficGraph->Draw(opt)
    else if (vsWho == "phi")
        phixEficGraph->Draw(opt)
    else if (vsWho == "et")
        etxEficGraph->Draw(opt)

    return HypoBase::OK;

}



