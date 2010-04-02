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
hypoCompCanvas(0),
infoCanvas(0),
scatterPlotPad(0),
spPlotPad(0),
outGraphs1(0),
outGraphs2(0),
useTestOnly(usetestonly),
testDivisionFactor(testdivisionfactor),
scatterPlot(0),
spPlot(0),
file(0)
{

  if (hypo1->getId().find("elc") != std::string::npos){
    if( !elcT2caData)
      elcT2caData = dynamic_cast<T2CaCommon*>(hypo1);
    else if (!elcNeuralData)
      elcNeuralData = dynamic_cast<NeuralCommon*>(hypo1);
  } else {
    if (!jetT2caData)
      jetT2caData = dynamic_cast<T2CaCommon*>(hypo1);
    else if (!jetNeuralData)
      jetNeuralData = dynamic_cast<NeuralCommon*>(hypo1);
  }

  if (hypo2->getId().find("elc") != std::string::npos){
    if( !elcT2caData)
      elcT2caData = dynamic_cast<T2CaCommon*>(hypo2);
    else if (!elcNeuralData)
      elcNeuralData = dynamic_cast<NeuralCommon*>(hypo2);
  } else {
    if (!jetT2caData)
      jetT2caData = dynamic_cast<T2CaCommon*>(hypo2);
    else if (!jetNeuralData)
      jetNeuralData = dynamic_cast<NeuralCommon*>(hypo2);
  }

  if ( (!elcT2caData && elcNeuralData) || ( elcT2caData && !elcT2caData) ){
    std::cout<<"HypoCompCanvas need both Hypos with same kind of data to make the comparision"<<std::endl;
    throw;
  }


  file = HypoBase::getFile();

  file->cd();
  file->mkdir("HypoCompTool");

  if (elcT2caData){
    if (!elcT2caData->getTotalData())
      elcT2caData->exec();
    if (!elcNeuralData->getTotalData())
      elcNeuralData->exec();
  }
  else{
    if (!jetT2caData->getTotalData())
      jetT2caData->exec();
    if (!jetNeuralData->getTotalData())
      jetNeuralData->exec();
  }

  exec();

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
hypoCompCanvas(0),
infoCanvas(0),
scatterPlotPad(0),
spPlotPad(0),
outGraphs1(0),
outGraphs2(0),
useTestOnly(usetestonly),
testDivisionFactor(testdivisionfactor),
scatterPlot(0),
spPlot(0),
file(0)
{

  if (hypo1->getId().find("elc") != std::string::npos){
    if( !elcT2caData)
      elcT2caData = dynamic_cast<T2CaCommon*>(hypo1);
    else if (!elcNeuralData)
      elcNeuralData = dynamic_cast<NeuralCommon*>(hypo1);
  } else {
    if (!jetT2caData)
      jetT2caData = dynamic_cast<T2CaCommon*>(hypo1);
    else if (!jetNeuralData)
      jetNeuralData = dynamic_cast<NeuralCommon*>(hypo1);
  }

  if (hypo2->getId().find("elc") != std::string::npos){
    if( !elcT2caData)
      elcT2caData = dynamic_cast<T2CaCommon*>(hypo2);
    else if (!elcNeuralData)
      elcNeuralData = dynamic_cast<NeuralCommon*>(hypo2);
  } else {
    if (!jetT2caData)
      jetT2caData = dynamic_cast<T2CaCommon*>(hypo2);
    else if (!jetNeuralData)
      jetNeuralData = dynamic_cast<NeuralCommon*>(hypo2);
  }

  if (hypo3->getId().find("elc") != std::string::npos){
    if( !elcT2caData)
      elcT2caData = dynamic_cast<T2CaCommon*>(hypo3);
    else if (!elcNeuralData)
      elcNeuralData = dynamic_cast<NeuralCommon*>(hypo3);
  } else {
    if (!jetT2caData)
      jetT2caData = dynamic_cast<T2CaCommon*>(hypo3);
    else if (!jetNeuralData)
      jetNeuralData = dynamic_cast<NeuralCommon*>(hypo3);
  }

  if (hypo4->getId().find("elc") != std::string::npos){
    if( !elcT2caData)
      elcT2caData = dynamic_cast<T2CaCommon*>(hypo4);
    else if (!elcNeuralData)
      elcNeuralData = dynamic_cast<NeuralCommon*>(hypo4);
  } else {
    if (!jetT2caData)
      jetT2caData = dynamic_cast<T2CaCommon*>(hypo4);
    else if (!jetNeuralData)
      jetNeuralData = dynamic_cast<NeuralCommon*>(hypo4);
  }

  if ( !elcT2caData || ! jetT2caData || !elcNeuralData || !jetNeuralData ){
    std::cout<<"HypoCompCanvas need both Hypos with both kind of data to make the comparision"<<std::endl;
    throw;
  }

  file = HypoBase::getFile();
  if (!jetT2caData->getTotalData())
    jetT2caData->exec();
  if (!jetNeuralData->getTotalData())
    jetNeuralData->exec();
  if (!elcT2caData->getTotalData())
    elcT2caData->exec();
  if (!elcNeuralData->getTotalData())
    elcNeuralData->exec();

  file->cd();
  file->mkdir("HypoCompTool");

  exec();

}


int HypoCompCanvas::exec(){

  std::vector<int>* ringerDec = new std::vector<int>;
  std::vector<int>* t2CaDec = new std::vector<int>;
  if ( elcT2caData && jetT2caData && elcNeuralData && jetNeuralData ){
    //Jets
    //T2Calo 
    jetT2caData->getExtraVariables()->SetBranchStatus("*", false);
    jetT2caData->getExtraVariables()->SetBranchStatus("T2CaDec", true);
    TTree *jetCompTree = jetT2caData->getExtraVariables()->CloneTree();
    jetCompTree->SetBranchAddress("T2CaDec", &t2CaDec);
    int nEntries = static_cast<int>(jetCompTree->GetEntries());
    int pos = 0;
    for( int i = 0; i<nEntries;++i){
      jetCompTree->GetEntry(i);
      for(size_t j=0; j<t2CaDec->size();++j){
        if ( useTestOnly && (pos = (pos +1) % testDivisionFactor ) ) 
          continue; // if using only test data
        ++noiseT2caTotal;
        if ( t2CaDec->at(j) == HypoBase::ELECTRON )
          ++noiseT2ca;
      }
    }
    jetCompTree->ResetBranchAddresses();
    jetCompTree->Delete();
    jetT2caData->getExtraVariables()->GetListOfClones()->RemoveAll();
    jetT2caData->ResetBranchAddresses();
    jetCompTree = 0;
    //Ringer
    jetNeuralData->getExtraVariables()->SetBranchStatus("*", false);
    jetNeuralData->getExtraVariables()->SetBranchStatus("Ringer_Dec", true);
    jetCompTree = jetNeuralData->getExtraVariables()->CloneTree();
    jetCompTree->ResetBranchAddresses();
    jetCompTree->SetBranchAddress("Ringer_Dec", &ringerDec);
    nEntries = static_cast<int>(jetCompTree->GetEntries());
    pos = 0;
    for( int i = 0; i<nEntries;++i){
      jetCompTree->GetEntry(i);
      for(size_t j=0; j<ringerDec->size();++j){
        if ( useTestOnly && (pos = (pos +1) % testDivisionFactor ) ) 
          continue; // if using only test data
        ++noiseNeuralTotal;
        if ( ringerDec->at(j) == HypoBase::ELECTRON )
          ++noiseNeural;
      }
    }
    jetCompTree->ResetBranchAddresses();
    jetCompTree->Delete();
    jetNeuralData->getExtraVariables()->GetListOfClones()->RemoveAll();
    jetNeuralData->ResetBranchAddresses();
    jetCompTree = 0;
    //Electrons
    //T2Calo 
    elcT2caData->getExtraVariables()->SetBranchStatus("*", false);
    elcT2caData->getExtraVariables()->SetBranchStatus("T2CaDec", true);
    TTree *elcCompTree = elcT2caData->getExtraVariables()->CloneTree();
    elcCompTree->SetBranchAddress("T2CaDec", &t2CaDec);
    nEntries = static_cast<int>(elcCompTree->GetEntries());
    pos = 0;
    for( int i = 0; i<nEntries;++i){
      elcCompTree->GetEntry(i);
      for(size_t j=0; j<t2CaDec->size();++j){
        if ( useTestOnly && (pos = (pos +1) % testDivisionFactor ) ) 
          continue; // if using only test data
        ++signalT2caTotal;
        if ( t2CaDec->at(j) == HypoBase::ELECTRON )
          ++signalT2ca;
      }
    }
    elcCompTree->ResetBranchAddresses();
    elcCompTree->Delete();
    elcT2caData->getExtraVariables()->GetListOfClones()->RemoveAll();
    elcT2caData->ResetBranchAddresses();
    elcCompTree = 0;
    //Ringer
    elcNeuralData->getExtraVariables()->SetBranchStatus("*", false);
    elcNeuralData->getExtraVariables()->SetBranchStatus("Ringer_Dec", true);
    elcCompTree = elcNeuralData->getExtraVariables()->CloneTree();
    elcCompTree->SetBranchAddress("Ringer_Dec", &ringerDec);
    pos = 0;
    nEntries = static_cast<int>(elcCompTree->GetEntries());
    for( int i = 0; i<nEntries;++i){
      elcCompTree->GetEntry(i);
      for(size_t j=0; j<ringerDec->size();++j){
        if ( useTestOnly && (pos = (pos +1) % testDivisionFactor ) ) 
          continue; // if using only test data
        ++signalNeuralTotal;
        if ( ringerDec->at(j) == HypoBase::ELECTRON )
          ++signalNeural;
      }
    }
    elcCompTree->ResetBranchAddresses();
    elcCompTree->Delete();
    elcNeuralData->getExtraVariables()->GetListOfClones()->RemoveAll();
    elcNeuralData->ResetBranchAddresses();
    elcCompTree = 0;

    detRateT2ca = static_cast<float>(signalT2ca)/static_cast<float>(signalT2caTotal)*100.;
    detRateNeural = static_cast<float>(signalNeural)/static_cast<float>(signalNeuralTotal)*100.;
    faRateT2ca = static_cast<float>(noiseT2ca)/static_cast<float>(noiseT2caTotal)*100.;
    faRateNeural = static_cast<float>(noiseNeural)/static_cast<float>(noiseNeuralTotal)*100.;

    spProductT2ca = calcSP(detRateT2ca, 100. - faRateT2ca);
    spProductNeural = calcSP(detRateNeural, 100. - faRateNeural);

  } else {
    if ( elcT2caData && elcNeuralData ){
      //Electrons
      //T2Calo 
      elcT2caData->getExtraVariables()->SetBranchStatus("*", false);
      elcT2caData->getExtraVariables()->SetBranchStatus("T2CaDec", true);
      TTree *elcCompTree = elcT2caData->getExtraVariables()->CloneTree();
      elcCompTree->SetBranchAddress("T2CaDec", &t2CaDec);
      int nEntries = static_cast<int>(elcCompTree->GetEntries());
      int pos = 0;
      for( int i = 0; i<nEntries;++i){
        elcCompTree->GetEntry(i);
        for(size_t j=0; j<t2CaDec->size();++j){
          if ( useTestOnly && (pos = (pos +1) % testDivisionFactor ) ) 
            continue; // if using only test data
          ++signalT2caTotal;
          if ( t2CaDec->at(j) == HypoBase::ELECTRON )
            ++signalT2ca;
        }
      }
      elcCompTree->ResetBranchAddresses();
      elcCompTree->Delete();
      elcT2caData->getExtraVariables()->GetListOfClones()->RemoveAll();
      elcT2caData->ResetBranchAddresses();
      elcCompTree = 0;
      //Ringer
      elcNeuralData->getExtraVariables()->SetBranchStatus("*", false);
      elcNeuralData->getExtraVariables()->SetBranchStatus("Ringer_Dec", true);
      elcCompTree = elcNeuralData->getExtraVariables()->CloneTree();
      elcCompTree->SetBranchAddress("Ringer_Dec", &ringerDec);
      pos = 0;
      nEntries = static_cast<int>(elcCompTree->GetEntries());
      for( int i = 0; i<nEntries;++i){
        elcCompTree->GetEntry(i);
        for(size_t j=0; j<ringerDec->size();++j){
          if ( useTestOnly && (pos = (pos +1) % testDivisionFactor ) ) 
            continue; // if using only test data
          ++signalNeuralTotal;
          if ( ringerDec->at(j) == HypoBase::ELECTRON )
            ++signalNeural;
        }
      }
      elcCompTree->ResetBranchAddresses();
      elcCompTree->Delete();
      elcNeuralData->getExtraVariables()->GetListOfClones()->RemoveAll();
      elcNeuralData->ResetBranchAddresses();
      elcCompTree = 0;
      detRateT2ca = static_cast<float>(signalT2ca)/static_cast<float>(signalT2caTotal)*100.;
      detRateNeural = static_cast<float>(signalNeural)/static_cast<float>(signalNeuralTotal)*100.;
    } else {
      //Jets
      //T2Calo 
      jetT2caData->getExtraVariables()->SetBranchStatus("*", false);
      jetT2caData->getExtraVariables()->SetBranchStatus("T2CaDec", true);
      TTree *jetCompTree = jetT2caData->getExtraVariables()->CloneTree();
      jetCompTree->SetBranchAddress("T2CaDec", &t2CaDec);
      int nEntries = static_cast<int>(jetCompTree->GetEntries());
      int pos = 0;
      for( int i = 0; i<nEntries;++i){
        jetCompTree->GetEntry(i);
        for(size_t j=0; j<t2CaDec->size();++j){
          if ( useTestOnly && (pos = (pos +1) % testDivisionFactor ) ) 
            continue; // if using only test data
          ++noiseT2caTotal;
          if ( t2CaDec->at(j) == HypoBase::ELECTRON )
            ++noiseT2ca;
        }
      }
      jetCompTree->ResetBranchAddresses();
      jetCompTree->Delete();
      jetT2caData->getExtraVariables()->GetListOfClones()->RemoveAll();
      jetT2caData->ResetBranchAddresses();
      jetCompTree = 0;
      //Ringer
      jetNeuralData->getExtraVariables()->SetBranchStatus("*", false);
      jetNeuralData->getExtraVariables()->SetBranchStatus("Ringer_Dec", true);
      jetCompTree = jetNeuralData->getExtraVariables()->CloneTree();
      jetCompTree->ResetBranchAddresses();
      jetCompTree->SetBranchAddress("Ringer_Dec", &ringerDec);
      nEntries = static_cast<int>(jetCompTree->GetEntries());
      pos = 0;
      for( int i = 0; i<nEntries;++i){
        jetCompTree->GetEntry(i);
        for(size_t j=0; j<ringerDec->size();++j){
          if ( useTestOnly && (pos = (pos +1) % testDivisionFactor ) ) 
            continue; // if using only test data
          ++noiseNeuralTotal;
          if ( ringerDec->at(j) == HypoBase::ELECTRON )
            ++noiseNeural;
        }
      }
      jetCompTree->ResetBranchAddresses();
      jetCompTree->Delete();
      jetNeuralData->getExtraVariables()->GetListOfClones()->RemoveAll();
      jetNeuralData->ResetBranchAddresses();
      jetCompTree = 0;
      faRateT2ca = static_cast<float>(noiseT2ca)/static_cast<float>(noiseT2caTotal)*100.;
      faRateNeural = static_cast<float>(noiseNeural)/static_cast<float>(noiseNeuralTotal)*100.;
    }
  }

  delete t2CaDec;
  delete ringerDec;
  return 0;

}


int HypoCompCanvas::DrawScatterPlot(){

  file->cd();
  file->cd("HypoCompTool");

  if ( elcT2caData && jetT2caData && elcNeuralData && jetNeuralData ){
    // Detection and False Alarm:
    scatterPlot = new TH2F("ScatterPlot", "Hypotesis Algorythms Comparision;;; Rates (%)", 2, -2, 2, 2, -2, 2);
    scatterPlot->SetOption("lego2 fb cg(1)");

    scatterPlot->Fill(-1., -1., faRateT2ca   );
    scatterPlot->Fill(1. , -1., faRateNeural );
    scatterPlot->Fill(-1.,  1., detRateT2ca  );
    scatterPlot->Fill(1. ,  1., detRateNeural);

    scatterPlot->SetAxisRange(0.,100.,"Z");

    scatterPlot->GetXaxis()->SetBinLabel(1,"T2Calo");
    scatterPlot->GetXaxis()->SetBinLabel(2,"Neural Ringer");
    scatterPlot->GetXaxis()->SetLabelSize(0.08);
    scatterPlot->GetXaxis()->SetLabelOffset(0.08);
    scatterPlot->GetXaxis()->CenterTitle();
    scatterPlot->GetYaxis()->SetBinLabel(1,"False Alarm");
    scatterPlot->GetYaxis()->SetBinLabel(2,"Detection");
    scatterPlot->GetYaxis()->SetLabelOffset(0.0075);
    scatterPlot->GetYaxis()->SetLabelSize(0.08);
    scatterPlot->GetYaxis()->CenterTitle();
    scatterPlot->GetZaxis()->SetTitleOffset(1.25);

    gPad->SetTheta(25);
    gPad->SetPhi(30);
    SetPallete("",99);
    scatterPlot->SetStats(kFALSE);
    scatterPlot->Draw();


  } else {


    if ( elcT2caData && elcNeuralData ){
      scatterPlot = new TH2F("ScatterPlot", "Hypotesis Algorythms Detection Comparision;;; Rates (%)", 2, -2, 2, 1, -1, 1);
      scatterPlot->Fill( -1., 0., detRateT2ca   );
      scatterPlot->Fill(  1., 0., detRateNeural );
    }else{
      scatterPlot = new TH2F("ScatterPlot", "Hypotesis Algorythms False Alarm Comparision;;; Rates (%)", 2, -2, 2, 1, -1, 1);
      scatterPlot->Fill( -1., 0., faRateT2ca   );
      scatterPlot->Fill(  1., 0., faRateNeural );
    }
    scatterPlot->SetOption("lego2 fb cg(1)");

    scatterPlot->GetXaxis()->SetBinLabel(1,"T2Calo");
    scatterPlot->GetXaxis()->SetBinLabel(2,"Neural Ringer");
    scatterPlot->GetXaxis()->SetLabelSize(0.08);
    scatterPlot->GetXaxis()->SetLabelOffset(0.05);
    scatterPlot->GetXaxis()->CenterTitle();
    scatterPlot->GetZaxis()->SetTitleOffset(.70);
    scatterPlot->GetZaxis()->SetTitleSize(.06);

    scatterPlot->SetAxisRange(0., scatterPlot->GetMaximum(),"Z");

    if ( elcT2caData )
      scatterPlot->GetYaxis()->SetBinLabel(1,"Detection");
    else
      scatterPlot->GetYaxis()->SetBinLabel(1,"False Alarm");
    scatterPlot->GetXaxis()->SetLabelSize(0.08);
    scatterPlot->GetYaxis()->SetLabelSize(0.08);
    scatterPlot->GetYaxis()->CenterTitle();

    gPad->SetTheta(10);
    gPad->SetPhi(160);
    SetPallete("",99);
    scatterPlot->SetStats(kFALSE);
    scatterPlot->Draw();
  }

  return 0;

}

int HypoCompCanvas::DrawSpPlot(){

    file->cd();
    file->cd("HypoCompTool");

    // SP Product:
    spPlot = new TH2F("spPlot", "Hypotesis Algorythms SP Product (%)", 2, -2, 2, 1, -1, 1);
    spPlot->SetOption("lego2 fb cg(1)");

    spPlot->Fill(-1.,0., spProductT2ca);
    spPlot->Fill( 1.,0., spProductNeural);

    spPlot->GetXaxis()->SetBinLabel(1,"T2Calo");
    spPlot->GetXaxis()->SetBinLabel(2,"Neural Ringer");
    spPlot->GetXaxis()->SetLabelOffset(0.05);
    spPlot->GetXaxis()->CenterTitle();
    spPlot->GetXaxis()->SetLabelSize(0.08);
    spPlot->GetYaxis()->SetBinLabel(1,"");
    spPlot->GetYaxis()->CenterTitle();
    spPlot->GetZaxis()->SetTitleOffset(1.25);

    spPlot->SetAxisRange(0.,100.,"Z");

    gPad->SetTheta(7);
    gPad->SetPhi(160);
    SetPallete("",99);
    spPlot->SetStats(kFALSE);
    spPlot->Draw();

    return 0;

}

int HypoCompCanvas::DrawInfoPad(){

  file->cd();
  file->cd("HypoCompTool");

  TPaveText *pt = new TPaveText(.05,.05,.95,.95);
  if ( elcT2caData && jetT2caData && elcNeuralData && jetNeuralData ){
    TString line1, line2, line3, line4, line5, line6, line7;
    if ( signalT2caTotal == signalNeuralTotal && noiseT2caTotal == noiseNeuralTotal)
      line1.Form("Total Data = %d : #color[4]{Electrons = %d} : #color[2]{Jets = %d}", signalNeuralTotal + noiseNeuralTotal, signalNeuralTotal, noiseNeuralTotal );
    else
      line1.Form("Total Data T2Calo = %d | Total Data NeuralRinger = %d", signalT2caTotal + noiseT2caTotal, signalNeuralTotal + noiseNeuralTotal);
    line2.Form("#scale[1.05]{T2Calo SP Product = %.4f%%}", spProductT2ca );
    line3.Form("#color[4]{#scale[1]{Det Rate = %.2f%%}}", detRateT2ca );
    line4.Form("#color[2]{#scale[1]{FA = %.2f%%}}", faRateT2ca );
    line5.Form("#scale[1.05]{NeuralRinger SP Product = %.4f%%}", spProductNeural );
    line6.Form("#color[4]{#scale[1]{Det Rate = %.2f%%}}", detRateNeural );
    line7.Form("#color[2]{#scale[1]{FA = %.2f%%}}", faRateNeural );
    pt->SetTextAlign(22);
    pt->AddText("");
    pt->AddText(line1);
    pt->AddText("");pt->AddText("");pt->AddText("");
    float y = 0.75, ylow = 0.02; const float yDecrement = (y - ylow)/4; float x1 = 0.3; float x2 = 0.5; float x3 = 0.7;
    pt->AddText(x2, y, line2);  y-=yDecrement;
    pt->AddText(x1, y, line3);
    pt->AddText(x3, y, line4);  y-=yDecrement;
    pt->AddText(x2, y, line5);  y-=yDecrement;
    pt->AddText(x1, y, line6);
    pt->AddText(x3, y, line7); 
    TString line666("Signal Processing Laboratory - COPPE/UFRJ");
    TText *p1 = pt->AddText(0.6, 0.02, line666);
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
      if ( elcT2caData)
        line1.Form("Total Data : #color[4]{Electrons = %d} ", signalT2caTotal);
      else
        line1.Form("Total Data : #color[2]{Jets = %d}", noiseNeuralTotal);
    } else {
      if (elcT2caData)
        line1.Form("#color[4]{T2Calo Electrons = %d : NeuralRinger Electrons = %d } ", signalT2caTotal, signalNeuralTotal);
      else
        line1.Form("#color[2]{T2Calo Jets = %d : NeuralRinger Jets = %d } ", noiseT2caTotal, noiseNeuralTotal);
    }
    if (elcT2caData){
      line2.Form("#scale[1.05]{T2Calo Detection Rate = %.2f%%}", detRateT2ca);
      line3.Form("#scale[1.05]{NeuralRinger Detection Rate = %.2f%%}", detRateNeural );
    } else {
      line2.Form("#scale[1.05]{T2Calo False Alarm Rate = %.2f%%}", faRateT2ca );
      line3.Form("#scale[1.05]{NeuralRinger False Alarm Rate = %.2f%%}", faRateNeural );
    }
    pt->SetTextAlign(22);
    pt->AddText(line1);
    pt->AddText(line2);
    pt->AddText(line3);
    TString line666("Signal Processing Laboratory - COPPE/UFRJ");
    TText *p1 = pt->AddText(0.6, 0.02, line666);
    p1->SetTextSize(0.04);
  }

  pt->SetLabel("Hypotesis Comparison Tool");
  pt->SetFillColor(33);
  pt->Draw();

  return 0;

}


