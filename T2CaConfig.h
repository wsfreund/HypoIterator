#ifndef T2CACONFIG_H
#define T2CACONFIG_H

#include <string.h>

//T2Calo Version : 00-07-85
struct t2ca_00_07_85_conf{
  private:
  static const int MAXSIZE = 9;

  public:
  float m_eTthr[MAXSIZE];
  float m_eT2thr[MAXSIZE];
  float m_hadeTthr[MAXSIZE];
  float m_hadeT2thr[MAXSIZE];
  float m_carcorethr[MAXSIZE];
  float m_caeratiothr[MAXSIZE];
  float m_etabin[MAXSIZE+1];
  static const float m_F1thr = .005;
  static const float m_detacluster = .1;
  static const float m_dphicluster = .1;

  t2ca_00_07_85_conf();

};

struct e5 : public t2ca_00_07_85_conf{
  e5();
};
    
struct e10 : public t2ca_00_07_85_conf{
  e10();
};

struct e15 : public t2ca_00_07_85_conf{
  e15();
};

#endif
