/*
Neural Network Implementation v3.0
Developed by: Dhiana Deva Cavalcanti Rocha
Contact: dhiana.deva@gmail.com
Laboratorio de Processamento de Sinais
Universidade Federal do Rio de Janeiro
*/

#include <vector>
#include <cmath>
#include "Neural.h"

Neural::Neural(const std::vector<unsigned int> &n, const std::vector<float> &w, const std::vector<float> &b)
  : nodes(n),
    weight(w),
    bias(b),
    wM(0),
    bM(0),
    mM(0)
{
    //Verifying weight vector size
    unsigned int wSize=0;
    for (unsigned int k=0; k<n.size()-1; ++k)
        wSize+=n[k]*n[k+1];
    try{
    if (wSize != w.size())
        throw BAD_WEIGHT_SIZE;
    //Verifying bias vector size
    unsigned int bSize=0;
    for (unsigned int k=1; k<n.size(); ++k)
        bSize+=n[k];
    if(bSize != b.size())
        throw BAD_BIAS_SIZE;
    }catch(int i){
    throw;}
    //First weight dimension
    try{
    wM = new float **[n.size()-1]; //number of layers excluding input
    } catch (std::bad_alloc xa){
    wM = NULL;
    throw;
    }
    //First bias dimension
    try{    
    bM = new float *[n.size()-1]; //number of layers excluding input
    } catch (std::bad_alloc xa){
    bM = NULL;
    throw;    
    }
    //First multiplication dimension
    try{
    mM = new float *[n.size()]; //number of layers including input
    } catch (std::bad_alloc xa){
    mM = NULL;    
    throw;
    }
  
    for (unsigned int l = 0; l<n.size(); ++l){ 
        //Checks if no bad_alloc happened to mM
        if(mM){
            try{
            //Second and last dimension of mM
            mM[l] = new float[n[l]]; //number of nodes in current layer
            } catch (std::bad_alloc xa){
            mM[l] = NULL;
            throw;
            }
        }
    }
    std::vector<float>::const_iterator itrB = b.begin();
    std::vector<float>::const_iterator itrW = w.begin();
    for (unsigned int l = 0; l < n.size()-1; ++l){  
        //Checks if no bad_alloc happened to bM
        if(bM){
            try{
            //Second and last dimension of bM
            bM[l] = new float[n[l+1]]; //number of nodes in next layer
            } catch (std::bad_alloc xa){
            bM[l] = NULL;
            throw;
            }
        }
        //Checks if no bad_alloc happened to wM
        if(wM){ 
            try{
            //Second dimension of wM
            wM[l] = new float*[n[l+1]]; //number of nodes in next layer
            } catch (std::bad_alloc xa){
            wM[l] = NULL;
            throw;
            }
        }
        for (unsigned int i=0; i<n[l+1]; i++){ 
            //Checks if no bad_alloc happened to wM[l]
            if(wM){
                if(wM[l]){
                    try{
                    //Third and last dimension of wM
                    wM[l][i]=new float [n[l]]; //number of nodes in current layer
                    } catch (std::bad_alloc xa){
                    wM[l][i] = NULL;
                    throw;
                    }
                }
            }
            //Populating bias matrix
            if (bM){
            //Checks if no bad_alloc happened to bM[l]
                if (bM[l]){
                    bM[l][i]=(*itrB++);}}
            //Populating weight matrix
            for (unsigned int j=0; j<n[l]; j++){
                if (wM){
                    if (wM[l]){
                        if(wM[l][i]){
                            wM[l][i][j]=(*itrW++);
                        }
                    }
                }
            }
        }
        //Populating multiplication matrix so that starting sum equals zero
        for (unsigned int i=0; i<n[l]; i++){
            //Checks if no bad_alloc happened to mM[L]
            if (mM){
                if (mM[l]){
                    mM[l][i]=0;
                }
            }
        }   
    }
}

Neural::~Neural(){
    for (unsigned int l=0; l<nodes.size()-1; l++){
        if (bM){
            if (bM[l]==NULL){
                delete bM[l]; //Deletes null pointer
            }else{
                delete[] bM[l]; //Deletes array of values at second dimension of bM
            }
        } 
        for (unsigned int i=0; i<nodes[l+1]; i++){
            if (wM){ 
                if(wM[l]){
                    if (wM[l][i]==NULL){
                        delete wM[l][i]; //Deletes null pointer
                    }
                }
            }else{
                delete[] wM[l][i]; //Deletes array of values at third dimension of wM
            }
        }
        if (wM){
            if (wM[l]==NULL){
                delete wM[l]; //Deletes null pointer
            }else{
                delete[] wM[l]; //Deletes array of pointers at second dimension of wM
            }
        } 
    }
    for (unsigned int l=0; l<nodes.size(); l++){
        if(mM){
            if (mM[l]==NULL){
                delete mM[l]; //Deletes null pointer
            }
        }else{
            delete[] mM[l]; //Deletes array of values at second dimension of mM
        }
    }
    if (wM==NULL){
        delete wM; //Deletes null pointer
    }else{
        delete[] wM; //Deletes array of pointers at first dimension of wM
    }
    if (bM==NULL){
        delete bM; //Deletes null pointer
    }else{
        delete[] bM; //Deletes array of pointers at first dimension of bM
    }
    if (mM==NULL){
        delete mM; //Deletes null pointer
    }else{
        delete[] mM; //Deletes array of pointers at first dimension of mM
    }
}

float Neural::propagate(const std::vector<float> &input){
    for(unsigned int i=0; i<input.size();i++)
        mM[0][i]=input[i];
    for(unsigned int l=0; l<nodes.size()-1;l++){
        for(unsigned int i=0; i<nodes[l+1]; i++){
            mM[l+1][i]=bM[l][i];
            for (unsigned int j=0;j<nodes[l]; j++)
                mM[l+1][i]+=mM[l][j]*wM[l][i][j];
            mM[l+1][i]=tanh(mM[l+1][i]);
        }
    }
    return (mM[nodes.size()-1][0]);
}

