#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

using namespace std;

template <typename T>
class BSTree{

	private:

		//atributos

		BSNode<T> *root;	//nodo raiz del ABB
		int nelem;	//numero de elementos almacenados en el ABB
		
		//metodos
		
		BSNode<T>* search(BSNode<T>* n, T e) const;
		BSNode<T>* insert(BSNode<T>* n, T e);
		BSNode<T>* remove(BSNode<T>* n, T e);
		T max(BSNode<T>* n) const;
		BSNode<T>* remove_max (BSNode<T>* n);
		void print_inorder(ostream& out, BSNode<T>* n) const;
		void delete_cascade(BSNode<T>* n);


	public:

		BSTree() : root(nullptr), nelem(0) {}	//constructor por defecto con lista de inicializacion

		~BSTree(){
			delete_cascade(root);
		}

		int size() const{
			return nelem;
		}

		T search(T e) const{
			BSNode<T>* result = search(root, e);	//llama al metodo recursivo
			return result->elem;	//devuelve el elemento contenido en el nodo encontrado
		}
		void insert(T e){
			root = insert(root, e);
			++nelem;
		}
		void remove(T e){
			root = remove(root,e);
		}

		T operator[](T e) const{	//actua como una interfaz para ayudar al usuario
			return search(e);	//con la busqueda de un elemento
		}

		friend ostream& operator<<(ostream& out, const BSTree<T>& bst){
		
			out << "{ ";
			bst.print_inorder(out, bst.root);
			out << "} ";
			return out;
		}
};


//busqueda recursiva

template <typename T>
BSNode<T>* BSTree<T>::search(BSNode<T>* n, T e) const{

	if(n == nullptr){
		throw runtime_error("elemento no encontrado");
	}else if (n->elem < e){
		return search(n->rigth, e);	//buscar en el sub-arbol derecho
	}else if(n->elem > e){
		return search(n->left, e);	//buscar en el sub-arbol izquierdo
	}else{
		return n;	//nodo encontrado
	}
}

//insercion de elementos

template<typename T>
BSNode<T>* BSTree<T>::insert(BSNode<T>* n, T e){

	if(n == nullptr){
		return new BSNode<T>(e);	//crea un nuevo nodo
	}else if(n->elem == e){
		throw runtime_error("elemento duplicado");	//elemento e, ya existe
	}else if(e < n->elem){
		n->left = insert(n->left, e);	//insertar en el sub-arbol izq.
	}else{
		n->rigth = insert(n->rigth, e);	//insertar en el sub-arbol der.
	}
	return n;	//devuelve el nodo actual
}

//recorrido e impresion del arbol

template<typename T>
void BSTree<T>::print_inorder(ostream& out, BSNode<T>* n) const{

	if(n != nullptr){
		print_inorder(out, n->left);	//procesa el sub-arbol izq.
		out << n->elem << " ";		//imprime el nodo actual
		print_inorder(out, n->rigth);	//procesa el sub-arbol der.
	}
}

//eliminacion de elementos

template<typename T>
BSNode<T>* BSTree<T>::remove(BSNode<T>* n, T e){

	if(n == nullptr){
		throw runtime_error("elemento no encontrado");
	}else if(e < n->elem){
		n->left = remove(n->left, e);	//buscar en el sub-arbol izq.
	}else if(e > n->elem){
		n->rigth = remove(n->rigth, e);	//buscar en el sub-arbol der.
	}else{
		//nodo con dos hijos
		
		if(n->left != nullptr && n->rigth != nullptr){
			n->elem = max(n->left);		//reemplazar con el max del sub-arbol izq.
			n->left = remove_max(n->left);	//eliminar el nodo del max
		}else{
			//nodo con uno o ningun hijo

			BSNode<T>* temp = n;
			n = (n->left != nullptr) ? n->left : n->rigth;
			delete temp;	//elimina la memoria del nodo eliminado
		}
	}
	return n;	//devuelve el nodo raiz del sub-arbol modificado
}

template<typename T>
BSNode<T>* BSTree<T>::remove_max(BSNode<T>* n){

	if(n->rigth == nullptr){
		return n->left;	//si no hay hijo izq, devolver el derecho
	}else{
		n->rigth = remove_max(n->rigth);//continuar eliminando en el sub-arbol der
		return n;
	}
}

template<typename T>
T BSTree<T>::max(BSNode<T>* n) const{

	if(n == nullptr){
		throw runtime_error("arbol vacio, no hay max");
	}else if(n->rigth != nullptr){
		return max(n->rigth);	//buscar en el sub-arbol der
	}else{
		return n->elem;		//nodo max encontrado
	}
}

//destruciion

template<typename T>
void BSTree<T>::delete_cascade(BSNode<T>* n){

	if(n != nullptr){
		delete_cascade(n->left);	//libera el sub-arbol izq.
		delete_cascade(n->rigth);	//libere el dub-arbol der.
		delete n;			//libera el nodo actual
	}
}

#endif
