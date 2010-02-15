#include "T2CaRelEffic.h"

T2CaRelEffic::T2CaRelEffic(const std::string &rPath, unsigned user_nRegions):
    T2CaCommon(rPath),
    RelEfficBase(user_nRegions){
    etaxEfficGraph = new HypoErrorsGraph(-2.5, 2.5, static_cast<HypoBase*>(this), std::string("T2CaEta"),NREGIONS, std::string("T2CaEfic x Eta"));
    phixEfficGraph = new HypoErrorsGraph(-TMath::Pi(), TMath::Pi(), static_cast<HypoBase*>(this), std::string("T2CaPhi"), NREGIONS, std::string("T2CaEfic x Phi"));
    etxEfficGraph = new HypoErrorsGraph(10e3, 80e3, static_cast<HypoBase*>(this), std::string("T2CaEt"),NREGIONS, std::string("T2CaEfic x Et"));

}

int T2CaRelEffic::DrawEfficVs(const std::string &vsWho, const std::string &opt){

    if ( vsWho == "eta")
        etaxEfficGraph->Draw(opt);
    else if (vsWho == "phi")
        phixEfficGraph->Draw(opt);
    else if (vsWho == "et")
        etxEfficGraph->Draw(opt);
    else if (vsWho == "all"){
        TCanvas *etaEffic = new TCanvas("Efficiency x Eta","Efficiency x Eta");
        etaxEfficGraph->Draw(opt);
        TCanvas *phiEffic = new TCanvas("Efficiency x Phi","Efficiency x Phi");
        phixEfficGraph->Draw(opt);
        TCanvas *etEffic = new TCanvas("Efficiency x Et","Efficiency x Et");
        etxEfficGraph->Draw(opt);
    }
    return 0;

}




T2CaRelEffic::~T2CaRelEffic(){

    delete etaxEfficGraph;
    delete phixEfficGraph;
    delete etxEfficGraph;

}
