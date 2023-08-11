#include "horno.h"
#include "solsistema.h"

int main() {
    cout<< "Escriba nombre de archivo de entrada"<<endl;
    string entrada;
    cin >> entrada;
    ifstream fin(entrada);

    cout<< "Escriba nombre de archivo de salida"<<endl;
    string salida;
    cin >> salida;
    ofstream fout;
    fout.open(salida);

    cout<< "Escriba 0 para correr Eliminacion Gaussiana y 1 para factorizacion LU"<<endl;
    int numeroDesicion;
    cin >>  numeroDesicion;

    double re;

    double ri;

    uint cantRad;

    uint cantAng;

    double iso;

    int ninst;
    //n es angulos y m es radios
    fin >> ri;
    fin >> re;
    fin >> cantRad;
    fin >> cantAng;
    fin >> iso;
    fin >> ninst;
    Horno horno = Horno(ri, re, cantRad, cantAng, iso);
    vector<vector<double>> m = horno.crearSis();
    if (numeroDesicion == 0){
    while(ninst>0) {
        vector<double> te(cantAng, 0);
        for (int i = 0; i < cantAng; ++i) {
            double temp;
            fin >> temp;
        }
        for (int i = 0; i < cantAng; ++i) {
                double temp;
                fin >> temp;
            te[i] = temp;

        }
        vector<double> v = vectorSalida(te, cantRad);
        vector<double> res;
        if (ninst == 1){ // Esto es para que, en el caso que sea solo una instancia, pasar la matriz por referencia evitando el costo agregado de copiarla
            res = elimGRef(m,v);
        } else { //Si hay mas de una instancia debo conservar la matriz original, asi que la copio
            res = elimG(m,v);
        } 
        fprintVector(res,fout);
        ninst--;
    }
    } else if (numeroDesicion == 1) {
        facLU(m);
        while (ninst > 0) {
            vector<double> te(cantAng, 0);
            for (int i = 0; i < cantAng; ++i) {
                double temp;
                fin >> temp;
            }
            for (int i = 0; i < cantAng; ++i) {
                double temp;
                fin >> temp;
                te[i] = temp;
            }
            vector<double> v = vectorSalida(te, cantRad);
            vector<double> res = resolverLU(m, v);
            fprintVector(res,fout);
            ninst--;
        }
    }
    else {
        cout << "Eleccion invalida" << endl;
        return 0;
    }
    fout.close();
    return 0;
}