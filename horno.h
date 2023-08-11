
#ifndef TP1METODOS_HORNO_H
#define TP1METODOS_HORNO_H

#include "solsistema.h"
using uint = unsigned int;

class Horno {
public:
    //Precondicion la cantidad de elementos de TE es la misma que la cantidad de angulos (uint ang).
    Horno(double ri, double re, uint rad, uint ang, double iso);
    uint cantRad();
    uint cantAng();
    double ti();
    double ri();
    double re();
    double isoterma();
    double deltaR();
    double deltaT();
    vector<vector<double>> crearSis();
private:
    uint cantRad_;
    uint cantAng_;
    double ri_;
    double re_;
    double deltaR_;
    double deltaT_;
    double iso_;
    double tempInt_;
};


#endif //TP1METODOS_HORNO_H
