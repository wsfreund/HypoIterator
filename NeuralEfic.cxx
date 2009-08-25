#include "NeuralEfic.h"
#include "NeuralEficConfig.h"

NeuralEfic::NeuralEfic(TChain *NeuralChain, TTree *NeuralFillingTree):
Efic(NeuralChain, NeuralFillingTree){

    rings           =       new vector<float>;
    neuralAns       =       new vector<float>;

    fillConfigVectors();

    neuralFile      =       NULL;
    neuralRinger    =       new Neural( nodesVector, weightVector, biasVector);

    eficReadingChain->SetBranchStatus("Ringer_Rings", 		true);
	eficReadingChain->SetBranchStatus("Ringer_LVL2_Eta", 	true);
	eficReadingChain->SetBranchStatus("Ringer_LVL2_Phi",    true);
	eficReadingChain->SetBranchStatus("Ringer_LVL2_Et",		true);


    eficReadingChain->SetBranchAddress("Ringer_Rings",      &rings);
    eficReadingChain->SetBranchAddress("Ringer_LVL2_Eta",   &lvl2_eta);       
    eficReadingChain->SetBranchAddress("Ringer_LVL2_Phi",   &lvl2_phi);       
	eficReadingChain->SetBranchAddress("Ringer_LVL2_Et",	&et);


	eficFillingTree->Branch("RingerOut",	&neuralAns);
	eficFillingTree->Branch("RingerDec",	&decision);
//	eficFillingTree->Branch("RingerLvl1Id",	&lvl1_id);
//	eficFillingTree->Branch("RingerRoiId",	&roi_id);
	eficFillingTree->Branch("RingerEta",	&lvl2_eta);
	eficFillingTree->Branch("RingerPhi",	&lvl2_phi);
	eficFillingTree->Branch("RingerET",	    &et);


}

NeuralEfic::NeuralEfic(TChain *NeuralChain, TTree *NeuralFillingTree, ofstream *file):
Efic(NeuralChain, NeuralFillingTree){

    rings           =       new vector<float>;
    neuralAns       =       new vector<float>;

    fillConfigVectors();

    neuralFile      =       file;

    neuralRinger    =       new Neural( nodesVector, weightVector, biasVector);

    eficReadingChain->SetBranchStatus("Ringer_Rings", 		true);
	eficReadingChain->SetBranchStatus("Ringer_LVL2_Eta",   	true);
	eficReadingChain->SetBranchStatus("Ringer_LVL2_Phi",    true);
	eficReadingChain->SetBranchStatus("Ringer_LVL2_Et",		true);


    eficReadingChain->SetBranchAddress("Ringer_Rings",      &rings);
    eficReadingChain->SetBranchAddress("Ringer_LVL2_Eta",   &lvl2_eta);       
    eficReadingChain->SetBranchAddress("Ringer_LVL2_Phi",   &lvl2_phi);       
	eficReadingChain->SetBranchAddress("Ringer_LVL2_Et",	&et);


	eficFillingTree->Branch("RingerOut",	&neuralAns);
	eficFillingTree->Branch("RingerDec",	&decision);
//	eficFillingTree->Branch("RingerLvl1Id",	&lvl1_id);
//	eficFillingTree->Branch("RingerRoiId",	&roi_id);
	eficFillingTree->Branch("RingerEta",	&lvl2_eta);
	eficFillingTree->Branch("RingerPhi",	&lvl2_phi);
	eficFillingTree->Branch("RingerET",    	&et);


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

        for(size_t k=( ((rings->size()*(j) ) / (lvl2_eta->size())) ); k<( ((rings->size()*(j+1) ) / (lvl2_eta->size())) ); ++k){

                roiInput.push_back(rings->at(k));
        }

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
		for(size_t j=0; j<ROISIZE; j++){

			*neuralFile<<roiInput.at(j+ROISIZE*i)<<" ";
		}
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

		for(size_t j=0; j<netAns->size();++j){

                        hNans->Fill(netAns->at(j));

                }

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

    vector<float>::iterator p;
    vector<int>::iterator p2;
    size_t j;

    for( j=0, p = lvl2_eta->begin(); j<index; ++j, ++p) {};
    lvl2_eta->erase(p,lvl2_eta->end());

    for( j=0, p = lvl2_phi->begin(); j<index; ++j, ++p) {};
    lvl2_phi->erase(p,lvl2_phi->end());

    for( j=0, p = et->begin(); j<index; ++j, ++p) {};
    et->erase(p,et->end());

    for( j=0, p = neuralAns->begin(); j<index; ++j, ++p) {};
    neuralAns->erase(p,neuralAns->end());

    for( j=0, p2 = decision->begin(); j<index; ++j, ++p2) {};
    decision->erase(p2,decision->end());


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

    delete neuralFile;
    delete rings;
    delete neuralAns;
    delete neuralRinger;

}
