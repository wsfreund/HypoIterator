#ifndef HYPOVARBASE_H 
#define HYPOVARBASE_H 

class HypoVarBase {

    public:
    virtual int DrawVar(const std::string &var, const std::string &mode, const bool scaled) = 0;
    virtual int setRange(const int varNumber, const float x1, const float x2, const std::string &axis = "X") = 0;
    virtual int setRange(const int varNumber, const float x1, const float x2, const float y1, const float y2) = 0;
    virtual int setRange(const std::string &var, const float x1, const float x2, const std::string &axis = "X") = 0;
    virtual int setRange(const std::string &var, const float x1, const float x2, const float y1, const float y2) = 0;

};

#endif
