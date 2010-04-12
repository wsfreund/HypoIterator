#include "T2CaConfig.h"

float t2ca_00_07_85_conf::m_F1thr = 0.005;
float t2ca_00_07_85_conf::m_detacluster = .1;
float t2ca_00_07_85_conf::m_dphicluster = .1;

t2ca_00_07_85_conf::t2ca_00_07_85_conf(){
    float m_etabin2[] = {.0, .6, .8, 1.15, 1.37, 1.52, 1.81, 2.01, 2.37, 2.47}; 
    float m_eT2thr2[] = {90e3, 90.0e3, 90.0e3, 90.0e3, 90.0e3, 90.0e3, 90.0e3, 90.0e3, 90.0e3};
    float m_hadeT2thr2[] = {999., 999., 999., 999., 999., 999., 999., 999., 999.};
    memcpy(m_etabin, m_etabin2, sizeof(m_etabin2));
    memcpy(m_eT2thr, m_eT2thr2, sizeof(m_eT2thr2));
    memcpy(m_hadeT2thr, m_hadeT2thr2, sizeof(m_hadeT2thr2));
}

e5::e5(){
    float m_eTthr2[] = {4.e3, 4.e3, 4.e3, 4.e3, 4.e3, 4.e3, 4.e3, 4.e3, 4.e3};
    float m_hadeTthr2[] = {0.058, 0.058, 0.058, 0.058, 0.058, 0.058, 0.058, 0.058, 0.058};
    float m_carcorethr2[] = {0.65, 0.65, 0.65, 0.65, 0.65, 0.65, 0.65, 0.65, 0.65};
    float m_caeratiothr2[] = {0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10};
    memcpy(m_eTthr, m_eTthr2, sizeof(m_eTthr2));
    memcpy(m_hadeTthr, m_hadeTthr2, sizeof(m_hadeTthr2));
    memcpy(m_carcorethr, m_carcorethr2, sizeof(m_carcorethr2));
    memcpy(m_caeratiothr, m_caeratiothr2, sizeof(m_caeratiothr2));

}
e10::e10(){
    float m_eTthr2[] = {9.e3, 9.e3, 9.e3, 9.e3, 9.e3, 9.e3, 9.e3, 9.e3, 9.e3};
    float m_hadeTthr2[] = {0.043, 0.043, 0.043, 0.043, 0.043, 0.043, 0.043, 0.043, 0.043};
    float m_carcorethr2[] = {0.66, 0.66, 0.66, 0.66, 0.66, 0.66, 0.66, 0.66, 0.66};
    float m_caeratiothr2[] = {0.29, 0.29, 0.29, 0.29, 0.29, 0.29, 0.29, 0.29, 0.29};
    memcpy(m_eTthr, m_eTthr2, sizeof(m_eTthr2));
    memcpy(m_hadeTthr, m_hadeTthr2, sizeof(m_hadeTthr2));
    memcpy(m_carcorethr, m_carcorethr2, sizeof(m_carcorethr2));
    memcpy(m_caeratiothr, m_caeratiothr2, sizeof(m_caeratiothr2));
}
e15::e15(){
    float m_eTthr2[] = {14.e3, 14.e3, 14.e3, 14.e3, 14.e3, 14.e3, 14.e3, 14.e3, 14.e3};
    float m_hadeTthr2[] = {0.043, 0.043, 0.043, 0.043, 0.043, 0.043, 0.043, 0.043, 0.043};
    float m_carcorethr2[] = {0.87, 0.87, 0.87, 0.87, 0.87, 0.87, 0.87, 0.87, 0.87};
    float m_caeratiothr2[] = {0.60, 0.60, 0.60, 0.60, 0.60, 0.60, 0.60, 0.60, 0.60};
    memcpy(m_eTthr, m_eTthr2, sizeof(m_eTthr2));
    memcpy(m_hadeTthr, m_hadeTthr2, sizeof(m_hadeTthr2));
    memcpy(m_carcorethr, m_carcorethr2, sizeof(m_carcorethr2));
    memcpy(m_caeratiothr, m_caeratiothr2, sizeof(m_caeratiothr2));
}
