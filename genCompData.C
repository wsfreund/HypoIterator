#include <fstream>
#include <iostream>
#include <cstring>
#include <TFile.h>
#include <TChain.h>
#include <TH2I.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TString.h>
#include <TPaveText.h>
#include "Efic.h"
#include "Neural.h"
#include "NeuralEfic.h"
#include "T2CaloEfic.h"
using namespace std;


float productSP(const float eDetRatio, const float jDetRatio);

int calcEfic(TTree *tree, float &detNeural, float &detT2Calo);

int scatterPlot(TTree *tree);

int genCompData(const char *inPut, const char *outPut){

	TFile 		*file;
	TChain		*chainAnalysis;
	TTree		*generateData;
	NeuralEfic	*myNeural;
	T2CaloEfic	*myT2Calo;

	chainAnalysis = new TChain("CollectionTree");
	chainAnalysis->Add(inPut);
	chainAnalysis->SetBranchStatus("*",	false);


	int nEvents	= static_cast<int>(chainAnalysis->GetEntries());
	
	file		= new TFile(outPut,"recreate");

	generateData= new TTree("HypoData", "Tree with Hypo data");

	myNeural    = new NeuralEfic(chainAnalysis, generateData);
	myT2Calo	= new T2CaloEfic(chainAnalysis, generateData);


	for(int i = 0; i<nEvents; ++i){
        cout<<i<<std::entdl;
		chainAnalysis->GetEntry(i);

		myNeural->exec();
		myT2Calo->exec();

        myT2Calo->ordenateRoi(myNeural->getEta(), myNeural->getPhi());

        generateData->Fill();

        myNeural->clearVectors();
        myT2Calo->clearVectors();

	}//for i

	generateData->Write(); //Gera arquivo .root


    float elcRateNeural;
    float elcRateT2Ca;

    TCanvas *canvas = new TCanvas("Analysis Graphics", "Analysis Graphics");

    canvas->Divide(2,2);
    canvas->cd(1);

    myNeural->drawNetAns();
    gPad->SetEditable(kFALSE);

    canvas->cd(2);
    scatterPlot(generateData);
    gPad->SetEditable(kFALSE);

    canvas->cd(3);
    myT2Calo->drawCutCounter();
    gPad->SetEditable(kFALSE);

    canvas->cd(4);
    calcEfic(generateData, elcRateNeural, elcRateT2Ca);
    gPad->SetEditable(kFALSE);

    canvas->cd();



    canvas->Update();

    cout<<"Ringer electron eficiency "<<elcRateNeural<<endl;

    cout<<"T2Calo electron eficiency "<<elcRateT2Ca<<endl;



	delete chainAnalysis;
	delete generateData;
    delete myT2Calo;
	delete myNeural;
//	delete file;

	return 0;


}

int genCompData(const char *inPut, const char *outPut, const char *txtFile){

	TFile 		*file;
	TChain		*chainAnalysis;
	TTree		*generateData;
	NeuralEfic	*myNeural;
	T2CaloEfic	*myT2Calo;

	ofstream matlabFile(txtFile, ios::out | ios::trunc);

	chainAnalysis 	= new TChain("CollectionTree");
	chainAnalysis->	Add(inPut);
	chainAnalysis->	SetBranchStatus("*",	false);


	int nEvents	= static_cast<int>(chainAnalysis->GetEntries());
	
	file		= new TFile(outPut,"recreate");

	generateData= new TTree("HypoData", "Tree with Hypo data");

	myNeural    = new NeuralEfic(chainAnalysis, generateData, &matlabFile);
	myT2Calo	= new T2CaloEfic(chainAnalysis, generateData);

	matlabFile<<txtFile;
    matlabFile.seekp(-2, ios::cur);
    matlabFile<<"Var = [";

	for(int i = 0; i<nEvents; ++i){

		chainAnalysis->GetEntry(i);

		myNeural->exec();
		myT2Calo->exec();

        myT2Calo->ordenateRoi(myNeural->getEta(), myNeural->getPhi());

        generateData->Fill();

        myNeural->clearVectors();
        myT2Calo->clearVectors();

	}//for i

    matlabFile.seekp(-1, ios::cur);
    matlabFile<<"];";

	generateData->Write(); //Gera arquivo .root

    float elcRateNeural;
    float elcRateT2Ca;

    TCanvas *canvas = new TCanvas("Analysis Graphics", "Analysis Graphics");

    canvas->Divide(2,2);
    canvas->cd(1);

    myNeural->drawNetAns();
    gPad->SetEditable(kFALSE);

    canvas->cd(2);
    scatterPlot(generateData);
    gPad->SetEditable(kFALSE);

    canvas->cd(3);
    myT2Calo->drawCutCounter();
    gPad->SetEditable(kFALSE);

    canvas->cd(4);
    calcEfic(generateData, elcRateNeural, elcRateT2Ca);
    gPad->SetEditable(kFALSE);

    canvas->cd();

    canvas->Update();

    cout<<"Ringer electron eficiency "<<elcRateNeural<<endl;

    cout<<"T2Calo electron eficiency "<<elcRateT2Ca<<endl;

    matlabFile.close();


	delete chainAnalysis;
	delete generateData;
    delete myT2Calo;
	delete myNeural;
//	delete file;

	return 0;


}

