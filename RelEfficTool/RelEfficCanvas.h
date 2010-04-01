#ifndef RELEFFICCANVAS_H
#define RELEFFICCANVAS_H

#include "RelEfficBase.h"
#include "T2CaRelEffic.h"
#include "NeuralRelEffic.h"
#include "TCanvas.h"
#include <string>
#include "TPad.h"
#include "TVirtualPad.h"
#include "TMath.h"
#include "TPaveText.h"
#include "TString.h"
#include "TLatex.h"
#include "TROOT.h"
#include "TLegend.h"

class RelEfficCanvas {

    // data:
    TCanvas *relCanvas;
    TCanvas *infoCanvas;
    TLegend *legend;
    TPaveText *pt;
    TPaveText *hypoPt;
    RelEfficBase *relEfficData;
    RelEfficBase *relEffic1;
    RelEfficBase *relEffic2;
    TH1F *th1EtaPad;
    TH1F *th1PhiPad;
    TH1F *th1EtPad;

    // Functions:
    TH1F* drawWithProperties(const std::string &var, RelEfficBase *&relEfficData, const std::string &title, 
        const float &xLow, const float &xHi, const std::string &xlabel, const std::string &ylabel, const float &xOffSet = .55, 
        const float &xSize = .08, const float &yOffSet = .6, const float &ySize = 0.06, const float &yLow = 0, const float &yHi = 100);
    TH1F* drawWithProperties(const std::string &var, RelEfficBase *&relEffic1, RelEfficBase *&relEffic2, 
        Color_t color1, Color_t color2, const std::string &title, const float &xLow, const float &xHi,  
        const std::string &xlabel, const std::string &ylabel, const float &xOffSet = .55, const float &xSize = .08,
        const float &yOffSet = .6, const float &ySize = .06, const float &yLow = 0, const float &yHi = 100);
    int genInfoPad();
    public:

    RelEfficCanvas(RelEfficBase *userRelEfficData);
    RelEfficCanvas(RelEfficBase *userRelEfficElc, RelEfficBase *userRelEfficJet);
    int Draw(const int numPads = 3);
    int setRange(const std::string &var, const float x1, const float x2, const std::string &axis = "X");
    int setRange(const std::string &var, const float x1, const float x2, const float y1, const float y2);

    ~RelEfficCanvas(){
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
      if (pt)
        delete pt;
      if (hypoPt)
        delete hypoPt;
      if (legend)
        delete legend;
    }
};


#endif
