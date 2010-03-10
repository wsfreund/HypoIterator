#include "T2CaRelEffic.h"

T2CaRelEffic::T2CaRelEffic(const std::string &rPath, unsigned user_nRegions):
    T2CaCommon(rPath),
    RelEfficBase(user_nRegions){

}

int T2CaRelEffic::DrawEfficVs(const std::string &vsWho, const std::string &opt){

    if ( vsWho == "eta"){
        if (etaxEfficGraph)
          delete etaxEfficGraph;
        etaxEfficGraph = new HypoErrorsGraph(-2.5, 2.5, static_cast<HypoBase*>(this), std::string("T2CaEta"),NREGIONS, std::string("T2CaEfic x Eta"));
        etaxEfficGraph->Draw(opt);
    }else if (vsWho == "phi"){
        if (phixEfficGraph)
          delete phixEfficGraph;
        phixEfficGraph = new HypoErrorsGraph(-TMath::Pi(), TMath::Pi(), static_cast<HypoBase*>(this), std::string("T2CaPhi"), NREGIONS, std::string("T2CaEfic x Phi"));
        phixEfficGraph->Draw(opt);
    }else if (vsWho == "et"){
        if (etxEfficGraph)
          delete etxEfficGraph;
        etxEfficGraph = new HypoErrorsGraph(10, 80, static_cast<HypoBase*>(this), std::string("T2CaEt"),NREGIONS, std::string("T2CaEfic x Et"));
        etxEfficGraph->Draw(opt);
    }else if (vsWho == "all"){
        if (etaxEfficGraph)
          delete etaxEfficGraph;
        if (phixEfficGraph)
          delete phixEfficGraph;
        if (etxEfficGraph)
          delete etxEfficGraph;
        etaxEfficGraph = new HypoErrorsGraph(-2.5, 2.5, static_cast<HypoBase*>(this), std::string("T2CaEta"),NREGIONS, std::string("T2CaEfic x Eta"));
        TCanvas *etaEffic = new TCanvas("Efficiency x Eta","Efficiency x Eta");
        etaxEfficGraph->Draw(opt);
        etxEfficGraph = new HypoErrorsGraph(10, 80, static_cast<HypoBase*>(this), std::string("T2CaEt"),NREGIONS, std::string("T2CaEfic x Et"));
        TCanvas *phiEffic = new TCanvas("Efficiency x Phi","Efficiency x Phi");
        phixEfficGraph->Draw(opt);
        etxEfficGraph = new HypoErrorsGraph(10, 80, static_cast<HypoBase*>(this), std::string("T2CaEt"),NREGIONS, std::string("T2CaEfic x Et"));
        TCanvas *etEffic = new TCanvas("Efficiency x Et","Efficiency x Et");
        etxEfficGraph->Draw(opt);
    }
    return 0;

}




T2CaRelEffic::~T2CaRelEffic(){

  if (etaxEfficGraph)
    delete etaxEfficGraph;
  if (phixEfficGraph)
    delete phixEfficGraph;
  if (etxEfficGraph)
    delete etxEfficGraph;

}
