#ifndef __NODOGENERAL_H__
#define __NODOGENERAL_H__

#include <list>
#include <iostream>
#include <queue>
#include <stack>

using namespace std;

template< class T >
class NodoGeneral {
  protected:
    T dato;
  public:
    typename std::list< NodoGeneral<T>* > desc;
    NodoGeneral();
   ~NodoGeneral();
    T& obtenerDato();
    void fijarDato(T& val);
    void limpiarLista();
    void adicionarDesc(T& nval);
    bool eliminarDesc(T& val);
    bool esHoja();
    int altura();
    void preOrden();
};

#include "NodoGeneral.hxx"

#endif