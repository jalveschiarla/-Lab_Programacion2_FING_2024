#include "../include/listaPromociones.h"

struct rep_listaPromociones {
  TPromocion promocion;
  TListaPromociones sig;
};

TListaPromociones crearTListaPromocionesVacia() {
  return NULL;
}

void agregarPromocionTListaPromociones(TListaPromociones &listaPromociones, TPromocion promocion) {
  TListaPromociones nueva = new rep_listaPromociones;
  nueva->promocion = promocion;
  nueva->sig = NULL;
  if (listaPromociones == NULL || compararTFechas(fechaInicioTPromocion(listaPromociones->promocion), fechaInicioTPromocion(promocion)) >= 0){
    nueva->sig = listaPromociones;
    listaPromociones = nueva;
  } else {
    TListaPromociones aux = listaPromociones;
    while (aux->sig != NULL && compararTFechas(fechaInicioTPromocion(aux->sig->promocion), fechaInicioTPromocion(promocion)) == -1){
      aux = aux->sig;
    }
    nueva->sig = aux->sig;
    aux->sig = nueva;
  }
}

void imprimirTListaPromociones(TListaPromociones listaPromociones) {
  while (listaPromociones != NULL){
    imprimirTPromocion(listaPromociones->promocion);
    listaPromociones = listaPromociones->sig;
  }
}

void liberarTListaPromociones(TListaPromociones &listaPromociones, bool liberarPromociones) {
  TListaPromociones aux;
  if(liberarPromociones == true){
    while(listaPromociones != NULL){
      aux = listaPromociones;
      listaPromociones = listaPromociones->sig;
      liberarTPromocion(aux->promocion);
      delete aux;
    }
  } else {
      while(listaPromociones != NULL){
        aux = listaPromociones;
        listaPromociones = listaPromociones->sig;
        delete aux;
    }
  }
}

bool esVaciaTListaPromociones(TListaPromociones promociones) {
  if (promociones == NULL){
    return true;
  } else {
    return false;
    }
}


bool pertenecePromocionTListaPromociones(TListaPromociones listaPromociones, int idPromocion) {
  while (listaPromociones != NULL && idTPromocion(listaPromociones->promocion) != idPromocion){
  listaPromociones = listaPromociones->sig;
  }
  if (listaPromociones == NULL){
    return false;
  } else {
    return true;
  }
}

TPromocion obtenerPromocionTListaPromociones(TListaPromociones listaPromociones, int idPromocion) {
  while (listaPromociones->sig != NULL && idTPromocion(listaPromociones->promocion) != idPromocion){
    listaPromociones = listaPromociones->sig;
  }
  return listaPromociones->promocion;
}


TListaPromociones obtenerPromocionesFinalizadas(TListaPromociones &listaPromociones, TFecha fecha) {
  TListaPromociones actual = listaPromociones;
  TListaPromociones anterior = NULL;
  TListaPromociones nuevaLista = NULL;
  TListaPromociones finNuevaLista = NULL;
  while (actual != NULL){
    if(compararTFechas(fechaFinTPromocion(actual->promocion), fecha) == -1){
      TListaPromociones nodoMovido = actual;

      if(anterior == NULL){
        listaPromociones = actual->sig;
      } else {
        anterior->sig = actual->sig;
      }
      actual = actual->sig;
      nodoMovido->sig = NULL;
      if (nuevaLista == NULL){
        nuevaLista = nodoMovido;
        finNuevaLista = nodoMovido;
      } else {
        finNuevaLista->sig=nodoMovido;
        finNuevaLista = nodoMovido;
      }
    } else {
      anterior = actual;
      actual = actual->sig;
    }
  }
  return nuevaLista;
}

TListaPromociones obtenerPromocionesActivas(TListaPromociones &listaPromociones, TFecha fecha) {
  TListaPromociones actual = listaPromociones;
  TListaPromociones anterior = NULL;
  TListaPromociones nuevaLista = NULL;
  TListaPromociones finNuevaLista = NULL;
  while (actual != NULL){
    if(compararTFechas(fechaInicioTPromocion(actual->promocion), fecha) <= 0 && compararTFechas(fechaFinTPromocion(actual->promocion), fecha) >=0){
      TListaPromociones nodoMovido = actual;

      if(anterior == NULL){
        listaPromociones = actual->sig;
      } else {
        anterior->sig = actual->sig;
      }
      actual = actual->sig;
      nodoMovido->sig = NULL;
      if (nuevaLista == NULL){
        nuevaLista = nodoMovido;
        finNuevaLista = nodoMovido;
      } else {
        finNuevaLista->sig=nodoMovido;
        finNuevaLista = nodoMovido;
      }
    } else {
      anterior = actual;
      actual = actual->sig;
    }
  }
  return nuevaLista;
}

bool esCompatibleTListaPromociones(TListaPromociones listaPromociones, TPromocion promocion) {
  TListaPromociones aux = listaPromociones;
  while (aux != NULL && sonPromocionesCompatibles(aux->promocion, promocion)){
    aux = aux->sig;
  }
  if (aux == NULL){
    return true;
  } else {
    return false;
  }
}

TListaPromociones unirListaPromociones(TListaPromociones listaPromociones1, TListaPromociones listaPromociones2) {
  TListaPromociones nuevaLista = NULL;
  while(listaPromociones1 != NULL){
    agregarPromocionTListaPromociones(nuevaLista, listaPromociones1->promocion);
    listaPromociones1 = listaPromociones1->sig;
  }
  while (listaPromociones2 != NULL){
    agregarPromocionTListaPromociones(nuevaLista, listaPromociones2->promocion);
    listaPromociones2 = listaPromociones2->sig;    
  }
  return nuevaLista;
}
