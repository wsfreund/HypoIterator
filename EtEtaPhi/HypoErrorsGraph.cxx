#include "HypoErrorsGraph.h"

HypoErrorsGraph::HypoErrorsGraph(const float userLOWEDGE, const float userHIEDGE, HypoBase *userDataHypo, const std::string &branchName, const unsigned userNREGIONS, const std::string &userTitle)
{
    NREGIONS = userNREGIONS;
    NPOINTS = userNREGIONS+1;
    LOWEDGE = userLOWEDGE;
    HIEDGE = userHIEDGE;
    dataHypo = userDataHypo;
    dataHypo->getExtraVariables(dataTree);
    vectorInput = new std::vector<float>;
    vectorDec = new std::vector<int>;
    dataTree->SetBranchAddress(branchName.c_str(), &vectorInput);
    HypoBase* pHypo = dynamic_cast<T2CaCommon*>(dataHypo);
    if (pHypo){
        dataTree->SetBranchAddress("T2CaDec", &vectorDec);
        title = userTitle;
    }else{
//        pHypo = dynamic_cast<const NeuralCommon*>(dataHypo);
        if (pHypo){
            dataTree->SetBranchAddress("Ringer_Dec", &vectorDec);
            title = userTitle;
        }else{
                cout<<"Entered wrong type of Hypo"<<endl;
                delete this;
        }
    }
    genGraph();
}

HypoErrorsGraph::HypoErrorsGraph(const float userLOWEDGE, const float userHIEDGE, std::vector<float> *&dataVector, std::vector<int> *&inputDec, const unsigned userNREGIONS, const std::string &userDataLabel, const std::string &userTitle)
/*:    NREGIONS(userNREGIONS),
    NPOINTS(userNREGIONS+1),
    LOWEDGE(userLOWEDGE),
    HIEDGE(userHIEDGE),                  
    vectorInput(dataVector),
    dataTree(0)*/{
    NREGIONS = userNREGIONS;
    NPOINTS = userNREGIONS+1;
    LOWEDGE = userLOWEDGE;
    HIEDGE = userHIEDGE;
    vectorInput = dataVector;
    vectorDec = inputDec;
    dataHypo = 0;
    dataLabel = userDataLabel;
    title = userTitle;
    genGraph();
}
    


HypoErrorsGraph::CODE HypoErrorsGraph::genGraph(){

    float edges[NPOINTS], *pEdges;
    pEdges = edges;
    genEdges(pEdges);
    
    float x[NREGIONS], effic[NREGIONS], hiErrors[NREGIONS], lowErrors[NREGIONS], *pX, *peffic, *pHiErrors, *pLowErrors;
    pX = x; peffic = effic; pHiErrors = hiErrors; pLowErrors = lowErrors;
    //Generating x
    incrementEdges(edges, pX);
    //Generating effic, lowErrors, hiErrors
    genEfficErrors(pEdges, peffic, pLowErrors, pHiErrors); 
    //No error on x
    float exl[NREGIONS], exh[NREGIONS];
    //Initializing them becouse the variable size:
    for( unsigned i=0; i<NREGIONS; ++i){
        exl[i]=0.;
        exh[i]=0.;
    }
    //Generating Graph
    graph = new TGraphAsymmErrors(NREGIONS, x, effic, exl, exh, lowErrors, hiErrors);
    //Setting graph parameters:
    if (dataHypo !=0){
        std::string hypoLabel;
        dataHypo->getDataLabel(hypoLabel);
        if (hypoLabel == "elc"){
            graph->SetLineColor(4);
            graph->SetMarkerColor(4);
            graph->SetMarkerStyle(20);
        }
        else if (hypoLabel == "jet"){
            graph->SetMarkerColor(2);
            graph->SetLineColor(2);
            graph->SetMarkerStyle(21);
        }else{
            cout<<"Data label definined incorrectly"<<endl;
            graph->SetMarkerColor(4);
            graph->SetMarkerStyle(21);
        }
    }else{
        size_t comp = dataLabel.find("elc");
        if (comp != std::string::npos){
            graph->SetLineColor(4);
            graph->SetMarkerColor(4);
            graph->SetMarkerStyle(20);
        }else{
            comp = dataLabel.find("jet");
            if( comp != std::string::npos){
                graph->SetMarkerColor(2);
                graph->SetLineColor(2);
                graph->SetMarkerStyle(21);
            }else{
                cout<<"Data label defined incorrectly"<<endl;
                graph->SetMarkerColor(4);
                graph->SetMarkerStyle(21);
            }
        }
    }
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
    const float HALF_REGION_SIZE = ( HIEDGE - LOWEDGE ) / ( NREGIONS ) * .5;
    for(unsigned i = 0; i < NREGIONS;++i, ++edges, ++centerBin)
        *centerBin = (*edges) + HALF_REGION_SIZE;
    edges -= NREGIONS; centerBin-= NREGIONS;// it only iterates for NREGIONS eventhough edges is NPOINTS size.
    return HypoErrorsGraph::OK;
}


HypoErrorsGraph::CODE HypoErrorsGraph::genEfficErrors(const float* edges, float* effic, float* lowEdgeErrors, float* hiEdgeErrors){

    if ( dataHypo!=0){
        Long64_t n_entries = static_cast<Long64_t>( dataTree->GetEntries());

        for(unsigned lowEdge = 0; lowEdge < NREGIONS; ++lowEdge, ++effic, ++lowEdgeErrors, ++hiEdgeErrors, ++edges){
            unsigned regElectrons = 0;
            unsigned regData = 0;
            for(Long64_t entry = 0; entry < n_entries; ++entry){
                dataTree->GetEntry(entry);
                for(size_t i=0; i < vectorInput->size();++i){
                    if ( isAtRegion(*edges, vectorInput->at(i), *(edges+1)) ){
                        ++regData;
                        if (vectorDec->at(i) == HypoBase::ELECTRON)
                            ++regElectrons;
                    }
                }
            }   
            *effic = (float)regElectrons / (float)regData*100.;
            float error = 1/TMath::Sqrt(regData)*100.;
            checkAndGenErrors(*effic, error, *lowEdgeErrors, *hiEdgeErrors);
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
            *effic = (float)regElectrons / (float)regData*100.; 
            float error = (1/TMath::Sqrt(regData))*100.;
            checkAndGenErrors(*effic, error, *lowEdgeErrors, *hiEdgeErrors);
        }
    }
    effic -= NREGIONS; lowEdgeErrors-=NREGIONS; hiEdgeErrors-=NREGIONS; edges -=NREGIONS;
    return HypoErrorsGraph::OK;

}


inline bool HypoErrorsGraph::isAtRegion(const float lowEdge, const float data, const float hiEdge){
    if ( ( data< hiEdge ) && ( data >= lowEdge ) ) return true;
    else return false;
}

inline HypoErrorsGraph::CODE HypoErrorsGraph::checkAndGenErrors(const float &effic, float &error, float &lowError, float &hiError){
    if ( error > effic )
        error = effic;
    if ( error + effic > 100.)
        hiError = 100.-effic;
    else
        hiError = error;
    lowError = error;
    return HypoErrorsGraph::OK;
}


HypoErrorsGraph::CODE HypoErrorsGraph::Draw(const std::string &input){
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
     dataLabel = graph2.dataLabel;
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
     dataLabel = graph2->dataLabel;
     title = graph2->title;

     return this;
}

HypoErrorsGraph::~HypoErrorsGraph(){
    if (dataHypo!=0){
        delete vectorInput;
        delete vectorDec;
    }
}
