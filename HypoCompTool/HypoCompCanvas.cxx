#include "HypoCompCanvas.h"

HypoCompCanvas::HypoCompCanvas(HypoBase *hypo1, HypoBase *hypo2, const bool usetestonly, const int testdivisionfactor):
elcT2caData(0),
jetT2caData(0),
elcNeuralData(0),
jetNeuralData(0),
signalT2caTotal(0),
noiseT2caTotal(0),
signalNeuralTotal(0),
noiseNeuralTotal(0),
signalT2ca(0),
noiseT2ca(0),
signalNeural(0),
noiseNeural(0),
detRateT2ca(0),
faRateT2ca(0),
detRateNeural(0),
faRateNeural(0),
spProductT2ca(0),
spProductNeural(0),
elcCompTree(0),
jetCompTree(0),
hypoCompCanvas(0),
infoCanvas(0),
th2Pads(0),
outGraphs(0),
useTestOnly(usetestonly),
testDivisionFactor(testdivisionfactor),
scatterPlot(0),
spPlot(0)
{

  if (hypo1->getId().find("elc")){
    if( !(elcT2caData = dynamic_cast<T2CaCommon*>(hypo1)))
      elcNeuralData = dynamic_cast<NeuralCommon*>(hypo1);
  } else {
    if( !(jetT2caData = dynamic_cast<T2CaCommon*>(hypo1)))
      jetNeuralData = dynamic_cast<NeuralCommon*>(hypo1);
  }
  if (hypo2->getId().find("elc")){
    if( !(elcT2caData = dynamic_cast<T2CaCommon*>(hypo2)))
      elcNeuralData = dynamic_cast<NeuralCommon*>(hypo2);
  } else {
    if( !(jetT2caData = dynamic_cast<T2CaCommon*>(hypo2)))
      jetNeuralData = dynamic_cast<NeuralCommon*>(hypo2);
  }

  if ( (!elcT2caData && !elcNeuralData) || (!jetNeuralData && !jetT2caData) ){
    std::cout<<"HypoCompCanvas need both Hypos with same kind of data to make the comparision"<<std::endl;
    throw;
  }

  if (elcT2caData){
    if (!elcT2caData->getTotalData())
      elcT2caData->exec();
    if (!elcNeuralData->getTotalData())
      elcNeuralData->exec();
    TList elcList;
    elcList.Add(elcT2caData->getExtraVariables());
    elcList.Add(elcNeuralData->getExtraVariables());
    elcCompTree = TTree::MergeTrees(&elcList);
    elcCompTree->SetBranchStatus("*",false);
  }
  else{
    if (!jetT2caData->getTotalData())
      jetT2caData->exec();
    if (!jetNeuralData->getTotalData())
      jetNeuralData->exec();
    TList jetList;
    jetList.Add(jetT2caData->getExtraVariables());
    jetList.Add(jetNeuralData->getExtraVariables());
    jetCompTree = TTree::MergeTrees(&jetList);
    jetCompTree->SetBranchStatus("*",false);
  }


}

