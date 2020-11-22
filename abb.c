#include "abb.h"

const int EXITO =  0;
const int FALLO = -1;


abb_t* arbol_crear(abb_comparador comparador, abb_liberar_elemento destructor){

  if(!comparador) return NULL;

  abb_t* abb = malloc( sizeof( abb_t ) );
  if( !abb ) return NULL;

  abb->nodo_raiz = NULL;
  abb->comparador = comparador;
  abb->destructor = destructor;

  return abb;
}

/*
 * Inserta un elemento en el arbol.
 * Devuelve 0 si pudo insertar o -1 si no pudo.
 * El arbol admite elementos con valores repetidos.
 */
int arbol_insertar_recursivo(abb_t* arbol, void* elemento, nodo_abb_t** nodo){

  if(!arbol || !arbol->comparador) return FALLO;
  if(!nodo) return FALLO;

  if( !(*nodo) ){
    nodo_abb_t* nuevo_nodo = malloc( sizeof(nodo_abb_t) );
    if( !nuevo_nodo ) return -FALLO;
    nuevo_nodo->elemento = elemento;
    nuevo_nodo->izquierda = nuevo_nodo->derecha = NULL;
    *nodo = nuevo_nodo;
    return EXITO;
  }

  if( (arbol->comparador)( elemento , (*nodo)->elemento ) >= 0 )
    return arbol_insertar_recursivo( arbol, elemento, &( (*nodo)->derecha ) );

  return arbol_insertar_recursivo( arbol, elemento, &( (*nodo)->izquierda ) );
}

int arbol_insertar(abb_t* arbol, void* elemento){
  if(!arbol) return FALLO;
  if(!elemento) return FALLO;
  return arbol_insertar_recursivo( arbol, elemento, &(arbol->nodo_raiz) );
}

// Borra un nodo cuyo elemento ya esta liberado
void nodo_borrar( nodo_abb_t** nodo ){

  nodo_abb_t* aux = (*nodo);
  if( !(*nodo)->izquierda && !(*nodo)->derecha  ){
    free( aux );
    (*nodo) = NULL;
    return;
  }
  if( !(*nodo)->izquierda  ){
    (*nodo) = aux->derecha;
    free(aux);
    return;
  }
  if( !(*nodo)->derecha  ){
    (*nodo)= aux->izquierda;
    free(aux);
    return;
  }

  nodo_abb_t** sucesor = &(aux->izquierda);

  if( !(*sucesor)->derecha ){
    (*sucesor)->derecha = aux->derecha;
    (*nodo) = (*sucesor);
    free(aux);
    return;
  }
  while( (*sucesor)->derecha ){
    (*sucesor) = (*sucesor)->derecha;
  }
  (*nodo) = (*sucesor);
  (*sucesor) = (*sucesor)->izquierda;
  (*nodo)->izquierda = aux->izquierda;
  (*nodo)->derecha = aux->derecha;
  free(aux);
  return;

}
/*
 * Busca en el arbol un elemento igual al provisto (utilizando la
 * funcion de comparación) y si lo encuentra lo quita del arbol.
 * Adicionalmente, si encuentra el elemento, invoca el destructor con
 * dicho elemento.
 * Devuelve 0 si pudo eliminar el elemento o -1 en caso contrario.
 */
 int arbol_borrar_recursivo(abb_t* arbol, void* elemento, nodo_abb_t** nodo){

   if(!arbol || !arbol->comparador) return FALLO;
   if(!nodo) return FALLO;

   if( !(arbol->comparador)( elemento , (*nodo)->elemento ) ){

     if( arbol->destructor )
      (arbol->destructor)( (*nodo)->elemento );
     nodo_borrar( nodo );
     return EXITO;
   }

   if( (arbol->comparador)( elemento , (*nodo)->elemento ) >= 0 )
     return arbol_borrar_recursivo( arbol, elemento, &( (*nodo)->derecha ) );

   return arbol_borrar_recursivo( arbol, elemento, &( (*nodo)->izquierda ) );
 }

