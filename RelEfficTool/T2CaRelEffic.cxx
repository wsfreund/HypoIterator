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

  HypoBase::getFile->cd();
    file->cd(("T2Calo Analysis" + dataLabel).c_str());
    if ( vsWho == "eta"){
        if (etaxEfficGraph)
          delete etaxEfficGraph;
        etaxEfficGraph = new HypoErrorsGraph(-2.5, 2.5, this, std::string("T2CaEta"),NREGIONS, std::string("T2CaEfic x Eta"));
        etaxEfficGraph->Draw(opt);
    }else if (vsWho == "phi"){
        if (phixEfficGraph)
          delete phixEfficGraph;
        phixEfficGraph = new HypoErrorsGraph(-TMath::Pi(), TMath::Pi(), this, std::string("T2CaPhi"), NREGIONS, std::string("T2CaEfic x Phi"));
        phixEfficGraph->Draw(opt);
    }else if (vsWho == "et"){
        if (etxEfficGraph)
          delete etxEfficGraph;
        etxEfficGraph = new HypoErrorsGraph(10, 80, this, std::string("T2CaEt"),NREGIONS, std::string("T2CaEfic x Et"));
        etxEfficGraph->Draw(opt);
    }else{
      std::cout<<"Option "<<opt<<" doesnt exists!"<<std::endl;
    }

    return 0;

}

int T2CaRelEffic::DrawEfficVs(const std::string &vsWho, const std::string &opt, Color_t color){

    if ( vsWho == "eta"){
        if (etaxEfficGraph)
          delete etaxEfficGraph;
        etaxEfficGraph = new HypoErrorsGraph(-2.5, 2.5, this, std::string("T2CaEta"),NREGIONS, std::string("T2CaEfic x Eta"));
        etaxEfficGraph->SetColor(color);
        etaxEfficGraph->Draw(opt);
    }else if (vsWho == "phi"){
        if (phixEfficGraph)
          delete phixEfficGraph;
        phixEfficGraph = new HypoErrorsGraph(-TMath::Pi(), TMath::Pi(), this, std::string("T2CaPhi"), NREGIONS, std::string("T2CaEfic x Phi"));
        phixEfficGraph->SetColor(color);
        phixEfficGraph->Draw(opt);
    }else if (vsWho == "et"){
        if (etxEfficGraph)
          delete etxEfficGraph;
        etxEfficGraph = new HypoErrorsGraph(10, 80, this, std::string("T2CaEt"),NREGIONS, std::string("T2CaEfic x Et"));
        etxEfficGraph->SetColor(color);
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
