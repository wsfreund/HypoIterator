#include "NeuralVarGraph.h"

NeuralVarGraph::NeuralVarGraph(const std::string &chainPath, const neuralConfig &userNeuralConfig, const std::string &userDataLabel):
NeuralCommon(chainPath, userNeuralConfig, userDataLabel)
{
  if (dataLabel.find("No") != std::string::npos){
    //do nothing
  } else if (dataLabel.find("NO") != std::string::npos){
    //do nothing
  } else if (dataLabel.find("no") != std::string::npos){
    //do nothing
  } else if (dataLabel == "electrons"){
    //do nothing
  } else if (dataLabel == "Electrons"){
    //do nothing
  } else if (dataLabel == "electron"){
    //do nothing
  } else if (dataLabel == "Electron"){
    //do nothing
  } else if (dataLabel == "elc"){
    //do nothing
  } else if (dataLabel == "jets"){
    //do nothing
  } else if (dataLabel == "Jets"){
    //do nothing
  } else if (dataLabel == "Jet"){
    //do nothing
  } else if (dataLabel == "jet"){
    //do nothing
  } else if (dataLabel.find("pile") != std::string::npos){
    id = "pile-"+id;
  } else if (dataLabel.find("Pile") != std::string::npos){
    id = "pile-"+id;
  } else {
    std::string input;
    while( (input != "yes") && (input != "no") ){
        cout<<"Could not set by ID for pile-up data. Type yes if this data contain pile-up, or no if it does not contain:[yes/no]"<<endl;
        std::getline(std::cin, input);
    }
    if ( input == "yes")
      id = input + "-" + id; 
  }
  cout<<"ID set to: "<<id<<endl;
  if (id=="pile-elc")
    color = kAzure + 1;
  else if(id=="pile-jet")
    color = kMagenta;
  initialise();
}
NeuralVarGraph::NeuralVarGraph(const std::string &chainPath, const neuralConfig &userNeuralConfig, const std::string &userDataLabel, const std::string &id):
NeuralCommon(chainPath, userNeuralConfig, userDataLabel, id)
{
  if (id=="pile-elc")
    color = kAzure + 1;
  else if(id=="pile-jet")
    color = kMagenta;
  else if(id=="elc"){
    //do nothing
  }else if(id=="jet"){
    //do nothing
  }
  initialise();
}

HypoBase::CODE NeuralVarGraph::exec(){

    int n_entries = static_cast<int>(hypoChain->GetEntries());

    for(int i=0; i<n_entries; ++i){
        hypoChain->GetEntry(i);

        for(size_t j=0; j<lvl2_eta->size(); ++j){
            std::vector<float> roiInput;

            for(size_t k=( ((rings->size()*(j) ) / (lvl2_eta->size())) ); k<( ((rings->size()*(j+1) ) / (lvl2_eta->size())) ); ++k)
                roiInput.push_back(rings->at(k));
            float roiAns = neuralRinger->propagate(roiInput);
            neuralAns->push_back(roiAns);

            neuralAnsHist->Fill(neuralAns->at(j));
            
            fillDecision(roiAns);
            roiInput.clear();
        }
        extraVariables->Fill();
        clearVectors();
    }
    fillHypoRate();
    return HypoBase::OK;
}


int NeuralVarGraph::DrawOutput(const std::string &mode, const bool scaled){
  file->cd();
  file->cd(("NeuralRinger Analysis_" + dataLabel).c_str());
  neuralAnsHist->Draw(mode, scaled);
  return 0;
}

TH1F* NeuralVarGraph::getHist(){
  return neuralAnsHist->getHist();
}

inline HypoBase::CODE NeuralVarGraph::initialise(){
  file->cd();
  file->cd(("NeuralRinger Analysis_" + dataLabel).c_str());
  if (id == "elc")
    neuralAnsHist = new HypoVarHist(100, -1.1, 1.1, color, dataLabel, std::string("Neural Answer"));
  else if(id == "pile-elc")
    neuralAnsHist = new HypoVarHist(100, -1.1, 1.1, color, dataLabel, std::string("Neural Answer"), .66, .81);
  else if (id == "jet")
    neuralAnsHist = new HypoVarHist(100, -1.1, 1.1, color, dataLabel, std::string("Neural Answer"), .49, .64);
  else if (id == "pile-jet")
    neuralAnsHist = new HypoVarHist(100, -1.1, 1.1, color, dataLabel, std::string("Neural Answer"), .32, .47);
  return HypoBase::OK;
}

NeuralVarGraph::~NeuralVarGraph(){
  delete neuralAnsHist;
}


