#ifndef HYPOBASE
#define HYPOBASE

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

        TChain *hypoChain;

    public:

        enum DECISION {JET = -1, ELECTRON = 1};


        HypoBase(const std::string &chainPath){

            cout<<"Entrei no HypoBase"<<endl;
            hypoChain = new TChain("CollectionTree");

            hypoChain->Add(chainPath.c_str());

            hypoChain->SetBranchStatus("*", false);

            lvl2_eta  = new std::vector<float>;
            lvl2_phi  = new std::vector<float>;
            decision  = new std::vector<int>;
            et        = new std::vector<float>;

            cout<<"Terminei HypoBase"<<endl;

        }

        const std::vector<float> *getEta(){  return lvl2_eta; }
        const std::vector<float> *getPhi(){  return lvl2_phi; }
        const std::vector<int>   *getDec(){  return decision; }
        const std::vector<float> *getEt() {  return et;       }

        virtual CODE exec() = 0;

        ~HypoBase(){ 
            delete lvl2_eta;
            delete lvl2_phi;
            delete decision;
            delete et;
        }

};

#endif
