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
#include <TROOT.h>
#include <TObject.h>
#include <TString.h>
#include <TColor.h>
#include <TPaveText.h>
#include <TFile.h>
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
  
  TCanvas *hypoCompCanvas; 
  TCanvas *infoCanvas; 
  TPad *scatterPlotPad;
  TPad *spPlotPad;
  TPad *outGraphs1;
  TPad *outGraphs2;
  
  const bool useTestOnly;
  const int testDivisionFactor;

  TH2F *scatterPlot;
  TH2F *spPlot;

  TFile *file;

  int exec();

  public:  

  int DrawScatterPlot();
  int DrawSpPlot();
  int DrawOutGraphs(int padNumber);
  int DrawInfoPad();
  int Draw();

  HypoCompCanvas(HypoBase *hypo1, HypoBase *hypo2, const bool usetestonly = true, const int testDivisionFactor = 3);
  HypoCompCanvas(HypoBase *hypo1, HypoBase *hypo2, HypoBase *hypo3, HypoBase *hypo4, const bool usetestonly = true, const int testDivisionFactor = 3);

  unsigned getSignalT2caTotal() const { return signalT2caTotal;}
  unsigned getNoiseT2caTotal()const { return noiseT2caTotal;}
  unsigned getSignalNeuralTotal()const { return signalNeuralTotal;}
  unsigned getNoiseNeuralTotal() const { return noiseNeuralTotal;}

  unsigned getSignalT2ca() const { return signalT2ca;}
  unsigned getNoiseT2ca() const { return noiseT2ca;}
  unsigned getSignalNeural() const { return signalNeural;} 
  unsigned getNoiseNeural() const { return noiseNeural;}

  float getDetRateT2ca() const { return detRateT2ca;}
  float getFaRateT2ca() const { return faRateT2ca;}
  float getDetRateNeural() const { return detRateNeural;}
  float getFaRateNeural() const { return faRateNeural;}

  ~HypoCompCanvas();

};



#endif