HypoCompCanvas::HypoCompCanvas(HypoBase *hypo1, HypoBase *hypo2, HypoBase *hypo3, HypoBase *hypo4, const bool usetestonly, const int testdivisionfactor):
elcT2caData(0),
jetT2caData(0),
elcNeuralData(0),
jetNeuralData(0),
signalT2caTotal(0),
noiseT2caTotal(0),
signalNeuralTotal(0),
noiseNeuralTotal(0),
signalT2ca(0),
noiseT2ca(0),
signalNeural(0),
noiseNeural(0),
detRateT2ca(0),
faRateT2ca(0),
detRateNeural(0),
faRateNeural(0),
spProductT2ca(0),
spProductNeural(0),
elcCompTree(0),
jetCompTree(0),
hypoCompCanvas(0),
infoCanvas(0),
th2Pads(0),
outGraphs(0),
useTestOnly(usetestonly),
testDivisionFactor(testdivisionfactor),
scatterPlot(0),
spPlot(0)
{

  if (hypo1->getId().find("elc")){
    if( !(elcT2caData = dynamic_cast<T2CaCommon*>(hypo1)))
      elcNeuralData = dynamic_cast<NeuralCommon*>(hypo1);
  } else {
    if( !(jetT2caData = dynamic_cast<T2CaCommon*>(hypo1)))
      jetNeuralData = dynamic_cast<NeuralCommon*>(hypo1);
  }
  if (hypo2->getId().find("elc")){
    if( !(elcT2caData = dynamic_cast<T2CaCommon*>(hypo2)))
      elcNeuralData = dynamic_cast<NeuralCommon*>(hypo2);
  } else {
    if( !(jetT2caData = dynamic_cast<T2CaCommon*>(hypo2)))
      jetNeuralData = dynamic_cast<NeuralCommon*>(hypo2);
  }
  if (hypo3->getId().find("elc")){
    if( !(elcT2caData = dynamic_cast<T2CaCommon*>(hypo3)))
      elcNeuralData = dynamic_cast<NeuralCommon*>(hypo3);
  } else {
    if( !(jetT2caData = dynamic_cast<T2CaCommon*>(hypo3)))
      jetNeuralData = dynamic_cast<NeuralCommon*>(hypo3);
  }
  if (hypo4->getId().find("elc")){
    if( !(elcT2caData = dynamic_cast<T2CaCommon*>(hypo4)))
      elcNeuralData = dynamic_cast<NeuralCommon*>(hypo4);
  } else {
    if( !(jetT2caData = dynamic_cast<T2CaCommon*>(hypo4)))
      jetNeuralData = dynamic_cast<NeuralCommon*>(hypo4);
  }

  if ( !elcT2caData || ! jetT2caData || !elcNeuralData || !jetNeuralData ){
    std::cout<<"HypoCompCanvas need both Hypos with both kind of data to make the comparision"<<std::endl;
    throw;
  }

  if (!elcT2caData->getTotalData())
    elcT2caData->exec();
  if (!jetT2caData->getTotalData())
    jetT2caData->exec();
  if (!elcNeuralData->getTotalData())
    elcNeuralData->exec();
  if (!jetNeuralData->getTotalData())
    jetNeuralData->exec();

  TList elcList;
  elcList.Add(elcT2caData->getExtraVariables());
  elcList.Add(elcNeuralData->getExtraVariables());
  TList jetList;
  jetList.Add(jetT2caData->getExtraVariables());
  jetList.Add(jetNeuralData->getExtraVariables());
  elcCompTree = TTree::MergeTrees(&elcList);
  jetCompTree = TTree::MergeTrees(&jetList);

  elcCompTree->SetBranchStatus("*",false);
  jetCompTree->SetBranchStatus("*",false);
  exec();

}


