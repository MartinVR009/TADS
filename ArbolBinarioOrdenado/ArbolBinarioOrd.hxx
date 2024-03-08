#include "ArbolBinarioOrd.h"
#include <queue>

template< class T >
ArbolBinarioOrd::ArbolBinarioOrd() {
  this->raiz = NULL;
}

template< class T >
ArbolBinarioOrd::~ArbolBinarioOrd() {
  if (this->raiz != NULL) {
    delete this->raiz;
    this->raiz = NULL;
  }
}

template< class T >
bool ArbolBinarioOrd::esVacio() {
  return this->raiz == NULL;
}

template< class T >
T ArbolBinarioOrd::datoRaiz() {
  return (this->raiz)->obtenerDato();
}

// recurrente
template< class T >
int ArbolBinarioOrd::altura() {
  if (this->esVacio())
    return -1;
  else
    return (this->raiz)->altura();
}

// recurrente
template< class T >
int ArbolBinarioOrd::tamano() {

}

// iterativa
template< class T >
bool ArbolBinarioOrd::insertar(T val) {
  NodoBinario<T>* nodo = this->raiz;
  NodoBinario<T>* padre = this->raiz;
  bool insertado = false;
  bool duplicado = false;
  
  while (nodo != NULL) {
    padre = nodo;
    if (val < nodo->obtenerDato()) {
      nodo = nodo->obtenerHijoIzq();
    } else if (val > nodo->obtenerDato()) {
      nodo = nodo->obtenerHijoDer();
    } else {
      duplicado = true;
      break;
    }
  }

  if (!duplicado) {
    NodoBinario<T>* nuevo = new NodoBinario<T>(val);
    if (nuevo != NULL) {
      if (val < padre->obtenerDato())
        padre->fijarHijoIzq(nuevo);
      else
        padre->fijarHijoDer(nuevo);
    }
    insertado = true;
  }

  return insertado;
}

// iterativa
template< class T >
bool ArbolBinarioOrd::eliminar(T val) {

// comparar con dato en nodo para bajar por izquierda o derecha
// y para saber si val esta en el arbol

// si val esta en el arbol
// verificar situacion de eliminacion:
// 1. nodo hoja, borrarlo
// 2. nodo con un solo hijo, usar hijo para reemplazar nodo
// 3. nodo con dos hijos, usar maximo del subarbol izquierdo
//    para reemplazar nodo

}

// iterativa
template< class T >
bool ArbolBinarioOrd::buscar(T val) {
  NodoBinario<T>* nodo = this->raiz;
  bool encontrado = false;

  while (nodo != NULL && !encontrado) {
    if (val < nodo->obtenerDato()) {
      nodo = nodo->obtenerHijoIzq();
    } else if (val > nodo->obtenerDato()) {
      nodo = nodo->obtenerHijoDer();
    } else {
      encontrado = true;
    }
  }

  return encontrado;
}

// recurrente
template< class T >
void ArbolBinarioOrd::preOrden() {

}

// recurrente
template< class T >
void ArbolBinarioOrd::inOrden() {
  if (!this->esVacio())
    (this->raiz)->inOrden();
}

// recurrente
template< class T >
void ArbolBinarioOrd::posOrden() {

}

// iterativa
template< class T >
void ArbolBinarioOrd::nivelOrden() {
	if (!this->esVacio()) {
    std::queue< NodoBinario<T>* > cola;
    cola.push(this->raiz);
    NodoBinario<T>* nodo;
    while (!cola.empty()) {
      nodo = cola.front();
      cola.pop();
      std::cout << nodo->obtenerDato() << " ";
      if (nodo->obtenerHijoIzq() != NULL)
        cola.push(nodo->obtenerHijoIzq());
      if (nodo->obtenerHijoDer() != NULL)
        cola.push(nodo->obtenerHijoDer());
    }
  }
}