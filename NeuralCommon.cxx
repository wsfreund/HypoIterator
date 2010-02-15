#include "NeuralCommon.h"


NeuralCommon::NeuralCommon(TChain *NeuralChain):
    HypoBase(NeuralChain){

    rings = new std::vector<float>;
    neuralAns = new std::vector<float>;
    //  lvl1_id = new vector<int>;
    //  roi_id = new vector<int>;

    std::vector<unsigned int> nodesVector;
    std::vector<float> weightVector;
    std::vector<float> biasVector;
    for(unsigned int i=0;i<(sizeof(NODESVECTOR)/sizeof(unsigned int));++i)
        nodesVector.push_back(NODESVECTOR[i]);
    for(unsigned int i=0;i<(sizeof(WEIGHTVECTOR)/sizeof(float));++i)
        weightVector.push_back(WEIGHTVECTOR[i]);
    for(unsigned int i=0;i<(sizeof(BIASVECTOR)/sizeof(float));++i)
        biasVector.push_back(BIASVECTOR[i]);
    neuralRinger = new Neural( nodesVector, weightVector, biasVector);

    hypoChain->SetBranchStatus("Ringer_Rings",       true);
    hypoChain->SetBranchStatus("Ringer_LVL2_Eta",    true);
    hypoChain->SetBranchStatus("Ringer_LVL2_Phi",    true);
    hypoChain->SetBranchStatus("Ringer_LVL2_Et",     true);
//  hypoChain->SetBranchStatus("Ringer_LVL1_Id",    true);
//  hypoChain->SetBranchStatus("Ringer_Roi_Id",      true);

    hypoChain->SetBranchAddress("Ringer_Rings",      &rings);
    hypoChain->SetBranchAddress("Ringer_LVL2_Eta",   &lvl2_eta);       
    hypoChain->SetBranchAddress("Ringer_LVL2_Phi",   &lvl2_phi);       
    hypoChain->SetBranchAddress("Ringer_LVL2_Et",    &et);
//  hypoChain->SetBranchAddress("Ringer_LVL1_Id",    &lvl1_id);
//  hypoChain->SetBranchAddress("Ringer_Roi_Id",     &roi_id);

    extraVariables = new TTree("HypoData", "Tree with Hypo data");

    extraVariables->Branch("Ringer_Out",       &neuralAns);
    extraVariables->Branch("Ringer_Dec",       &decision);
    extraVariables->Branch("Ringer_LVL2_Eta",  &lvl2_eta);
    extraVariables->Branch("Ringer_LVL2_Phi",  &lvl2_phi);
    extraVariables->Branch("Ringer_LVL2_Et",   &et);

    exec();

}


HypoBase::CODE NeuralCommon::exec(){

    int n_entries = static_cast<int>(hypoChain->GetEntries());

    for(int i=0; i<n_entries; ++i){
        hypoChain->GetEntry(i);

        for(size_t j=0; j<lvl2_eta->size(); ++j){
            std::vector<float> roiInput;

            for(size_t k=( ((rings->size()*(j) ) / (lvl2_eta->size())) ); k<( ((rings->size()*(j+1) ) / (lvl2_eta->size())) ); ++k)
                roiInput.push_back(rings->at(k));
            float roiAns = neuralRinger->propagate(roiInput);
            neuralAns->push_back(roiAns);
            fillDecision(roiAns);          
            roiInput.clear();
        }
    }
    fillHypoRate();
    return HypoBase::OK;
}

HypoBase::CODE NeuralCommon::drawNetAns(){

    TH1F *hNans = new TH1F("NeuralNetworkOutput", "L2 Calo Neural Network Output", 220, -1.1, 1.1);
    hNans->GetXaxis()->SetTitle("OutPut Neuron Value");
    vector<float> *netAns = new std::vector<float>;
    int nEntries = static_cast<int>(extraVariables->GetEntries());

    for(int i=0; i<nEntries;++i){
        extraVariables->GetEntry(i);
        for(size_t j=0; j<netAns->size();++j)
            hNans->Fill(netAns->at(j));
    }
    hNans->Draw();
    delete netAns;
    return HypoBase::OK;
}

HypoBase::CODE NeuralCommon::fillDecision(const float entry){
    
    ++totalData;
    if (entry>threshold){
        ++detElc;
        decision->push_back(HypoBase::ELECTRON);
    }else{
        ++detJet;
        decision->push_back(HypoBase::JET);
    }
    return HypoBase::OK;
}

HypoBase::CODE NeuralCommon::eraseVectors(const size_t index){

    lvl2_eta->erase(lvl2_eta->begin() + index,lvl2_eta->end());
    lvl2_phi->erase( lvl2_phi->begin() + index ,lvl2_phi->end());
    et->erase(et->begin()+index,et->end());
    neuralAns->erase(neuralAns->begin()+index,neuralAns->end());
    decision->erase(decision->begin()+index,decision->end());
    return HypoBase::OK;

}

HypoBase::CODE NeuralCommon::swapVectors(const size_t index1, const size_t index2){

    float temp;
    temp=lvl2_eta->at(index1);
    lvl2_eta->at(index1)=lvl2_eta->at(index2);
    lvl2_eta->at(index2)=temp;

    temp=lvl2_phi->at(index1);
    lvl2_phi->at(index1)=lvl2_phi->at(index2);
    lvl2_phi->at(index2)=temp;

    temp=et->at(index1);
    et->at(index1)=et->at(index2);
    et->at(index2)=temp;

    temp=neuralAns->at(index1);
    neuralAns->at(index1)=neuralAns->at(index2);
    neuralAns->at(index2)=temp;

    int temp2;
    temp2=decision->at(index1);
    decision->at(index1)=decision->at(index2);
    decision->at(index2)=temp;

//    temp2=lvl1_id->at(index1);
//    lvl1_id->at(index1)=lvl1_id->at(index2);
//    lvl1_id->at(index2)=temp;

//    temp2=roi_id->at(index1);
//    roi_id->at(index1)=roi_id->at(index2);
//    roi_id->at(index2)=temp;

    return HypoBase::OK;

}

HypoBase::CODE NeuralCommon::clearVectors(){

    neuralAns->clear();
    decision->clear();

    return HypoBase::OK;

}

NeuralCommon::~NeuralCommon(){

    if (neuralFile!=NULL) delete neuralFile;

    //    delete lvl1_id;
    //    delete roi_id;
    delete rings;
    delete neuralAns;
    delete neuralRinger;

}
