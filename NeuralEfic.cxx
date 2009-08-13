#include "NeuralEfic.h"
#include "NeuralEficConfig.h"

NeuralEfic::NeuralEfic(const char *fileName){

        rings           =       new vector<float>;
        neuralAns       =       new vector<float>;

        fillConfigVectors();

        neuralRinger    =       new Neural( nodesVector, weightVector, biasVector);

        readFile = new ifstream(fileName, ios::in | ios::binary);

        if (!readFile) {
                cout<<"Cannot open file"<<endl;
                exit(1);
        }

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

        while (!readFile->eof()){
                float temp;
                readFile->read( (char *) &temp, sizeof(float) );
                rings->push_back(temp);
        }


        cout<<"Rings size"<<rings->size()<<endl;
        cout<<"Number of ROIs"<<rings->size()/100<<endl;
        
        
        for(size_t j=0; j < (rings->size()/100) ; ++j){

                vector<float> roiInput;
                cout<<"Entrou no loop"<<endl;
                for(size_t k=0; k<100; ++k){
                        cout<<"Entrou no loop2"<<endl;
                        roiInput.push_back(rings->front());
                        rings->erase(rings->begin());
                }

                cout<<"Passou o Loop2"<<endl;

                float roiAns = neuralRinger->propagate(roiInput);

                fillDecision(roiAns);          

                roiInput.clear();

        }

        cout<<"Passou o Loop"<<endl;
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

        delete readFile;
}
