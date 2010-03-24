#include "HypoErrorsGraph.h"

HypoErrorsGraph::HypoErrorsGraph(const float userLOWEDGE, const float userHIEDGE, HypoBase *userDataHypo, const std::string &branchName, const unsigned userNREGIONS, const std::string &userTitle)
{
    NREGIONS = userNREGIONS;
    NPOINTS = userNREGIONS+1;
    LOWEDGE = userLOWEDGE;
    HIEDGE = userHIEDGE;
    dataHypo = userDataHypo;
    title = userTitle;
    id = dataHypo->getId();
    cout<<"Alpha 1"<<endl;
    dataTree = dataHypo->getExtraVariables();
    cout<<"Alpha 2"<<endl;
    vectorInput = new std::vector<float>;
    vectorDec = new std::vector<int>;
    cout<<"Alpha 3"<<endl;
    cout<<"extraVariables "<<dataTree<<endl;
    dataTree->SetBranchAddress(branchName.c_str(), &vectorInput);
    if (branchName == "T2CaEt")
        mev2gev = true;
    else 
        mev2gev = false;
    cout<<"Alpha 4"<<endl;
    const char * decBranch;
    if (dynamic_cast<T2CaCommon*>(dataHypo)){
        cout<<"Alpha 5"<<endl;
        decBranch = "T2CaDec";
    }else{
      cout<<"Alpha 6"<<endl;
      if (dynamic_cast<NeuralCommon*>(dataHypo)){
          decBranch = "Ringer_Dec";
      }
      else{
        cout<<"Entered wrong type of Hypo"<<endl;
        throw;
      }
    }
    cout<<"Alpha 7"<<endl;
    dataTree->SetBranchAddress(decBranch, &vectorDec);
    cout<<"Alpha 8"<<endl;
}

HypoErrorsGraph::HypoErrorsGraph(const float userLOWEDGE, const float userHIEDGE, std::vector<float> *&dataVector, std::vector<int> *&inputDec, const unsigned userNREGIONS, const std::string &userId, const std::string &userTitle)
{
    NREGIONS = userNREGIONS;
    NPOINTS = userNREGIONS+1;
    LOWEDGE = userLOWEDGE;
    HIEDGE = userHIEDGE;
    vectorInput = dataVector;
    vectorDec = inputDec;
    id = userId;
    dataHypo = 0;
    title = userTitle;
    mev2gev = false;
}
    


HypoErrorsGraph::CODE HypoErrorsGraph::genGraph(){

    float edges[NPOINTS], *pEdges;
    pEdges = edges;
    genEdges(pEdges);
    float exl[NREGIONS], exh[NREGIONS], x[NREGIONS], effic[NREGIONS], hiErrors[NREGIONS], lowErrors[NREGIONS], *pX, *peffic, *pHiErrors, *pLowErrors;
    for( unsigned i=0; i<NREGIONS; ++i){
        exl[i]=0.; exh[i]=0.; x[i]=0; effic[i]=0; hiErrors[i]=0; lowErrors[i]=0;
    }
    pX = x; peffic = effic; pHiErrors = hiErrors; pLowErrors = lowErrors;
    //Generating x, effic, lowErrors, hiErrors, also eliminate regions with no data.
    genEfficErrors(pEdges, pX, peffic, pLowErrors, pHiErrors); 
    //Generating Graph
    graph = new TGraphAsymmErrors(NREGIONS, x, effic, exl, exh, lowErrors, hiErrors);
    graph->SetFillColor(19);
    //Setting graph parameters:
    graph->SetTitle(title.c_str());

    return HypoErrorsGraph::OK;
}

inline HypoErrorsGraph::CODE HypoErrorsGraph::genEdges(float* edges){
    unsigned i = 0;
    for(float edge = LOWEDGE; i<NPOINTS; edge+= ( HIEDGE - LOWEDGE ) / ( NREGIONS ), ++edges, ++i)
        *edges=edge;
    edges -= NPOINTS; 
    return HypoErrorsGraph::OK;
}

inline HypoErrorsGraph::CODE HypoErrorsGraph::incrementEdges(const float* edges, float* centerBin){
    for(unsigned i = 0; i < NREGIONS;++i, ++edges, ++centerBin)
    edges -= NREGIONS; centerBin-= NREGIONS;// it only iterates for NREGIONS even though edges is NPOINTS size.
    return HypoErrorsGraph::OK;
}


