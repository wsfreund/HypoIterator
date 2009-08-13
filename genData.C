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

int calcEfic(float &detNeural, NeuralEfic* Neural);

int scatterPlot(TTree *tree);

int genData(const char *inPut){

	NeuralEfic	*myNeural;

	myNeural        = new NeuralEfic(inPut);

	myNeural->exec();


        float elcRateNeural;

        TCanvas *canvas = new TCanvas("Analysis Graphics", "Analysis Graphics");

        calcEfic(elcRateNeural, myNeural);
        gPad->SetEditable(kFALSE);

        canvas->Update();

        cout<<"Ringer electron eficiency "<<elcRateNeural<<endl;


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

	tree->SetBranchStatus("RingerDec",	true);

	tree->SetBranchAddress("RingerDec",	&ringerDec);

	tree->SetBranchStatus("T2CaDec",	true);

	tree->SetBranchAddress("T2CaDec",	&t2CaDec);


	for(int i=0; i<nEntries;++i){
		tree->GetEntry(i);
		for(size_t j=0; j<ringerDec->size();++j){
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

int calcEfic(float &detNeural, NeuralEfic* Neural){

        float neuralElc, totalData, neuralJet, t2CaJet, t2CaElc;
        neuralElc = neuralJet = t2CaElc = t2CaJet = totalData = 0;

	vector<int> *ringerDec	= Neural->getDecision();

	for(size_t j=0; j<ringerDec->size();++j){
                if (ringerDec->at(j)==Efic::ELECTRON) ++neuralElc;
                else ++neuralJet;
                ++totalData;                 
        }


        cout<<"Total Data "<<totalData<<endl;
        cout<<"Neural Electrons "<<neuralElc<<endl;
        cout<<"Neural Jets "<<neuralJet<<endl;

        detNeural = neuralElc*100./totalData;

        TPaveText *pt = new TPaveText(.05,.05,.95,.95);
        TString line1, line2, line3, line6, line7;

        line1.Form("Total Data = %.0f",totalData);
        line2.Form("Neural Ringer Detected Electrons = %.0f", neuralElc);
        line3.Form("Neural Ringer Detected Jets = %.0f", neuralJet);
        line6.Form("Neural Ringer Electrons Rate = %.4f", detNeural);
        line7.Form("Neural Ringer Jets Rate = %.4f", 100.-detNeural);

        pt->AddText("");
        pt->AddText(line1);
        pt->AddText("");
        pt->AddText(line2);
        pt->AddText(line3);
        pt->AddText("");
        pt->AddText(line6);
        pt->AddText(line7);

        pt->SetFillColor(30);
        pt->SetTextAlign(12);

        pt->SetLabel("Hypos Comparison v1.0");

        pt->Draw();

        return 0;

}


float productSP(const float eDetRatio, const float jDetRatio){
	return ((eDetRatio/100.+jDetRatio/100.)/2.)*sqrt(eDetRatio/100.*jDetRatio/100.);
}
