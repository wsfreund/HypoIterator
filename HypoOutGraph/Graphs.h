#include "TChain.h"
#include <cstring>

#ifndef GRAPHS
#define GRAPHS



class Graphs {

    protected:

    static const int DEBUG = 0;
	std::vector<float> *lvl2_eta;
	std::vector<float> *lvl2_phi;
	std::vector<float> *et;

	enum CODE {ERROR=0, OK};

    //Chain:
    TChain  *readChain;
    std::string dataLabel;


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
    
    ~Graphs(){
    
		delete  lvl2_eta;
		delete  lvl2_phi;
		delete  et;
        delete readChain;
    }


};

#endif
