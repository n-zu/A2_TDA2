#include "abb.h"
#include "pa2m.h"
#include <stdio.h>
#include <string.h>

typedef struct cosa{
    int clave;
    char contenido[10];
}cosa;

cosa* crear_cosa(int clave){
    cosa* c = (cosa*)malloc(sizeof(cosa));
    if(c)
        c->clave = clave;
    return c;
}

void destruir_cosa(cosa* c){
    free(c);
}
int comparar_cosas(void* elemento1, void* elemento2){
    if(!elemento1 || !elemento2)
        return 0;

    if(((cosa*)elemento1)->clave>((cosa*)elemento2)->clave)
        return 1;
    if(((cosa*)elemento1)->clave<((cosa*)elemento2)->clave)
        return -1;
    return 0;
}
void destructor_de_cosas(void* elemento){
    if(!elemento)
        return;
    destruir_cosa((cosa*)elemento);
}

bool mostrar_elemento(void* elemento, void* extra){
    extra=extra; //para que no se queje el compilador, gracias -Werror -Wall
    if(elemento)
        printf("%i ", ((cosa*)elemento)->clave);
    return false;
}
bool mostrar_hasta_5(void* elemento, void* extra){
    extra=extra; //para que no se queje el compilador, gracias -Werror -Wall
    if(elemento){
        printf("%i ", ((cosa*)elemento)->clave);
        if(((cosa*)elemento)->clave == 5)
            return true;
    }
    return false;
}
bool mostrar_acumulado(void* elemento, void* extra){
    if(elemento && extra){
        *(int*)extra += ((cosa*)elemento)->clave;
        printf("%i ", *(int*)extra);
    }
    return false;
}
void mini_pruebas_originales(){

  abb_t* arbol = arbol_crear(comparar_cosas, destructor_de_cosas);

  cosa* c1= crear_cosa(1);
  cosa* c2= crear_cosa(2);
  cosa* c3= crear_cosa(3);
  cosa* c4= crear_cosa(4);
  cosa* c5= crear_cosa(5);
  cosa* c6= crear_cosa(6);
  cosa* c7= crear_cosa(7);
  cosa* auxiliar = crear_cosa(0);

  arbol_insertar(arbol, c4);
  arbol_insertar(arbol, c2);
  arbol_insertar(arbol, c6);
  arbol_insertar(arbol, c1);
  arbol_insertar(arbol, c3);
  arbol_insertar(arbol, c5);
  arbol_insertar(arbol, c7);

  printf("El nodo raiz deberia ser 4: %s\n", ((cosa*)arbol_raiz(arbol))->clave==4?"SI":"NO");

  auxiliar->clave = 5;
  printf("Busco el elemento 5: %s\n", ((cosa*)arbol_buscar(arbol, auxiliar))->clave==5?"SI":"NO");

  auxiliar->clave = 7;
  printf("Borro nodo hoja (7): %s\n", (arbol_borrar(arbol, auxiliar))==0?"SI":"NO");

  auxiliar->clave = 6;
  printf("Borro nodo con un hijo (6): %s\n", (arbol_borrar(arbol, auxiliar))==0?"SI":"NO");

  auxiliar->clave = 2;
  printf("Borro nodo con dos hijos (2): %s\n", (arbol_borrar(arbol, auxiliar))==0?"SI":"NO");

  auxiliar->clave = 4;
  printf("Borro la raiz (4): %s\n", (arbol_borrar(arbol, auxiliar))==0?"SI":"NO");

  auxiliar->clave = 3;
  printf("Busco el elemento (3): %s\n", ((cosa*)arbol_buscar(arbol, auxiliar))->clave==3?"SI":"NO");

  cosa* elementos[10];

  printf("Recorrido inorden (deberian salir en orden 1 3 5): ");
  size_t cantidad = arbol_recorrido_inorden(arbol, (void**)elementos, 10);
  for(size_t i=0;i<cantidad;i++)
      printf("%i ", elementos[i]->clave);
  printf("\n");

  printf("\n\nInserto mas valores y pruebo el iterador interno\n\n");
  arbol_insertar(arbol, crear_cosa(15));
  arbol_insertar(arbol, crear_cosa(0));
  arbol_insertar(arbol, crear_cosa(9));
  arbol_insertar(arbol, crear_cosa(7));
  arbol_insertar(arbol, crear_cosa(4));


  printf("Recorrido inorden iterador interno: ");
  abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_elemento, NULL);
  printf("\n");

  printf("Recorrido preorden iterador interno: ");
  abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_elemento, NULL);
  printf("\n");

  printf("Recorrido postorden iterador interno: ");
  abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_elemento, NULL);
  printf("\n");

  printf("\nRecorrido inorden hasta encontrar el 5: ");
  abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_hasta_5, NULL);
  printf("\n");

  printf("Recorrido preorden hasta encontrar el 5: ");
  abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_hasta_5, NULL);
  printf("\n");

  printf("Recorrido postorden hasta encontrar el 5: ");
  abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_hasta_5, NULL);
  printf("\n");

  int acumulador=0;
  printf("\nRecorrido inorden acumulando los valores: ");
  abb_con_cada_elemento(arbol, ABB_RECORRER_INORDEN, mostrar_acumulado, &acumulador);
  printf("\n");

  acumulador=0;
  printf("Recorrido preorden acumulando los valores: ");
  abb_con_cada_elemento(arbol, ABB_RECORRER_PREORDEN, mostrar_acumulado, &acumulador);
  printf("\n");

  acumulador=0;
  printf("Recorrido postorden acumulando los valores: ");
  abb_con_cada_elemento(arbol, ABB_RECORRER_POSTORDEN, mostrar_acumulado, &acumulador);
  printf("\n");

  free(auxiliar);
  arbol_destruir(arbol);

  return;
}

