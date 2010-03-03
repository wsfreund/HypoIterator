#ifndef HYPOVARBASE_H 
#define HYPOVARBASE_H 

#include <cstring>
#include "TCanvas.h"
#include <iostream>
#include "HypoVarHist.h"

class HypoVarBase {

    public:
    virtual int DrawVar(const std::string &var, const std::string &mode) = 0;

};

#endif
