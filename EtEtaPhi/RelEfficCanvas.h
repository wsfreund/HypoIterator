#ifndef RELEFFICCANVAS_H
#define RELEFFICCANVAS_H

#include "HypoBase.h"
#include "T2CaRelEffic.h"
//#include "NeuralCaRelEffic.h"
#include "TCanvas.h"
#include "TPaveText.h"
#include "TString.h"

class RelEfficCanvas {

    protected:
    enum CODE {ERROR=0, OK};
    TCanvas *relCanvas;
    HypoBase *relEfficData;
    HypoBase *relEfficElc;
    HypoBase *relEfficJet;

    public:

    RelEfficCanvas(HypoBase *userRelEfficData);
    RelEfficCanvas(HypoBase *userRelEfficElc, HypoBase *userRelEfficJet);
    CODE Draw();
    float calcSP(float detelc, float detjet);
    ~RelEfficCanvas(){
        delete relCanvas;
    }

};


#endif
