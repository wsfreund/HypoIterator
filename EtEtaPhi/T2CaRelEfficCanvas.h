#ifndef RELEFFICCANVAS_H
#define RELEFFICCANVAS_H

#include "HypoBase.h"
#include "T2CaRelEffic.h"
//#include "NeuralCaRelEffic.h"
#include "TCanvas.h"
#include "TPaveText.h"
#include "TString.h"

class RelEfficCanvas {

    TCanvas *relCanvas;
    HypoBase *relEfficData;
    HypoBase *relEfficElc;
    HypoBase *relEfficJet;

    public:

    RelEfficCanvas(HypoBase *userRelEfficData):
        relCanvas = new TCanvas("Relative Efficiency", "Relative Efficiency");
        relEfficData = userRelEfficData;
        relEfficElc = 0;
        relEfficJet = 0;
    }
    RelEfficCanvas(HypoBase *userRelEfficElc, HypoBase *userRelEfficJet){
        relCanvas = new TCanvas("Relative Efficiency", "Relative Efficiency");
        relEfficData = 0;
        relEfficElc = userRelEfficElc;
        relEfficJet = userRelEfficJet;
    }
    CODE Draw();
    float calcSP(float detelc, float detjet);
    ~RelEfficCanvas(){
        delete relCanvas;
    }

};




#endif
