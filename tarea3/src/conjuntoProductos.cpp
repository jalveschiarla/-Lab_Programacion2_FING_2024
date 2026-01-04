#include "../include/conjuntoProductos.h"


// Definición de tipo TConjuntoProductos como un puntero a rep_conjuntoproductos
// El conjunto es acotado, y la cantidad máxima de elementos define el rango de 
// identificadores que almacena.
// Los identificadores que almacena el conjunto cumplen 0 <= id < cantMax
struct rep_conjuntoProductos{
    bool *productos;
    int cantMax;
};

TConjuntoProductos crearTConjuntoProductos(int cantMax){ 
    TConjuntoProductos nuevoConjunto = new rep_conjuntoProductos;
    nuevoConjunto->cantMax = cantMax;
    nuevoConjunto->productos = new bool[cantMax];
    for(int i=0; i < cantMax; i++){
        nuevoConjunto->productos[i] = false;
    }
    return nuevoConjunto;
}

void insertarTConjuntoProductos(TConjuntoProductos &conjuntoProductos, int idProducto){
    if (idProducto < conjuntoProductos->cantMax) {
        conjuntoProductos->productos[idProducto] = true;
    }
}

void imprimirTConjuntoProductos(TConjuntoProductos conjuntoProductos){
    for(int i=0; i < conjuntoProductos->cantMax; i++){
        if (conjuntoProductos->productos[i] == true){
            printf("%d ", i);
        }
    }
    printf("\n");
}

void liberarTConjuntoProductos(TConjuntoProductos &conjuntoProductos){
    delete[]conjuntoProductos->productos;
    delete conjuntoProductos;
    conjuntoProductos = NULL;
}

bool esVacioTConjuntoProductos(TConjuntoProductos conjuntoProductos){
    for(int i=0; i < conjuntoProductos->cantMax; i++){
        if(conjuntoProductos->productos[i]== true){
            return false;
        }
    }
    return true;
}

int cantidadTConjuntoProductos(TConjuntoProductos conjuntoProductos){
    int cont=0;
    for(int i=0; i < conjuntoProductos->cantMax; i++){
        if (conjuntoProductos->productos[i] == true){
            cont++;
        }
    }
    return cont;
}

int cantMaxTConjuntoProductos(TConjuntoProductos conjuntoProductos){ 
    return conjuntoProductos->cantMax;
}

bool perteneceTConjuntoProductos(TConjuntoProductos conjuntoProductos, int idProducto){
    if (idProducto < conjuntoProductos->cantMax){
        return (conjuntoProductos->productos[idProducto]==true);
    } else {
        return false;
    }
}

void borrarDeTConjuntoProductos(TConjuntoProductos &conjuntoProductos, int idProducto){
    if (idProducto < conjuntoProductos->cantMax){
        conjuntoProductos->productos[idProducto] = false;
    } else {
        return;
    }
}

TConjuntoProductos unionTConjuntoProductos(TConjuntoProductos conjuntoProductos1, TConjuntoProductos conjuntoProductos2){
    TConjuntoProductos conjuntoUnido = crearTConjuntoProductos(conjuntoProductos1->cantMax);
    for(int i=0; i < conjuntoProductos1->cantMax; i++){
        if (conjuntoProductos1->productos[i] == true || conjuntoProductos2->productos[i] == true){
            conjuntoUnido->productos[i] = true;
        } else {
            conjuntoUnido->productos[i] = false;
        }
    }    
    return conjuntoUnido;
}

TConjuntoProductos interseccionTConjuntoProductos(TConjuntoProductos conjuntoProductos1, TConjuntoProductos conjuntoProductos2){
    TConjuntoProductos conjuntoInter = crearTConjuntoProductos(conjuntoProductos1->cantMax);
    for(int i=0; i < conjuntoProductos1->cantMax; i++){
        if (conjuntoProductos1->productos[i] == true && conjuntoProductos2->productos[i] == true){
            conjuntoInter->productos[i] = true;
        } else {
            conjuntoInter->productos[i] = false;
        }
    }    
    return conjuntoInter;
}

TConjuntoProductos diferenciaTConjuntoProductos(TConjuntoProductos conjuntoProductos1, TConjuntoProductos conjuntoProductos2){
    TConjuntoProductos conjuntoDif = crearTConjuntoProductos(conjuntoProductos1->cantMax);
    for(int i=0; i < conjuntoProductos1->cantMax; i++){
        if (conjuntoProductos1->productos[i] == true && conjuntoProductos2->productos[i] == false){
            conjuntoDif->productos[i] = true;
        } else {
            conjuntoDif->productos[i] = false;
        }
    }    
    return conjuntoDif;
}
