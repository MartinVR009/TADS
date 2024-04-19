 #include "ArbolGeneral.h"
 #include <queue>

 template <class T>
 ArbolGeneral<T>::ArbolGeneral() {
     this->raiz = NULL;
 }

 template <class T>
 ArbolGeneral<T>::ArbolGeneral(T val) {
     NodoGeneral<T>* nodo = new NodoGeneral<T>;
     nodo->fijarDato(val);
     this->raiz = nodo;
 }

 template <class T>
 ArbolGeneral<T>::~ArbolGeneral() {
     delete this->raiz;
     this->raiz = NULL;
 }

 template <class T>
 bool ArbolGeneral<T>::esVacio() {
     return this->raiz == NULL;
 }

 template <class T>
 NodoGeneral<T>* ArbolGeneral<T>::obtenerRaiz() {
     return this->raiz;
 }

 template <class T>
 void ArbolGeneral<T>::fijarRaiz(NodoGeneral<T>* nraiz) {
     this->raiz = nraiz;
 }

 template <class T>
 bool ArbolGeneral<T>::insertarNodo(T padre, T n) {
     // Si el árbol es vacío:
     if (this->raiz == nullptr) {
         // Crear nuevo nodo, asignar dato, poner ese nodo como raíz
         this->raiz = new NodoGeneral<T>();
         this->raiz->fijarDato(n);
         return true;
     } else {
         // Si hay al menos un nodo en el árbol:
         // Buscar el nodo padre.
         NodoGeneral<T>* nodoPadre = buscarNodo(this->raiz, padre);
         if (nodoPadre != nullptr) {
             // Si es padre, insertar ahí el nuevo hijo
             nodoPadre->adicionarDesc(n);
             return true;
         } else {
             // Si no es el padre, el nodo padre no se encontró en el árbol.
             return false;
         }
     }
 }

 template <class T>
 NodoGeneral<T>* ArbolGeneral<T>::buscarNodo(NodoGeneral<T>* nodo, const T& valor) {
   if (nodo == nullptr) {
     // Caso base: nodo es nullptr, no se encontró el valor.
     return nullptr;
   }
   if (nodo->obtenerDato() == valor) {
     // Caso base: se encontró el valor en el nodo actual.
     return nodo;
   }

   // Recorrer cada hijo buscando el valor.
   typename std::list<NodoGeneral<T>*>::iterator it;
   for (it = nodo->desc.begin(); it != nodo->desc.end(); ++it) {
     NodoGeneral<T>* resultado = buscarNodo(*it, valor);
     //return(buscarNodo(*it, valor));

     if (resultado != nullptr) {
       // Si se encontró el valor en algún subárbol, retornar el nodo.
       return resultado;
     }
   }
   // Si se recorrieron todos los hijos y no se encontró el valor, retornar nullptr.
   return nullptr;
 }

 template <class T>
 bool ArbolGeneral<T>::eliminarNodo(T valor) {
     // Caso especial: si la raíz es el nodo a eliminar
     if (this->raiz != nullptr && this->raiz->obtenerDato() == valor) {
       // Elimina toda la subestructura del árbol
       this->raiz->limpiarLista();
       delete this->raiz;
       this->raiz = nullptr;
       return true;
     }
     // Iniciar la búsqueda y eliminación recursiva desde la raíz
     return eliminarNodoRecursivo(nullptr, this->raiz, valor);
 }

 template <class T>
 bool ArbolGeneral<T>::eliminarNodoRecursivo(NodoGeneral<T>* padre, NodoGeneral<T>* nodoActual, T valor){
   if (nodoActual == nullptr) return false;
   if (nodoActual->obtenerDato() == valor){
     //no tiene padre porque tiene raíz
     if (padre == nullptr){
       delete this->raiz;
       this->raiz = nullptr;
     }
     else{
       //en cada iteración del recursivo, habrá un momento donde el nodoActual no tenga hijos y se elimine desde abajo hacia arriba (en recursivo lit) y se van eliminando todos los nodos que se encuentran en el subarbol
       padre->desc.remove(nodoActual);
     }
     return true;

   }
   //eliminar todos los hijos del nodo actual
   typename std::list<NodoGeneral<T>*>::iterator it;
   for (it = nodoActual->desc.begin(); it != nodoActual->desc.end(); ++it){
     if (eliminarNodoRecursivo(nodoActual, *it, valor)){
       return true;
     }
   }
   return false;
 }

 /*
 template <class T>
 bool ArbolGeneral<T>::eliminarNodoRecursivo(NodoGeneral<T>* padre, NodoGeneral<T>* nodoActual, T n) {
     if (nodoActual == nullptr) {
         return false; // Base de la recursión: nodoActual es nulo.
     }

     // Buscar en los hijos del nodo actual
   for (auto it = nodoActual->desc.begin(); it != nodoActual->desc.end(); ) {
       NodoGeneral<T>* hijo = *it;
       if (hijo->obtenerDato() == n) {
           eliminarSubarbol(hijo);
           it = nodoActual->desc.erase(it); // Incrementa `it` antes de la eliminación
           return true;
       } else {
           // Incrementar el iterador aquí si no entra al if
           ++it;
           if (eliminarNodoRecursivo(nodoActual, hijo, n)) {
               return true;
           }
       }
   }


     return false; // No se encontró el nodo con el valor especificado
 }

 template <class T>
 void ArbolGeneral<T>::eliminarSubarbol(NodoGeneral<T>* nodo) {
     if (nodo == nullptr) return;
     // Eliminar recursivamente cada uno de los hijos del nodo
     typename std::list<NodoGeneral<T>*>::iterator it;
     for (it = nodo->desc.begin(); it != nodo->desc.end(); ++it){
         eliminarSubarbol(*it);

     }
     delete nodo;
   /*
     for (auto hijo : nodo->desc) {
         eliminarSubarbol(hijo);
     }
     // Eliminar el nodo actual después de haber eliminado a sus hijos
     delete nodo;
   */

 template <class T>
 int ArbolGeneral<T>::altura() {
   if (this->esVacio() && this->raiz == nullptr) {
     return -1;
   } else {
     return (this->raiz)->altura();
   }
 }

 template <class T>
  int ArbolGeneral<T>::tamano() {
   return tamanoAux(this->raiz);
 }

 template <class T>
  int ArbolGeneral<T>::tamanoAux(NodoGeneral<T>* nodo) {
   if (nodo == nullptr) {
     return 0; // Si el nodo es nullptr, no contribuye al tamaño del árbol.
   }
   // Inicia el contador de tamaño para este nodo.
   unsigned int tam = 1; // Contando el nodo actual.

   // Itera sobre todos los hijos del nodo actual y suma sus tamaños.
   typename std::list<NodoGeneral<T>*>::iterator it;
   for (it = nodo->desc.begin(); it != nodo->desc.end(); ++it) {
     tam += tamanoAux(*it); // Suma el tamaño del subárbol hijo.
   }
   return tam; // Retorna el tamaño total encontrado desde este nodo hacia abajo.
 }




 template <class T>
 void ArbolGeneral<T>::preOrden() {
     if (!this->esVacio())
         (this->raiz)->preOrden();
 }

 template <class T>
 void ArbolGeneral<T>::posOrden() {
   if(this->raiz != nullptr)
     this->posOrden(this->raiz);// llamar a posorden sobre cada hijo
   // imprimo en pantalla el dato del nodo actual
 }
 template <class T>
 void ArbolGeneral<T>::posOrden(NodoGeneral<T>* nodo){
   // para cada hijo, llamo a posorden
   typename std::list<NodoGeneral<T>*>::iterator it; 
   for (it = nodo->desc.begin(); it != nodo->desc.end(); ++it){
     this->posOrden(*it);
   }
   // imprimo en pantalla el dato del nodo actual
   std::cout << nodo->obtenerDato() << " ";

 }

 template <class T>
 void ArbolGeneral<T>::nivelOrden() {
   // NO ES RECURRENTE (O RECURSIVO)
   if(this->raiz == nullptr) return; //si está vac{io, no hay nada que hacer.
   std::queue<NodoGeneral<T>*> cola;
   // ubicarme en la raiz
   // poner la raiz en una cola
   cola.push(this->raiz);

   // hacer un ciclo mientras haya algo en la cola
   while(!cola.empty()){
     // - saco el primero disponible en la cola
     NodoGeneral<T>* nodo = cola.front();
     cola.pop();

     // - imprimo su dato
     std::cout << nodo->obtenerDato() << " ";
     // - inserto en la cola todos sus hijos
     typename std::list<NodoGeneral<T>*>::iterator it;
     for (it = nodo->desc.begin(); it != nodo->desc.end(); ++it)
       cola.push(*it);
   }

 }