#ifndef BSNODE_H
#define BSNODE_H

#include <ostream>

using namespace std;

template <typename T>
class BSNode{
	public:

		T elem;
		BSNode<T>* left;	//pumtero al nodo izq.
		BSNode<T>* rigth;	//puntyero al nodo der.
		
		BSNode(T elem, BSNode<T>* left=nullptr, BSNode<T>* rigth=nullptr):elem(elem), left(left), rigth(rigth){}

		friend ostream& operator << (ostream& out, const BSNode<T>& bsn){
			out << bsn.elem; 
			return out;
		}
};

#endif
