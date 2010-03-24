#include "HypoBase.h"

HypoBase::CODE HypoBase::baseInit(const std::string &chainPath, const std::string &userDataLabel){
  cout<<"Alpha"<<endl;
  totalData = 0;
  detElc = 0;
  detJet = 0;
  dataLabel = userDataLabel;
  hypoChain = new TChain("CollectionTree");
  extraVariables = 0;
  hypoChain->Add(chainPath.c_str());
  hypoChain->SetBranchStatus("*", false);
  lvl2_eta  = new std::vector<float>;
  lvl2_phi  = new std::vector<float>;
  decision  = new std::vector<int>;
  et        = new std::vector<float>;
  cout<<"Alpha1"<<endl;
  if (dataLabel.find("Electron") != std::string::npos){
    id = "elc";
  } else if (dataLabel.find("electron") != std::string::npos){
    id = "elc";
  } else if (dataLabel.find("elc") != std::string::npos){
    id = "elc";
  } else if (dataLabel.find("Jet") != std::string::npos){
    id = "jet";
  } else if (dataLabel.find("jet") != std::string::npos){
    id = "jet";
  } else {
    std::string input;
    while( (input != "elc") && (input != "jet") ){
        cout<<"Could not set by ID. Type elc for electrons, jet for jets:[elc/jet]"<<endl;
        std::getline(std::cin, input);
    }
    id = input;
  }
  cout<<"ID set to: "<<id<<endl;
  if( id == "elc")
    color = kBlue;
  else if ( id == "jet")
    color = kRed;
  cout<<"Alpha3"<<endl;
  return HypoBase::OK;
}

HypoBase::CODE HypoBase::baseInit(const std::string &chainPath, const std::string &userDataLabel, const std::string &userId){
  totalData = 0;
  detElc = 0;
  detJet = 0,
  dataLabel = userDataLabel;
  id = userId;
  if(userId == "elc")
    color = kBlue;
  else if (userId == "jet")
    color = kRed;
  else if (userId != "pile-elc" && userId != "pile-jet")//TODO Change this stupid way of dealing error
    throw;
  hypoChain = new TChain("CollectionTree");
  hypoChain->Add(chainPath.c_str());
  hypoChain->SetBranchStatus("*", false);
  lvl2_eta  = new std::vector<float>;
  lvl2_phi  = new std::vector<float>;
  decision  = new std::vector<int>;
  et        = new std::vector<float>;
  return HypoBase::OK;
}

//Old Code that would match Eta and Phi and do not consider coordinate pi discontinuously 
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

    for(size_t i=0; i<lvl2_eta->size(); ++i){
        if ( i < eta->size() ){
            float deta = 999999.;
            float dphi = 999999.;
            int matchingPair = -1;
            for(size_t j=i; j<eta->size(); ++j){
                float tdeta = std::abs(lvl2_eta->at(j) - eta->at(i));
                float tfdphi = std::abs( lvl2_phi->at(j) - phi->at(i) );
                float tsdphi = std::abs( lvl2_phi->at(j) + phi->at(i) );
                float tdphi = (tfdphi<tsdphi)?tfdphi:tsdphi;
                if (tdeta < deta && tdphi < dphi){
                    deta = tdeta;
                    dphi = tdphi;
                    if ( deta < MAXDETA && dphi < MAXDPHI )
                        matchingPair = j;
                }
            }
            if (matchingPair == -1){
                cout<<"WARNING :: T2Calo Cluster doesnt match with any inside Ringer Clusters"<<endl;
                cout<<"T2Calo Cluster : "<<endl;
                cout<<"     eta : ";
                for (size_t pos=0; pos<lvl2_eta->size(); ++pos)
                    cout<<lvl2_eta->at(pos)<<" ";
                cout<<endl<<"     phi : ";
                for (size_t pos=0; pos<lvl2_phi->size(); ++pos)
                    cout<<lvl2_phi->at(pos)<<" ";
                cout<<endl<<"Ringer Cluster : "<<endl;
                cout<<"     eta : ";
                for (size_t pos=0; pos<eta->size(); ++pos)
                    cout<<eta->at(pos)<<" ";
                cout<<endl<<"     phi : ";
                for (size_t pos=0; pos<phi->size(); ++pos)
                    cout<<phi->at(pos)<<" ";
                cout<<endl<<"WARNING :: Deleting event!"<<endl;
                eraseVectors(0);
                break;
            }else{ 
                unsigned uMatching = matchingPair;
                if ( uMatching != i ){ 
                    swapVectors(i,uMatching);
                }
            }
        }else{
            eraseVectors(i);
            break;
        }  
    }
    return HypoBase::OK;
}

HypoBase::CODE HypoBase::fillHypoRate(){
    if (totalData !=0){
        if (id  == "elc"){
            detRate = (float)detElc/(float)totalData*100.;
            faDetRate = (float)detJet/(float)totalData*100.;
        }
        else if (id == "jet"){
            detRate = (float)detJet/(float)totalData*100.;
            faDetRate = (float)detJet/(float)totalData*100.;
        }
    }
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
