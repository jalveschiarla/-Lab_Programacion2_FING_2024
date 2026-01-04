#include "../include/promocion.h"

//  La estructura almacena un id de tipo entero, dos fechas para representar el inicio y el fin 
// de la promocion, así como la información de qué productos forman parte de la promocion.
struct rep_promocion {
    int idProm;
    TFecha ini;
    TFecha fin;
    TConjuntoProductos productos;
};

TPromocion crearTPromocion(int idProm, TFecha ini, TFecha fin, int cantMax){ 
    TPromocion nuevaPromo = new rep_promocion; 
    nuevaPromo->idProm = idProm;
    nuevaPromo->ini = ini;
    nuevaPromo->fin = fin;
    nuevaPromo->productos = crearTConjuntoProductos(cantMax);
    return nuevaPromo;
}

void agregarATPromocion(TPromocion &prom, TProducto p){
    insertarTConjuntoProductos(prom->productos, idTProducto(p));
}

void imprimirTPromocion(TPromocion prom){
    printf("Promocion #%d del ", prom->idProm);
    imprimirTFecha(prom->ini);
    printf(" al ");
    imprimirTFecha(prom->fin);
    printf("\nProductos: ");
    imprimirTConjuntoProductos(prom->productos);
}

void liberarTPromocion(TPromocion &prom){
    liberarTFecha(prom->ini);
    liberarTFecha(prom->fin);
    liberarTConjuntoProductos(prom->productos);
    delete prom;
    prom = NULL;
}

bool perteneceATPromocion(TPromocion prom, TProducto p){
    return (perteneceTConjuntoProductos(prom->productos, idTProducto(p)));
}

int idTPromocion(TPromocion prom){ 
    return prom->idProm;
}

TFecha fechaInicioTPromocion(TPromocion prom){
    return prom->ini;
}

TFecha fechaFinTPromocion(TPromocion prom){
    return prom->fin;
}

bool compatibleFecha(TPromocion prom1, TPromocion prom2){
    bool devolver;
    if (compararTFechas(prom1->ini, prom2->ini) == 0){
        devolver = false;
    } else if (compararTFechas(prom1->ini, prom2->ini) == 1){
        if(compararTFechas(prom1->ini, prom2->fin) == 1){
            devolver = true;
        } else {
            devolver = false;
            }
    } else if (compararTFechas(prom1->ini, prom2->ini) == -1){
        if(compararTFechas(prom2->ini, prom1->fin) == 1){
            devolver = true;
        } else {
            devolver = false;
            }       
    }
    return devolver;
}

bool sonPromocionesCompatibles(TPromocion prom1, TPromocion prom2){
    if(compatibleFecha(prom1, prom2) == true){
        return true;
    } else {
        TConjuntoProductos conjuntoInter = interseccionTConjuntoProductos(prom1->productos, prom2->productos);
        if (esVacioTConjuntoProductos(conjuntoInter) == true){
            liberarTConjuntoProductos(conjuntoInter);
            return true;
        } else {
            liberarTConjuntoProductos(conjuntoInter);
            return false;
        }
    }
}



