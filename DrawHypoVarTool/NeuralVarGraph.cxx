#include "NeuralVarGraph.h"

NeuralVarGraph::NeuralVarGraph(const std::string &chainPath, const neuralConfig &userNeuralConfig, const std::string &userDataLabel):
NeuralCommon(chainPath, userNeuralConfig, userDataLabel)
{
}
NeuralVarGraph::NeuralVarGraph(const std::string &chainPath, const neuralConfig &userNeuralConfig, const std::string &userDataLabel, const std::string &id):
NeuralCommon(chainPath, userNeuralConfig, userDataLabel, id)
{
}
NeuralVarGraph::~NeuralVarGraph(){
}
