#ifndef HYPOVARHIST_H
#define HYPOVARHIST_H

#include "TH1F"
#include "TPaveStats.h"
#include "TList.h"
#include <cstring>
#include "TPad.h"

class HypoVarHist{

    TH1F *hist;
    TPaveStats *histStats;

public:

    HypoVarHist(const float xLow, const float xHi, const unsigned nBins, const std::string &dataLabel, const std::varName);
    ~HypoVarHist();
    int Draw(bool scaled);
    int Draw(const std::string method, bool scaled);
    int Fill(float fillValue); 
    double getMaximum() const {return hist->GetMaximum();}

};


#endif
