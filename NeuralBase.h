#ifndef NEURALBASE_H
#define NEURALBASE_H

#include "HypoBase.h"

class NeuralBase : virtual public HypoBase{
  public:
  NeuralBase(const std::string &chainPath, const std::string &userDataLabel)
  { 
    HypoBase::baseInit(chainPath, userDataLabel);
  }
  NeuralBase(const std::string &chainPath, const std::string &userDataLabel, const std::string &userId)
  { 
    HypoBase::baseInit(chainPath, userDataLabel, userId);
  }
  //const std::string & getId() const{ return id;}
  //const std::string & getDataLabel() const { return dataLabel; }
};

#endif
