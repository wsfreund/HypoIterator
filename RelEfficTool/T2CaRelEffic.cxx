#include "T2CaRelEffic.h"

T2CaRelEffic::T2CaRelEffic(const std::string &chainPath, const t2ca_00_07_85_conf userL2chain, const std::string &userDataLabel, unsigned user_nRegions):
T2CaCommon(chainPath, userL2chain, userDataLabel),
RelEfficBase(user_nRegions){
}


T2CaRelEffic::T2CaRelEffic(const std::string &chainPath, const t2ca_00_07_85_conf userL2chain, const std::string &userDataLabel, const std::string &id, unsigned user_nRegions):
T2CaCommon(chainPath, userL2chain, userDataLabel, id),
RelEfficBase(user_nRegions){
}

int T2CaRelEffic::DrawEfficVs(const std::string &vsWho, const std::string &opt){

    if ( vsWho == "eta"){
        if (etaxEfficGraph)
          delete etaxEfficGraph;
        etaxEfficGraph = new HypoErrorsGraph(-2.5, 2.5, static_cast<HypoBase*>(this), std::string("T2CaEta"),NREGIONS, std::string("T2CaEfic x Eta"));
        if (id.find("elc") != std::string::npos){
          etaxEfficGraph->getGraph()->SetMarkerSize(0.8);
          etaxEfficGraph->getGraph()->SetLineWidth(0.4);
          etaxEfficGraph->getGraph()->SetLineColor(4);
          etaxEfficGraph->getGraph()->SetMarkerColor(4);
          etaxEfficGraph->getGraph()->SetMarkerStyle(20);
        }
        if (id.find("jet") != std::string::npos){
          etaxEfficGraph->getGraph()->SetMarkerSize(0.8);
          etaxEfficGraph->getGraph()->SetLineWidth(0.4);
          etaxEfficGraph->getGraph()->SetMarkerColor(2);
          etaxEfficGraph->getGraph()->SetLineColor(2);
          etaxEfficGraph->getGraph()->SetMarkerStyle(21);
        }
        etaxEfficGraph->Draw(opt);
    }else if (vsWho == "phi"){
        if (phixEfficGraph)
          delete phixEfficGraph;
        phixEfficGraph = new HypoErrorsGraph(-TMath::Pi(), TMath::Pi(), static_cast<HypoBase*>(this), std::string("T2CaPhi"), NREGIONS, std::string("T2CaEfic x Phi"));
        if (id.find("elc") != std::string::npos){
          phixEfficGraph->getGraph()->SetMarkerSize(0.8);
          phixEfficGraph->getGraph()->SetLineWidth(0.4);
          phixEfficGraph->getGraph()->SetLineColor(4);
          phixEfficGraph->getGraph()->SetMarkerColor(4);
          phixEfficGraph->getGraph()->SetMarkerStyle(20);
        }
        if (id.find("jet") != std::string::npos){
          phixEfficGraph->getGraph()->SetMarkerSize(0.8);
          phixEfficGraph->getGraph()->SetLineWidth(0.4);
          phixEfficGraph->getGraph()->SetMarkerColor(2);
          phixEfficGraph->getGraph()->SetLineColor(2);
          phixEfficGraph->getGraph()->SetMarkerStyle(21);
        }
        phixEfficGraph->Draw(opt);
    }else if (vsWho == "et"){
        if (etxEfficGraph)
          delete etxEfficGraph;
        etxEfficGraph = new HypoErrorsGraph(10, 80, static_cast<HypoBase*>(this), std::string("T2CaEt"),NREGIONS, std::string("T2CaEfic x Et"));
        if (id.find("elc") != std::string::npos){
          etxEfficGraph->getGraph()->SetMarkerSize(0.8);
          etxEfficGraph->getGraph()->SetLineWidth(0.4);
          etxEfficGraph->getGraph()->SetLineColor(4);
          etxEfficGraph->getGraph()->SetMarkerColor(4);
          etxEfficGraph->getGraph()->SetMarkerStyle(20);
        }
        if (id.find("jet") != std::string::npos){
          etxEfficGraph->getGraph()->SetMarkerSize(0.8);
          etxEfficGraph->getGraph()->SetLineWidth(0.4);
          etxEfficGraph->getGraph()->SetMarkerColor(2);
          etxEfficGraph->getGraph()->SetLineColor(2);
          etxEfficGraph->getGraph()->SetMarkerStyle(21);
        }
        etxEfficGraph->Draw(opt);
    }else{
      std::cout<<"Option "<<opt<<" doesnt exists!"<<std::endl;
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
