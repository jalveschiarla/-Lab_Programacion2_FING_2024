#include "../include/tablaQuejas.h"

struct nodoHash {
  TFecha dominio;
  TQueja rango;
  nodoHash* sig;
};


struct rep_tablaQuejas {
  nodoHash** tabla;
  int cantidad;
  int cota;
};

int funcionHash(TFecha fecha, int cantEstimadas){
  return (31 * (int) mesTFecha(fecha) + (int) diaTFecha(fecha)) % cantEstimadas;
}

TablaQuejas crearTablaQuejas(int cantEstimadas) {
  TablaQuejas NuevaTabla = new rep_tablaQuejas;
  NuevaTabla->cantidad = 0;
  NuevaTabla->cota = cantEstimadas;
  NuevaTabla->tabla = new nodoHash* [cantEstimadas];
  for (int i=0; i < cantEstimadas; i++) {
    NuevaTabla->tabla[i]=NULL;
  }
  return NuevaTabla;
}

void agregarQuejaTablaQuejas(TablaQuejas tabla, TQueja queja) {
  int posicion = funcionHash(fechaTQueja(queja), tabla->cota);
  nodoHash* lista = tabla->tabla[posicion];
  while (lista != NULL && lista->dominio != fechaTQueja(queja)){
    lista = lista->sig;
  }
  if (lista == NULL){
      nodoHash* nuevo = new nodoHash;
      nuevo->dominio = fechaTQueja(queja);
      nuevo->rango = queja;
      nuevo->sig = tabla->tabla[posicion];
      tabla->tabla[posicion] = nuevo;
      tabla->cantidad++;
  }
  else lista->rango = queja;
}

void imprimirTablaQuejas(TablaQuejas tabla) {
  for (int i = 0; i < tabla->cota; i++) {
    nodoHash* actual = tabla->tabla[i];
    if (actual == NULL){
      printf("No hay elementos guardados en la posicion %u de la tabla.\n", i);
    } else {
      printf("Elementos en la posicion %u de la tabla:\n", i);
      while (actual != NULL){
        imprimirTQueja(actual->rango);
        actual = actual->sig;
      }
    }

  }
}

bool perteneceQuejaTablaQuejas(TablaQuejas tabla, TFecha fecha) {
  nodoHash* lista = tabla->tabla[funcionHash(fecha, tabla->cota)];
  while (lista != NULL && compararTFechas(lista->dominio, fecha) != 0){
      lista = lista->sig;
  }
  return lista != NULL;
}

TQueja obtenerQuejaTablaQuejas(TablaQuejas tabla, TFecha fecha) {
    nodoHash* lista = tabla->tabla[funcionHash(fecha, tabla->cota)];
  while (lista != NULL && compararTFechas(lista->dominio, fecha) != 0){
      lista = lista->sig;
  }
  if (lista == NULL){
    return NULL;
  } else {
    return lista->rango;
  }
}

void liberarTablaQuejas(TablaQuejas &tabla) {
  for (int i = 0; i < tabla->cota; i++) {
    nodoHash* actual = tabla->tabla[i]; 
    while (actual != nullptr) {
      nodoHash* aEliminar = actual;
      liberarTQueja(actual->rango);
      actual = actual->sig;
      delete aEliminar;
    }
  }
  delete[] tabla->tabla;
  tabla->tabla = NULL;
  delete tabla;
  tabla = NULL;
}
