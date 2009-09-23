#include "NeuralEfic.h"
#include "NeuralEficConfig.h"

NeuralEfic::NeuralEfic(TChain *NeuralChain, TTree *NeuralFillingTree):
Efic(NeuralChain, NeuralFillingTree){

    rings           =       new vector<float>;
    neuralAns       =       new vector<float>;
    lvl1_id         =       new vector<float>;
    roi_id          =       new vector<float>;


    fillConfigVectors();

    neuralFile      =       NULL;
    neuralRinger    =       new Neural( nodesVector, weightVector, biasVector);

    eficReadingChain->SetBranchStatus("Ringer_Rings", 		true);
	eficReadingChain->SetBranchStatus("Ringer_LVL2_Eta", 	true);
	eficReadingChain->SetBranchStatus("Ringer_LVL2_Phi",    true);
	eficReadingChain->SetBranchStatus("Ringer_LVL2_Et",		true);
	eficReadingChain->SetBranchStatus("Ringer_LVL1_Id",		true);
	eficReadingChain->SetBranchStatus("Ringer_Roi_Id",		true);


    eficReadingChain->SetBranchAddress("Ringer_Rings",      &rings);
    eficReadingChain->SetBranchAddress("Ringer_LVL2_Eta",   &lvl2_eta);       
    eficReadingChain->SetBranchAddress("Ringer_LVL2_Phi",   &lvl2_phi);       
	eficReadingChain->SetBranchAddress("Ringer_LVL2_Et",	&et);
	eficReadingChain->SetBranchAddress("Ringer_LVL1_Id",	&lvl1_id);
	eficReadingChain->SetBranchAddress("Ringer_Roi_Id",	    &roi_id);



	eficFillingTree->Branch("Ringer_Out",	    &neuralAns);
	eficFillingTree->Branch("Ringer_Dec",	    &decision);
	eficFillingTree->Branch("Ringer_LVL2_Eta",	&lvl2_eta);
	eficFillingTree->Branch("Ringer_LVL2_Phi",	&lvl2_phi);
	eficFillingTree->Branch("Ringer_LVL2_Et",	&et);
	eficFillingTree->Branch("Ringer_Roi_Id",	&roi_id);
	eficFillingTree->Branch("Ringer_LVL1_Id",	&lvl1_id);


}

NeuralEfic::NeuralEfic(TChain *NeuralChain, TTree *NeuralFillingTree, ofstream *file):
Efic(NeuralChain, NeuralFillingTree){

    rings           =       new vector<float>;
    neuralAns       =       new vector<float>;
    lvl1_id         =       new vector<float>;
    roi_id          =       new vector<float>;

    fillConfigVectors();

    neuralFile      =       file;

    neuralRinger    =       new Neural( nodesVector, weightVector, biasVector);

    eficReadingChain->SetBranchStatus("Ringer_Rings", 		true);
	eficReadingChain->SetBranchStatus("Ringer_LVL2_Eta",   	true);
	eficReadingChain->SetBranchStatus("Ringer_LVL2_Phi",    true);
	eficReadingChain->SetBranchStatus("Ringer_LVL2_Et",		true);
	eficReadingChain->SetBranchStatus("Ringer_LVL1_Id",		true);
	eficReadingChain->SetBranchStatus("Ringer_Roi_Id",		true);


    eficReadingChain->SetBranchAddress("Ringer_Rings",      &rings);
    eficReadingChain->SetBranchAddress("Ringer_LVL2_Eta",   &lvl2_eta);       
    eficReadingChain->SetBranchAddress("Ringer_LVL2_Phi",   &lvl2_phi);       
	eficReadingChain->SetBranchAddress("Ringer_LVL2_Et",	&et);
	eficReadingChain->SetBranchAddress("Ringer_LVL1_Id",	&lvl1_id);
	eficReadingChain->SetBranchAddress("Ringer_Roi_Id",	    &roi_id);


	eficFillingTree->Branch("Ringer_Out",	    &neuralAns);
	eficFillingTree->Branch("Ringer_Dec",	    &decision);
	eficFillingTree->Branch("Ringer_LVL2_Eta",	&lvl2_eta);
	eficFillingTree->Branch("Ringer_LVL2_Phi",	&lvl2_phi);
	eficFillingTree->Branch("Ringer_LVL2_Et",	&et);
	eficFillingTree->Branch("Ringer_Roi_Id",	&roi_id);
	eficFillingTree->Branch("Ringer_LVL1_Id",	&lvl1_id);


}


