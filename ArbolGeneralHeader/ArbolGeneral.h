#ifndef __ARBOLGENERAL_H__
#define __ARBOLGENERAL_H__

#include "NodoGeneral.h"

template <class T>
class ArbolGeneral {
  protected:
    NodoGeneral<T>* raiz;
  public:
    ArbolGeneral();
    ArbolGeneral(T val);
    ~ArbolGeneral();
    bool esVacio();
    NodoGeneral<T>* obtenerRaiz();
    void fijarRaiz(NodoGeneral<T>* nraiz);
    bool insertarNodo(T padre, T n);
    void eliminarSubarbol(NodoGeneral<T>* nodo);
    bool eliminarNodo(T n); 
    bool eliminarNodoRecursivo(NodoGeneral<T>* padre, NodoGeneral<T>* nodoActual, T n);
    int altura();
    unsigned int tamano();
    unsigned int tamanoAux(NodoGeneral<T>* nodo);
    void preOrden();
    void posOrden();
    void posOrden(NodoGeneral<T>* nodo);
    void nivelOrden();
    NodoGeneral<T>* buscarNodo(NodoGeneral<T>* nodo, const T& valor);
    void eliminarTodosLosDescendientes(NodoGeneral<T>* nodo);

};

#include "ArbolGeneral.hxx"

#endif