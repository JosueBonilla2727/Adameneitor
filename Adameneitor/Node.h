#pragma once
#include<conio.h>
#include<iostream>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

using namespace std;

class Node {
	public:
		Node* arbol = NULL;
		Node* der = nullptr;
		Node* izq = nullptr;
		Node* raiz = nullptr;

		string dato;
		int opz, contador = 0;

	public:
		void mostrar_arbol(Node* arbol, int cont) {
			if (arbol == NULL) {
				return;
			}
			else {
				mostrar_arbol(arbol->der, cont + 1);
				for (int i = 0; i < cont; i++) {
					cout << "   ";
				}
				cout << arbol->dato << endl;
				mostrar_arbol(arbol->izq, cont + 1);
			}
		}
};

Node* crearNodo(string n, Node* arbol) {
	Node* nuevo_nodo = new Node();
	nuevo_nodo->dato = n;
	nuevo_nodo->der = NULL;
	nuevo_nodo->izq = NULL;
	nuevo_nodo->raiz = *&arbol->raiz;
	return nuevo_nodo;
}

