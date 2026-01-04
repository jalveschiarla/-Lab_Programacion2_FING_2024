#include "../include/colaEnvios.h"

struct rep_cola_envios {
    TEnvio* heap;
    int tope;
    int max;
    bool invertido;
};

TColaEnvios crearTColaEnvios(int N) {
    TColaEnvios NuevaCola = new rep_cola_envios;
    NuevaCola->heap = new rep_envio* [N+1];
    NuevaCola->max = N;
    NuevaCola->tope = 0;
    NuevaCola->invertido = false;
    for (int j = 0; j < N + 1; j++){
        NuevaCola->heap[j] = NULL;
    }
    return NuevaCola;
 }

void filtradoAscendente(int pos, TColaEnvios &colaEnvios) {
    if(colaEnvios->invertido == false){
        while (pos > 1){
            int padre = pos/2;
            if (compararTFechas(obtenerFechaTEnvio(colaEnvios->heap[padre]), obtenerFechaTEnvio(colaEnvios->heap[pos])) == -1){
                TEnvio aux = colaEnvios->heap[pos];
                colaEnvios->heap[pos] = colaEnvios->heap[padre];
                colaEnvios->heap[padre] = aux;
            }
            pos = padre;
        }
    } else if(colaEnvios->invertido == true){
        while (pos > 1){
            int padre = pos/2;
            if (compararTFechas(obtenerFechaTEnvio(colaEnvios->heap[padre]), obtenerFechaTEnvio(colaEnvios->heap[pos])) == 1){
                TEnvio aux = colaEnvios->heap[pos];
                colaEnvios->heap[pos] = colaEnvios->heap[padre];
                colaEnvios->heap[padre] = aux;
            }
            pos = padre;
        }
    }
}

void encolarEnvioTColaEnvios(TColaEnvios &colaEnvios, TEnvio envio) {
    if (colaEnvios->tope < colaEnvios->max){
        colaEnvios->tope++;
        int pos = colaEnvios->tope;
        colaEnvios->heap[pos] = envio;
        filtradoAscendente(pos, colaEnvios);
    }
}

int cantidadTColaEnvios(TColaEnvios colaEnvios) {
    return colaEnvios->tope;
}

int potencia(int base, int exp){
    if (exp == 0){
        return 1;
    } else if ((exp % 2) != 0){
        return base * potencia(base, exp-1);
    } else {
        int aux = potencia(base, exp/2);
        return aux * aux;
    }
}

void imprimirTColaEnvios(TColaEnvios colaEnvios) {
    printf("\n");
    int nivel = 1;
    int indiceActual = 1;
    int indiceEnNivel = 1;
    while (indiceActual <= (colaEnvios->tope)) {
        int cantidadEnNivel = potencia(2, nivel-1);
        printf("Nivel %d\n", nivel);
        while (indiceEnNivel <= cantidadEnNivel && indiceActual <= (colaEnvios->tope)){
            printf("%d) ", indiceActual);
            imprimirTEnvio(colaEnvios->heap[indiceActual]);
            indiceActual++;
            indiceEnNivel++;
        }
        printf("\n");
        indiceEnNivel = 1;
        nivel++;
    }
}

