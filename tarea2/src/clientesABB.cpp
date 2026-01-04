#include "../include/clientesABB.h"

struct rep_clientesABB {
    TCliente cliente;
    TClientesABB izq, der;
};


TClientesABB crearTClientesABBVacio(){
    return NULL;
}

void insertarTClienteTClientesABB(TClientesABB &clientesABB, TCliente cliente){
    if (clientesABB == NULL){
        clientesABB = new rep_clientesABB;
        clientesABB->cliente = cliente;
        clientesABB->izq = NULL;
        clientesABB->der = NULL;
    } else if(idTCliente(cliente) < idTCliente(clientesABB->cliente)){
            insertarTClienteTClientesABB(clientesABB->izq, cliente);
        } else if(idTCliente(cliente) > idTCliente(clientesABB->cliente)){
            insertarTClienteTClientesABB(clientesABB->der, cliente);
        }
}

void imprimirTClientesABB(TClientesABB clientesABB){
    if (clientesABB != NULL){
        imprimirTClientesABB(clientesABB->izq);
        imprimirTCliente(clientesABB->cliente);
        imprimirTClientesABB(clientesABB->der);
    } else {
        return;
        }
}

void liberarNodo(TClientesABB &clientesABB){
    if (clientesABB != NULL){
        liberarTCliente(clientesABB->cliente);
        delete clientesABB;
        clientesABB = NULL;
    }
}

void liberarTClientesABB(TClientesABB &clientesABB){
    if (clientesABB != NULL){
        liberarTClientesABB(clientesABB->izq);
        liberarTClientesABB(clientesABB->der);
        liberarNodo(clientesABB);
    } 
}

bool existeTClienteTClientesABB(TClientesABB clientesABB, int idCliente){
    if (clientesABB == NULL){
        return false;
    } else if (idTCliente(clientesABB->cliente) == idCliente) {
        return true;
    } else if (idTCliente(clientesABB->cliente) < idCliente){
        return existeTClienteTClientesABB(clientesABB->der, idCliente);
     } else return existeTClienteTClientesABB(clientesABB->izq, idCliente);
}

TCliente obtenerTClienteTClientesABB(TClientesABB clientesABB, int idCliente){
    if (idTCliente(clientesABB->cliente) == idCliente){
        return clientesABB->cliente;
    } else if (existeTClienteTClientesABB(clientesABB->der, idCliente)){
        return obtenerTClienteTClientesABB(clientesABB->der, idCliente);
    } else if (existeTClienteTClientesABB(clientesABB->izq, idCliente)){
        return obtenerTClienteTClientesABB(clientesABB->izq, idCliente);
    } else return NULL;
}

nat alturaTClientesABB(TClientesABB clientesABB){
    if (clientesABB == NULL){
        return 0;
    } else {
    int alturaIzq = alturaTClientesABB(clientesABB->izq);
    int alturaDer = alturaTClientesABB(clientesABB->der);
    if (alturaIzq < alturaDer){
        return 1 + alturaDer;
    } else {
        return 1 + alturaIzq;
        }
    }
}

TCliente maxIdTClienteTClientesABB(TClientesABB clientesABB){    
    while (clientesABB->der != NULL){
        clientesABB = clientesABB->der;
    }
    return clientesABB->cliente;
}

TClientesABB maxClientesABB(TClientesABB clientesABB){
    if (clientesABB==NULL) return NULL;
    else {
        while(clientesABB->der != NULL){
            clientesABB = clientesABB->der;
        }
        return clientesABB;
    }
}

void removerTClienteTClientesABB(TClientesABB &clientesABB, int idCliente){
    if (clientesABB != NULL) {

        if (clientesABB->izq != NULL && idTCliente(clientesABB->cliente) > idCliente){
                removerTClienteTClientesABB(clientesABB->izq, idCliente);

        } else if (clientesABB->der != NULL && idTCliente(clientesABB->cliente) < idCliente){
                removerTClienteTClientesABB(clientesABB->der, idCliente);

        } else if (clientesABB->izq == NULL && clientesABB->der == NULL){
            liberarNodo(clientesABB);

        } else if (clientesABB->izq == NULL){
                TClientesABB aux = clientesABB;
                clientesABB = clientesABB->der;
                liberarNodo(aux);
        } else if (clientesABB->der == NULL){
                TClientesABB auxi = clientesABB;
                clientesABB = clientesABB->izq;
                liberarNodo(auxi);
        } else {
            TClientesABB maxi = maxClientesABB(clientesABB->izq);
            liberarTCliente(clientesABB->cliente);
            clientesABB->cliente = maxi->cliente;
            maxi->cliente = NULL;
            removerTClienteTClientesABB(clientesABB->izq, idTCliente(clientesABB->cliente));
            }
        }
    }

int cantidadClientesTClientesABB(TClientesABB clientesABB){
    if (clientesABB == NULL){
        return 0;
    } else return cantidadClientesTClientesABB(clientesABB->der) + cantidadClientesTClientesABB(clientesABB->izq) + 1;
}

float SumaEdades(TClientesABB clientesABB){
    if (clientesABB == NULL){
        return 0;
    } else return SumaEdades(clientesABB->der) + SumaEdades(clientesABB->izq) + edadTCliente(clientesABB->cliente);
}

float edadPromedioTClientesABB(TClientesABB clientesABB){
    if (clientesABB == NULL){
    return 0;
    } else {
        float res = SumaEdades(clientesABB)/cantidadClientesTClientesABB(clientesABB);
        return res;
    }
}

TCliente obtenerNesimoClienteTClientesABB(TClientesABB clientesABB, int n){
    if (clientesABB == NULL){
        return NULL;
    } else {
        int ClientesIzq = cantidadClientesTClientesABB(clientesABB->izq);
        if (n == ClientesIzq + 1){
            return clientesABB->cliente;
        } else if (n <= ClientesIzq){
            return obtenerNesimoClienteTClientesABB(clientesABB->izq, n);
        } else {
            return obtenerNesimoClienteTClientesABB(clientesABB->der, n - ClientesIzq - 1);
        }
    }
}
