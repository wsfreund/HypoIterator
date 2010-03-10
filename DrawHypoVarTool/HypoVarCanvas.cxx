#include "HypoVarCanvas.h"
HypoVarCanvas::HypoVarCanvas(HypoVarBase *hypoVar1, HypoVarBase *hypoVar2){
    hypoVarCanvas = 0;
    HypoBase *hypoBase1 = dynamic_cast<HypoBase*>(hypoVar1);
    HypoBase *hypoBase2 = dynamic_cast<HypoBase*>(hypoVar2);
    if (hypoBase1){
        std::string dataLabel;
        hypoBase1->getDataLabel(dataLabel);
        size_t comp = dataLabel.find("pile");
        if (comp != std::string::npos)
             hypoVarPile = hypoVar1;
        else if (dataLabel == "elc" || dataLabel == "jet")
             hypoVarCommon = hypoVar1;
    }
    if (hypoBase2){
        std::string dataLabel;
        hypoBase2->getDataLabel(dataLabel);
        size_t comp = dataLabel.find("pile");
        if (comp != std::string::npos)
             hypoVarPile = hypoVar2;
        else if (dataLabel == "elc" || dataLabel == "jet")
             hypoVarCommon = hypoVar2;
    }
    if ( !(hypoVarCommon) || !(hypoVarPile)){
        cout<<"Wrong parameters"<<endl;
        delete this;
    }

}   


int HypoVarCanvas::Draw(){

    hypoVarCanvas = new TCanvas("Hypo Variables Analysis", "Hypo Variables Analysis");
    T2CaVarGraph *t2varPile   = dynamic_cast<T2CaVarGraph*>(hypoVarPile);
    T2CaVarGraph *t2varCommon = dynamic_cast<T2CaVarGraph*>(hypoVarCommon);

    hypoVarCanvas->Divide(2,2);

    if (t2varPile && t2varCommon){
        TVirtualPad *rcorePad = hypoVarCanvas->cd(1);
        cout<<"Common rcore maximum = "<<t2varCommon->getHist("rcore")->GetMaximum()/t2varCommon->getHist("rcore")->GetEntries()<<endl;
        cout<<"Pile rcore maximum = "<<t2varPile->getHist("rcore")->GetMaximum()/t2varPile->getHist("rcore")->GetEntries()<<endl;
        if (t2varCommon->getHist("rcore")->GetMaximum()/ t2varCommon->getHist("rcore")->GetEntries()> t2varPile->getHist("rcore")->GetMaximum()/t2varPile->getHist("rcore")->GetEntries()){
          t2varCommon->DrawVar("rcore");
          t2varPile->DrawVar("rcore","sames");
        } else {
          t2varPile->DrawVar("rcore");
          t2varCommon->DrawVar("rcore","sames");
        }
        rcorePad->SetFillColor(33);
        rcorePad->Modified();
        TVirtualPad *eratioPad = hypoVarCanvas->cd(2);
        cout<<"Common eratio maximum = "<<t2varCommon->getHist("eratio")->GetMaximum()/t2varCommon->getHist("eratio")->GetEntries()<<endl;
        cout<<"Pile eratio maximum = "<<t2varPile->getHist("eratio")->GetMaximum()/t2varPile->getHist("eratio")->GetEntries()<<endl;
        if (t2varCommon->getHist("eratio")->GetMaximum()/t2varCommon->getHist("eratio")->GetEntries() > t2varPile->getHist("eratio")->GetMaximum()/t2varPile->getHist("eratio")->GetEntries()){
          t2varCommon->DrawVar("eratio");
          t2varPile->DrawVar("eratio","sames");
        } else {
          t2varPile->DrawVar("eratio");
          t2varCommon->DrawVar("eratio","sames");
        }
        eratioPad->SetFillColor(33);
        eratioPad->Modified();
        cout<<"Common et maximum = "<<t2varCommon->getHist("et")->GetMaximum()/t2varCommon->getHist("et")->GetEntries()<<endl;
        cout<<"Pile et maximum = "<<t2varPile->getHist("et")->GetMaximum()/t2varPile->getHist("et")->GetEntries()<<endl;
        TVirtualPad *etPad = hypoVarCanvas->cd(3);
        if (t2varCommon->getHist("et")->GetMaximum()/t2varCommon->getHist("et")->GetEntries()> t2varPile->getHist("et")->GetMaximum()/t2varPile->getHist("et")->GetEntries()){
          t2varCommon->DrawVar("et");
          t2varPile->DrawVar("et","sames");
        } else {
          t2varPile->DrawVar("et");
          t2varCommon->DrawVar("et","sames");
        }
        etPad->SetFillColor(33);
        etPad->Modified();
        cout<<"Common hadet maximum = "<<t2varCommon->getHist("hadet")->GetMaximum()/t2varCommon->getHist("hadet")->GetEntries()<<endl;
        cout<<"Pile hadet maximum = "<<t2varPile->getHist("hadet")->GetMaximum()/t2varPile->getHist("hadet")->GetEntries()<<endl;
        TVirtualPad *hadEtPad = hypoVarCanvas->cd(4);
        if (t2varCommon->getHist("hadet")->GetMaximum()/t2varCommon->getHist("hadet")->GetEntries() > t2varPile->getHist("hadet")->GetMaximum()/t2varPile->getHist("hadet")->GetEntries()){
          t2varCommon->DrawVar("hadet");
          t2varPile->DrawVar("hadet","sames");
        } else {
          t2varPile->DrawVar("hadet");
          t2varCommon->DrawVar("hadet","sames");
        }
        hadEtPad->SetFillColor(33);
        hadEtPad->Modified();
        TVirtualPad *t2caVarPad = hypoVarCanvas->cd();
        t2caVarPad->SetFillColor(18);
    }
    return 0;

}


