#include "HypoErrorsGraph.h"

HypoErrorsGraph::HypoErrorsGraph() {
};
HypoErrorsGraph::HypoErrorsGraph(const float userLOWEDGE, const float userHIEDGE, TTree* &userDataTree, const std::string &branchName, const std::string &decBranch, const unsigned userNREGIONS, const std::string &userDataLabel, const std::string &userTitle)
/*:NREGIONS(userNREGIONS),
NPOINTS(userNREGIONS+1),
LOWEDGE(userLOWEDGE),
HIEDGE(userHIEDGE),
dataTree(userDataTree)*/
{
    cout<<"Entrei construtor!!"<<endl;
    NREGIONS = userNREGIONS;
    NPOINTS = userNREGIONS+1;
    LOWEDGE = userLOWEDGE;
    HIEDGE = userHIEDGE;
    vectorInput = new std::vector<float>;
    dataTree=userDataTree;
    dataTree->SetBranchAddress(branchName.c_str(), &vectorInput);
    dataTree->SetBranchAddress(decBranch.c_str(), &vectorDec);
    dataLabel = userDataLabel;
    title = userTitle;
    genGraph();
}

HypoErrorsGraph::HypoErrorsGraph(const float userLOWEDGE, const float userHIEDGE, std::vector<float> *&dataVector, std::vector<float> *&inputDec, const unsigned userNREGIONS, const std::string &userDataLabel, const std::string &userTitle)
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
    dataTree = 0;
    dataLabel = userDataLabel;
    title = userTitle;
    genGraph();
}
    


HypoErrorsGraph::CODE HypoErrorsGraph::genGraph(){

    cout<<"Entrei no genGraph()"<<endl;
    float edges[NPOINTS], *pEdges;
    pEdges = edges;
    cout<<"Criei ponteiro pEdges"<<endl;
    genEdges(pEdges);
    cout<<"criei genEdges"<<endl;
    for(unsigned i =0; i<NPOINTS; ++i)
        cout<<edges[i]<<" ";
    cout<<endl;
    
    float x[NREGIONS], efic[NREGIONS], hiErrors[NREGIONS], lowErrors[NREGIONS], *pX, *pEfic, *pHiErrors, *pLowErrors;
    pX = x; pEfic = efic; pHiErrors = hiErrors; pLowErrors = lowErrors;
    cout<<"criei um monte de ponteiro"<<endl;
    //Generating x
    incrementEdges(edges, pX);
    cout<<"dei incrementEdges"<<endl;
    for(unsigned i =0; i<NREGIONS; ++i)
        cout<<x[i]<<" ";
    cout<<endl;

    cout<<"ponteiro de edges "<<*pEdges<<endl;
    //Generating Efic, lowErrors, hiErrors
    genEficErrors(pEdges, pEfic, pLowErrors, pHiErrors); 
    //No error on x
    cout<<"passou EficErrors"<<endl;
    float exl[NREGIONS], exh[NREGIONS];
    //Initializing them becouse the variable size:
    for( unsigned i=0; i<NREGIONS; ++i){
        exl[i]=0.;
        exh[i]=0.;
    }
    cout<<"inicialisei os erros em x para zeros"<<endl;
    //Generating Graph
    graph = new TGraphAsymmErrors(NREGIONS, x, efic, exl, exh, lowErrors, hiErrors);
    //Setting graph parameters:
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
            graph->SetMarkerColor(4);
            graph->SetMarkerStyle(21);
        }

    }
    graph->SetTitle(title.c_str());

    cout<<"terminei de setar as coisas"<<endl;
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


HypoErrorsGraph::CODE HypoErrorsGraph::genEficErrors(const float* edges, float* efic, float* lowEdgeErrors, float* hiEdgeErrors){

    if ( dataTree!=0){
        cout<<"Entrei loop com dataTree"<<endl;
        Long64_t n_entries = static_cast<Long64_t>( dataTree->GetEntries());

        for(unsigned lowEdge = 0; lowEdge < NREGIONS; ++lowEdge, ++efic, ++lowEdgeErrors, ++hiEdgeErrors, ++edges){
            cout<<"lowEdge = "<<lowEdge<<endl;
            unsigned regElectrons = 0;
            unsigned regData = 0;
            for(Long64_t entry = 0; entry < n_entries; ++entry){
                cout<<"Pegando entry "<<entry<<endl;
                dataTree->GetEntry(entry);
                for(size_t i=0; i < vectorInput->size();++i){
                    cout<<"Pegando entrada "<<i<<" de vectorInput("<<vectorInput->size()<<")"<<endl;
                    ++regData;
                    cout<<"chamando isAtRegion"<<endl;
                    if ( isAtRegion(*edges, vectorInput->at(i), *(edges+1)) ){
                        cout<<"Esta na regiao!!"<<endl;
                        if (vectorDec->at(entry) == HypoErrorsGraph::PARTICLES::ELECTRON)
                            ++regElectrons;
                    }
                }
            }   
            cout<<"chegou na parte dos erros"<<endl;
            *efic = (float)regElectrons / (float)regData;
            float error = 1/TMath::Sqrt(regData);
            if (error>*efic) error = *efic;
            *lowEdgeErrors = *efic - error; 
            *hiEdgeErrors = ((*efic + error) > 100)?100:(*efic+ error); 
        }
    }else{
        for(unsigned lowEdge = 0; lowEdge < NREGIONS; ++lowEdge, ++efic, ++lowEdgeErrors, ++hiEdgeErrors){
            unsigned regElectrons = 0;
            unsigned regData = 0;
            for(size_t i=0; i < vectorInput->size();++i){
                ++regData;
                if ( isAtRegion(*edges, vectorInput->at(i), *(edges+1)) ){
                    if (vectorDec->at(i) == HypoErrorsGraph::ELECTRON)
                        ++regElectrons;
                }
            }
            *efic = (float)regElectrons / (float)regData; 
            float error = 1/TMath::Sqrt(regData);
            if (error>*efic) error = *efic;
            *lowEdgeErrors = *efic - error; 
            *hiEdgeErrors = ((*efic + error) > 100)?100:(*efic+ error); 
        }
    }
    efic -= NREGIONS; lowEdgeErrors-=NREGIONS; hiEdgeErrors-=NREGIONS; edges -=NREGIONS;
    return HypoErrorsGraph::OK;

}


inline bool HypoErrorsGraph::isAtRegion(const float lowEdge, const float data, const float hiEdge){
    if ( ( data< hiEdge ) && ( data >= lowEdge ) ) return true;
    else return false;
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
     dataTree= graph2->dataTree;
     dataLabel = graph2->dataLabel;
     title = graph2->title;

     return this;
}

HypoErrorsGraph::~HypoErrorsGraph(){
    if (dataTree!=0) delete vectorInput;
}
