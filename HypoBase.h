#ifndef HYPOBASE_H
#define HYPOBASE_H

#include<vector>
#include<iostream>
#include<cmath>
#include<TChain.h>
#include<TH1I.h>
#include<TTree.h>
#include<iostream>
using std::cout;
using std::endl;

class HypoBase {

    protected:

        enum CODE {ERROR=0, OK};
        virtual CODE swapVectors(const size_t index1, const size_t index2) = 0;
        virtual CODE eraseVectors(const size_t index) = 0;
        std::vector<float>      *lvl2_eta;
        std::vector<float>      *lvl2_phi;
        std::vector<int>        *decision;
        std::vector<float>      *et;
        //Some analysis data:
        unsigned totalData;
        unsigned detElc;
        unsigned detJet;
        float detRate;
        float faRate;
        std::string dataLabel;

        TChain *hypoChain;
        TTree *extraVariables;

    public:
        enum DECISION {JET = -1, ELECTRON = 1};

        HypoBase(const std::string &chainPath){
            extraVariables = 0;
            hypoChain = new TChain("CollectionTree");
            hypoChain->Add(chainPath.c_str());
            hypoChain->SetBranchStatus("*", false);
            lvl2_eta  = new std::vector<float>;
            lvl2_phi  = new std::vector<float>;
            decision  = new std::vector<int>;
            et        = new std::vector<float>;
            size_t comp = chainPath.find("electrons");
            if (comp != std::string::npos){
                dataLabel = "elc";
            } else {
                comp = chainPath.find("jet");
                if (comp!= std::string::npos){
                    dataLabel = "jet";
                }else{
                    std::string input;
                    cout<<"No ID found, insert elc/jet"<<endl;
                    while( input == "elc" || input == "jet" ){
                        std::getline(cin,input);
                    }
                    dataLabel = input;
                }
            }
        }

        virtual void getExtraVariables(const TTree*& refExtraVariables){ refExtraVariables = extraVariables; };
        unsigned getTotalData(){ return totalData;};
        unsigned getDetElc(){return detElc;};
        unsigned getDetJet(){return detJet;};
        float    getDetRate(){return detRate;};
        float    getFaRate(){return faRate;};
        float    getDataLabel(const std::string &hypoDataLabel){ hypodataLabel = dataLabel;};

        virtual CODE exec() = 0;
        virtual ~HypoBase(){ 
            delete hypoChain;
            if (extraVariables !=0)
                delete extraVariables;
            delete lvl2_eta;
            delete lvl2_phi;
            delete decision;
            delete et;
        }

};

#endif
