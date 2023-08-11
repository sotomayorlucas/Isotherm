#include "solsistema.h"

vector<vector<double>> crearMatriz (int n)
{
    vector<vector<double>> mat(n,vector<double>(n,0));

    return mat;
}

//Factoriza en LU
void facLU (vector<vector<double>> &m )
{
    for (int i = 0; i < m.size()-1; i++)
    {
        for (int j = i+1; j < m.size(); j++)
        {
            double coef = m[j][i]/m[i][i];
            for (int k = i+1; k < m.size(); k++)
            {

                m[j][k] = m[j][k] - coef* m[i][k];
            }
            m[j][i] = coef;

        }
    }

}


//Eliminacion Gaussiana
vector<double> elimG (vector<vector<double>> m, vector<double> &b){
    for (int i = 0; i < m.size()-1; i++)
    {
        for (int j = i+1; j < m.size(); j++)
        {
            double coef = m[j][i]/m[i][i];
            for (int k = i; k < m.size(); k++)
            {

                m[j][k] = m[j][k] - coef* m[i][k];
            }
            b[j] = b[j] - coef*b[i];
            m[j][i] = 0;

        }
    }
    return solSisTs(m, b);
}
//Eliminacion Gaussiana por referencia 
vector<double> elimGRef(vector<vector<double>> &m, vector<double> &b){
    for (int i = 0; i < m.size()-1; i++){
        for (int j = i+1; j < m.size(); j++){
            double coef = m[j][i]/m[i][i];
            for (int k = i; k < m.size(); k++){

                m[j][k] = m[j][k] - coef* m[i][k];
            }
            b[j] = b[j] - coef*b[i];
            m[j][i] = 0;
        }
    }
    return solSisTs(m, b);
}
vector<double> resolverLU(vector<vector<double>> &m,vector<double> b){
    double res = 0;
    vector<double> y =  solSisTi(m,b);
    return solSisTs(m,y);
}
double sumatoria(vector<vector<double>> &m, int i, int j, int n, vector<double> b){
    double res = 0;
    while (j <= n){
        res = res + m[i][j]*b[j];
        j++;
    }
    return res;
}


//resuelve sistema de matriz triangular inferior
vector<double> solSisTi(vector<vector<double>> &m, vector<double> b){
    vector<double> res(m.size());
    for(int i = 0; i < m.size(); i++){
        res[i]=(b[i]- sumatoria(m,i,0,i-1,res));
    }
    return res;
}

//resuelve sistema de matriz triangular superior
vector<double> solSisTs(vector<vector<double>> &m, vector<double> b){
    vector<double> res(m.size());
    for(int i = m.size()-1; 0<=i; i--){
        res[i]=((b[i]- sumatoria(m,i,i+1,m.size()-1,res))/m[i][i]);
    }
    return res;
}

//Imprime la matriz
void printMat(vector<vector<double>> mat){
    for (int i = 0; i < mat.size(); i++)
    {
        cout<< "[";
        for (int j = 0; j < mat.size()-1; j++)
        {
            cout << mat[i][j] <<", ";
        }
        cout<< mat[i][mat.size()-1] << "]" << endl;
    }
    cout<<endl;
}

//Imprime la matriz en archivo
void fprintMat(vector<vector<double>> mat, ofstream& fout){
    for (int i = 0; i < mat.size(); i++)
    {
        for (int j = 0; j < mat.size()-1; j++)
        {
            fout << mat[i][j] <<" ,";
        }
        fout<< mat[i][mat.size()-1] <<"\n";
    }
    fout<<"\n";
}


//Imprime el Vector
void printVector (vector<double> v){
    for(int i=0; i<v.size(); i++){
        cout<<"["<<v[i]<<"]"<<endl;
    }
    cout<<endl;
}

//Imprime el Vector en archivo
void fprintVector (vector<double> v, ofstream& fout){
    for(int i=0; i<v.size(); i++){
        fout<<v[i]<<endl;
    }
    fout<<endl;
}

//Imprime la matriz en archivo en un formato conveniente para plotear
void fprintVectorToMaxRadAng(vector<double> v, ofstream& fout, uint cantRad, uint cantAng){
    fout << "[";
    int i = 0;
    for (int ang = 0; ang < cantAng-1; ang++){
        fout << "[";
        for (int rad = 0; rad < cantRad-1; rad++){
            fout << v[ang + cantAng*rad] << ", ";
        }
        fout << v[ang + cantAng*(cantRad-1)] << "]," << "\n";
    }
    fout << "[";
    for (int rad = 0; rad < cantRad-1; rad++){
       fout << v[cantAng-1 + cantAng*rad] << ", ";
    }
    fout << v[cantAng-1 + cantAng*(cantRad-1)] << "]]" << "\n";
}
//calcula el vector resultado del alto horno
vector<double> vectorSalida(vector<double> te, int cantRad){
    vector<double> temp (te.size() * cantRad, 0);
    for (int i = 0; i < te.size(); i++){
        temp[i] = 1500;
        temp[temp.size()-1-i] = te[te.size()-i-1];
    }
    return temp;
}

/* 
Devuelve, mediante busqueda binaria, los indices de los 
radios que encierran la isoterma en un angulo especifico
*/
pair <int, int> busqBinSolSis(vector<double> &v, uint tita , uint cantRad, uint cantAng){
    int low = 0;
    int high = cantRad-1;
    int mid;
    while(low < high-1){
        mid = (low + high)/2;
        if (v[tita + cantAng*mid] >= 500){
            low = mid;
        }else{
            high = mid;
        }
    }
        pair <int, int> res = make_pair(low,high);
    return res;
}


/*
calcula la isoterma para cada angulo y lo devuelve en forma de vector dada por:
iso(tita) = r + (t(r,tita) - 500)*(deltaR / deltaT)
deltaT= la distancia entre las temperaturas de los radios que encierran la isoterma
*/
vector<double> isoterma(vector<double> &temps, uint cantRad, uint cantAng, double ri, double deltaR){
    vector<double> res(cantAng,0);
    double iso;
    double r;
    double deltaT;
    for (uint tita = 0; tita < cantAng; tita++){
        pair <int, int> rads = busqBinSolSis(temps, tita, cantRad, cantAng);
        r = ri + deltaR*rads.first;
        deltaT = temps[tita + cantAng * rads.first] - temps[tita + cantAng * rads.second];
        iso = r + ((temps[tita + cantAng*rads.first] - 500)*(deltaR/deltaT));
        res[tita] = iso;
    }
    return res;

}