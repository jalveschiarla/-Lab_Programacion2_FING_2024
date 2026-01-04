#include "../include/clientesSucursalesLDE.h"

struct auxClientesSucursales {
	TClientesABB clientesABB;
	int idSucursal;
	auxClientesSucursales *sig;
	auxClientesSucursales *ant;
};

typedef struct auxClientesSucursales *TClientesSucursalesLDEAux;

struct rep_clientesSucursalesLDE {
	TClientesSucursalesLDEAux ini;
	TClientesSucursalesLDEAux fin;
};

TClientesSucursalesLDE crearTClientesSucursalesLDEVacia(){
	TClientesSucursalesLDE nuevo = new rep_clientesSucursalesLDE;
	nuevo->ini = NULL;
	nuevo->fin = NULL;
	return nuevo;
}

void insertarClientesABBTClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE, TClientesABB clientesABB, int idSucursal){
	auxClientesSucursales* nuevaSucursal = new auxClientesSucursales;
	nuevaSucursal->idSucursal = idSucursal;
	nuevaSucursal->clientesABB = clientesABB;
	nuevaSucursal->ant = NULL;
	nuevaSucursal->sig = NULL;

	if (clientesSucursalesLDE->ini == NULL){
		clientesSucursalesLDE->ini = nuevaSucursal;
		clientesSucursalesLDE->fin = nuevaSucursal;
		return;
	} else {
		auxClientesSucursales* actual = clientesSucursalesLDE->ini;
		auxClientesSucursales* anterior = NULL;
		while (actual != NULL && edadPromedioTClientesABB(actual->clientesABB) <= edadPromedioTClientesABB(nuevaSucursal->clientesABB)){
			anterior = actual;
			actual = actual->sig;
		}
		if (anterior == NULL){
			nuevaSucursal->sig = clientesSucursalesLDE->ini;
			clientesSucursalesLDE->ini->ant = nuevaSucursal;
			clientesSucursalesLDE->ini = nuevaSucursal;
		} else {
			nuevaSucursal->sig = anterior->sig;
			if (anterior->sig != NULL){
				anterior->sig->ant = nuevaSucursal;
			} else {
				clientesSucursalesLDE->fin = nuevaSucursal;
			}
			anterior->sig = nuevaSucursal;
			nuevaSucursal->ant = anterior;
		}
	}
}

void liberarNodoIndividual(auxClientesSucursales* &clientesSucursalesLDE){
	if(clientesSucursalesLDE != NULL){
		liberarTClientesABB(clientesSucursalesLDE->clientesABB);
		delete clientesSucursalesLDE;
		clientesSucursalesLDE = NULL;
	}
}

void liberarTClientesSucursalesLDE(TClientesSucursalesLDE &clientesSucursalesLDE){
	if (clientesSucursalesLDE->ini == NULL){
		delete clientesSucursalesLDE;
		clientesSucursalesLDE = NULL;
		return;
	} else {
		if (clientesSucursalesLDE->ini != NULL){
			auxClientesSucursales* aux = clientesSucursalesLDE->ini;
			clientesSucursalesLDE->ini = clientesSucursalesLDE->ini->sig;
			liberarNodoIndividual(aux);	
		}
	}
	liberarTClientesSucursalesLDE(clientesSucursalesLDE);
}

void imprimirTClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE){
	TClientesSucursalesLDEAux actual = clientesSucursalesLDE->ini;
	printf("clientesSucursalesLDE de grupos:\n");
	while (actual != NULL){
		float edadPromedio = edadPromedioTClientesABB(actual->clientesABB);
		printf("Grupo con edad promedio %.2f:\n", edadPromedio);
		imprimirTClientesABB(actual->clientesABB);
		actual = actual->sig;
	}
}

void imprimirInvertidoTClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE){
	TClientesSucursalesLDEAux actual = clientesSucursalesLDE->fin;
	printf("clientesSucursalesLDE de grupos:\n");
	while (actual != NULL){
		float edadPromedio = edadPromedioTClientesABB(actual->clientesABB);
		printf("Grupo con edad promedio %.2f:\n", edadPromedio);
		imprimirTClientesABB(actual->clientesABB);
		actual = actual->ant;
	}
}

