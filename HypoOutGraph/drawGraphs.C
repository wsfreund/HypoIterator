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
    myT2CaloGraphs.draw_rCore();

    hypoOutGraphsCanvas->cd(2);
    myT2CaloGraphs.draw_eRatio();

    hypoOutGraphsCanvas->cd(3);
    myT2CaloGraphs.draw_et();

    hypoOutGraphsCanvas->cd(4);
    myT2CaloGraphs.draw_hadEt();

    hypoOutGraphsCanvas->cd();
    hypoOutGraphsCanvas->Update();


    return 0;

}



int drawGraphs(const std::string &dataPath1, const std::string &dataPath2, const std::string &dataType1, const std::string &dataType2){

    TCanvas *hypoOutGraphsCanvas = new TCanvas("HypoOutGraphs", "HypoOutGraphs");
    hypoOutGraphsCanvas->SetFillColor(kYellow-10);
    hypoOutGraphsCanvas->Divide(2,2);

    T2CaloGraphs myT2CaloGraphs1(dataPath1, dataType1);

    T2CaloGraphs myT2CaloGraphs2(dataPath2, dataType2);

    float minrCore1 = myT2CaloGraphs1.getMinrCore();
    float maxrCore1 = myT2CaloGraphs1.getMaxrCore();
    float mineRatio1 = myT2CaloGraphs1.getMineRatio();
    float maxeRatio1 = myT2CaloGraphs1.getMaxeRatio();
    float minEt1 = myT2CaloGraphs1.getMinEt();
    float maxEt1 = myT2CaloGraphs1.getMaxEt();
    float minHadEt1 = myT2CaloGraphs1.getMinHadEt();
    float maxHadEt1 = myT2CaloGraphs1.getMaxHadEt();

    float minrCore2 = myT2CaloGraphs2.getMinrCore();
    float maxrCore2 = myT2CaloGraphs2.getMaxrCore();
    float mineRatio2 = myT2CaloGraphs2.getMineRatio();
    float maxeRatio2 = myT2CaloGraphs2.getMaxeRatio();
    float minEt2 = myT2CaloGraphs2.getMinEt();
    float maxEt2 = myT2CaloGraphs2.getMaxEt();
    float minHadEt2 = myT2CaloGraphs2.getMinHadEt();
    float maxHadEt2 = myT2CaloGraphs2.getMaxHadEt();

    float minrCore = (minrCore1<minrCore2)?minrCore1:minrCore2;
    float maxrCore = (maxrCore1>maxrCore2)?maxrCore1:maxrCore2;
    float mineRatio = (mineRatio1<mineRatio2)?mineRatio1:mineRatio2;
    float maxeRatio = (maxeRatio1>maxeRatio2)?maxeRatio1:maxeRatio2;
    float minEt = (minEt1<minEt2)?minEt1:minEt2;
    float maxEt = (maxEt1>maxEt2)?maxEt1:maxEt2;
    float minHadEt = (minHadEt1<minHadEt2)?minHadEt1:minHadEt2;
    float maxHadEt = (maxHadEt1>maxHadEt2)?maxHadEt1:maxHadEt2;

    myT2CaloGraphs1.exec(minrCore, maxrCore, mineRatio, maxeRatio, minEt, maxEt, minHadEt, maxHadEt);
    myT2CaloGraphs2.exec(minrCore, maxrCore, mineRatio, maxeRatio, minEt, maxEt, minHadEt, maxHadEt);

    float yrcore1 = myT2CaloGraphs1.getY("rcore");
    float yeratio1 = myT2CaloGraphs1.getY("eratio");
    float yet1 = myT2CaloGraphs1.getY("et");
    float yhadet1 = myT2CaloGraphs1.getY("hadet");

    float yrcore2 = myT2CaloGraphs2.getY("rcore");
    float yeratio2 = myT2CaloGraphs2.getY("eratio");
    float yet2 = myT2CaloGraphs2.getY("et");
    float yhadet2 = myT2CaloGraphs2.getY("hadet");

    float yrcore = (yrcore1>yrcore2)?yrcore1:yrcore2;
    float yeratio = (yeratio1>yeratio2)?yeratio1:yeratio2;
    float yet = (yet1>yet2)?yet1:yet2;
    float yhadet = (yhadet1>yhadet2)?yhadet1:yhadet2;

    myT2CaloGraphs1.setRange("rcore", yrcore);
    myT2CaloGraphs1.setRange("eratio", yeratio);
    myT2CaloGraphs1.setRange("et", yet);
    myT2CaloGraphs1.setRange("hadet", yhadet);


    myT2CaloGraphs2.setRange("rcore", yrcore);
    myT2CaloGraphs2.setRange("eratio", yeratio);
    myT2CaloGraphs2.setRange("et", yet);
    myT2CaloGraphs2.setRange("hadet", yhadet);

    hypoOutGraphsCanvas->cd(1);
//    setAxisRange(myT2CaloGraphs1, myT2CaloGraphs2, "rcore");
    myT2CaloGraphs1.draw_rCore();
    myT2CaloGraphs2.draw_rCore("sames");

    hypoOutGraphsCanvas->cd(2);
//    setAxisRange(myT2CaloGraphs1, myT2CaloGraphs2, "eratio");
    myT2CaloGraphs1.draw_eRatio();
    myT2CaloGraphs2.draw_eRatio("sames");

    hypoOutGraphsCanvas->cd(3);
    myT2CaloGraphs1.draw_et();
//    setAxisRange(myT2CaloGraphs1, myT2CaloGraphs2, "et");
    myT2CaloGraphs2.draw_et("sames");

    hypoOutGraphsCanvas->cd(4);
//    setAxisRange(myT2CaloGraphs1, myT2CaloGraphs2, "hadet");
    myT2CaloGraphs1.draw_hadEt();
    myT2CaloGraphs2.draw_hadEt("sames");

    hypoOutGraphsCanvas->cd();
    hypoOutGraphsCanvas->Update();


    return 0;

}

/*

int setAxisRange(T2CaloGraphs &myT2CaloGraphs1, T2CaloGraphs &myT2CaloGraphs2, const std::string &datatype){

    float minX1 = myT2CaloGraphs1.getminX(datatype);
    float maxX1 = myT2CaloGraphs1.getmaxX(datatype);

    float minX2 = myT2CaloGraphs2.getminX(datatype);
    float maxX2 = myT2CaloGraphs2.getmaxX(datatype);

    float maxY1 = myT2CaloGraphs1.getY(datatype);
    float maxY2 = myT2CaloGraphs2.getY(datatype);

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
