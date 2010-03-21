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
#include "TLegend.h"

class RelEfficCanvas {

    protected:
    TCanvas *relCanvas;
    TCanvas *infoCanvas;
    TLegend *legend;
    RelEfficBase *relEfficData;
    RelEfficBase *relEffic1;
    RelEfficBase *relEffic2;

    float calcSP(float detelc, float detjet);
    public:

    RelEfficCanvas(RelEfficBase *userRelEfficData);
    RelEfficCanvas(RelEfficBase *userRelEfficElc, RelEfficBase *userRelEfficJet);
    int Draw(const int numPads = 4);
    ~RelEfficCanvas(){
        if (legend)
          delete legend;
        if (relCanvas){
            if (gROOT->GetListOfCanvases()->FindObject("Relative Efficiency")){
                relCanvas->Closed();
                delete relCanvas;
            }
        }
        if (infoCanvas){
          if (gROOT->GetListOfCanvases()->FindObject("Analysis Information")){
            infoCanvas->Closed();
            delete infoCanvas;
          }
        }
    }
};


#endif
