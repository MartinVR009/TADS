#ifndef __ARBOLBINARIOORD_H__
#define __ARBOLBINARIOORD_H__

#include "NodoBinario.h"

template <class T> class ArbolBinarioOrd {
protected:
  NodoBinario<T> *raiz;
  void preOrden(NodoBinario<T> *nodo);
  void inOrden(NodoBinario<T> *nodo);
  void posOrden(NodoBinario<T> *nodo);
  int tamanoRecursivo(NodoBinario<T> *nodo);

public:
  ArbolBinarioOrd();
  ~ArbolBinarioOrd();
  bool esVacio();
  T datoRaiz();
  int altura();
  int tamano();
  bool insertar(T val);
  bool eliminar(T val);
  bool buscar(T val);
  void preOrden();
  void inOrden();
  void posOrden();
  void nivelOrden();
  NodoBinario<T> *obtenerMaximo(NodoBinario<T> *nodo) const;
  NodoBinario<T> *obtenerPadre(T val) const;
};

#include "ArbolBinarioOrd.hxx"

#endif