int arbol_borrar(abb_t* arbol, void* elemento){
  if(!arbol) return FALLO;
  if(!elemento) return FALLO;
  return arbol_borrar_recursivo( arbol, elemento, &(arbol->nodo_raiz) );
}

/*
 * Busca en el arbol un elemento igual al provisto (utilizando la
 * funcion de comparación).
 *
 * Devuelve el elemento encontrado o NULL si no lo encuentra.
 */
void* arbol_buscar(abb_t* arbol, void* elemento){
  return 0;
}

void* arbol_raiz(abb_t* arbol){
  if(!arbol) return NULL;
  if(!arbol->nodo_raiz) return NULL;
  return arbol->nodo_raiz->elemento;
}

/*
 * Determina si el árbol está vacío.
 * Devuelve true si está vacío o el arbol es NULL, false si el árbol tiene elementos.
 */
bool arbol_vacio(abb_t* arbol){
  if(!arbol) return true;
  if(!arbol->nodo_raiz) return true;
  return false;
}

/*
 * Llena el array del tamaño dado con los elementos de arbol
 * en secuencia inorden.
 * Devuelve la cantidad de elementos del array que pudo llenar (si el
 * espacio en el array no alcanza para almacenar todos los elementos,
 * llena hasta donde puede y devuelve la cantidad de elementos que
 * pudo poner).
 */
size_t arbol_recorrido_inorden(abb_t* arbol, void** array, size_t tamanio_array){
  return 0;
}

/*
 * Llena el array del tamaño dado con los elementos de arbol
 * en secuencia preorden.
 * Devuelve la cantidad de elementos del array que pudo llenar (si el
 * espacio en el array no alcanza para almacenar todos los elementos,
 * llena hasta donde puede y devuelve la cantidad de elementos que
 * pudo poner).
 */
size_t arbol_recorrido_preorden(abb_t* arbol, void** array, size_t tamanio_array){
  return 0;
}

/*
 * Llena el array del tamaño dado con los elementos de arbol
 * en secuencia postorden.
 * Devuelve la cantidad de elementos del array que pudo llenar (si el
 * espacio en el array no alcanza para almacenar todos los elementos,
 * llena hasta donde puede y devuelve la cantidad de elementos que
 * pudo poner).
 */
size_t arbol_recorrido_postorden(abb_t* arbol, void** array, size_t tamanio_array){
  return 0;
}


/*
 * Destruye un nodo y a sus hijos liberando la memoria reservada .
 * Adicionalmente invoca el destructor con el elemento presente en el
 */
void nodo_destruir(abb_t* arbol, nodo_abb_t* nodo){

  if( !nodo ) return;
  nodo_destruir(arbol,nodo->izquierda);
  nodo_destruir(arbol,nodo->derecha);

  if( arbol->destructor )
    (arbol->destructor)(nodo->elemento);
  free(nodo);

  return;
}

void arbol_destruir(abb_t* arbol){
  nodo_destruir( arbol , arbol->nodo_raiz );
  free(arbol);
  return;
}

/*
 * Iterador interno. Recorre el arbol e invoca la funcion con cada
 * elemento del mismo. El puntero 'extra' se pasa como segundo
 * parámetro a la función. Si la función devuelve true, se finaliza el
 * recorrido aun si quedan elementos por recorrer. Si devuelve false
 * se sigue recorriendo mientras queden elementos.
 * El recorrido se realiza de acuerdo al recorrido solicitado.  Los
 * recorridos válidos son: ABB_RECORRER_INORDEN, ABB_RECORRER_PREORDEN
 * y ABB_RECORRER_POSTORDEN.
 * Devuelve la cantidad de elementos que fueron recorridos.
*/
size_t abb_con_cada_elemento(abb_t* arbol, int recorrido, bool (*funcion)(void*, void*), void* extra){
  return 0;
}
