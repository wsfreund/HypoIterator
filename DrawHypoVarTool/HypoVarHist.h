#ifndef HYPOVARHIST_H
#define HYPOVARHIST_H

#include "TH1F.h"
#include "TPaveStats.h"
#include "TList.h"
#include <cstring>
#include "TPad.h"
#include <iostream>
using std::cout;
using std::endl;

class HypoVarHist{

    TH1F *hist;
    TPaveStats *histStats;
    const std::string dataLabel;

public:

    HypoVarHist(const unsigned nBins, const float xLow, const float xHi, const std::string &dataLabel, const std::string varName);
    ~HypoVarHist();
    int Draw(const std::string method = "", bool scaled = true);
    int Fill(float fillValue); 
    double getMaximum() const {return hist->GetMaximum();}

};


#endif