int HypoCompCanvas::exec(){

  std::vector<int> ringerDec;
  std::vector<int> t2CaDec;
  if ( elcCompTree && jetCompTree ){
    //Jets
    jetCompTree->SetBranchStatus("Ringer_Dec", true);
    jetCompTree->SetBranchAddress("Ringer_Dec", &ringerDec);
    jetCompTree->SetBranchStatus("T2CaDec", true);
    jetCompTree->SetBranchAddress("T2CaDec", &t2CaDec);
    int nEntries = static_cast<int>(jetCompTree->GetEntries());
    int pos = 0;
    for( int i = 0; i<nEntries;++i){
      jetCompTree->GetEntry(i);
      for(size_t j=0; j<ringerDec.size();++j){
        if ( useTestOnly && (pos = (pos +1) % testDivisionFactor ) ) 
          continue; // if using only test data
        ++noiseNeuralTotal;
        if ( ringerDec.at(j) == HypoBase::ELECTRON )
          ++noiseNeural;
      }
      for(size_t j=0; j<t2CaDec.size();++j){
        if ( useTestOnly && (pos = (pos +1) % testDivisionFactor ) ) 
          continue; // if using only test data
        ++noiseT2caTotal;
        if ( t2CaDec.at(j) == HypoBase::ELECTRON )
          ++noiseT2ca;
      }
    }
    jetCompTree->ResetBranchAddresses();
    //Electrons
    elcCompTree->SetBranchStatus("Ringer_Dec", true);
    elcCompTree->SetBranchAddress("Ringer_Dec", &ringerDec);
    elcCompTree->SetBranchStatus("T2CaDec", true);
    elcCompTree->SetBranchAddress("T2CaDec", &t2CaDec);
    pos = 0;
    nEntries = static_cast<int>(elcCompTree->GetEntries());
    for( int i = 0; i<nEntries;++i){
      elcCompTree->GetEntry(i);
      for(size_t j=0; j<ringerDec.size();++j){
        if ( useTestOnly && (pos = (pos +1) % testDivisionFactor ) ) 
          continue; // if using only test data
        ++signalNeuralTotal;
        if ( ringerDec.at(j) == HypoBase::ELECTRON )
          ++signalNeural;
      }
      for(size_t j=0; j<t2CaDec.size();++j){
        if ( useTestOnly && (pos = (pos +1) % testDivisionFactor ) ) 
          continue; // if using only test data
        ++signalT2caTotal;
        if ( t2CaDec.at(j) == HypoBase::ELECTRON )
          ++signalT2ca;
      }
    }
    elcCompTree->ResetBranchAddresses();
    detRateT2ca = static_cast<float>(signalT2ca)/static_cast<float>(signalT2caTotal)*100.;
    detRateNeural = static_cast<float>(signalNeural)/static_cast<float>(signalNeuralTotal)*100.;
    faRateT2ca = static_cast<float>(noiseT2ca)/static_cast<float>(noiseT2caTotal)*100.;
    faRateNeural = static_cast<float>(noiseNeural)/static_cast<float>(noiseNeuralTotal)*100.;

    spProductT2ca = calcSP(detRateT2ca, 100. - faRateT2ca);
    spProductNeural = calcSP(detRateNeural, 100. - faRateNeural);

    elcCompTree->SetBranchStatus("*", false);
    jetCompTree->SetBranchStatus("*", false);

  } else {
    TTree *tree = 0;
    tree = elcCompTree;
    if (!tree)
      tree = jetCompTree;
    tree->SetBranchStatus("Ringer_Dec", true);
    tree->SetBranchAddress("Ringer_Dec", &ringerDec);
    tree->SetBranchStatus("T2CaDec", true);
    tree->SetBranchAddress("T2CaDec", &t2CaDec);
    if (tree == elcCompTree){
      int pos = 0;
      int nEntries = static_cast<int>(elcCompTree->GetEntries());
      for( int i = 0; i<nEntries;++i){
        tree->GetEntry(i);
        for(size_t j=0; j<ringerDec.size();++j){
          if ( useTestOnly && (pos = (pos +1) % testDivisionFactor ) ) 
            continue; // if using only test data
          ++signalNeuralTotal;
          if ( ringerDec.at(j) == HypoBase::ELECTRON )
            ++signalNeural;
        }
        for(size_t j=0; j<t2CaDec.size();++j){
          if ( useTestOnly && (pos = (pos +1) % testDivisionFactor ) ) 
            continue; // if using only test data
          ++signalT2caTotal;
          if ( t2CaDec.at(j) == HypoBase::ELECTRON )
            ++signalT2ca;
        }
      }
    }else{
      int pos = 0;
      int nEntries = static_cast<int>(jetCompTree->GetEntries());
      for( int i = 0; i<nEntries;++i){
        tree->GetEntry(i);
        for(size_t j=0; j<ringerDec.size();++j){
          if ( useTestOnly && (pos = (pos +1) % testDivisionFactor ) ) 
            continue; // if using only test data
          ++signalNeuralTotal;
          if ( ringerDec.at(j) == HypoBase::JET )
            ++signalNeural;
        }
        for(size_t j=0; j<t2CaDec.size();++j){
          if ( useTestOnly && (pos = (pos +1) % testDivisionFactor ) ) 
            continue; // if using only test data
          ++signalT2caTotal;
          if ( t2CaDec.at(j) == HypoBase::JET )
            ++signalT2ca;
        }
      }
    }
    tree->ResetBranchAddresses();
    detRateT2ca = static_cast<float>(signalT2ca)/static_cast<float>(signalT2caTotal)*100.;
    detRateNeural = static_cast<float>(signalNeural)/static_cast<float>(signalNeuralTotal)*100.;
  }

  return 0;

}


