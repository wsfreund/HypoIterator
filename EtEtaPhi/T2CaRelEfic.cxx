#include "T2CaRelEfic.h"

T2CaRelEfic::T2CaRelEfic(std::string &rPath, unsigned user_nRegions, std::string &userDataLabel):
    T2CaloCommon(rPath),
    NREGIONS(user_nRegions),
    dataLabel(userDataLabel){

    etaxEficGraph = new HypoErrorsGraph(-2.5, 2.5, static_cast<HypoBase*>(this) , NREGIONS, dataLabel, "T2CaEfic x Eta");
    phixEficGraph = new HypoErrorsGraph(-TMath::Pi(), TMath::Pi(), static_cast<HypoBase*>(this), NREGIONS, dataLabel, "T2CaEfic x Phi");
    etxEficGraph = new HypoErrorsGraph(10e3, 80e3, static_cast<HypoBase*>(this), NREGIONS, dataLabel, "T2CaEfic x Et");

}

HypoBase::CODE T2CaRelEfic::DrawEficVs(const std::string &vsWho, const std::string &opt){

    if ( vsWho == "eta")
        etaxEficGraph->Draw(opt);
    else if (vsWho == "phi")
        phixEficGraph->Draw(opt);
    else if (vsWho == "et")
        etxEficGraph->Draw(opt);
    else if (vsWho == "all"){
        etaxEficGraph->Draw(opt);
        phixEficGraph->Draw(opt);
        etxEficGraph->Draw(opt);
    }
    return HypoBase::OK;

}




T2CaRelEfic::~T2CaRelEfic(){

    delete etaxEficGraph;
    delete phixEficGraph;
    delete etxEficGraph;

}
