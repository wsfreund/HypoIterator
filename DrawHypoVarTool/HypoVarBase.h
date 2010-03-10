#ifndef HYPOVARBASE_H 
#define HYPOVARBASE_H 

class HypoVarBase {

    public:
    virtual int DrawVar(const std::string &var, const std::string &mode, const bool scaled) = 0;

};

#endif
