#include "lista.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;
} nodo_t;

struct lista {
	nodo_t *nodo_inicio;
	nodo_t *nodo_final;
	size_t cantidad;
};

struct lista_iterador {
	nodo_t *corriente;
	lista_t *lista;
};

nodo_t *_nodo_crear(void *elemento)
{
	nodo_t *nodo = malloc(sizeof(nodo_t));
	if (!nodo)
		return NULL;
	nodo->elemento = elemento;
	nodo->siguiente = NULL;
	return nodo;
}

void _nodo_destruir(nodo_t *nodo)
{
	if (!nodo)
		return;
	free(nodo);
}

nodo_t *nodo_en_posicion(lista_t *lista, size_t posicion)
{
	if (!lista || posicion > lista->cantidad)
		return NULL;
	nodo_t *nodo = lista->nodo_inicio;
	for (size_t i = 0; i < posicion; i++) {
		if (!nodo)
			return NULL;
		nodo = nodo->siguiente;
	}
	return nodo;
}

lista_t *lista_crear()
{
	return calloc(1, sizeof(lista_t));
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	if (!lista)
		return NULL;
	nodo_t *nuevo_nodo = _nodo_crear(elemento);
	if (!nuevo_nodo)
		return NULL;

	if (lista_vacia(lista)) {
		lista->nodo_inicio = nuevo_nodo;
		lista->nodo_final = nuevo_nodo;
		lista->cantidad++;
		return lista;
	}
	lista->nodo_final->siguiente = nuevo_nodo;
	lista->nodo_final = nuevo_nodo;
	lista->cantidad++;
	return lista;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{
	if (!lista)
		return NULL;
	if (lista_vacia(lista) || posicion >= lista_tamanio(lista))
		return lista_insertar(lista, elemento);

	nodo_t *nodo_agregar = _nodo_crear(elemento);
	if (!nodo_agregar)
		return NULL;

	if (posicion == 0) {
		nodo_agregar->siguiente = lista->nodo_inicio;
		lista->nodo_inicio = nodo_agregar;
		lista->cantidad++;
		return lista;
	}

	nodo_t *nodo_anterior = nodo_en_posicion(lista, posicion - 1);
	if (!nodo_agregar)
		return NULL;

	nodo_agregar->siguiente = nodo_anterior->siguiente;
	nodo_anterior->siguiente = nodo_agregar;
	lista->cantidad++;

	return lista;
}

void *lista_quitar(lista_t *lista)
{
	if (!lista)
		return NULL;
	void *elemento = NULL;
	nodo_t *nodo_borrar = NULL, *nodo_aux = NULL;
	if (lista_tamanio(lista) == 1) {
		elemento = lista->nodo_inicio->elemento;
		_nodo_destruir(lista->nodo_inicio);
		lista->nodo_inicio = NULL;
		lista->nodo_final = NULL;
		lista->cantidad = 0;

		return elemento;
	}

	nodo_aux = nodo_en_posicion(lista, lista_tamanio(lista) - 2);
	if (!nodo_aux)
		return NULL;

	elemento = nodo_aux->siguiente->elemento;
	nodo_borrar = nodo_aux->siguiente;
	_nodo_destruir(nodo_borrar);

	nodo_aux->siguiente = NULL;
	lista->nodo_final = nodo_aux;
	lista->cantidad--;

	return elemento;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{
	if (!lista || lista_vacia(lista))
		return NULL;

	void *elemento = NULL;
	nodo_t *nodo_aux = NULL, *nodo_buscar = NULL;
	if (lista_tamanio(lista) == 1 || posicion >= lista_tamanio(lista))
		return lista_quitar(lista);

	if (posicion == 0) {
		elemento = lista->nodo_inicio->elemento;
		nodo_aux = lista->nodo_inicio;
		lista->nodo_inicio = lista->nodo_inicio->siguiente;
		_nodo_destruir(nodo_aux);
		lista->cantidad--;

		return elemento;
	}

	nodo_buscar = nodo_en_posicion(lista, posicion - 1);
	if (!nodo_buscar)
		return NULL;

	elemento = nodo_buscar->siguiente->elemento;
	nodo_aux = nodo_buscar->siguiente;
	nodo_buscar->siguiente = nodo_buscar->siguiente->siguiente;
	_nodo_destruir(nodo_aux);
	lista->cantidad--;

	return elemento;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{
	if (!lista || lista_vacia(lista) || posicion >= lista_tamanio(lista))
		return NULL;
	if (posicion == 0 || lista_tamanio(lista) == 1)
		return lista_primero(lista);
	if (posicion == lista_tamanio(lista) - 1)
		return lista_ultimo(lista);

	nodo_t *aux = nodo_en_posicion(lista, posicion);
	return aux->elemento;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{
	if (!lista || lista_vacia(lista))
		return NULL;
	nodo_t *aux = lista->nodo_inicio;

	while (aux) {
		if (comparador) {
			if (!comparador(aux->elemento, contexto))
				return aux->elemento;
		}
		aux = aux->siguiente;
	}

	return NULL;
}

void *lista_primero(lista_t *lista)
{
	return (!lista || lista_vacia(lista)) ? NULL :
						lista->nodo_inicio->elemento;
}

void *lista_ultimo(lista_t *lista)
{
	return (!lista || lista_vacia(lista)) ? NULL :
						lista->nodo_final->elemento;
}

bool lista_vacia(lista_t *lista)
{
	return (!lista || lista->cantidad == 0) ? true : false;
}

size_t lista_tamanio(lista_t *lista)
{
	return (!lista || lista_vacia(lista)) ? 0 : lista->cantidad;
}

void lista_destruir(lista_t *lista)
{
	lista_destruir_todo(lista, NULL);
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
	if (!lista)
		return;
	while (lista->nodo_inicio) {
		if (funcion)
			funcion(lista_primero(lista));
		lista_quitar_de_posicion(lista, 0);
	}
	free(lista);
	lista = NULL;
}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{
	if (!lista)
		return NULL;
	lista_iterador_t *iterador = malloc(sizeof(lista_iterador_t));
	if (!iterador)
		return NULL;
	iterador->lista = lista;
	iterador->corriente = lista->nodo_inicio;

	if (lista_vacia(lista))
		return iterador;

	return iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{
	if (!iterador || lista_vacia(iterador->lista))
		return false;
	return iterador->corriente;
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	if (!iterador || lista_vacia(iterador->lista) || !iterador->corriente)
		return false;
	iterador->corriente = iterador->corriente->siguiente;
	return iterador->corriente;
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	if (!iterador || lista_vacia(iterador->lista) || !iterador->corriente)
		return NULL;
	return iterador->corriente->elemento;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
	if (!iterador)
		return;
	free(iterador);
	iterador = NULL;
}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	if (!lista || !funcion || lista_vacia(lista))
		return 0;
	size_t elementos = 0;
	nodo_t *nodo = lista->nodo_inicio;

	while (nodo) {
		if (funcion(nodo->elemento, contexto)) {
			elementos++;
			nodo = nodo->siguiente;
		} else {
			elementos++;
			break;
		}
	}
	return elementos;
}
