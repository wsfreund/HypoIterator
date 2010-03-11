#ifndef RELEFFICCANVAS_H
#define RELEFFICCANVAS_H

#include "HypoVarBase.h"
#include "T2CaVarGraph.h"
//#include "NeuralRelEffic.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TPaveText.h"
#include "TString.h"
#include "TROOT.h"

class HypoVarCanvas {

    protected:
    TCanvas *hypoVarCanvas;
    HypoVarBase *hypoVarCommon;
    HypoVarBase *hypoVarPile;

    TGraph *grCoreCut;
    TGraph *geRatioCut;
    TGraph *gEtCut;
    TGraph *gHadEtCut;

    bool scaled;

    public:

    HypoVarCanvas(HypoVarBase *hypoVar1, HypoVarBase *hypoVar2);
    int Draw(bool scaled = true);
    ~HypoVarCanvas(){
        if (grCoreCut)
          delete grCoreCut;
        if (geRatioCut)
          delete geRatioCut;
        if (gEtCut)
          delete gEtCut;
        if (gHadEtCut)
          delete gHadEtCut;
        if (hypoVarCanvas){
            if (gROOT->GetListOfCanvases()->FindObject("Hypo Variables Analysis")){
                hypoVarCanvas->Closed();
                delete hypoVarCanvas;
            }
        }
    }
    

};


#endif
