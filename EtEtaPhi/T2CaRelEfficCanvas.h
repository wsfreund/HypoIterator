#ifndef T2CARELEFFICCANVAS_H
#define T2CARELEFFICCANVAS_H

#include "T2CaRelEffic.h"
#include "TCanvas.h"

class T2CaRelEfficCanvas : public T2CaRelEffic {

    TCanvas *relCanvas;

    public:

    T2CaRelEfficCanvas(const std::string rPath, unsigned nRegions, const std::strings &userDataLabel):
        T2CaRelEffic(rPath, nRegions, userDataLabel){
        relCanvas = new TCanvas("Relative Efficiency", "Analysis Graphics");
    }
    CODE Draw();
    ~T2CaRelEfficCanvas();

};




#endif
