#include "../include/carritoProductos.h"

struct rep_carritoProductos{
    TProducto producto;
    TCarritoProductos sig;
};


TCarritoProductos crearCarritoProductosVacio(){
    return NULL;
}

void insertarProductoCarritoProductos(TCarritoProductos &carritoProductos, TProducto producto){
    TCarritoProductos nuevo = new rep_carritoProductos;
    nuevo->producto = producto;
    if ((carritoProductos == NULL) || (idTProducto(carritoProductos->producto) > idTProducto(producto))){
        nuevo->sig = carritoProductos;
        carritoProductos = nuevo;
    } else {
        TCarritoProductos p = carritoProductos;
        while (p->sig != NULL && idTProducto(p->sig->producto) < idTProducto(producto)){
            p = p->sig;
        }
        nuevo->sig = p->sig;
        p->sig = nuevo; 
    }
}

void imprimirCarritoProductos(TCarritoProductos carritoProductos){
    while(carritoProductos != NULL){
        imprimirTProducto(carritoProductos->producto);
        carritoProductos = carritoProductos->sig;
    }
}

void liberarCarritoProductos(TCarritoProductos &carritoProductos){
    while(carritoProductos != NULL){
        TCarritoProductos p = carritoProductos;
        liberarTProducto(p->producto);
        carritoProductos = carritoProductos->sig;
        delete p;
    }
    carritoProductos = NULL;
}

bool esVacioCarritoProductos(TCarritoProductos carritoProductos){
    if (carritoProductos == NULL){
        return true;
    } else {
        return false;
        }
}

bool existeProductoCarritoProductos(TCarritoProductos carritoProductos, int idProducto){
    while(carritoProductos != NULL && (idTProducto(carritoProductos->producto) != idProducto)){
        carritoProductos = carritoProductos->sig;
    }
    if (carritoProductos != NULL && idTProducto(carritoProductos->producto) == idProducto){
        return true;
    } else {
        return false;
    }
}

TProducto obtenerProductoCarritoProductos(TCarritoProductos carritoProductos, int idProducto){
    TCarritoProductos p = carritoProductos;
    while(idTProducto(p->producto) != idProducto){
        p = p->sig;
    }
    if (p != NULL){
    return (p->producto);
    } else {
        return NULL;
    }
}

void removerProductoCarritoProductos(TCarritoProductos &carritoProductos, int idProducto){
    if (carritoProductos != NULL && idTProducto(carritoProductos->producto) == idProducto){
        TCarritoProductos aux = carritoProductos;
        carritoProductos = carritoProductos -> sig;
        liberarTProducto(aux->producto);
        delete aux;
    } else {
        if (carritoProductos != NULL){
            TCarritoProductos iter = carritoProductos;
            while(iter->sig != NULL && idTProducto(iter->sig->producto) != idProducto){
                iter = iter->sig;
            }
            TCarritoProductos aux = iter->sig->sig;
            liberarTProducto(iter->sig->producto);
            delete iter->sig;
            iter->sig = aux;
        } else return;
    }
}