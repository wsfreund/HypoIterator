#ifndef T2CABASE_H
#define T2CABASE_H

#include "HypoBase.h"

class T2CaBase : virtual public HypoBase{
  public:
  T2CaBase(const std::string &chainPath, const std::string &userDataLabel)
  { 
    HypoBase::baseInit(chainPath, userDataLabel);
  }
  T2CaBase(const std::string &chainPath, const std::string &userDataLabel, const std::string &userId)
  { 
    HypoBase::baseInit(chainPath, userDataLabel, userId);
  }
};

#endif
