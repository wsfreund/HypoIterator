#include "T2CaRelEffic.h"

T2CaRelEffic::T2CaRelEffic(const std::string &rPath, unsigned user_nRegions):
    T2CaCommon(rPath),
    NREGIONS(user_nRegions){
    etaxEficGraph = new HypoErrorsGraph(-2.5, 2.5, static_cast<HypoBase*>(this), std::string("T2CaEta"),NREGIONS, std::string("T2CaEfic x Eta"));
    phixEficGraph = new HypoErrorsGraph(-TMath::Pi(), TMath::Pi(), static_cast<HypoBase*>(this), std::string("T2CaPhi"), NREGIONS, std::string("T2CaEfic x Phi"));
    etxEficGraph = new HypoErrorsGraph(10e3, 80e3, static_cast<HypoBase*>(this), std::string("T2CaEt"),NREGIONS, std::string("T2CaEfic x Et"));

}

HypoBase::CODE T2CaRelEffic::DrawEfficVs(const std::string &vsWho, const std::string &opt){

    if ( vsWho == "eta")
        etaxEficGraph->Draw(opt);
    else if (vsWho == "phi")
        phixEficGraph->Draw(opt);
    else if (vsWho == "et")
        etxEficGraph->Draw(opt);
    else if (vsWho == "all"){
        TCanvas *etaEfic = new TCanvas("Efficiency x Eta","Efficiency x Eta");
        etaxEficGraph->Draw(opt);
        TCanvas *phiEfic = new TCanvas("Efficiency x Phi","Efficiency x Phi");
        phixEficGraph->Draw(opt);
        TCanvas *etEfic = new TCanvas("Efficiency x Et","Efficiency x Et");
        etxEficGraph->Draw(opt);
    }
    return HypoBase::OK;

}




T2CaRelEffic::~T2CaRelEffic(){

    delete etaxEficGraph;
    delete phixEficGraph;
    delete etxEficGraph;

}
