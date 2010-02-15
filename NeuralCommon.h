#ifndef NEURAL_COMMON
#define NEURAL_COMMON


#include "HypoBase.h"
#include "Neural.h"  
#include "NeuralConfig.h"
#include <vector>
#include "TH1F"
#include "TTree.h"
#include "TChain.h"
#include <iostream>


class NeuralCommon : public HypoBase {

    enum normalizations {sequential = 0};
    std::vector<float> *rings;
    std::vector<float> *neuralAns;
//    std::vector<int> *lvl1_id;
//    std::vector<int> *roi_id;

    Neural *neuralRinger;
    CODE fillDecision(const float);

    CODE clearVectors();
    CODE swapVectors(const size_t index1, const size_t index2);
    CODE eraseVectors(const size_t index);

    public:
    NeuralCommon(TChain *NeuralChain);
    CODE exec();
    CODE drawNetAns();

    ~NeuralEfic();

};

#endif