int HypoCompCanvas::DrawOutGraphs(int padNumber){

  file->cd();
  file->cd("HypoCompTool");

  if ( elcT2caData && jetT2caData && elcNeuralData && jetNeuralData ){
    // T2Calo Out:
    switch (padNumber){
      case 1:{
        elcT2caData->DrawCutCounter("", true);
        jetT2caData->DrawCutCounter("sames", true);
        break;
      }
      case 2:{
        elcNeuralData->drawNetAns("","scaled");
        jetNeuralData->drawNetAns("sames","scaled");
        if ( elcNeuralData->getNetAns()->GetMaximum() < jetNeuralData->getNetAns()->GetMaximum() ){
          elcNeuralData->getNetAns()->SetAxisRange(0, jetNeuralData->getNetAns()->GetMaximum() *1.1, "Y");
          jetNeuralData->getNetAns()->SetAxisRange(0, jetNeuralData->getNetAns()->GetMaximum() *1.1, "Y");
        }
        break;
      }
      default:{
        std::cout<<"Only pad 1 or 2 can be Draw"<<std::endl;
        return 1;
      }
    }
  } else {
    // T2Calo Out:
    switch (padNumber){
      case 1:{
        if (elcT2caData)
          elcT2caData->DrawCutCounter();
        else
          jetT2caData->DrawCutCounter();
        break;
      }
      case 2:{
        if (elcNeuralData)
          elcNeuralData->drawNetAns();
        else
          jetNeuralData->drawNetAns();
        break;
      }
      default:{
        std::cout<<"Only pad 1 or 2 can be Draw"<<std::endl;
        return 1;
      }
    }
  }

  return 0;
}