Efic::CODE NeuralEfic::fillConfigVectors(){

    for(unsigned int i=0;i<(sizeof(NODESVECTOR)/sizeof(unsigned int));++i){
            nodesVector.push_back(NODESVECTOR[i]);
    }
    for(unsigned int i=0;i<(sizeof(WEIGHTVECTOR)/sizeof(float));++i){
            weightVector.push_back(WEIGHTVECTOR[i]);
    }
    for(unsigned int i=0;i<(sizeof(BIASVECTOR)/sizeof(float));++i){
            biasVector.push_back(BIASVECTOR[i]);
    }

    return Efic::OK;

}

Efic::CODE NeuralEfic::exec(){

    for(size_t j=0; j<lvl2_eta->size(); ++j){

        vector<float> roiInput;

        for(size_t k=( ((rings->size()*(j) ) / (lvl2_eta->size())) ); k<( ((rings->size()*(j+1) ) / (lvl2_eta->size())) ); ++k)
            roiInput.push_back(rings->at(k));
        
	if (neuralFile!=NULL) writeMatlabTxt(roiInput);

        float roiAns = neuralRinger->propagate(roiInput);

        neuralAns->push_back(roiAns);
        fillDecision(roiAns);          
        roiInput.clear();
    }

	return Efic::OK;

}
            
        

Efic::CODE NeuralEfic::writeMatlabTxt(const vector<float> &roiInput){

	for(size_t i=0; i<roiInput.size()/ROISIZE;++i){
		for(size_t j=0; j<ROISIZE; j++)
			*neuralFile<<roiInput.at(j+ROISIZE*i)<<" ";
		*neuralFile<<";";
	}	
	
	return Efic::OK;
}

Efic::CODE NeuralEfic::drawNetAns(){

    TH1F *hNans = new TH1F("NeuralNetworkOutput", "L2 Calo Neural Network Output", 220, -1.1, 1.1);
    hNans -> GetXaxis() -> SetTitle("OutPut Neuron Value");

    vector<float> *netAns   =       new vector<float>;
    int nEntries            =       static_cast<int>(eficFillingTree->GetEntries());

	eficFillingTree->SetBranchStatus("RingerOut",	true);
	eficFillingTree->SetBranchAddress("RingerOut",	&netAns);

	for(int i=0; i<nEntries;++i){
	    eficFillingTree->GetEntry(i);
	    for(size_t j=0; j<netAns->size();++j)
            hNans->Fill(netAns->at(j));
    }

    hNans->Draw();

    delete netAns;

    return Efic::OK;

    eficFillingTree->ResetBranchAddresses();

}

Efic::CODE NeuralEfic::fillDecision(const float entry){

    if (entry>threshold) {
            decision->push_back(Efic::ELECTRON);
    }
    else {
            decision->push_back(Efic::JET);
    }

    return Efic::OK;

}

Efic::CODE NeuralEfic::eraseVectors(const size_t index){

    lvl2_eta->erase(lvl2_eta->begin() + index,lvl2_eta->end());
    lvl2_phi->erase( lvl2_phi->begin() + index ,lvl2_phi->end());
    et->erase(et->begin()+index,et->end());
    neuralAns->erase(neuralAns->begin()+index,neuralAns->end());
    decision->erase(decision->begin()+index,decision->end());

    return Efic::OK;

}

Efic::CODE NeuralEfic::swapVectors(const size_t index1, const size_t index2){

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

    return Efic::OK;

}

Efic::CODE NeuralEfic::clearVectors(){

	neuralAns->clear();
	decision->clear();

	return Efic::OK;

}

NeuralEfic::~NeuralEfic(){

    if (neuralFile!=NULL) delete neuralFile;
    delete rings;
    delete neuralAns;
    delete neuralRinger;

}
