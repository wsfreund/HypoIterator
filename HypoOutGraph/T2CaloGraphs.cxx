inline bool T2CaloEfic::cutrCore(const float rCore, const size_t etaBin){

    if ( rCore < m_carcorethr[etaBin] )  {
        return true;
    }
    return false;

}

inline bool T2CaloEfic::cuteRatio(const float eRatio, const float eta, const size_t etaBin){

    bool inCrack = ( fabs (eta) > 2.37 || ( fabs (eta) > 1.37 && fabs (eta) < 1.52 ) );
     
    if ( (!inCrack) && (eRatio < m_caeratiothr[etaBin])) {
        return true;
    }
 
    return false;

}

inline bool T2CaloEfic::cuteT_T2Calo(const float eT_T2Calo, const size_t etaBin){


    if ( eT_T2Calo < m_eTthr[etaBin] ){
        return true;
    }
    return false;
}

inline bool T2CaloEfic::cuthadET_T2Calo(const float hadET_T2Calo, const float eT_T2Calo, const size_t etaBin){


    float hadET_cut;
    if ( eT_T2Calo >  m_eT2thr[etaBin] ) hadET_cut = m_hadeT2thr[etaBin] ;
    else hadET_cut = m_hadeTthr[etaBin];

    if ( hadET_T2Calo > hadET_cut ) {
        return true;
    }
    return false;
}

inline bool T2CaloEfic::cutF1(const float F1){

    if ( F1 < m_F1thr){
        return true;
    }
    return false;