int HypoCompCanvas::Draw(){

  file->cd();
  file->cd("HypoCompTool");
  if ( elcT2caData && jetT2caData && elcNeuralData && jetNeuralData ){
    hypoCompCanvas = new TCanvas("Hypotesys Comparision Analysis", "Hypotesis Comparision Analyisis");
    scatterPlotPad = new TPad("Scatter Plot Pad", "Hypotesys Comparision", 0.0025, 0.3600, .60, .9975, 18);
    scatterPlotPad->Draw();
    scatterPlotPad->cd();
    DrawScatterPlot();
    hypoCompCanvas->cd();
    spPlotPad = new TPad("SP Product Plot Pad", " Algorythms SP Product", 0.6025, 0.3600, .9975, .9975,18);
    spPlotPad->Draw();
    spPlotPad->cd();
    DrawSpPlot();
    hypoCompCanvas->cd();
    outGraphs1 = new TPad("OutGraphs1", "Out Graphics T2Calo", 0.0025, 0.01, .5, .3550);
    outGraphs1->Draw();
    outGraphs1->cd();
    DrawOutGraphs(1);
    outGraphs1->SetFillColor(18);
    hypoCompCanvas->cd();
    outGraphs2 = new TPad("OutGraphs2", "Out Graphics NeuralRinger", 0.5025, 0.01, .9975, .3550);
    outGraphs2->Draw();
    outGraphs2->cd();
    DrawOutGraphs(2);
    outGraphs2->SetFillColor(18);
    infoCanvas = new TCanvas("Hypotesis Analysis Info", "Analysis Info");
    DrawInfoPad();
    hypoCompCanvas->Write("Hypotesis Algorythms Comparision_4Hypos", TObject::kOverwrite);
    infoCanvas->Write("Hypotesis Analysis Info_4Hypos", TObject::kOverwrite);
  }else{
    hypoCompCanvas = new TCanvas("Hypotesys Comparision Analysis", "Hypotesis Comparision Analyisis");
    scatterPlotPad = new TPad("Scatter Plot Pad", "Hypotesys Comparision", 0.0025, 0.4025, .9975, .9975, 18);
    scatterPlotPad->Draw();
    scatterPlotPad->cd();
    DrawScatterPlot();
    hypoCompCanvas->cd();
    outGraphs1 = new TPad("OutGraphs1", "Out Graphics T2Calo", 0.0025, 0.01, .5, .40);
    outGraphs1->Draw();
    outGraphs1->cd();
    DrawOutGraphs(1);
    outGraphs1->SetFillColor(18);
    hypoCompCanvas->cd();
    outGraphs2 = new TPad("OutGraphs2", "Out Graphics NeuralRinger", 0.5025, 0.01, .9975, .40);
    outGraphs2->Draw();
    outGraphs2->cd();
    DrawOutGraphs(2);
    outGraphs2->SetFillColor(18);
    infoCanvas = new TCanvas("Analysis Info", "Analysis Info");
    DrawInfoPad();
    hypoCompCanvas->Write("Hypotesis Algorythms Comparision_2Hypos", TObject::kOverwrite);
    infoCanvas->Write("Hypotesis Analysis Info_2Hypos", TObject::kOverwrite);
  }

  return 0;

}




HypoCompCanvas::~HypoCompCanvas(){

  if (scatterPlot)
    scatterPlot->Delete();
  if (spPlot)
    spPlot->Delete();
  if (infoCanvas){
    if (gROOT->GetListOfCanvases()->FindObject("Analysis Info")){
      infoCanvas->Delete();
    }
  }
  if (hypoCompCanvas){
    if ( (hypoCompCanvas = static_cast<TCanvas*>(gROOT->GetListOfCanvases()->FindObject("Hypotesys Comparision Analysis")))){
      delete hypoCompCanvas;
    }
  }


}
