// TorresDeHanoiBusquedaAnchura.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"
#include <stdio.h>
#include <tchar.h>
#include <conio.h>
#include <algorithm>
#include <vector>
#include <stack>
#include <queue>

#include <iostream>

using namespace std;
stack<int> torre1;
stack<int> torre2;
stack<int> torre3;
vector<stack<int>> torres;
queue<vector<int>> cola;
queue<queue<vector<stack<int>>>> colaHistorial;
int cantidadDiscos;

void agregarDicos(int cantidadDiscos) {
	for (int i = cantidadDiscos; i > 0; i--)
	{
		torre1.push(i);
	}
	torres.push_back(torre1);
	torres.push_back(torre2);
	torres.push_back(torre3);
}

void imprimirTorre(stack<int> t) {
	stack<int> torre = t;
	if (torre.empty()) {
		cout << "***";
	}
	while (!torre.empty())
	{
		cout <<torre.top()<<" ";
		torre.pop();
	}
	cout << endl;
}

void imprimirTorres(vector<stack<int>> torres) {
	for (size_t i = 0; i < torres.size(); i++)
	{
		imprimirTorre(torres[i]);
	}
	cout << "\n--------------------------" << endl;

}

void imprimirSolucion(queue<vector<stack<int>>> cola){
	
	while (!cola.empty())
	{
		if(cola.size()!= 1){
			imprimirTorres(cola.front());
		}
		
		cola.pop();
		
	}
}

queue<vector<stack<int>>> crearNivel(vector<stack<int>> torre) {
	queue<vector<stack<int>>> cola;
	vector<stack<int>> aux;
	if (!torre[0].empty()){
		if (torre[1].empty() || torre[0].top() < torre[1].top()) {
			aux = torre;
			aux[1].push(aux[0].top()); aux[0].pop();
			cola.push(aux);
		}

		if (torre[2].empty() || torre[0].top() < torre[2].top()) {
			aux = torre;
			aux[2].push(aux[0].top()); aux[0].pop();
			cola.push(aux);
		}
	}

	if (!torre[1].empty()) {
		if (torre[0].empty() || torre[1].top() < torre[0].top()) {
			aux = torre;
			aux[0].push(aux[1].top()); aux[1].pop();
			cola.push(aux);
		}

		if (torre[2].empty() || torre[1].top() < torre[2].top()) {
			aux = torre;
			aux[2].push(aux[1].top()); aux[1].pop();
			cola.push(aux);
		}
	}

	if (!torre[2].empty()) {
		if (torre[0].empty() || torre[2].top() < torre[0].top()) {
			aux = torre;
			aux[0].push(aux[2].top()); aux[2].pop();
			cola.push(aux);
		}

		if (torre[1].empty() || torre[2].top() < torre[1].top()) {
			aux = torre;
			aux[1].push(aux[2].top()); aux[2].pop();
			cola.push(aux);
		}
	}
	return cola;
}

queue<vector<stack<int>>> crearNodoColaHistorial(queue<vector<stack<int>>> colaPadre, vector<stack<int>> nodoHijo) {
	queue<vector<stack<int>>> cp = colaPadre;
	cp.push(nodoHijo);	
	return cp;
}

void agregarColaHistorial(queue<vector<stack<int>>> colaPadre, queue<vector<stack<int>>> colaHijos) {

	while (!colaHijos.empty())
	{
		colaHistorial.push(crearNodoColaHistorial(colaPadre, colaHijos.front()));	
		colaHijos.pop();
	}
	//cout << "hijos: " << colaHistorial.back().size() << endl;
}

bool buscar(queue<vector<stack<int>>> colaNodo) {
	colaHistorial.push(colaNodo);
	vector<stack<int>> nodo = colaNodo.front();
	while (!(nodo[2].size() == cantidadDiscos))
	{
		nodo = colaHistorial.front().back();
		queue<vector<stack<int>>> nivel = crearNivel(nodo);
		agregarColaHistorial(colaHistorial.front(), nivel);
		colaHistorial.pop();
	}

	return nodo[2].size() == cantidadDiscos;
}



int main()
{
	
	cout << "Ingrese la cantidad de discos :"; cin >> cantidadDiscos;
	agregarDicos(cantidadDiscos);
	queue<vector<stack<int>>> iNodo;
	iNodo.push(torres);
	//imprimirTorre(torre1);
	cout << "Procesado sea paciente ..." << endl;
	if (buscar(iNodo)) {
		cout << "\nSolucion Encontrada..." << endl;
		imprimirSolucion(colaHistorial.back());

	}
	else
	{
		cout << "\nSin Solucion Encontrada..." << endl;
	}
	system("pause");
    return 0;
}

