#ifndef T2CACONFIG
#define T2CACONFIG


//T2Calo Version : 00-07-85
class t2ca_00_07_85_conf{
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

  t2ca_00_07_85_conf(){
    m_etabin = {.0, .6, .8, 1.15, 1.37, 1.52, 1.81, 2.01, 2.37, 2.47}; 
    m_eT2thr = {90e3, 90.0e3, 90.0e3, 90.0e3, 90.0e3, 90.0e3, 90.0e3, 90.0e3, 90.0e3};
    m_hadeT2thr = {999., 999., 999., 999., 999., 999., 999., 999., 999.};
  }

};

class e5 : public t2ca_00_07_85_conf{
  public:
  e5(){
    m_eTthr = {4.e3, 4.e3, 4.e3, 4.e3, 4.e3, 4.e3, 4.e3, 4.e3, 4.e3};
    m_hadeTthr = {0.058, 0.058, 0.058, 0.058, 0.058, 0.058, 0.058, 0.058, 0.058};
    m_carcorethr = {0.65, 0.65, 0.65, 0.65, 0.65, 0.65, 0.65, 0.65, 0.65};
    m_caeratiothr = {0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10, 0.10};
  }
};
    
class e10 : public t2ca_00_07_85_conf{
  public:
  e10(){
    m_eTthr = {9.e3, 9.e3, 9.e3, 9.e3, 9.e3, 9.e3, 9.e3, 9.e3, 9.e3};
    m_hadeTthr = {0.043, 0.043, 0.043, 0.043, 0.043, 0.043, 0.043, 0.043, 0.043};
    m_carcorethr = {0.66, 0.66, 0.66, 0.66, 0.66, 0.66, 0.66, 0.66, 0.66};
    m_caeratiothr = {0.29, 0.29, 0.29, 0.29, 0.29, 0.29, 0.29, 0.29, 0.29};
  }
};

class e15 : public t2ca_00_07_85_conf{
  public:
  e15(){
    m_eTthr = {14.e3, 14.e3, 14.e3, 14.e3, 14.e3, 14.e3, 14.e3, 14.e3, 14.e3};
    m_hadeTthr = {0.043, 0.043, 0.043, 0.043, 0.043, 0.043, 0.043, 0.043, 0.043};
    m_carcorethr = {0.87, 0.87, 0.87, 0.87, 0.87, 0.87, 0.87, 0.87, 0.87};
    m_caeratiothr = {0.60, 0.60, 0.60, 0.60, 0.60, 0.60, 0.60, 0.60, 0.60};
  }
};

#endif
