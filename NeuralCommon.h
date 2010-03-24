#ifndef NEURAL_COMMON_H
#define NEURAL_COMMON_H


#include "NeuralBase.h"
#include "Neural.h"  
#include "NeuralConfig.h"
#include <vector>
#include "TH1F.h"
#include "TTree.h"
#include "TChain.h"


class NeuralCommon : public NeuralBase { 

    protected:
    std::vector<float> *rings;
    std::vector<float> *neuralAns;
//    std::vector<int> *lvl1_id;
//    std::vector<int> *roi_id;

    Neural *neuralRinger;
    CODE fillDecision(const float);

    float threshold;

    virtual CODE clearVectors();
    virtual CODE swapVectors(const size_t index1, const size_t index2);
    virtual CODE eraseVectors(const size_t index);
    CODE initialize(const neuralConfig &userNeuralConfig);

    TTree *getExtraVariables(){ 
      return extraVariables;
    } 

    public:
    NeuralCommon(const std::string &chainPath, const neuralConfig &userNeuralConfig, const std::string &userDataLabel);
    NeuralCommon(const std::string &chainPath, const neuralConfig &userNeuralConfig, const std::string &userDataLabel, const std::string &id);
    CODE exec();
    CODE drawNetAns();

    virtual ~NeuralCommon();

};

#endif
