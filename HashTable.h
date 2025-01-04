#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "TableEntry.h"
#include "/home/gastt/pra/p1/ListLinked.h"

using namespace std;

template <typename V>
class HashTable: public Dict<V>{

	private:

		//atributos

		int n;					//num de elementos almacenados en la tabla hash
		int max;				//tamanyo de la tabla hash
		ListLinked<TableEntry<V>>* table;	//array dinamico de listas enlazadas

		//funcion hash

		int h(string key){
		
			int hash = 0;

			for(char c : key){	//recorre cada caracter c del string key
			
				hash += int(c);	//convierte cada carcter en su valor ASCII y lo suma
			}
			return hash % max;	//resto de la division entre hash y el tamnyo de la tabla
		}
	public:

		//constructor

		HashTable(int size) : n(0), max(size){
			table = new ListLinked<TableEntry<V>>[max];	//reservamos memoria dinamica para crear un
									//array de max elementos, cada uno de estos
									//elementos es una lista enlazada (ListLinked)
		}

		~HashTable(){
			delete[] table;	//libera la memoria reservada para el array dinamico
		}

		int capacity(){
			return max;
		}

		friend ostream& operator << (ostream& out, const HashTable<V> &th){
		
			for(int i = 0; i<th.max; i++){
				out << "cubeta" << i << ": ";
				th.table[i].print(out);
				out << endl;
			}
		return out;
	      	}

		V operator[](string key){
		
			V kValue = search(key);
			return kValue;
		}

		void insert(string key, V value) override{
		
			int pos = h(key);	//calcula la posicion actual en la tabla

			//verifica si la clave ya existe usando search() de ListLinked
			for(int i = 0; i < table[pos].size(); i++){
				
				if(table[pos].get(i).key == key){	//usamos get para acceder al elemento
					throw runtime_error("la key ya existe");
				}
			}

			//creamos el nuevo par calve->valor y lo agregamos al final de la lista enlazada
			TableEntry<V> newEntry(key, value);
			table[pos].append(newEntry);	//append del ListLinked
			++n;	//incremento de numero de elemntos
		}

		V search(string key) override {

   			 int pos = h(key);  // Calcula la posición en la tabla hash

   			 // Recorre la lista enlazada de la cubeta para buscar la clave

   			 for (int i = 0; i < table[pos].size(); ++i){	 // Usa size para el rango
       			
				 if (table[pos].get(i).key == key) {  // Compara usando get
          	
				       	 return table[pos].get(i).value;  // Devuelve el valor asociado
      				 }
  			 }

			  // Si no se encuentra, lanza una excepción
			  throw runtime_error("Imposible encontrar la llave");
		}

		void remove(string key) override {
		       	int pos = h(key);  // Calcula la posición en la tabla hash
			// Busca la posición del elemento en la lista enlazada
			for (int i = 0; i < table[pos].size(); ++i) {  // Usa size para iterar
       				 if (table[pos].get(i).key == key) {  // Compara claves usando get
           				table[pos].remove(i);  // Elimina el elemento en la posición i
           				--n;  // Decrementa el número de elementos
            				return;
       				 }
    			}

			// Si no se encuentra, lanza una excepción
   			throw runtime_error("Imposible encontrar la llave");
		}
};

#endif
