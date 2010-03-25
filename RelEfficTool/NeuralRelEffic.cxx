#include "NeuralRelEffic.h"

NeuralRelEffic::NeuralRelEffic(const std::string &chainPath, const neuralConfig &userNeuralConfig,const std::string &userDataLabel, unsigned user_nRegions):
NeuralCommon(chainPath, userNeuralConfig, userDataLabel),
RelEfficBase(user_nRegions){
}


NeuralRelEffic::NeuralRelEffic(const std::string &chainPath, const neuralConfig &userNeuralConfig, const std::string &userDataLabel, const std::string &id, unsigned user_nRegions):
NeuralCommon(chainPath, userNeuralConfig, userDataLabel, id),
RelEfficBase(user_nRegions){
}

int NeuralRelEffic::DrawEfficVs(const std::string &vsWho, const std::string &opt){

    if ( vsWho == "eta"){
        if (etaxEfficGraph)
          delete etaxEfficGraph;
        etaxEfficGraph = new HypoErrorsGraph(-2.5, 2.5, this, std::string("Ringer_LVL2_Eta"),NREGIONS, std::string("NeuralRinger x Eta"));
        etaxEfficGraph->Draw(opt);
    }else if (vsWho == "phi"){
        if (phixEfficGraph)
          delete phixEfficGraph;
        phixEfficGraph = new HypoErrorsGraph(-TMath::Pi(), TMath::Pi(), this, std::string("Ringer_LVL2_Phi"), NREGIONS, std::string("NeuralRinger x Phi"));
        phixEfficGraph->Draw(opt);
    }else if (vsWho == "et"){
        if (etxEfficGraph)
          delete etxEfficGraph;
        etxEfficGraph = new HypoErrorsGraph(10, 80, this, std::string("Ringer_LVL2_Et"),NREGIONS, std::string("NeuralRinger x Et"));
        etxEfficGraph->Draw(opt);
    }else{
      std::cout<<"Option "<<opt<<" doesnt exists!"<<std::endl;
    }

    return 0;

}

int NeuralRelEffic::DrawEfficVs(const std::string &vsWho, const std::string &opt, Color_t color){

    if ( vsWho == "eta"){
        if (etaxEfficGraph)
          delete etaxEfficGraph;
        etaxEfficGraph = new HypoErrorsGraph(-2.5, 2.5, this, std::string("Ringer_LVL2_Eta"),NREGIONS, std::string("NeuralRinger x Eta"));
        etaxEfficGraph->SetColor(color);
        etaxEfficGraph->Draw(opt);
    }else if (vsWho == "phi"){
        if (phixEfficGraph)
          delete phixEfficGraph;
        phixEfficGraph = new HypoErrorsGraph(-TMath::Pi(), TMath::Pi(), this, std::string("Ringer_LVL2_Phi"), NREGIONS, std::string("NeuralRinger x Phi"));
        phixEfficGraph->SetColor(color);
        phixEfficGraph->Draw(opt);
    }else if (vsWho == "et"){
        if (etxEfficGraph)
          delete etxEfficGraph;
        etxEfficGraph = new HypoErrorsGraph(10, 80, this, std::string("Ringer_LVL2_Et"),NREGIONS, std::string("NeuralRinger x Et"));
        etxEfficGraph->SetColor(color);
        etxEfficGraph->Draw(opt);
    }else{
      std::cout<<"Option "<<opt<<" doesnt exists!"<<std::endl;
    }

    return 0;

}


NeuralRelEffic::~NeuralRelEffic(){

  if (etaxEfficGraph)
    delete etaxEfficGraph;
  if (phixEfficGraph)
    delete phixEfficGraph;
  if (etxEfficGraph)
    delete etxEfficGraph;

}
