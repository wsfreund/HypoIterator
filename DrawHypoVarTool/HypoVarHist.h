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
    const Color_t color;
    const float statsPosBegin;
    const float statsPosEnd;

public:

    HypoVarHist(const unsigned nBins, const float xLow, const float xHi, const Color_t userColor, const std::string &userDataLabel, const std::string varName, const float userStatsPosBegin = 0.83, const float userStatsPosEnd = 0.98);
    ~HypoVarHist();
    int Draw(const std::string method = "", bool scaled = true);
    int Fill(float fillValue); 
    TH1F *getHist() {return hist;}
};


#endif
