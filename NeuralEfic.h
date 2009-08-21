#include "Efic.h"
#include "Neural.h"  
#include <fstream>

#ifndef NEURAL_EFIC
#define NEURAL_EFIC

#define ROISIZE 100

export class NeuralEfic : public Efic {

        vector<float> *rings;
        vector<float> *neuralAns;

        vector<unsigned int> nodesVector;
        vector<float> weightVector;
        vector<float> biasVector;

        static const float threshold;

        ofstream *neuralFile;

        Neural *neuralRinger;

        CODE fillConfigVectors();

        CODE fillDecision(const float);

	CODE writeMatlabTxt(const vector<float> &roiInput);

	public:

	NeuralEfic(TChain *NeuralChain, TTree *NeuralfillingTree);
	NeuralEfic(TChain *NeuralChain, TTree *NeuralfillingTree, ofstream *file);
    CODE exec();
    CODE drawNetAns();
    CODE clearVectors();
    CODE swapVectors(const size_t index1, const size_t index2);
    CODE eraseVectors(const size_t index);


    ~NeuralEfic();

};

#endif
