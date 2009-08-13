#include "Efic.h"
#include "Neural.h"  
#include <fstream>

#ifndef NEURAL_EFIC
#define NEURAL_EFIC
#define ROISIZE = 100

class NeuralEfic : public Efic {

        vector<float> *rings;
        vector<float> *neuralAns;

        vector<unsigned int> nodesVector;
        vector<float> weightVector;
        vector<float> biasVector;

        ifstream *readFile;

        static const float threshold;

        Neural *neuralRinger;

        CODE fillConfigVectors();

        CODE fillDecision(const float);


	public:

	NeuralEfic(const char *filename);
        
        vector<int>* const &getDecision(){return decision;}

        CODE exec();
        CODE drawNetAns();
        CODE clearVectors();
        CODE swapVectors(const size_t index1, const size_t index2);
        CODE eraseVectors(const size_t index);


        ~NeuralEfic();

};

#endif
