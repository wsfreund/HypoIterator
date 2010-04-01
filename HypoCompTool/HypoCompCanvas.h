#ifndef HYPOCOMPCANVAS_H
#define HYPOCOMPCANVAS_H

#include "../HypoBase.h"
#include "../T2CaCommon.h"
#include "../NeuralCommon.h"
#include <string>
#include <TH2F.h>
#include <TPad.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TList.h>
#include "TROOT.h"
#include <TString.h>
#include <TColor.h>
#include <TPaveText.h>
#include <iostream>

class HypoCompCanvas {

  T2CaCommon *elcT2caData;
  T2CaCommon *jetT2caData;
  NeuralCommon *elcNeuralData;
  NeuralCommon *jetNeuralData;

  unsigned signalT2caTotal;
  unsigned noiseT2caTotal;
  unsigned signalNeuralTotal;
  unsigned noiseNeuralTotal;

  unsigned signalT2ca;
  unsigned noiseT2ca;
  unsigned signalNeural;
  unsigned noiseNeural;

  float detRateT2ca;
  float faRateT2ca;
  float detRateNeural;
  float faRateNeural;

  float spProductT2ca;
  float spProductNeural;
  
  TTree *elcCompTree;
  TTree *jetCompTree;

  TCanvas *hypoCompCanvas; 
  TCanvas *infoCanvas; 
  TPad *th2Pads;
  TPad *outGraphs;
  
  const bool useTestOnly;
  const int testDivisionFactor;

  TH2F *scatterPlot;
  TH2F *spPlot;

  int exec();

  public:  

  int ScatterPlot();
  int HypoOutGraphs();
  int InfoPad();
  int Draw();

  HypoCompCanvas(HypoBase *hypo1, HypoBase *hypo2, const bool usetestonly = true, const int testDivisionFactor = 3);
  HypoCompCanvas(HypoBase *hypo1, HypoBase *hypo2, HypoBase *hypo3, HypoBase *hypo4, const bool usetestonly = true, const int testDivisionFactor = 3);

  ~HypoCompCanvas();

};



#endif
