/*
Neural Network Implementation v3.0
Developed by: Dhiana Deva Cavalcanti Rocha
Contact: dhiana.deva@gmail.com
Laboratorio de Processamento de Sinais
Universidade Federal do Rio de Janeiro
*/

#ifndef NEURAL_H
#define NEURAL_H
#define BAD_WEIGHT_SIZE 101
#define BAD_BIAS_SIZE 102
class Neural {
    std::vector<unsigned int> nodes;
    std::vector<float> input;
    std::vector<float> weight;
    std::vector<float> bias;
    float ***wM;
    float **bM;
    float **mM;
public:
    Neural(const std::vector<unsigned int> &, const std::vector<float> &, const std::vector<float> &);
    ~Neural();
    float propagate(const std::vector<float> &);
};

#endif
