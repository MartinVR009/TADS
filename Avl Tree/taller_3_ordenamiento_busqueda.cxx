#include <ctime>
#include <iostream>
#include <fstream>
#include <string>

#include "AVLNode.h"
#include "AVLTree.h"
#include "AVLNode.hxx"
#include "AVLTree.hxx"

#include <list>
#include <set>
// TODO #1: incluir cabecera arbol AVL
// #include "arbolAVL.h"

// -------------------------------------------------------------------------
using TList = std::list< std::string >;
using TAVL = AVLTree<std::string>;
typedef std::set< std::string >  TSet;
// TODO #2: definir arbol AVL de tipo std::string
// typedef arbolAVL< std::string > TAVL;

std::list< std::string > lista;
std::list< std::string >::iterator it = lista.begin();


// -------------------------------------------------------------------------

template<typename T>
void printSet(const std::set<T>& mySet) {
    std::cout << "Set elements: \n";
    for (const auto& element : mySet) {
        std::cout << element << " ";
    }
    std::cout << std::endl;
}

template< class TArbol >
bool LeerArbol( TArbol& arbol, const std::string& nomArch )
{
  std::ifstream entrada( nomArch.c_str( ) );
  if( !entrada )
    return( false );
  while( !entrada.eof( ) )
  {
    std::string codigo, valor;
    entrada >> codigo >> valor;
    
    if( codigo == "add" ){
    std::cout<<"Valor a añadir RN: " << valor <<"\n";
    printSet(arbol);
      arbol.insert( valor );  // El arbol debe proveer el metodo "insert"
    }
    else if( codigo == "del" ){
    std::cout<<"Valor a borrar RN: " << valor <<"\n";
    printSet(arbol);
      arbol.erase( valor );   // El arbol debo proveer el metodo "erase"
    }

  } // elihw
  entrada.close( );
  return( true );
}


template< class TArbol >
bool LeerArbolAVL( TArbol& arbol, const std::string& nomArch )
{
  std::ifstream entrada( nomArch.c_str( ) );
  if( !entrada )
    return( false );
  while( !entrada.eof( ) )
  {
    std::string codigo, valor;
    entrada >> codigo >> valor;
    if( codigo == "add" ){
      std::cout<<"Valor a añadir AVL: " << valor <<"\n";
      arbol.inOrder();
      arbol.Insert( valor );  // El arbol debe proveer el metodo "insert"
    }
    else if( codigo == "del" ){
    std::cout<<"Valor a borrar AVL: " << valor <<"\n";
    arbol.inOrder();
      arbol.Delete( valor );   // El arbol debo proveer el metodo "erase"
    }

  } // elihw
  entrada.close( );
  return( true );
}

template< class TArbol , class TArbol2>
bool Leer2Arboles( TArbol& arbolRN, TArbol2& arbolAVL, const std::string& nomArch )
{
  std::ifstream entrada( nomArch.c_str( ) );
  if( !entrada )
    return( false );
  while( !entrada.eof( ) )
  {
    std::string codigo, valor;
    entrada >> codigo >> valor;
    std::cout << "Valor: " << valor << "\n";
    if( codigo == "add" ){
      std::cout<<"______________añadir RN______________\n";
      arbolRN.insert( valor);
      printSet(arbolRN);
      std::cout<<"______________añadir AVL__________\n";
      arbolAVL.Insert( valor ); 
      arbolAVL.inOrder(); std::cout<<"\n";  // El arbol debe proveer el metodo "insert"
    }
    else if( codigo == "del" ){
      std::cout<<"_________________borrar RN_______________\n";
      arbolRN.erase( valor);
      printSet(arbolRN);
      std::cout<<"______________________borrar AVL___________________\n";
      arbolAVL.Delete( valor ); 
      arbolAVL.inOrder(); std::cout<<"\n"; // El arbol debo proveer el metodo "erase"
    }

  } // elihw
  entrada.close( );
  return( true );
}



