#ifndef RELEFFICCANVAS_H
#define RELEFFICCANVAS_H

#include "HypoVarBase.h"
#include "T2CaVarGraph.h"
#include "NeuralVarGraph.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TPaveText.h"
#include "TString.h"
#include "TROOT.h"
#include "iostream"

class HypoVarCanvas {

    protected:
    TCanvas *hypoVarCanvas;
    NeuralVarGraph *neuralVar1;
    NeuralVarGraph *neuralVar2;
    T2CaVarGraph *t2Var1;
    T2CaVarGraph *t2Var2;

    TGraph *grCoreCut;
    TGraph *geRatioCut;
    TGraph *gEtCut;
    TGraph *gHadEtCut;
    TGraph *gNeural;

    bool scaled;

    TFile *file;

    public:

    HypoVarCanvas(HypoVarBase *userHypoVar1, HypoVarBase *userHypoVar2);
    int Draw(bool scaled = true);
    int setRange(const std::string &var, const float x1, const float x2, const std::string &axis = "X");
    int setRange(const int padNumber, const float x1, const float x2, const std::string &axis = "X");
    int setRange(const std::string &var, const float x1, const float x2, const float y1, const float y2);
    int setRange(const int padNumber, const float x1, const float x2, const float y1, const float y2);
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
            if (( hypoVarCanvas = static_cast<TCanvas*>(gROOT->GetListOfCanvases()->FindObject("Hypo Variables Analysis")))){
                hypoVarCanvas->Closed();
                delete hypoVarCanvas;
            }
        }
    }
    

};


#endif
