#include "../include/queja.h"

struct rep_queja {
  TCliente cliente;
  TProducto producto;
  char comentario[MAX_COMENTARIO];
  TFecha fecha;
};

TQueja crearTQueja(TFecha fecha, TProducto producto, TCliente cliente, const char comentario[MAX_COMENTARIO]) {
  TQueja Nuevaqueja = new rep_queja;
  Nuevaqueja->cliente = cliente;
  Nuevaqueja->producto = producto;
  Nuevaqueja->fecha = fecha;
  strcpy(Nuevaqueja->comentario, comentario);
  return Nuevaqueja;
}

void imprimirTQueja(TQueja queja) {
  printf("Fecha: ");
  imprimirTFecha(queja->fecha);
  printf("\n");
  printf("Cliente: ");
  imprimirTCliente(queja->cliente);
  imprimirTProducto(queja->producto);
  printf("\n");
  printf("Comentario: %s\n", queja->comentario);
}

void liberarTQueja(TQueja &queja) {
  liberarTCliente(queja->cliente);
  liberarTFecha(queja->fecha);
  liberarTProducto(queja->producto);
  delete queja;
  queja = NULL;
}

TFecha fechaTQueja(TQueja queja) {
  return queja->fecha;
}