HypoErrorsGraph::CODE HypoErrorsGraph::genEfficErrors(float* edges, float* pX, float* effic, float* lowEdgeErrors, float* hiEdgeErrors){

    const float HALF_REGION_SIZE = ( HIEDGE - LOWEDGE ) / ( NREGIONS ) * .5;

    if ( dataHypo!=0){
        Long64_t n_entries = static_cast<Long64_t>( dataTree->GetEntries());
        for(unsigned lowEdge = 0; lowEdge < NREGIONS; ++lowEdge ){
            unsigned regElectrons = 0;
            unsigned regData = 0;
            for(Long64_t entry = 0; entry < n_entries; ++entry){
                dataTree->GetEntry(entry);
                for(size_t i=0; i < vectorInput->size();++i){
                    if ( mev2gev )
                        vectorInput->at(i) *= 0.001;
                    if ( isAtRegion(*edges, vectorInput->at(i), *(edges+1)) ){
                        ++regData;
                        if (vectorDec->at(i) == HypoBase::ELECTRON)
                            ++regElectrons;
                    }
                }
            }   
            float error =-1;
            if (regData!=0){
                error = 1/TMath::Sqrt(regData)*100.;
                *pX = (*edges) + HALF_REGION_SIZE;
                if ( id.find("elc") != std::string::npos )
                    *effic = (float)regElectrons / (float)regData*100.;
                else if ( id.find("jet") != std::string::npos )
                    *effic = (float)regElectrons / (float)regData *100.;
                checkAndGenErrors(*effic, error, *lowEdgeErrors, *hiEdgeErrors);
                ++pX; ++effic; ++lowEdgeErrors; ++hiEdgeErrors; ++edges;
            }else{
                for(unsigned decrementEdges = lowEdge; decrementEdges < NREGIONS; ++decrementEdges, ++edges)
                    *edges = *(edges+1);
                edges-=(NREGIONS - lowEdge);
                --NREGIONS, --lowEdge;
            }
        }
    }else{
        for(unsigned lowEdge = 0; lowEdge < NREGIONS; ++lowEdge, ++effic, ++lowEdgeErrors, ++hiEdgeErrors){
            unsigned regElectrons = 0;
            unsigned regData = 0;
            for(size_t i=0; i < vectorInput->size();++i){
                ++regData;
                if ( isAtRegion(*edges, vectorInput->at(i), *(edges+1)) ){
                    if (vectorDec->at(i) == HypoBase::ELECTRON)
                        ++regElectrons;
                }
            }
            float error =-1;
            if (regData!=0){
                error = 1/TMath::Sqrt(regData)*100.;
                *pX = (*edges) + HALF_REGION_SIZE;
                if ( id.find("elc") != std::string::npos )
                    *effic = (float)regElectrons / (float)regData*100.;
                else if ( id.find("jet") != std::string::npos)
                    *effic = (float)regElectrons / (float)regData *100.;
                checkAndGenErrors(*effic, error, *lowEdgeErrors, *hiEdgeErrors);
                ++pX; ++effic; ++lowEdgeErrors; ++hiEdgeErrors; ++edges;
            }else{
                for(unsigned decrementEdges = lowEdge; decrementEdges < NREGIONS; ++decrementEdges, ++edges)
                    *edges = *(edges+1);
                edges-=(NREGIONS - lowEdge);
                --NREGIONS, --lowEdge;
            }
        }
    }
    effic -= NREGIONS; lowEdgeErrors-=NREGIONS; hiEdgeErrors-=NREGIONS; edges -=NREGIONS; pX -= NREGIONS;
    return HypoErrorsGraph::OK;

}


inline bool HypoErrorsGraph::isAtRegion(const float lowEdge, const float data, const float hiEdge){
    if ( ( data< hiEdge ) && ( data >= lowEdge ) ) 
        return true;
    else return false;
}

inline HypoErrorsGraph::CODE HypoErrorsGraph::checkAndGenErrors(const float &effic, float &error, float &lowError, float &hiError){
    if ( error + effic > 100.)
        hiError = 100.-effic;
    else
        hiError = error;
    if ( effic - error < 0)
        lowError = effic;
    else
        lowError = error;
    
    return HypoErrorsGraph::OK;
}


HypoErrorsGraph::CODE HypoErrorsGraph::Draw(const std::string &input){
    genGraph();
    graph->Draw(input.c_str());
    return HypoErrorsGraph::OK;
}

HypoErrorsGraph::HypoErrorsGraph &HypoErrorsGraph::operator=(const HypoErrorsGraph &graph2){
     NREGIONS = graph2.NREGIONS;
     NPOINTS = graph2.NPOINTS;
     LOWEDGE = graph2.LOWEDGE;
     HIEDGE = graph2.HIEDGE;
     vectorInput = graph2.vectorInput;
     vectorDec = graph2.vectorDec;
     dataHypo = graph2.dataHypo;
     dataTree= graph2.dataTree;
     title = graph2.title;

     return *this;
}

HypoErrorsGraph::HypoErrorsGraph* HypoErrorsGraph::operator=(const HypoErrorsGraph* &graph2){
     NREGIONS = graph2->NREGIONS;
     NPOINTS = graph2->NPOINTS;
     LOWEDGE = graph2->LOWEDGE;
     HIEDGE = graph2->HIEDGE;
     vectorInput = graph2->vectorInput;
     vectorDec = graph2->vectorDec;
     dataHypo = graph2->dataHypo;
     dataTree= graph2->dataTree;
     title = graph2->title;

     return this;
}

HypoErrorsGraph::~HypoErrorsGraph(){
    if (dataHypo!=0){
        delete vectorInput;
        delete vectorDec;
    }
}
