#include <iostream>
#include <cstring>
#include <TChain.h>
#include <TTree.h>
#include <TCanvas.h>
#include <TString.h>
#include <TPaveText.h>
#include "Graphs.h"
#include "../Neural.h"
#include "NeuralGraphs.h"
#include "T2CaloGraphs.h"

//int setAxisRange(T2CaloGraphs &T2CaloGraphs1, T2CaloGraphs &T2CaloGraphs2, const std::string &datatype);

int drawGraphs(const std::string &dataPath, const std::string &dataType){

    TCanvas *hypoOutGraphsCanvas = new TCanvas("HypoOutGraphs", "HypoOutGraphs");
    hypoOutGraphsCanvas->SetFillColor(kYellow-10);
    hypoOutGraphsCanvas->Divide(2,2);

    T2CaloGraphs myT2CaloGraphs(dataPath, dataType);

    myT2CaloGraphs.exec();

    hypoOutGraphsCanvas->cd(1);
    myT2CaloGraphs.drawCut("rcore");

    hypoOutGraphsCanvas->cd(2);
    myT2CaloGraphs.drawCut("eratio");

    hypoOutGraphsCanvas->cd(3);
    myT2CaloGraphs.drawCut("et");

    hypoOutGraphsCanvas->cd(4);
    myT2CaloGraphs.drawCut("hadet");

    hypoOutGraphsCanvas->cd();
//    hypoOutGraphsCanvas->Update();


    return 0;

}



int drawGraphs(const std::string &dataPath1, const std::string &dataPath2, const std::string &dataType1, const std::string &dataType2){

    TCanvas *hypoOutGraphsCanvas = new TCanvas("HypoOutGraphs", "HypoOutGraphs");
    hypoOutGraphsCanvas->SetFillColor(kYellow-10);
    hypoOutGraphsCanvas->Divide(2,2);

    T2CaloGraphs *myT2CaloGraphs1 = new T2CaloGraphs(dataPath1, dataType1);

    T2CaloGraphs *myT2CaloGraphs2 = new T2CaloGraphs(dataPath2, dataType2);

    myT2CaloGraphs1->exec();
    myT2CaloGraphs2->exec();

    float yrcore1 = myT2CaloGraphs1->getMaximum("rcore");
    float yeratio1 = myT2CaloGraphs1->getMaximum("eratio");
    float yet1 = myT2CaloGraphs1->getMaximum("et");
    float yhadet1 = myT2CaloGraphs1->getMaximum("hadet");

    float yrcore2 = myT2CaloGraphs2->getMaximum("rcore");
    float yeratio2 = myT2CaloGraphs2->getMaximum("eratio");
    float yet2 = myT2CaloGraphs2->getMaximum("et");
    float yhadet2 = myT2CaloGraphs2->getMaximum("hadet");

    std::cout<<"Drawing rCore"<<std::endl;
    hypoOutGraphsCanvas->cd(1);
    if (yrcore1>yrcore2){
        myT2CaloGraphs1->drawCut("rcore");
        myT2CaloGraphs2->drawCut("rcore","sames");
    }else{
        myT2CaloGraphs2->drawCut("rcore");
        myT2CaloGraphs1->drawCut("rcore","sames");
    }
    std::cout<<"Drawing eRatio"<<std::endl;

    hypoOutGraphsCanvas->cd(2);
    if (yeratio1>yeratio2){
        myT2CaloGraphs1->drawCut("eratio");
        hypoOutGraphsCanvas->cd(2)->Update();
        myT2CaloGraphs2->drawCut("eratio","sames");
    }else{
        myT2CaloGraphs2->drawCut("eratio");
        hypoOutGraphsCanvas->cd(2)->Update();
        myT2CaloGraphs1->drawCut("eratio","sames");
    }

    std::cout<<"Drawing Et"<<std::endl;
    hypoOutGraphsCanvas->cd(3);
    if (yet1>yet2){
        myT2CaloGraphs1->drawCut("et");
        myT2CaloGraphs2->drawCut("et","sames");
    }else{
        myT2CaloGraphs2->drawCut("et");
        myT2CaloGraphs1->drawCut("et","sames");
    }    

    std::cout<<"Drawing hadEt"<<std::endl;
    hypoOutGraphsCanvas->cd(4);
    if (yhadet1>yhadet2){
        myT2CaloGraphs1->drawCut("hadet");
        myT2CaloGraphs2->drawCut("hadet","sames");
    }else{
        myT2CaloGraphs2->drawCut("hadet");
        myT2CaloGraphs1->drawCut("hadet","sames");
    }


    hypoOutGraphsCanvas->cd();
    hypoOutGraphsCanvas->Update();

    TCanvas *debug = new TCanvas("Debug", "Debug");
   
    myT2CaloGraphs1->drawCutCounter();
 
    TCanvas *debug2 = new TCanvas("Debug2", "Debug2");
     
    myT2CaloGraphs2->drawCutCounter();

    return 0;

}

/*

int setAxisRange(T2CaloGraphs &myT2CaloGraphs1, T2CaloGraphs &myT2CaloGraphs2, const std::string &datatype){

    float minX1 = myT2CaloGraphs1.getminX(datatype);
    float maxX1 = myT2CaloGraphs1.getmaxX(datatype);

    float minX2 = myT2CaloGraphs2.getminX(datatype);
    float maxX2 = myT2CaloGraphs2.getmaxX(datatype);

    float maxY1 = myT2CaloGraphs1.getMaximum(datatype);
    float maxY2 = myT2CaloGraphs2.getMaximum(datatype);

    if (minX1<minX2)
        if (maxX1>maxX2)
            if (maxY1 > maxY2){   
                std::cout<<"caso1"<<std::endl;
                myT2CaloGraphs2.setRange(datatype,minX1, maxX1, maxY1);
            }else{
                std::cout<<"caso2"<<std::endl;
                myT2CaloGraphs2.setRange(datatype,minX1, maxX1, maxY2);
                myT2CaloGraphs1.setRange(datatype,minX1, maxX1, maxY2);
        }else if (maxY1 > maxY2){
                std::cout<<"caso3"<<std::endl;
                myT2CaloGraphs2.setRange(datatype,minX1, maxX2, maxY1);
                myT2CaloGraphs1.setRange(datatype,minX1, maxX2, maxY1);
            }else{
                std::cout<<"caso4"<<std::endl;
                myT2CaloGraphs2.setRange(datatype,minX1, maxX2, maxY2);
                myT2CaloGraphs1.setRange(datatype,minX1, maxX2, maxY2);
    }else if (maxX1>maxX2)
            if (maxY1 > maxY2){
                std::cout<<"caso5"<<std::endl;
                myT2CaloGraphs2.setRange(datatype,minX2, maxX1, maxY1);
                myT2CaloGraphs1.setRange(datatype,minX2, maxX1, maxY1);
            }else {
                std::cout<<"caso6"<<std::endl;
                myT2CaloGraphs2.setRange(datatype,minX2, maxX1, maxY2);
                myT2CaloGraphs1.setRange(datatype,minX2, maxX1, maxY2);
        }else if(maxY1 > maxY2){
                myT2CaloGraphs2.setRange(datatype,minX2, maxX2, maxY1);
                myT2CaloGraphs1.setRange(datatype,minX2, maxX2, maxY1);
        }
    else {
            myT2CaloGraphs1.setRange(datatype,minX2, maxX2, maxY2);
    }

    return 0;

}

*/
