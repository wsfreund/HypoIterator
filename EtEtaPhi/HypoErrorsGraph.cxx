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
    float exl[NREGIONS], exh[NREGIONS], x[NREGIONS], effic[NREGIONS], hiErrors[NREGIONS], lowErrors[NREGIONS], *pX, *peffic, *pHiErrors, *pLowErrors;
    for( unsigned i=0; i<NREGIONS; ++i){
        exl[i]=0.; exh[i]=0.; x[i]=0; effic[i]=0; hiErrors[i]=0; lowErrors[i]=0;
    }
    pX = x; peffic = effic; pHiErrors = hiErrors; pLowErrors = lowErrors;
    //Generating x, effic, lowErrors, hiErrors, also eliminate regions with no data.
    genEfficErrors(pEdges, pX, peffic, pLowErrors, pHiErrors); 
    //Generating Graph
    graph = new TGraphAsymmErrors(NREGIONS, x, effic, exl, exh, lowErrors, hiErrors);
    //Setting graph parameters:
    if (dataHypo !=0){
        std::string hypoLabel;
        dataHypo->getDataLabel(hypoLabel);
        if (hypoLabel == "elc"){
            graph->SetMarkerSize(0.8);
            graph->SetLineWidth(0.4);
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
    for(unsigned i = 0; i < NREGIONS;++i, ++edges, ++centerBin)
    edges -= NREGIONS; centerBin-= NREGIONS;// it only iterates for NREGIONS eventhough edges is NPOINTS size.
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
                    if ( isAtRegion(*edges, vectorInput->at(i), *(edges+1)) ){
                        ++regData;
                        if (vectorDec->at(i) == HypoBase::ELECTRON)
                            ++regElectrons;
                    }
                }
            }   
            std::string dataLabel;
            dataHypo->getDataLabel(dataLabel);
            float error =-1;
            if (regData!=0){
                error = 1/TMath::Sqrt(regData)*100.;
                *pX = (*edges) + HALF_REGION_SIZE;
                if (dataLabel == "elc")
                    *effic = (float)regElectrons / (float)regData*100.;
                else if (dataLabel == "jet")
                    *effic = (float)(regData - regElectrons)/(float)regData *100.;
                checkAndGenErrors(*effic, error, *lowEdgeErrors, *hiEdgeErrors);
                ++px; ++effic; ++lowEdgeErrors; ++hiEdgeErrors; ++edges;
            }else{
                unsigned decrementEdges = lowEdge;
                for(; decrementEdges < NREGIONS - 1; ++decrementEdges, ++edges)
                    *edges = *(edges+1);
                edges-=decrementEdges;
                --NREGIONS;
            }
        }
    }/*else{
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
            if (regData!=0){
            if (dataLabel == "elc")
                *effic = (float)regElectrons / (float)regData*100.;
            else if (dataLabel == "jet")
                *effic = (float)(regData - regElectrons)/(float)regData *100.;
            }else 
                *effic = 0;
            float error = (1/TMath::Sqrt(regData))*100.;
            checkAndGenErrors(*effic, error, *lowEdgeErrors, *hiEdgeErrors);
        }
    }*/
    effic -= NREGIONS; lowEdgeErrors-=NREGIONS; hiEdgeErrors-=NREGIONS; edges -=NREGIONS; px -= NREGIONS;
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
