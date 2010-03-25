#ifndef NEURALRELEFFIC_H
#define NEURALRELEFFIC_H
#include "../NeuralCommon.h"
#include "RelEfficBase.h"
#include <string>
#include "HypoErrorsGraph.h"
#include "TMath.h"
#include "TCanvas.h"
#include <iostream>

class NeuralRelEffic : public NeuralCommon, public RelEfficBase{

    public:
    NeuralRelEffic(const std::string &chainPath, const neuralConfig &userNeuralConfig, const std::string &userDataLabel, unsigned user_nRegions = 50);
    NeuralRelEffic(const std::string &chainPath, const neuralConfig &userNeuralConfig, const std::string &userDataLabel, const std::string &id, unsigned user_nRegions = 50);
    int DrawEfficVs(const std::string &vsWho, const std::string &opt = "");
    int DrawEfficVs(const std::string &vsWho, const std::string &opt, Color_t color);

    virtual ~NeuralRelEffic();


};


#endif