int HypoCompCanvas::ScatterPlot(){

  if ( elcCompTree && jetCompTree ){
    TVirtualPad *hyposComp = gPad->cd();
    hyposComp->Divide(2,1);
    // Detection and False Alarm:
    hyposComp->cd(1);
    scatterPlot = new TH2F("ScatterPlot", "Hypotesis Algorythms Comparision; Hypo; Merit; Rates (%)", 2, -2, 2, 2, -2, 2);
    scatterPlot->SetOption("lego2 cg(1)");

    scatterPlot->SetBinContent(1, faRateT2ca   );
    scatterPlot->SetBinContent(2, faRateNeural );
    scatterPlot->SetBinContent(3, detRateT2ca  );
    scatterPlot->SetBinContent(4, faRateNeural );

    scatterPlot->GetXaxis()->SetBinLabel(1,"T2Calo");
    scatterPlot->GetXaxis()->SetBinLabel(2,"Neural Ringer");
    scatterPlot->GetXaxis()->CenterTitle();
    scatterPlot->GetYaxis()->SetBinLabel(1,"False Alarm");
    scatterPlot->GetYaxis()->SetBinLabel(2,"Detection");
    scatterPlot->GetYaxis()->CenterTitle();

    gPad->SetTheta(10);
    gPad->SetPhi(0);
    SetPallete("",99);
    scatterPlot->SetStats(kFALSE);
    scatterPlot->Draw();
    // SP Product:
    hyposComp->cd(2);
    spPlot = new TH2F("spPlot", "Hypotesis Algorythms SP Product; Hypo; Product SP; Rates (%)", 2, -2, 2, 1, -1, 1);
    spPlot->SetOption("lego2 cg(1)");

    spPlot->SetBinContent(1, spProductT2ca);
    spPlot->SetBinContent(2, spProductNeural);

    spPlot->GetXaxis()->SetBinLabel(1,"T2Calo");
    spPlot->GetXaxis()->SetBinLabel(2,"Neural Ringer");
    spPlot->GetXaxis()->CenterTitle();
    spPlot->GetYaxis()->SetBinLabel(1,"");
    spPlot->GetYaxis()->CenterTitle();

    hyposComp->SetTheta(10);
    hyposComp->SetPhi(0);
    SetPallete("",99);
    spPlot->SetStats(kFALSE);
    spPlot->Draw();

  } else {

    scatterPlot = new TH2F("ScatterPlot", "Hypotesis Algorythms Comparision; Hypo; Merit; Rates (%)", 2, -2, 2, 1, -1, 1);
    scatterPlot->SetOption("lego2 cg(1)");

    scatterPlot->SetBinContent(1, detRateT2ca   );
    scatterPlot->SetBinContent(2, detRateNeural );

    scatterPlot->GetXaxis()->SetBinLabel(1,"T2Calo");
    scatterPlot->GetXaxis()->SetBinLabel(2,"Neural Ringer");
    scatterPlot->GetXaxis()->CenterTitle();
    if (elcCompTree)
      scatterPlot->GetYaxis()->SetBinLabel(1,"Electrons Detection Rate");
    else
      scatterPlot->GetYaxis()->SetBinLabel(1,"Jets Detection Rate");
    scatterPlot->GetYaxis()->CenterTitle();

    gPad->SetTheta(10);
    gPad->SetPhi(0);
    SetPallete("",99);
    scatterPlot->SetStats(kFALSE);
    scatterPlot->Draw();

  }

  return 0;

}

