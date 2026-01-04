#include "../include/historial.h"

struct rep_historial {
    TListaPromociones pasadas;
    TListaPromociones activas;
    TListaPromociones futuras;
    TFecha fechaActual;
};

THistorial crearTHistorial(TFecha fecha) { 
    THistorial nuevo = new rep_historial;
    nuevo->pasadas = crearTListaPromocionesVacia();
    nuevo->activas = crearTListaPromocionesVacia();
    nuevo->futuras = crearTListaPromocionesVacia();
    nuevo->fechaActual = fecha;
    return nuevo;
}

void agregarPromocionTHistorial(THistorial historial, TPromocion promocion) {
    if (compararTFechas(historial->fechaActual, fechaInicioTPromocion(promocion)) == -1){
        agregarPromocionTListaPromociones(historial->futuras, promocion);
    } else if (compararTFechas(historial->fechaActual, fechaFinTPromocion(promocion)) == 1){
            agregarPromocionTListaPromociones(historial->pasadas, promocion);
        } else {
            agregarPromocionTListaPromociones(historial->activas, promocion);
        }
}

void agregarProductoAPromocionTHistorial(THistorial historial, TProducto producto, int idPromo) {
    if(pertenecePromocionTListaPromociones(historial->activas, idPromo)){
        TPromocion promo = obtenerPromocionTListaPromociones(historial->activas, idPromo);
        agregarATPromocion(promo, producto);
    } else if(pertenecePromocionTListaPromociones(historial->futuras, idPromo)){
            TPromocion promo = obtenerPromocionTListaPromociones(historial->futuras, idPromo);
            agregarATPromocion(promo, producto);
        } else {
            TPromocion promo = obtenerPromocionTListaPromociones(historial->pasadas, idPromo);
            agregarATPromocion(promo, producto);
        }
}

void avanzarAFechaTHistorial(THistorial historial, TFecha fecha) {
    liberarTFecha(historial->fechaActual);
    historial->fechaActual = fecha;
    
    TListaPromociones terminaron1 = obtenerPromocionesFinalizadas(historial->activas, fecha);
    TListaPromociones terminaron2 = obtenerPromocionesFinalizadas(historial->futuras, fecha);
    TListaPromociones temp1 = historial->pasadas;
    TListaPromociones aux1 = unirListaPromociones(temp1, terminaron1);
    TListaPromociones nueva1 = unirListaPromociones(aux1, terminaron2);
    historial->pasadas = nueva1;
    liberarTListaPromociones(temp1, false);
    liberarTListaPromociones(terminaron1, false);
    liberarTListaPromociones(terminaron2, false);
    liberarTListaPromociones(aux1, false);
    
    TListaPromociones empezaron = obtenerPromocionesActivas(historial->futuras, fecha);
    TListaPromociones temp2 = obtenerPromocionesActivas(historial->activas, fecha);
    TListaPromociones borrar = historial->activas;
    TListaPromociones aux2 = unirListaPromociones(temp2, empezaron);
    historial->activas = aux2;
    liberarTListaPromociones(borrar, false);
    liberarTListaPromociones(temp2, false);
    liberarTListaPromociones(empezaron, false);

}

void imprimirPromocionesFinalizadosTHistorial(THistorial historial) {
    imprimirTListaPromociones(historial->pasadas);
}

void imprimirPromocionesActivasTHistorial(THistorial historial) {
    imprimirTListaPromociones(historial->activas);
}

void imprimirPromocionesFuturasTHistorial(THistorial historial) {
    imprimirTListaPromociones(historial->futuras);
}

bool esCompatiblePromocionTHistorial(THistorial historial, TPromocion promocion) { 
    if(esCompatibleTListaPromociones(historial->activas, promocion) && esCompatibleTListaPromociones(historial->futuras, promocion) && esCompatibleTListaPromociones(historial->pasadas, promocion)){
        return true;
    } else { 
        return false;
    }
}

void liberarTHistorial(THistorial &historial) {
    liberarTListaPromociones(historial->activas, true);
    liberarTListaPromociones(historial->futuras, true);
    liberarTListaPromociones(historial->pasadas, true);
    liberarTFecha(historial->fechaActual);
    delete historial;
    historial = NULL;
}
