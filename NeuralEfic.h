#include "Efic.h"
#include "Neural.h"  

#ifndef NEURAL_EFIC
#define NEURAL_EFIC


class NeuralEfic : public Efic {

        vector<float> *rings;
        vector<float> *neuralAns;

        vector<unsigned int> nodesVector;
        vector<float> weightVector;
        vector<float> biasVector;

        static const float threshold;

        Neural *neuralRinger;

        CODE fillConfigVectors();

        CODE fillDecision(const float);


	public:

	NeuralEfic(TChain *&NeuralChain, TTree *&NeuralfillingTree);

        CODE exec();
        CODE drawNetAns();
        CODE clearVectors();
        CODE swapVectors(const size_t index1, const size_t index2);
        CODE eraseVectors(const size_t index);


        ~NeuralEfic();

};

#endif
