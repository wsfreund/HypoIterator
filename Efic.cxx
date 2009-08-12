#include"Efic.h"

Efic::CODE Efic::ordenateRoi(const vector<float> *eta, const vector<float> *phi){


        for(size_t j=0; j<lvl2_eta->size();++j){

                if ( j < eta->size() ){
	                unsigned matchingPair	        = 	j;
	                float	vError			=	sqrt (pow(( eta->at(j) - lvl2_eta->at(j) ),2)+pow(( phi->at(j) - lvl2_phi->at(j) ),2) );


	                for(size_t k = (j+1) ; k < (lvl2_eta->size()); ++k){

		                float actualError =  sqrt (pow(( eta->at(j) - lvl2_eta->at(k) ),2)+pow(( phi->at(j) - lvl2_phi->at(k) ),2) );

		                if ( actualError < vError ) {
			                vError = actualError;
			                matchingPair = k;
		                }
	                }

                        if (j!=matchingPair) {
                                swapVectors(j,matchingPair);
                        }
                }

                else {
                        eraseVectors(j);
                        break;
                }

        }

	return Efic::OK;
}