int HypoCompCanvas::InfoPad(){

  TPaveText *pt = new TPaveText(.05,.05,.95,.95);
  if (elcCompTree && jetCompTree){
    TString line1, line2, line3, line4, line5, line6, line7;
    if ( signalT2caTotal == signalNeuralTotal && noiseT2caTotal == noiseNeuralTotal)
      line1.Form("Total Data = %d : #color[4]{Electrons = %d} : #color[2]{Jets = %d}", signalNeuralTotal + noiseNeuralTotal, signalNeuralTotal, noiseNeuralTotal );
    else
      line1.Form("Total Data T2Calo = %d | Total Data NeuralRinger = %d", signalT2caTotal + noiseT2caTotal, signalNeuralTotal + noiseNeuralTotal);
    line2.Form("#scale[1.05]{T2Calo SP Product = %.4f%%}", spProductT2ca );
    line3.Form("#color[4]{#scale[1]{Det Rate = %.4f%%}}", detRateT2ca );
    line4.Form("#color[2]{#scale[1]{FA = %.4f%%}}", faRateT2ca );
    line5.Form("#scale[1.05]{NeuralRinger SP Product = %.4f%%}", spProductNeural );
    line6.Form("#color[4]{#scale[1]{Det Rate = %.4f%%}}", detRateNeural );
    line7.Form("#color[2]{#scale[1]{FA = %.4f%%}}", faRateNeural );
    pt->SetTextAlign(22);
    pt->AddText(line1);
    float y = 0.90; const float yDecrement = (.90 - .05)/4; float x1 = 0.2; float x2 = 0.4; float x3 = 0.6;
    pt->AddText(x2, y, line2);  y-=yDecrement;
    pt->AddText(x1, y, line3);
    pt->AddText(x3, y, line4);  y-=yDecrement;
    pt->AddText(x2, y, line5);  y-=yDecrement;
    pt->AddText(x1, y, line6);
    pt->AddText(x3, y, line7); 
    TString line666("Signal Processing Laboratory - COPPE/UFRJ");
    TText *p1 = pt->AddText(0.4, 0.02, line666);
    p1->SetTextSize(0.04);
    p1->SetTextSize(0.04);
    p1->SetTextSize(0.04);
    p1->SetTextSize(0.04);
    p1->SetTextSize(0.04);
    p1->SetTextSize(0.04);
    p1->SetTextSize(0.04);
  } else {
    TString line1, line2, line3, line4, line5, line6, line7, line8, line9;
    if ( signalT2caTotal == signalNeuralTotal ){
      if (elcCompTree)
        line1.Form("#color[4]{Electrons = %d} ", signalT2caTotal);
      else
        line1.Form("#color[2]{Jets = %d}", signalNeuralTotal);
    } else {
      if (elcCompTree)
        line1.Form("#color[4]{T2Calo Electrons = %d : NeuralRinger Electrons = %d } ", signalT2caTotal, signalNeuralTotal);
      else
        line1.Form("#color[2]{T2Calo Jets = %d : NeuralRinger Jets = %d } ", signalT2caTotal, signalNeuralTotal);
    }
    if (elcCompTree){
      line2.Form("#color[4]{#scale[1.05]{T2Calo Electrons Detection Rate = %.4f%%}}", detRateT2ca);
      line3.Form("#color[4]{#scale[1.05]{NeuralRinger Electrons Detection Rate = %.4f%%}", detRateNeural );
    } else {
      line2.Form("#color[2]{#scale[1.05]{T2Calo Jets Detection Rate = %.4f%%}}", detRateT2ca );
      line3.Form("#color[2]{#scale[1.05]{NeuralRinger Jets Detection Rate = %.4f%%}}", detRateNeural );
    }
    pt->SetTextAlign(22);
    pt->AddText(line1);
    pt->AddText(line2);
    pt->AddText(line3);
    TString line666("Signal Processing Laboratory - COPPE/UFRJ");
    TText *p1 = pt->AddText(0.4, 0.02, line666);
    p1->SetTextSize(0.04);
  }

  pt->SetLabel("Hypotesis Comparison Tool");
  pt->Draw();

  return 0;

}


int HypoCompCanvas::HypoOutGraphs(){

  if (elcCompTree && jetCompTree){
    TVirtualPad* outGraphs = gPad->cd();
    outGraphs->Divide(2,1);
    // T2Calo Out:
    outGraphs->cd(1);
    elcT2caData->DrawCutCounter();
    jetT2caData->DrawCutCounter("sames");
    outGraphs->cd(2);
    elcNeuralData->drawNetAns();
    jetNeuralData->drawNetAns("sames");
  } else {
    TVirtualPad* outGraphs = gPad->cd();
    outGraphs->Divide(2,1);
    // T2Calo Out:
    outGraphs->cd(1);
    if (elcT2caData)
      elcT2caData->DrawCutCounter();
    else
      jetT2caData->DrawCutCounter();
    outGraphs->cd(2);
    if (elcNeuralData)
      elcNeuralData->drawNetAns();
    else
      jetNeuralData->drawNetAns();
  }

  return 0;
}

int HypoCompCanvas::Draw(){

  hypoCompCanvas = new TCanvas("Hypotesys Comparision Analysis", "Hypotesis Comparision Analyisis");
  th2Pads = new TPad("TH2Pads", "Hypotesys Comparision", 0.2, 0.26, .98, .99, 18);
  th2Pads->cd();
  ScatterPlot();
  outGraphs = new TPad("OutGraphs", "Out Graphics", 0.2, 0.01, .98, .25, 18);
  outGraphs->cd();
  HypoOutGraphs();

  infoCanvas = new TCanvas("Analysis Info", "Analysis Info");
  InfoPad();

  return 0;

}




HypoCompCanvas::~HypoCompCanvas(){

  if (infoCanvas){
    if (gROOT->GetListOfCanvases()->FindObject("Analysis Info")){
      infoCanvas->Closed();
      delete infoCanvas;
    }
  }
  if (hypoCompCanvas){
    if (gROOT->GetListOfCanvases()->FindObject("Hypotesys Comparision Analysis")){
      hypoCompCanvas->Closed();
      delete hypoCompCanvas;
    }
  }
  if (scatterPlot)
    delete scatterPlot;
  if (spPlot)
    delete spPlot;
  if (th2Pads)
    delete th2Pads;
  if (outGraphs)
    delete outGraphs;

}
