#ifndef TABLEENTRY_H
#define TABLEENTRY_H

#include <string>
#include <ostream>

using namespace std;

template <typename V>
class TableEntry{

	public:

		//atributos

		string key;
		V value;

		//constructores

		TableEntry(string key, V value) : key(key), value(value) {}
		TableEntry(string key) : key(key), value(V()) {}
		TableEntry() : key(""), value(V()) {}

		//sobrecarga de ==
		
		friend bool operator == (const TableEntry<V> &te1, const TableEntry<V> &te2){
			
			return te1.key == te2.key;	//igualdad basada en la clave
		}

		//sobrecarga de !=

		friend bool operator != (const TableEntry<V> &te1, const TableEntry<V> &te2){
		
			return te1.key != te2.key;	//igualdad basada en la clave
		}

		//sobrecarga de <<

		friend ostream& operator <<(ostream &out, const TableEntry<V> &te){
			
				out << "{" << te.key << " -> " << te.value << "}";
				return out;		//permite encadenar mas operaciones con <<
			}
};

#endif
