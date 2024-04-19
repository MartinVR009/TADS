#include "ArbolBinarioOrd.h"
#include <queue>

template<class T>
ArbolBinarioOrd<T>::ArbolBinarioOrd() {
  this->raiz = NULL;
}

template<class T>
ArbolBinarioOrd<T>::~ArbolBinarioOrd() {
  if (this->raiz != NULL) {
    delete this->raiz;
    this->raiz = NULL;
  }
}

template<class T>
bool ArbolBinarioOrd<T>::esVacio() {
  return this->raiz == NULL;
}

template<class T>
T ArbolBinarioOrd<T>::datoRaiz() {
  if (this->raiz != NULL) {
    return (this->raiz)->obtenerDato();
  } else {
    throw std::logic_error("El árbol está vacío");
  }
}

template<class T>
int ArbolBinarioOrd<T>::altura() {
  if (this->esVacio())
    return -1;
  else
    return (this->raiz)->altura();
}

template<class T>
int ArbolBinarioOrd<T>::tamano() {
  return tamanoRecursivo(this->raiz);
}
template<class T>
int ArbolBinarioOrd<T>::tamanoRecursivo(NodoBinario<T>* nodo) {
  if (nodo == NULL) {
    return 0;
  } else {
    return 1 + tamanoRecursivo(nodo->obtenerHijoIzq()) + tamanoRecursivo(nodo->obtenerHijoDer());
  }
}

template<class T>
bool ArbolBinarioOrd<T>::insertar(T val) {
  if(this->raiz == nullptr) {
    this->raiz = new NodoBinario<T>(val);
    return true;
  }

  NodoBinario<T>* nodo = this->raiz;
  NodoBinario<T>* padre = nullptr;

  while (nodo != nullptr) {
    padre = nodo;
    if (val < nodo->obtenerDato()) {
      nodo = nodo->obtenerHijoIzq();
    } else if (val > nodo->obtenerDato()) {
      nodo = nodo->obtenerHijoDer();
    } else {
      // Valor duplicado, no se inserta en el árbol
      return false;
    }
  }

  NodoBinario<T>* nuevo = new NodoBinario<T>(val);
  if (val < padre->obtenerDato()) {
    padre->fijarHijoIzq(nuevo);
  } else {
    padre->fijarHijoDer(nuevo);
  }

  return true;
}


template<class T>
bool ArbolBinarioOrd<T>::buscar(T val) {
  NodoBinario<T>* nodo = this->raiz;
  while (nodo != nullptr) {
    if (val < nodo->obtenerDato()) {
      nodo = nodo->obtenerHijoIzq();
    } else if (val > nodo->obtenerDato()) {
      nodo = nodo->obtenerHijoDer();
    } else {
      return true; 
    }
  }
  return false; 
}

template< class T >
bool ArbolBinarioOrd<T>::eliminar(T val) {
  if(this->raiz == nullptr) return false; 

  NodoBinario<T>* nodo = this->raiz;
  NodoBinario<T>* padre = nullptr;
  bool esHijoIzq = true;
  NodoBinario<T>* nodoaux = nullptr;

  // Buscar el nodo a eliminar y su padre
  while(nodo != nullptr && nodo->obtenerDato() != val) {
    padre = nodo;
    if(val < nodo->obtenerDato()) {
      nodo = nodo->obtenerHijoIzq();
      esHijoIzq = true;
    } else {
      nodo = nodo->obtenerHijoDer();
      esHijoIzq = false;
    }
  }

  if(nodo == nullptr) return false; // No se encontró el valor

  // Caso 1: Nodo es una hoja
  if(nodo->esHoja()) {
    if(nodo == this->raiz) {
      this->raiz = nullptr;
    } else if(esHijoIzq) {
      padre->fijarHijoIzq(nullptr);
    } else {
      padre->fijarHijoDer(nullptr);
    }
    //delete nodo;
  }

  // Caso 2: Nodo tiene un solo hijo
  else if(nodo->obtenerHijoIzq() == nullptr) { // Solo hijo derecho
    if(nodo == this->raiz) {
      this->raiz = nodo->obtenerHijoDer();
    } else if(esHijoIzq) {
      padre->fijarHijoIzq(nodo->obtenerHijoDer());
    } else {
      padre->fijarHijoDer(nodo->obtenerHijoDer());
    }
  } else if(nodo->obtenerHijoDer() == nullptr){ // Solo hijo izquierdo
    if(nodo == this->raiz) {
      this->raiz = nodo->obtenerHijoIzq();
      } else if(esHijoIzq) {
        padre->fijarHijoIzq(nodo->obtenerHijoIzq());
      } else {
        padre->fijarHijoDer(nodo->obtenerHijoIzq());
    }
  }

  // Caso 3: Nodo tiene dos hijos
  else if (nodo->obtenerHijoIzq() != nullptr && nodo->obtenerHijoDer() != nullptr){
    NodoBinario<T>* sucesor = obtenerMaximo(nodo->obtenerHijoIzq());
    T valorSucesor = sucesor->obtenerDato();
    eliminar(sucesor->obtenerDato()); 
    nodo->fijarDato(valorSucesor);
  }
  return true;
}

template<class T>
NodoBinario<T>* ArbolBinarioOrd<T>::obtenerMaximo(NodoBinario<T>* nodo) {
  while (nodo->obtenerHijoDer() != nullptr) {
    nodo = nodo->obtenerHijoDer();
  }
  return nodo;
}



template<class T>
void ArbolBinarioOrd<T>::posOrden(NodoBinario<T>* nodo) {
  if (nodo != nullptr) {
    posOrden(nodo->obtenerHijoIzq()); 
    posOrden(nodo->obtenerHijoDer());
    std::cout << nodo->obtenerDato() << " "; 
  }
}
template<class T>
void ArbolBinarioOrd<T>::posOrden() {
  posOrden(this->raiz); 
}


template<class T>
void ArbolBinarioOrd<T>::preOrden(NodoBinario<T>* nodo) {
  if (nodo != nullptr) {
    std::cout << nodo->obtenerDato() << " ";
    preOrden(nodo->obtenerHijoIzq());
    preOrden(nodo->obtenerHijoDer());
  }
}
template<class T>
void ArbolBinarioOrd<T>::preOrden() {
  preOrden(this->raiz);
}


template<class T>
void ArbolBinarioOrd<T>::inOrden(NodoBinario<T>* nodo) {
  if (nodo != nullptr) {
    inOrden(nodo->obtenerHijoIzq()); 
    std::cout << nodo->obtenerDato() << " "; 
    inOrden(nodo->obtenerHijoDer()); 
  }
}
template<class T>
void ArbolBinarioOrd<T>::inOrden() {
  inOrden(this->raiz); 
}

template<class T>
void ArbolBinarioOrd<T>::nivelOrden() {
  if (!this->esVacio()) {
    std::queue<NodoBinario<T>*> cola;
    cola.push(this->raiz);
    NodoBinario<T>* nodo;
    while (!cola.empty()) {
      nodo = cola.front();
      cola.pop();
      std::cout << nodo->obtenerDato() << " ";
      if (nodo->obtenerHijoIzq() != nullptr)
        cola.push(nodo->obtenerHijoIzq());
      if (nodo->obtenerHijoDer() != nullptr)
        cola.push(nodo->obtenerHijoDer());
    }
  }
}