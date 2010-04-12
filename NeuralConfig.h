#ifndef NEURALCONFIG_H
#define NEURALCONFIG_H


#include <string.h>

struct neuralConfig {
  int ROISIZE;
  float threshold;
  unsigned int *NODESVECTOR;
  float *WEIGHTVECTOR;
  float *BIASVECTOR;
  unsigned int sizeNode;
  unsigned int sizeWeight;
  unsigned int sizeBias;
  neuralConfig(){ ROISIZE = 100; NODESVECTOR = 0; WEIGHTVECTOR = 0; BIASVECTOR = 0;}
  ~neuralConfig(){ if (NODESVECTOR) delete [] NODESVECTOR; if (WEIGHTVECTOR) delete [] WEIGHTVECTOR; if (BIASVECTOR) delete [] BIASVECTOR; }
};

struct norm1: public neuralConfig{
  norm1();
};

#endif
