#ifndef RELEFFICCANVAS_H
#define RELEFFICCANVAS_H

#include <typeinfo>
#include "RelEfficBase.h"
#include "T2CaRelEffic.h"
//#include "NeuralRelEffic.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TMath.h"
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
        if (relCanvas!=0){
            relCanvas->Close();
            delete relCanvas;
        }
    }

};


#endif