void filtradoDescendente(int pos, TColaEnvios &colaEnvios){
    if(colaEnvios->invertido == false){
        while(pos < colaEnvios->tope){
            int HDer = 2*pos+1;
            int HIzq = 2*pos;
            if (HDer <= colaEnvios->tope && HIzq <= colaEnvios->tope){
                if(compararTFechas(obtenerFechaTEnvio(colaEnvios->heap[HDer]), obtenerFechaTEnvio(colaEnvios->heap[HIzq])) == 1 && compararTFechas(obtenerFechaTEnvio(colaEnvios->heap[HDer]), obtenerFechaTEnvio(colaEnvios->heap[pos])) == 1){
                    TEnvio aux = colaEnvios->heap[pos];
                    colaEnvios->heap[pos] = colaEnvios->heap[HDer];
                    colaEnvios->heap[HDer] = aux;
                    pos = HDer;
                } else if (compararTFechas(obtenerFechaTEnvio(colaEnvios->heap[HIzq]), obtenerFechaTEnvio(colaEnvios->heap[pos])) == 1){
                    TEnvio aux = colaEnvios->heap[pos];
                    colaEnvios->heap[pos] = colaEnvios->heap[HIzq];
                    colaEnvios->heap[HIzq] = aux;
                    pos = HIzq;
                }
            } else if (HDer <= colaEnvios->tope && compararTFechas(obtenerFechaTEnvio(colaEnvios->heap[HDer]), obtenerFechaTEnvio(colaEnvios->heap[pos])) == 1){
                    TEnvio aux = colaEnvios->heap[pos];
                    colaEnvios->heap[pos] = colaEnvios->heap[HDer];
                    colaEnvios->heap[HDer] = aux;
                    pos = HDer;
            } else if (HIzq <= colaEnvios->tope && compararTFechas(obtenerFechaTEnvio(colaEnvios->heap[HIzq]), obtenerFechaTEnvio(colaEnvios->heap[pos])) == 1){
                    TEnvio aux = colaEnvios->heap[pos];
                    colaEnvios->heap[pos] = colaEnvios->heap[HIzq];
                    colaEnvios->heap[HIzq] = aux;
                    pos = HIzq;
            } else {
                break;
            }
        }
    } else if(colaEnvios->invertido == true) {
       while(pos < colaEnvios->tope){
            int HDer = 2*pos+1;
            int HIzq = 2*pos;
            if (HDer <= colaEnvios->tope && HIzq <= colaEnvios->tope){
                if(compararTFechas(obtenerFechaTEnvio(colaEnvios->heap[HDer]), obtenerFechaTEnvio(colaEnvios->heap[HIzq])) == -1 && compararTFechas(obtenerFechaTEnvio(colaEnvios->heap[HDer]), obtenerFechaTEnvio(colaEnvios->heap[pos])) == -1){
                    TEnvio aux = colaEnvios->heap[pos];
                    colaEnvios->heap[pos] = colaEnvios->heap[HDer];
                    colaEnvios->heap[HDer] = aux;
                    pos = HDer;
                } else if (compararTFechas(obtenerFechaTEnvio(colaEnvios->heap[HIzq]), obtenerFechaTEnvio(colaEnvios->heap[pos])) == -1){
                    TEnvio aux = colaEnvios->heap[pos];
                    colaEnvios->heap[pos] = colaEnvios->heap[HIzq];
                    colaEnvios->heap[HIzq] = aux;
                    pos = HIzq;
                }
            } else if (HDer <= colaEnvios->tope && compararTFechas(obtenerFechaTEnvio(colaEnvios->heap[HDer]), obtenerFechaTEnvio(colaEnvios->heap[pos])) == -1){
                    TEnvio aux = colaEnvios->heap[pos];
                    colaEnvios->heap[pos] = colaEnvios->heap[HDer];
                    colaEnvios->heap[HDer] = aux;
                    pos = HDer;
            } else if (HIzq <= colaEnvios->tope && compararTFechas(obtenerFechaTEnvio(colaEnvios->heap[HIzq]), obtenerFechaTEnvio(colaEnvios->heap[pos])) == -1){
                    TEnvio aux = colaEnvios->heap[pos];
                    colaEnvios->heap[pos] = colaEnvios->heap[HIzq];
                    colaEnvios->heap[HIzq] = aux;
                    pos = HIzq;
            } else {
                break;
            }
        } 
    }
}

TEnvio desencolarTColaEnvios(TColaEnvios &colaEnvios) { 
    TEnvio res = colaEnvios->heap[1];
    colaEnvios->heap[1] = colaEnvios->heap[colaEnvios->tope];
    colaEnvios->heap[colaEnvios->tope] = NULL;
    colaEnvios->tope--;
    filtradoDescendente(1, colaEnvios);
    return res;
}

void liberarTColaEnvios(TColaEnvios &colaEnvios) {
    for (int i = 1; i <= colaEnvios->tope; i++){
        liberarTEnvio(colaEnvios->heap[i]);
    }
    delete[] colaEnvios->heap;
    delete colaEnvios;
    colaEnvios = NULL;
}

void invertirPrioridadTColaEnvios(TColaEnvios &colaEnvio) {
    colaEnvio->invertido = !colaEnvio->invertido;
    for (int i = 1; i <= colaEnvio->tope; i++){
        filtradoAscendente(i, colaEnvio);
    }
}

TEnvio masPrioritarioTColaEnvios(TColaEnvios colaEnvio) {
    return colaEnvio->heap[1];
}

int maxTColaEnvios(TColaEnvios colaEnvio) {
    return colaEnvio->max;
}