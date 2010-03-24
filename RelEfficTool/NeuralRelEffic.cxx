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
        cout<<"Beta"<<endl;
        etaxEfficGraph = new HypoErrorsGraph(-2.5, 2.5, static_cast<HypoBase *>(this), std::string("Ringer_LVL2_Eta"),NREGIONS, std::string("NeuralEfic x Eta"));
        cout<<"Beta1"<<endl;
        etaxEfficGraph->Draw(opt);
        cout<<"Beta2"<<endl;
        if (id.find("elc") != std::string::npos){
          cout<<"Beta3"<<endl;
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
    }else if (vsWho == "phi"){
        if (phixEfficGraph)
          delete phixEfficGraph;
        phixEfficGraph = new HypoErrorsGraph(-TMath::Pi(), TMath::Pi(), static_cast<HypoBase *>(this), std::string("Ringer_LVL2_Phi"), NREGIONS, std::string("NeuralEfic x Phi"));
        phixEfficGraph->Draw(opt);
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
    }else if (vsWho == "et"){
        if (etxEfficGraph)
          delete etxEfficGraph;
        etxEfficGraph = new HypoErrorsGraph(10, 80, static_cast<HypoBase *>(this), std::string("Ringer_LVL2_Et"),NREGIONS, std::string("NeuralEfic x Et"));
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




NeuralRelEffic::~NeuralRelEffic(){

  if (etaxEfficGraph)
    delete etaxEfficGraph;
  if (phixEfficGraph)
    delete phixEfficGraph;
  if (etxEfficGraph)
    delete etxEfficGraph;

}
