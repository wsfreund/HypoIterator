#include "HypoBase.h"

HypoBase::HypoBase(const std::string &chainPath){
    extraVariables = 0;
    hypoChain = new TChain("CollectionTree");
    hypoChain->Add(chainPath.c_str());
    hypoChain->SetBranchStatus("*", false);
    lvl2_eta  = new std::vector<float>;
    lvl2_phi  = new std::vector<float>;
    decision  = new std::vector<int>;
    et        = new std::vector<float>;
    size_t comp = chainPath.find("singlepart");
    if (comp != std::string::npos){
        dataLabel = "elc";
    } else {
        comp = chainPath.find("jf17");
        if (comp!= std::string::npos){
            dataLabel = "jet";
        }else{
            std::string input;
            while( (input != "elc") && (input != "jet") ){
                cout<<"No ID found, insert elc/jet"<<endl;
                std::getline(std::cin, input);
            }
            cout<<"Data will be treated as "<<input<<endl;
            dataLabel = input;
        }
    }
}

//Old Code that would match Eta and Phi that would not consider the -pi and +pi discontinuously 
/*HypoBase::CODE HypoBase::matchAndOrdenate(const std::vector<float> *eta, const std::vector<float> *phi){

    for(size_t j=0; j<lvl2_eta->size();++j){
        if ( j < eta->size() ){
            unsigned matchingPair =     j;
            float    vError  =       sqrt (pow(( eta->at(j) - lvl2_eta->at(j) ),2)+pow(( phi->at(j) - lvl2_phi->at(j) ),2) );
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
    return HypoBase::OK;
}*/

HypoBase::CODE HypoBase::matchAndOrdenate(const std::vector<float> *eta, const std::vector<float> *phi){

    const float MAXDPHI = 0.1;
    const float MAXDETA = 0.1;

    for(size_t i=0; i<lvl2_eta->size(); ++i){
        cout<<"Stating loop over T2Ca Eta:"<<i<<endl;
        float deta = 999999.;
        float dphi = 999999.;
        int matchingPair = -1;
        for(size_t j=i; j<eta->size(); ++j){
            cout<<"Starting loop over Ringer Eta:"<<j<<endl;
            cout<<"Initial deta = "<<deta<<"    |  Initial   dphi = "<<dphi<<endl;
            cout<<"|T2Ca Eta - Ringer Eta| = "<<abs(lvl2_eta->at(j) - eta->at(i))<<endl;
            cout<<"|T2Ca Phi - Ringer Phi| = "<<abs(lvl2_phi->at(j) - phi->at(i))<<endl;
            cout<<"|T2Ca Phi + Ringer Phi| = "<<abs(lvl2_phi->at(j) + phi->at(i))<<endl;
            if ( abs(lvl2_eta->at(j) - eta->at(i))< deta )
                deta = abs(lvl2_eta->at(j) - eta->at(i));
            float fdphi = abs( lvl2_phi->at(j) - phi->at(i) );
            float sdphi = abs( lvl2_phi->at(j) + phi->at(i) );
            if (sdphi<fdphi)
                fdphi = sdphi;
            if (fdphi<dphi)
                dphi = fdphi;
            cout<<"Final deta = "<<deta<<"    |  Final  dphi = "<<dphi<<endl;
            if ( deta < MAXDETA && dphi < MAXDPHI )
                matchingPair = j;
        }
        if (matchingPair == -1){
            cout<<"WARNING :: T2Calo Cluster doesnt match with any inside Ringer Clusters"<<endl;
            cout<<"WARNING :: Deleting event!"<<endl;
            eraseVectors(0);
            break;
        }else {
            unsigned uMatching = matchingPair;
            if ( i == uMatching){
                eraseVectors(i);
                break;
            }else{ 
                swapVectors(i,uMatching);
            }   
        }
    }
    return HypoBase::OK;
}

HypoBase::CODE HypoBase::fillHypoRate(){

    if (dataLabel == "elc")
        detRate = (float)detElc/(float)totalData*100;
    else if (dataLabel == "jet")
        detRate = (float)detJet/(float)totalData*100;
    return HypoBase::OK;
}

HypoBase::~HypoBase(){ 
    delete hypoChain;
    if (extraVariables !=0)
        delete extraVariables;
    delete lvl2_eta;
    delete lvl2_phi;
    delete decision;
    delete et;
}