// -------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
  if( argc < 2 )
  {
    std::cerr << "Uso: " << argv[ 0 ] << " archivo_entrada" << std::endl;
    return( -1 );

  } // fi

  // Declarar arboles a usar
  TSet miArbolRN; // arbol rojinegro
  TList miHeap;
  // TODO #3: arbol AVL 
  // TAVL miArbolAVL;
  TAVL miArbolAVL;
  // Llenar arbol rojinegro y calcular el tiempo empleado
  std::clock_t inicioLecturaRN = std::clock( );
  std::clock_t inicioLecturaAVL = std::clock( );
  bool lectura = Leer2Arboles( miArbolRN, miArbolAVL, argv[ 1 ] );
  std::clock_t finLecturaRN = std::clock( );
  std::clock_t finLecturaAVL = std::clock( );
  double tiempoLecturaRN = ( finLecturaRN - inicioLecturaRN ) / double( CLOCKS_PER_SEC );
  double tiempoLecturaAVL = ( finLecturaAVL - inicioLecturaAVL ) / double( CLOCKS_PER_SEC );
  if( lectura )
    std::cout
      << "Tiempo de llenado arbol RN = "
      << tiempoLecturaRN << "segs."
      << std::endl;
  else
    std::cout
      << "Error al leer \"" << argv[ 1 ]
      << "\" para llenar el arbol RN."
      << std::endl;
if( lectura )
    std::cout
      << "Tiempo de llenado arbol AVL = "
      << tiempoLecturaRN << "segs."
      << std::endl;
  else
    std::cout
      << "Error al leer \"" << argv[ 1 ]
      << "\" para llenar el arbol AVL."
      << std::endl;

  // TODO #4: usar el archivo para llenar el arbol AVL 
  // bool lecturaAVL = LeerArbol( miArbolAVL, argv[ 1 ] );
  // Llenar arbol AVL y calcular el tiempo empleado

  /*Por ahora
  std::clock_t inicioLecturaAVL = std::clock( );
  bool lecturaAVL = LeerArbolAVL( miArbolAVL, argv[ 1 ] );
  std::clock_t finLecturaAVL = std::clock( );
  double tiempoLecturaAVL = ( finLecturaAVL - inicioLecturaAVL ) / double( CLOCKS_PER_SEC );
  if( lecturaAVL )
    std::cout
      << "Tiempo de llenado arbol AVL = "
      << tiempoLecturaRN << "segs."
      << std::endl;
  else
    std::cout
      << "Error al leer \"" << argv[ 1 ]
      << "\" para llenar el arbol AVL."
      << std::endl;
  */

  // Obtener el recorrido en inorden del arbol AVL
  TList inordenAVL;
  // TODO #6: llamar funcion que genera el recorrido en inorden
  // miArbolAVL.inordenEnLista( inordenAVL );
  inordenAVL = miArbolAVL.inOrderList();

  if( miArbolAVL.size( ) != miArbolRN.size( ) )
  {
    std::cout << "Cantidad de elementos en los arboles no coinciden." << std::endl;

    std::cout<<"\nDatos arbol RN:\n";
    printSet(miArbolRN);
    std::cout<<"\nDatos arbol AVL: \n";
    miArbolAVL.inOrder();

    return( -1 ); 

  } // fi

  // Comparar los arboles
  TSet::const_iterator rnIt = miArbolRN.begin( );
  TList::const_iterator avlIt = inordenAVL.begin( );
  bool iguales = true;
  for( ; rnIt != miArbolRN.end( ); rnIt++, avlIt++ )
    iguales &= ( *rnIt == *avlIt );

  // Informar si los arboles coinciden o no
  std::cout << "Los arboles ";
  if( !iguales )
    std::cout << "no ";
  std::cout << "coinciden." << std::endl;
  
  return( 0 );
}

// ------------------------------------------------------------------------

// eof - taller_3_ordenamiento_busqueda.cxx
