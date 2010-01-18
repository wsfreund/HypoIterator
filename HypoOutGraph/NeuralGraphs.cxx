#include "NeuralGraphs.h"


NeuralGraphs::NeuralGraphs(const std::string &stringPath, const std::string &userDataLabel):
Graphs(stringPath, userDataLabel){

    rings           =       new std::vector<float>;
    neuralAns       =       new std::vector<float>;


    fillConfigVectors();


    neuralRinger    =       new Neural( nodesVector, weightVector, biasVector);


    readChain->SetBranchStatus("Ringer_Rings",     true);
	readChain->SetBranchStatus("Ringer_LVL2_Eta",  true);
	readChain->SetBranchStatus("Ringer_LVL2_Phi",  true);
	readChain->SetBranchStatus("Ringer_LVL2_Et",   true);



    readChain->SetBranchAddress("Ringer_Rings",      &rings);
    readChain->SetBranchAddress("Ringer_LVL2_Eta",   &lvl2_eta);       
    readChain->SetBranchAddress("Ringer_LVL2_Phi",   &lvl2_phi);       
	readChain->SetBranchAddress("Ringer_LVL2_Et",	 &et);


}



Graphs::CODE NeuralGraphs::fillConfigVectors(){

    if (DEBUG) std::cout<<"Dando fill nos config vectors"<<std::endl;

    for(unsigned int i=0;i<(sizeof(NODESVECTOR)/sizeof(unsigned int));++i){
            nodesVector.push_back(NODESVECTOR[i]);
    }
    for(unsigned int i=0;i<(sizeof(WEIGHTVECTOR)/sizeof(float));++i){
            weightVector.push_back(WEIGHTVECTOR[i]);
    }
    for(unsigned int i=0;i<(sizeof(BIASVECTOR)/sizeof(float));++i){
            biasVector.push_back(BIASVECTOR[i]);
    }

    return Graphs::OK;

}

Graphs::CODE NeuralGraphs::exec(){

	int nEvents	= static_cast<int>(readChain->GetEntries());

    if (DEBUG) std::cout<<"Iniciado execute"<<std::endl;

    if (DEBUG) std::cout<<"nEvents = "<<nEvents<<std::endl;    

	for(int i = 0; i<nEvents; ++i){

        if (DEBUG) std::cout<<"------------"<<std::endl;

		readChain->GetEntry(i);
 
        if (DEBUG) std::cout<<"Lida a entrada "<<i<<std::endl;

        if (DEBUG) std::cout<<"lvl2_eta size "<<lvl2_eta->size()<<std::endl;

        for(size_t j=0; j<lvl2_eta->size(); ++j){

            std::vector<float> roiInput;

            if (DEBUG) std::cout<<"Separando os rings em conjuntos de 100"<<std::endl;

            for(size_t k=( ((rings->size()*(j) ) / (lvl2_eta->size())) ); k<( ((rings->size()*(j+1) ) / (lvl2_eta->size())) ); ++k)
                roiInput.push_back(rings->at(k));
            
            if (DEBUG) std::cout<<"Propagando"<<std::endl;

            float roiAns = neuralRinger->propagate(roiInput);

            if (DEBUG) std::cout<<"Copiando a resposta"<<std::endl;

            neuralAns->push_back(roiAns);

            roiInput.clear();

        }

        if (DEBUG) std::cout<<"Entrada "<<i<<" concluida com sucesso"<<std::endl;

        if (DEBUG) std::cout<<"------------"<<std::endl;

    }

	return Graphs::OK;

}
            
        

Graphs::CODE NeuralGraphs::draw_netAns(){

    TH1F *hNans = new TH1F("NeuralNetworkOutput", "L2 Calo Neural Network Output", 220, -1.1, 1.1);
    hNans -> GetXaxis() -> SetTitle("OutPut Neuron Value");

    if (dataLabel == "electrons") {
        hNans->SetLineColor(kBlue);
    }else{
        hNans->SetLineColor(kRed);
    }


	for(size_t i=0; i<neuralAns->size();++i){
        hNans->Fill(neuralAns->at(i));
    }

    hNans->Draw();

    return Graphs::OK;

}

Graphs::CODE NeuralGraphs::draw_netAns(std::string input){

    TH1F *hNans = new TH1F("NeuralNetworkOutput", "L2 Calo Neural Network Output", 220, -1.1, 1.1);
    hNans -> GetXaxis() -> SetTitle("OutPut Neuron Value");

    if (dataLabel == "electrons") {
        hNans->SetLineColor(kBlue);
    }else{
        hNans->SetLineColor(kRed);
    }


	for(size_t i=0; i<neuralAns->size();++i){
        hNans->Fill(neuralAns->at(i));
    }

    hNans->Draw(input.c_str());

    return Graphs::OK;

}



NeuralGraphs::~NeuralGraphs(){

    delete rings;
    delete neuralRinger;

}