int comparar_int(void* elemento1, void* elemento2){

  if( *(int*)elemento1 > *(int*)elemento2 )
    return 1;
  if( *(int*)elemento1 < *(int*)elemento2 )
    return -1;
  return 0;
}

void mostrar_cosas_inorder( nodo_abb_t* nodo ){

  if(!nodo) return;
  mostrar_cosas_inorder( nodo->izquierda );
  printf("%i\n", ((cosa*)(nodo->elemento))->clave );
  mostrar_cosas_inorder( nodo->derecha );
}

void mostrar_int_inorder( nodo_abb_t* nodo ){

  if(!nodo) return;
  mostrar_int_inorder( nodo->izquierda );
  printf("%i ",  *(int*)(nodo->elemento) );
  mostrar_int_inorder( nodo->derecha );
}

void pruebas_insertar(){

  abb_t* abb = arbol_crear(comparar_int, NULL);

  int num[10];
  for(int i=0;i<10;i++) num[i]=i;

  arbol_insertar( abb, &num[4] );//      4      |
  arbol_insertar( abb, &num[2] );//    /  \     |
  arbol_insertar( abb, &num[6] );//   2   6     |
  arbol_insertar( abb, &num[1] );//  /\  /\     |
  arbol_insertar( abb, &num[3] );// 1 3 5 7     |
  arbol_insertar( abb, &num[5] );
  arbol_insertar( abb, &num[7] );

  pa2m_afirmar(
    *(int*)abb->nodo_raiz->elemento  == 4 &&
    *(int*)abb->nodo_raiz->izquierda->elemento  == 2 &&
    *(int*)abb->nodo_raiz->derecha->elemento  == 6 &&
    *(int*)abb->nodo_raiz->izquierda->izquierda->elemento  == 1 &&
    *(int*)abb->nodo_raiz->izquierda->derecha->elemento  == 3 &&
    *(int*)abb->nodo_raiz->derecha->izquierda->elemento  == 5 &&
    *(int*)abb->nodo_raiz->derecha->derecha->elemento  == 7
  ,"arbol_insertar");



  arbol_borrar( abb, &num[0] );
  mostrar_int_inorder(abb->nodo_raiz);

  arbol_destruir( abb );
}

int main(int argc, char const *argv[]){

  if( argc == 2 && !strcmp( argv[1], "minipruebas" ) ){
    mini_pruebas_originales();
  } else {

    pa2m_nuevo_grupo("PRUEBAS DE CAJA BLANCA");
    pruebas_insertar();
  }
  printf("\n");
  return 0;
}