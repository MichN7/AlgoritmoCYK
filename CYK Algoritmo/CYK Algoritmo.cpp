#include "stdafx.h"
#include <iostream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <set>
#include <map>
#include <vector>

using namespace std;

typedef std::set<int> conjunto;
typedef std::map<int,conjunto> fila;
typedef std::map<int, fila> tabla;
typedef enum{Q=81,E=69,T=84,F=70,J=74,K=75,L=76,G=71,A=65,C=67,M=77,I=73,N=78,D=68,O=79,B=66,H=72} generadores;
std::set<int>::iterator it1;
std::set<int>::iterator it2;
string w;

typedef struct {
	int generador;
	int primero;
	int segundo;
} Regla;

typedef std::vector<Regla> Gramatica;

Regla crearRegla(int a, int b, int c) {
	
	Regla regla;
	
	regla.generador = a;
	regla.primero = b;
	regla.segundo = c;

	return regla;

}

Gramatica gramatica;
tabla P;

void mostrarGramatica(Gramatica &s) {
	Gramatica::iterator ir;
	for (ir = s.begin(); ir != s.end(); ++ir)
	{
		printf("%c -> %c%c \n", ir->generador, ir->primero, ir->segundo);
	}
}

void crearGramatica() {
	
	//Q-> EJ
	gramatica.push_back(crearRegla(Q, E, J));
	//Q-> CE
	gramatica.push_back(crearRegla(Q, C, E));
	//Q-> x
	gramatica.push_back(crearRegla(Q, 'x', 0));
	//Q-> EM
	gramatica.push_back(crearRegla(Q, E, M));
	//Q-> TN
	gramatica.push_back(crearRegla(Q, T, N));
	//Q-> BO
	gramatica.push_back(crearRegla(Q, B, O));
	//J-> GK
	gramatica.push_back(crearRegla(J, G, K));
	//L-> AQ
	gramatica.push_back(crearRegla(L, A, Q));
	//G-> q
	gramatica.push_back(crearRegla(G, 'q', 0));
	//A-> e
	gramatica.push_back(crearRegla(A, 'e', 0));
	//C-> n
	gramatica.push_back(crearRegla(C, 'n', 0));
	//M-> IT
	gramatica.push_back(crearRegla(M, I, T));
	//I-> s
	gramatica.push_back(crearRegla(I, 's', 0));
	//N-> DF
	gramatica.push_back(crearRegla(N, D, F));
	//D-> p
	gramatica.push_back(crearRegla(D, 'p', 0));
	//O->QH 
	gramatica.push_back(crearRegla(O, Q, H));
	//B-> l
	gramatica.push_back(crearRegla(B, 'l', 0));
	//H-> r
	gramatica.push_back(crearRegla(H, 'r', 0));
	//E-> x
	gramatica.push_back(crearRegla(E, 'x', 0));
	//E-> CE
	gramatica.push_back(crearRegla(E, C, E));
	//E-> TN
	gramatica.push_back(crearRegla(E, T, N));
	//E-> BO
	gramatica.push_back(crearRegla(E, B, O));
	//E-> EM
	gramatica.push_back(crearRegla(E, E, M));
	//T-> BO
	gramatica.push_back(crearRegla(T, B, O));
	//T-> x
	gramatica.push_back(crearRegla(T, 'x', 0));
	//T-> CE
	gramatica.push_back(crearRegla(T, C, E));
	//T-> TN
	gramatica.push_back(crearRegla(T, T, N));
	//F-> x
	gramatica.push_back(crearRegla(F, 'x', 0));
	//F-> CE
	gramatica.push_back(crearRegla(F, C, E));
	//F-> BO
	gramatica.push_back(crearRegla(F, B, O));

}

bool esMiembro(conjunto &s, int a) {
	return s.find(a) != s.end();
}

void limpiarTabla() {
	for (int i = 0; i < w.length(); i++)
	{
		for (int y = 0; y < w.length(); y++)
		{
			P[i][y].clear();
		}
	}
}

void insertarEnConjunto(conjunto &s, int a) {
	for (int i = 0; i < gramatica.size(); i++)
	{
		if (gramatica[i].primero == a || gramatica[i].segundo == a) {
			s.insert(gramatica[i].generador);
		}
	}
}

void insertarEnConjunto(conjunto &s, int a, int b) {
	for (int i = 0; i < gramatica.size(); i++)
	{
		if (gramatica[i].primero == a && gramatica[i].segundo == b) {
			s.insert(gramatica[i].generador);
		}
	}
}

void obtenerConjunto(conjunto &s, conjunto &s1,conjunto &s2) {
	conjunto::iterator it;
	conjunto::iterator it2;
	for (it = s1.begin(); it != s1.end(); it++)
	{
		for (it2 = s2.begin(); it2 != s2.end(); it2++)
		{
			insertarEnConjunto(s, *it, *it2);
		}
	}
}


bool evaluar(Gramatica &g, string &w) {
	
	int n = w.length();

	for (int i = 1; i <= n; i++){
		insertarEnConjunto(P[i][1],w[i-1]);
	}
	for (int j = 2; j <= n; j++){
		for (int i = 1; i <= n-j+1; i++){
			for (int k = 1; k <= j-1; k++){
				obtenerConjunto(P[i][j], P[i][k], P[i + k][j - k]);
			}
		}
	}
	if (esMiembro(P[1][n], Q)) {
		limpiarTabla();
		return true;
	}
	else {
		limpiarTabla();
		return false;
	}
	
}



int main()
{
	
	crearGramatica();
	mostrarGramatica(gramatica);
	while (w != "exit") {
		cout << "\n ingresa cadena (Escriba exit para salir) \n";
		cin >> w;
		if (evaluar(gramatica, w)) {
			cout << "la cadena fue aceptada \n";

		}
		else {
			cout << "la cadena no fue aceptada \n";
		}

		system("PAUSE");
	}
}


