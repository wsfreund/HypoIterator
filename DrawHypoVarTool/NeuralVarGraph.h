#ifndef NEURALVARGRAPH_H
#define NEURALVARGRAPH_H

#include "../HypoBase.h"
#include "../NeuralCommon.h"
#include "HypoVarBase.h"
#include "HypoVarHist.h"
#include <string>
#include <iostream>
#include "TGraph.h"
#include <TPad.h>
#include "TString.h"
#include "TPaveText.h"

class NeuralVarGraph : public NeuralCommon, public HypoVarBase {

    HypoVarHist *neuralAnsHist;
    CODE initialise();

    public:
    NeuralVarGraph(const std::string &chainPath, const neuralConfig &userNeuralConfig, const std::string &userDataLabel);
    NeuralVarGraph(const std::string &chainPath, const neuralConfig &userNeuralConfig, const std::string &userDataLabel, const std::string &id);
    TH1F* getHist();

    CODE exec();

    int DrawOutput(const std::string &mode="", const bool scaled = true);

    ~NeuralVarGraph();

};

#endif
