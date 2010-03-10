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
        cout<<"Drawing rcore"<<endl;
        hypoVarCanvas->cd(1);
        t2varPile->DrawVar("rcore");
        t2varCommon->DrawVar("rcore","sames");
        cout<<"Drawing eratio"<<endl;
        hypoVarCanvas->cd(1);
        hypoVarCanvas->cd(2);
        t2varPile->DrawVar("eratio");
        t2varCommon->DrawVar("eratio","sames");
        cout<<"Drawing et"<<endl;
        hypoVarCanvas->cd(3);
        t2varPile->DrawVar("et");
        t2varCommon->DrawVar("et","sames");
        cout<<"Drawing hadet"<<endl;
        hypoVarCanvas->cd(4);
        t2varPile->DrawVar("hadet");
        t2varCommon->DrawVar("hadet","sames");
    }
    return 0;

}


