#ifndef DICT_H
#define DICT_H

#include <string>
using namespace std;

template <typename V>
class Dict {
	
	public:

   		 virtual void insert(string key, V value) = 0;   // Inserta un par clave->valor
   		 virtual V search(string key) = 0;              // Busca el valor asociado a la clave
   		 virtual V remove(string key) = 0;              // Elimina un par clave->valor
   		 virtual int entries() = 0;                     // Devuelve el número de elementos
   		 virtual ~Dict() {}                             // Destructor virtual
};

#endif // DICT_H

