#ifndef RELEFFICCANVAS_H
#define RELEFFICCANVAS_H

#include "RelEfficBase.h"
#include "T2CaRelEffic.h"
//#include "NeuralRelEffic.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TVirtualPad.h"
#include "TMath.h"
#include "TPaveText.h"
#include "TString.h"
#include "TLatex.h"
#include "TROOT.h"

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
        if (relCanvas){
            if (gROOT->GetListOfCanvases()->FindObject("Relative Efficiency")){
                relCanvas->Closed();
                delete relCanvas;
            }
        }
    }

};


#endif