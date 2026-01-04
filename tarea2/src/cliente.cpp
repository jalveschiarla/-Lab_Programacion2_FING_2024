#include "../include/cliente.h"

struct rep_cliente {
    int id;
    int edad;
    char nombre[MAX_NOMBRE];
    char apellido[MAX_APELLIDO];
};


TCliente crearTCliente(int id, const char nombre[MAX_NOMBRE], const char apellido[MAX_APELLIDO], int edad){
    TCliente nuevoCliente = new rep_cliente;
    nuevoCliente -> id = id;
    strcpy(nuevoCliente -> nombre, nombre);
    strcpy(nuevoCliente -> apellido, apellido);
    nuevoCliente -> edad = edad;
    return nuevoCliente;
}

void imprimirTCliente(TCliente cliente){
    printf("Cliente %s %s\n", cliente->nombre, cliente->apellido);
    printf("Id: %d\n", cliente->id);
    printf("Edad: %d\n", cliente->edad);
}

void liberarTCliente(TCliente &cliente){
    if (cliente != NULL){
        delete cliente;
        cliente = NULL;
    }
}

void nombreTCliente(TCliente cliente, char nombre[MAX_NOMBRE]){
    for(int i=0; i<MAX_NOMBRE; i++){
        nombre[i]=cliente->nombre[i];
    }
}

void apellidoTCliente(TCliente cliente, char apellido[MAX_APELLIDO]){
    for(int i=0; i<MAX_APELLIDO; i++){
        apellido[i]=cliente->apellido[i];
    }
}

int idTCliente(TCliente cliente){
    return cliente->id;
}

int edadTCliente(TCliente cliente){
    return cliente->edad;
}

TCliente copiarTCliente(TCliente cliente){
    TCliente copiaCliente = NULL;
    copiaCliente = new rep_cliente;  
    copiaCliente -> id = cliente->id;
    strcpy(copiaCliente->nombre, cliente->nombre);
    strcpy(copiaCliente -> apellido, cliente->apellido);
    copiaCliente->edad = cliente->edad;
    return copiaCliente;
}