nat cantidadTClientesABBClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE){
	if (clientesSucursalesLDE->ini == NULL){
		return 0;
	} else {
		if (clientesSucursalesLDE->ini == clientesSucursalesLDE->fin){
			return 1;
		} else {
			TClientesSucursalesLDEAux actual = clientesSucursalesLDE->ini;
			int cont = 0;
			while (actual != NULL){
				cont++;
				actual = actual->sig;
			}
			return cont;
		}
	}
}

TClientesABB obtenerPrimeroClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE){
	return clientesSucursalesLDE->ini->clientesABB;
}

TClientesABB obtenerNesimoClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE, int n){
	if (clientesSucursalesLDE->ini == NULL){
		return NULL;
	} else {
		TClientesSucursalesLDEAux actual = clientesSucursalesLDE->ini;
		int cont = 1;
		while (actual != NULL && cont != n){
			cont++;
			actual = actual->sig;
		}
		if (actual != NULL && cont == n){
			return actual->clientesABB;
		} else return NULL;
	}
}

TClientesABB removerUltimoClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE){
	TClientesSucursalesLDEAux ultimo = clientesSucursalesLDE->fin;
	if (clientesSucursalesLDE->fin == clientesSucursalesLDE->ini){
		clientesSucursalesLDE->fin = NULL;
		clientesSucursalesLDE->ini = NULL;
	} else {
		clientesSucursalesLDE->fin = ultimo->ant;
		if (clientesSucursalesLDE->fin != NULL){
			clientesSucursalesLDE->fin->sig = NULL;
		}
	}
	TClientesABB removido = ultimo->clientesABB;
	delete ultimo;
	return removido;
}

TClientesABB removerNesimoClientesSucursalesLDE(TClientesSucursalesLDE clientesSucursalesLDE, int n){
	TClientesSucursalesLDEAux actual = clientesSucursalesLDE->ini;
	int cont = 1;
	while (actual != NULL && cont != n){
		cont++;
		actual = actual->sig;
	}
	if (actual == NULL || cont != n){
		return NULL;
	} else {
		if (actual == clientesSucursalesLDE->ini){
			TClientesSucursalesLDEAux aux = clientesSucursalesLDE->ini->sig;
			actual->sig = NULL;
			if (aux != NULL){
				aux->ant = NULL;
			}
			clientesSucursalesLDE->ini = aux;
			TClientesABB removido = actual->clientesABB;
			delete actual;
			return removido;
		} else if (actual == clientesSucursalesLDE->fin){
			TClientesSucursalesLDEAux aux = clientesSucursalesLDE->fin->ant;
			actual->ant = NULL;
			if (aux != NULL){
				aux->sig = NULL;
			}
			clientesSucursalesLDE->fin = aux;
			TClientesABB removido = actual->clientesABB;
			delete actual;
			return removido;			
		} else {
			TClientesSucursalesLDEAux aux1 = actual->ant;
			TClientesSucursalesLDEAux aux2 = actual->sig;
			actual->ant = NULL;
			aux1->sig = aux2;
			actual->sig = NULL;
			aux2->ant = aux1;
			TClientesABB removido = actual->clientesABB;
			delete actual;
			return removido;	
		}
	}
}

TCliente clienteMasRepetido(TClientesSucursalesLDE clientesSucursalesLDE){
	int MaxSuc = cantidadTClientesABBClientesSucursalesLDE(clientesSucursalesLDE);
	int cont = 0;
	int contDef = 0;
	TCliente Adevolver = NULL;
	for(int j=1; j<=MaxSuc; j++){
		TClientesABB SucursalActual = obtenerNesimoClientesSucursalesLDE(clientesSucursalesLDE, j);
		int MaxABB = cantidadClientesTClientesABB(SucursalActual);
		TClientesABB SucursalSiguiente = obtenerNesimoClientesSucursalesLDE(clientesSucursalesLDE, 1);
		int p=1;
		for(int i=1; i<=MaxABB; i++){
			TCliente actual = obtenerNesimoClienteTClientesABB(SucursalActual, i);
			while (SucursalSiguiente != NULL){
				if (existeTClienteTClientesABB(SucursalSiguiente, idTCliente(actual))){
					cont++;
				}
				p++;
				SucursalSiguiente = obtenerNesimoClientesSucursalesLDE(clientesSucursalesLDE, p);
			}
			if (cont > contDef){
				contDef = cont;
				Adevolver = actual;
			}
			cont = 0;
			actual = NULL;
		}
	}
	return Adevolver;
}
