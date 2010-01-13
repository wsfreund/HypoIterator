#include "Efic.h"
#include "../Neural.h"  
#include "../NeuralConfig.h"
#include <fstream>


#ifndef NEURAL_EFIC
#define NEURAL_EFIC

class NeuralEfic : public Efic {

    enum normalizations {sequential = 0};
    std::vector<float> *rings;
    std::vector<float> *neuralAns;
//    std::vector<int> *lvl1_id;
//    std::vector<int> *roi_id;

    std::vector<unsigned int> nodesVector;
    std::vector<float> weightVector;
    std::vector<float> biasVector;


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
