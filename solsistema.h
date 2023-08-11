#ifndef TP1METODOS_SOLSISTEMA_H
#define TP1METODOS_SOLSISTEMA_H

#include <stdio.h>
#include <ctime>
#include <vector>
#include <math.h>
#include <iostream>
#include <fstream>

using namespace std;

vector<vector<double>> crearMatriz (int n);
void facLU (vector<vector<double>> &m );
vector<double> solSisTs(vector<vector<double>> &m, vector<double> b);
vector<double> solSisTi(vector<vector<double>> &m, vector<double> b);
double sumatoria(vector<vector<double>> &m, int i, int j, int n, vector<double> b);
void printVector (vector<double> v);
void printMat(vector<vector<double>> mat);
void fprintMat(vector<vector<double>> mat, ofstream& fout);
void fprintVector (vector<double> v, ofstream& fout);
vector<double> resolverLU(vector<vector<double>> &m,vector<double> b);
vector<double> elimG (vector<vector<double>> m, vector<double> &b);
vector<double> elimGRef(vector<vector<double>> &m, vector<double> &b);
vector<double> vectorSalida(vector<double> te, int cantRad);
void fprintVectorToMaxRadAng(vector<double> v, ofstream& fout, uint cantRad, uint cantAng);
pair <int, int> busqBinSolSis(vector<double> &v, uint tita , uint cantRad, uint cantAng);
vector<double> isoterma(vector<double> &v, uint cantRad, uint cantAng, double ri, double deltaR);


#endif //TP1METODOS_SOLSISTEMA_H
