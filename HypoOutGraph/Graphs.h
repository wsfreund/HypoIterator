#include "TChain.h"
#include <cstring>
#include <cmath>
#include <iostream>

#ifndef GRAPHS
#define GRAPHS



class Graphs {

    protected:

    static const int DEBUG = 1;
	std::vector<float> *lvl2_eta;
	std::vector<float> *lvl2_phi;
	std::vector<float> *et;

	enum CODE {ERROR=0, OK};

    //Chain:
    TChain  *readChain;
    std::string dataLabel;

    virtual CODE swapVectors(const size_t index1, const size_t index2) = 0;
    virtual CODE eraseVectors(const size_t index) = 0;

    public: 

    Graphs(const std::string &stringPath, const std::string &userDataLabel){

	    lvl2_eta = new std::vector<float>;
        lvl2_phi = new std::vector<float>;
        et = new std::vector<float>;
      

    	readChain = new TChain("CollectionTree");
	    readChain->Add(stringPath.c_str());
	    readChain->SetBranchStatus("*",	false);

        dataLabel = userDataLabel;

    }

    CODE ordenateRoi(const std::vector<float> *eta, const std::vector<float> *phi){

        for(size_t j=0; j<lvl2_eta->size();++j){
            if ( j < eta->size() ){
                unsigned matchingPair = 	j;
                float	vError	=	sqrt (pow(( eta->at(j) - lvl2_eta->at(j) ),2)+pow(( phi->at(j) - lvl2_phi->at(j) ),2) );
                for(size_t k= (j+1) ; k < (lvl2_eta->size()); ++k){
                    float actualError =  sqrt (pow(( eta->at(j) - lvl2_eta->at(k) ),2)+pow(( phi->at(j) - lvl2_phi->at(k) ),2) );
                    if ( actualError < vError ) {
                        vError = actualError;
                        matchingPair = k;
                    }
                }
                if (j!=matchingPair) {
                    swapVectors(j,matchingPair);
                }
            }else{
                eraseVectors(j);
                break;
            }
        }
	    return OK;
    }
    
    ~Graphs(){
    
		delete  lvl2_eta;
		delete  lvl2_phi;
		delete  et;
        delete  readChain;
    }


};

#endif