int scatterPlot(TTree *tree){

	int nEntries	        =       static_cast<int>(tree->GetEntries());

    TH2I *scatterPlot = new TH2I("ScatterPlot", "eGammaHyppo x Ringer; T2Calo; Ringer; Log Scale", 2, -2, 2, 2, -2, 2);

    scatterPlot->SetOption("lego1 cg(1)");

	vector<int> *ringerDec	=	new vector<int>;

	vector<int> *t2CaDec	=	new vector<int>;

	tree->SetBranchStatus("Ringer_Dec",	true);

	tree->SetBranchAddress("Ringer_Dec",	&ringerDec);

	tree->SetBranchStatus("T2CaDec",	true);

	tree->SetBranchAddress("T2CaDec",	&t2CaDec);
	int pos = 0;

	for(int i=0; i<nEntries;++i){
		tree->GetEntry(i);
		for(size_t j=0; j<ringerDec->size();++j){
        		if ( (pos = (pos +1) % 3) ) continue;//Utilizando apenas conjunto de teste
                        scatterPlot->Fill(t2CaDec->at(j), ringerDec->at(j));                        
                }
    }

    scatterPlot->GetXaxis()->SetBinLabel(1,"Jets");

    scatterPlot->GetXaxis()->SetBinLabel(2,"Electrons");
    
    scatterPlot->GetXaxis()->CenterTitle();

    scatterPlot->GetYaxis()->SetBinLabel(1,"Jets");

    scatterPlot->GetYaxis()->SetBinLabel(2,"Electrons");

    scatterPlot->GetYaxis()->CenterTitle();

    scatterPlot->SetFillColor(41);

    gPad->SetLogz();

    if (scatterPlot->GetBinContent(1,1)>scatterPlot->GetBinContent(2,2)) {
        gPad->SetTheta(10);
        gPad->SetPhi(-150);
    } else {
        gPad->SetTheta(10);
        gPad->SetPhi(30);
    }

    scatterPlot->SetStats(kFALSE);
   
    scatterPlot->Draw();

    tree->ResetBranchAddresses();

    return 0;
}

int calcEfic(TTree *tree, float &detNeural, float &detT2Calo){

    float neuralElc, totalData, neuralJet, t2CaJet, t2CaElc;
    neuralElc = neuralJet = t2CaElc = t2CaJet = totalData = 0;

	vector<int> *ringerDec	=	new vector<int>;

	vector<int> *t2CaDec	=	new vector<int>;

	tree->SetBranchStatus("Ringer_Dec",	true);

	tree->SetBranchAddress("Ringer_Dec",	&ringerDec);

	tree->SetBranchStatus("T2CaDec",	true);

	tree->SetBranchAddress("T2CaDec",	&t2CaDec);

	int nEntries	        =       static_cast<int>(tree->GetEntries());

	int pos = 0;
	for(int i=0; i<nEntries;++i){
	    tree->GetEntry(i);
	    for(size_t j=0; j<t2CaDec->size();++j){
		       if ( (pos = (pos +1) % 3) ) continue;//Utilizando apenas conjunto de teste
            if (ringerDec->at(j)==Efic::ELECTRON) ++neuralElc;
            else ++neuralJet;
            if (t2CaDec->at(j)==Efic::ELECTRON) ++t2CaElc;
            else ++t2CaJet;
            ++totalData;                 
        }
    }

    cout<<"Total Data "<<totalData<<endl;
    cout<<"Neural Electrons "<<neuralElc<<endl;
    cout<<"Neural Jets "<<neuralJet<<endl;
    cout<<"T2Calo Electrons "<<t2CaElc<<endl;
    cout<<"T2Calo Jets "<<t2CaJet<<endl;



    detNeural = neuralElc*100./totalData;
    detT2Calo = t2CaElc*100./totalData;

    TPaveText *pt = new TPaveText(.05,.05,.95,.95);
    TString line1, line2, line3, line4, line5, line6, line7, line8, line9;

    line1.Form("Total Data = %.0f",totalData);
    line2.Form("Neural Ringer Detected Electrons = %.0f", neuralElc);
    line3.Form("Neural Ringer Detected Jets = %.0f", neuralJet);
    line4.Form("T2Calo Detected Electrons = %.0f", t2CaElc);
    line5.Form("T2Calo Detected Jets = %.0f", t2CaJet);
    line6.Form("Neural Ringer Electrons Rate = %.4f", detNeural);
    line7.Form("Neural Ringer Jets Rate = %.4f", 100.-detNeural);
    line8.Form("T2Calo Electrons Rate = %.4f", detT2Calo);
    line9.Form("T2Calo Jets Rate = %.4f", 100.-detT2Calo);

    pt->AddText("");
    pt->AddText(line1);
    pt->AddText("");
    pt->AddText(line2);
    pt->AddText(line3);
    pt->AddText("");
    pt->AddText(line4);
    pt->AddText(line5);
    pt->AddText("");
    pt->AddText(line6);
    pt->AddText(line7);
    pt->AddText("");
    pt->AddText(line8);
    pt->AddText(line9);

    pt->SetFillColor(30);
    pt->SetTextAlign(12);

    pt->SetLabel("Hypos Comparison v1.1.3");

    pt->Draw();

    tree->ResetBranchAddresses();

    return 0;

}


inline float productSP(const float eDetRatio, const float jDetRatio){
	return ((eDetRatio/100.+jDetRatio/100.)/2.)*sqrt(eDetRatio/100.*jDetRatio/100.);
}
