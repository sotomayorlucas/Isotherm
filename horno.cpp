#include "horno.h"
Horno::Horno(double ri, double re, uint rads, uint angs, double iso) :
        re_(re), ri_(ri), cantAng_(angs), cantRad_(rads),  iso_(iso), tempInt_(1500){
    deltaR_ = (re_-ri_)/(cantRad_ -1);
    deltaT_ = 2*M_PI/cantAng_;
};

uint Horno::cantRad(){
    return cantRad_;
}

uint Horno::cantAng(){
    return cantAng_;
}
double Horno:: ti (){
    return tempInt_;
}
double Horno::ri (){
    return ri_;
}
double Horno::re (){
    return re_;
}

double Horno::deltaR(){
    return deltaR_;
}

double Horno::deltaT(){
    return deltaT_;
}

double Horno::isoterma(){
    return iso_;
}

//Armamos el sistema de ecuaciones a resolver

vector<vector<double>> Horno:: crearSis(){
    /*La convencion que usamos para las columnas del sistema es el siguiente:
    rIt0, rIt1,...,rItn,r1t0,...,rEt0,...,rEtn*/
    vector<vector<double>> sis = crearMatriz(cantRad_*cantAng_);
    for (int i = 0; i < cantAng_; i++){
        sis[i][i] = 1;
        sis[sis.size()-i-1][sis.size()-i-1] =1;
    }
    for (size_t  j = cantAng_; j < sis.size()-cantAng_; j++){
        int b = j/cantAng_;
        double r = ri_ + deltaR_*(b); //division entera
        sis[j][j] = 1/(r*deltaR_) - 2/(pow(deltaR_,2)) - 2/(pow(r*deltaT_,2));
        if( j%cantAng_ == 0){
            sis[j][j+1] = 1/pow((r*deltaT_),2);
            sis[j][j-1+cantAng_] = 1/pow((r*deltaT_),2);
        }else if (j%cantAng_ == cantAng_-1){
            sis[j][j + 1-cantAng_] = 1 / pow((r * deltaT_), 2);
            sis[j][j - 1] = 1 / pow((r * deltaT_), 2);
        } else{
            sis[j][j + 1] = 1 / pow((r * deltaT_), 2);
            sis[j][j - 1] = 1 / pow((r * deltaT_), 2);
        }
        sis[j][j + cantAng_] = 1/pow(deltaR_,2);
        sis[j][j- cantAng_] = (1/pow(deltaR_,2)) - (1/(r* deltaR_));
    }

    return sis;
}

