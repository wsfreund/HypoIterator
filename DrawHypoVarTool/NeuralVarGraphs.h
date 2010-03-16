#include "Graphs.h"
#include "TChain.h"
#include "TH1F.h"
#include <cstring>
#include "../Neural.h"  
#include "../NeuralConfig.h"
#include <iostream>


#ifndef NEURAL_GRAPHS
#define NEURAL_GRAPHS

class NeuralGraphs : public Graphs {

    std::vector<float> *rings;
    std::vector<float> *neuralAns;
    std::vector<float> *roiAns;


    std::vector<unsigned int> nodesVector;
    std::vector<float> weightVector;
    std::vector<float> biasVector;


    Neural *neuralRinger;

    CODE fillConfigVectors();

    CODE fillDecision(const float);

    CODE swapVectors(const size_t index1, const size_t index2);
    CODE eraseVectors(const size_t index);

    public:

    NeuralGraphs(const std::string &stringPath,const  std::string &userDataLabel);
    CODE exec();

    CODE draw_netAns();
    CODE draw_netAns(std::string input);

    ~NeuralGraphs();

};

#endif
