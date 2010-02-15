#ifndef RELEFFICCANVAS_H
#define RELEFFICCANVAS_H

#include "RelEfficBase.h"
#include "T2CaRelEffic.h"
//#include "NeuralCaRelEffic.h"
#include "TCanvas.h"
#include "TPaveText.h"
#include "TString.h"

class RelEfficCanvas {

    protected:
    TCanvas *relCanvas;
    RelEfficBase *relEfficData;
    RelEfficBase *relEfficElc;
    RelEfficBase *relEfficJet;

    float calcSP(float detelc, float detjet);
    public:

    RelEfficCanvas(RelEfficBase *userRelEfficData);
    RelEfficCanvas(RelEfficBase *userRelEfficElc, RelEfficBase *userRelEfficJet);
    int Draw();
    ~RelEfficCanvas(){
        delete relCanvas;
    }

};


#endif
