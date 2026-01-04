#include "../include/grupo.h"

struct rep_grupo {
    /************ Parte 5.1 ************/
    /*Escriba el código a continuación */
    TPersona arreglo[MAX_PERSONAS];
    int tope;
    /****** Fin de parte Parte 5.1 *****/
};


TGrupo crearTGrupo(){
    TGrupo grupo = NULL;
    /************ Parte 5.2 ************/
    /*Escriba el código a continuación */
    grupo = new rep_grupo;
    grupo->tope=0;
    /****** Fin de parte Parte 5.2 *****/
    return grupo;
}

// Función para agregar una persona a un grupo
// Recibe un elemento de tipo TGrupo y un elemento de tipo TPersona y lo agrega al grupo en orden por fecha de nacimiento (de menor a mayor)
// Si dos personas tienen la misma fecha de nacimiento, deben ordenarse por orden de ingreso al grupo, de más nuevo a más antiguo
// Si la cantidad de personas en el grupo es igual a MAX_PERSONAS, la función no tiene efecto
void agregarAGrupo(TGrupo& grupo, TPersona persona){
    /************ Parte 5.2 ************/
    /*Escriba el código a continuación */
    TPersona Backup;
    if(grupo->tope < MAX_PERSONAS){
        grupo->tope++;
        for(int i = (grupo->tope-1); i > 0; i--){
            grupo->arreglo[i] = grupo->arreglo[i-1];
        }
        grupo->arreglo[0] = persona;
        for(int i = 1; i < grupo->tope ; i++){
            int j = esMasJoven(grupo->arreglo[i-1], grupo->arreglo[i]);
            if (j == true) {
                Backup = grupo->arreglo[i-1];
                grupo->arreglo[i-1] = grupo->arreglo[i];
                grupo->arreglo[i] = Backup;
            }
        }
    }
    /****** Fin de parte Parte 5.2 *****/
}

// Función para imprimir todas las personas de un grupo
// Recibe un elemento de tipo TGrupo e imprime sus personas en orden cronológico
// El formato en el que se debe imprimir el grupo es utilizando de forma secuencial la función imprimirTPersona
// Si el grupo está vacío no imprime nada
void imprimirTGrupo(TGrupo grupo){
    /************ Parte 5.2 ************/
    /*Escriba el código a continuación */
    for(int i = 0; i < grupo->tope; i++){
        imprimirTPersona(grupo->arreglo[i]);
    }
    /****** Fin de parte Parte 5.2 *****/
}

// Función para liberar un grupo
// Recibe una referencia a un elemento de tipo TGrupo y libera su memoria
// Libera además la memoria de cada una de las personas en el grupo
void liberarTGrupo(TGrupo& grupo){
   /************ Parte 5.2 ************/
    /*Escriba el código a continuación */
    for(int i = 0; i < grupo->tope; i++){
    liberarTPersona(grupo->arreglo[i]);
    }
    delete grupo;
    grupo = NULL;
    /****** Fin de parte Parte 5.2 *****/
}

// Función para verificar si un elemento de tipo TPersona existe en un grupo
// Recibe un grupo y la cédula de la persona y regresa un booleano indicando su existencia
bool estaEnGrupo(TGrupo grupo, int cedula){
    bool esta = false;
	/************ Parte 5.3 ************/
    /*Escriba el código a continuación */
    int i=0;
    while (esta != true && (i < grupo->tope)){
        if (cedulaTPersona(grupo->arreglo[i]) == cedula) {
            esta = true;
        }
        i++;
    }
    /****** Fin de parte Parte 5.3 *****/
	return esta;
}

// Esta función remueve la persona con ci "cedula" del grupo "grupo"
void removerDeGrupo(TGrupo &grupo, int cedula){
    /************ Parte 5.4 ************/
    /*Escriba el código a continuación */
    int pos = -1;
    int i;
    bool k = false;
    for(i= 0; (i < grupo->tope) && (k != true); i++){
        if (cedulaTPersona(grupo->arreglo[i]) == cedula){
            k = true;
            pos = i;
            liberarTPersona(grupo->arreglo[i]);
        }
    }
    for(i = pos; i < (grupo->tope-1); i++){
        grupo->arreglo[i] = grupo->arreglo[i+1];
    }
    grupo->arreglo[grupo->tope] = NULL;
    grupo->tope--;
    /****** Fin de parte Parte 5.4 *****/   
}

// Función para verificar si hay, al menos, una persona en el grupo que tenga la fecha de nacimiento "fecha"
// Debe implementarse utilizando búsqueda binaria
bool hayPersonasFecha(TGrupo grupo, TFecha fecha){
    bool hay = false;
    /************ Parte 5.5 ************/
    /*Escriba el código a continuación */
    int primero = 0;
    int ultimo = (grupo->tope - 1);
    while (primero <= ultimo && hay == false){
        int medio = ((primero + ultimo)/2);
        if (compararTFechas(fechaNacimientoTPersona(grupo->arreglo[medio]), fecha) == -1){
            primero = (medio + 1);
        } else if (compararTFechas(fechaNacimientoTPersona(grupo->arreglo[medio]), fecha) == 1){
            ultimo = (medio - 1); 
        } else if (compararTFechas(fechaNacimientoTPersona(grupo->arreglo[medio]), fecha) == 0){
            hay = true;
        }
    }
    /****** Fin de parte Parte 5.5 *****/ 
    return hay;
}

// Imprime en pantalla las personas del grupo que tengan la fecha de nacimiento "fecha" 
void imprimirPersonasFecha(TGrupo grupo, TFecha fecha){
    /************ Parte 5.5 ************/
    /*Escriba el código a continuación */
    if ((hayPersonasFecha(grupo, fecha)) == true){
        for(int i=0; i<grupo->tope; i++){
            if(compararTFechas(fechaNacimientoTPersona(grupo->arreglo[i]), fecha) == 0){
                imprimirTPersona(grupo->arreglo[i]);
            }
        }
    }
    /****** Fin de parte Parte 5.5 *****/ 
}
