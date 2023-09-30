#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"
#include "pruebas_alumno.h"
#include "pa2m.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	pa2m_nuevo_grupo("Pruebas de creacion de lista");
	creo_una_lista_y_es_valida();
	prueba_funcion_lista_vacia_con_una_lista_nula_y_no_explota();
	prueba_que_una_lista_recien_creada_esta_vacia_y_tiene_cero_elementos();

	pa2m_nuevo_grupo("Insertar en lista");
	no_se_puede_insertar_en_un_ninguna_posicion_de_una_lista_inexistente();
	prueba_insercion_de_una_lista_recien_creada_y_verifica_que_el_tamanio_crece();
	se_inserta_un_elemento_en_una_lista_vacia_y_verifica_que_ese_elemento_sea_el_que_se_inserto();
	se_puede_insertar_NULL_como_elemento_en_una_lista_puedo_devolver_ese_elemento_nulo();
	se_insertan_elementos_y_se_verifica_que_el_primer_elemento_insertado_y_el_ultimo_insertado_esten_en_correcta_posicion();
	se_insertan_varios_elementos_antes_del_ultimo_elemento_en_una_lista_no_vacia_y_se_verifica_que_el_ultimo_elemento_sigue_siendo_el_ultimo();
	se_insertan_varios_elementos_en_ultima_posicion_de_una_lista_no_vacia_y_se_verifica_que_el_ultimo_elemento_sigue_siendo_el_ultimo();
	se_inserta_un_elemento_en_una_posicion_mayor_al_tamanio_de_una_lista_no_vacia_y_se_verifica_que_lo_inserta_en_ultima_posicion();
	se_insertan_varios_elementos_al_principio_de_una_lista_y_el_ultimo_insertado_en_primera_posicion_queda_en_la_primera_posicion();

	pa2m_nuevo_grupo("Insercion variada");
	se_insertan_varios_elementos_en_distintas_posiciones_de_la_lista_y_al_recorrerla_cada_elemento_insertado_quedo_en_posicion_correcta();

	pa2m_nuevo_grupo("Quitar en lista");
	remover_elemento_de_lista_inexistente();
	remover_elemento_de_lista_vacia();
	remover_un_elemento_de_lista_de_un_elemento_deja_la_lista_vacia_y_me_devuelve_el_elemento();
	remover_el_ultimo_elemento_de_una_lista_de_tres_elementos_y_el_segundo_elemento_ahora_es_el_ultimo();
	remover_el_primer_elemento_de_una_lista_de_tres_elementos_y_el_segundo_elemento_ahora_es_el_primero();
	remover_una_posicion_mas_grande_que_el_tamanio_de_la_lista_remueve_la_ultima_posicion();
	pa2m_nuevo_grupo("Busqueda de elementos con lista");
	no_puedo_buscar_elementos_en_una_lista_que_no_existe_o_que_esta_vacia();
	no_puedo_buscar_elementos_que_estan_fuera_del_rango_de_mi_lista();
	verificar_que_en_una_lista_de_un_elemento_el_primero_y_el_ultimo_son_el_mismo();

	pa2m_nuevo_grupo("Busqueda de elementos con funcion comparadora");
	no_puedo_buscar_elementos_en_una_lista_inexistente();
	buscar_un_elemento_con_una_funcion_nula_me_devuelve_null();
	buscar_en_una_lista_vacia_devuelve_null();

	pa2m_nuevo_grupo("Iterador interno");
	iterar_todos_los_elementos_de_lista_con_it_interno_me_devuelve_todos_los_elementos_iterados();
	al_iterar_la_lista_con_el_it_interno_devuelve_todos_los_elementos_iterados_aunque_no_cumplan_con_la_condicion_de_la_funcion();

	pa2m_nuevo_grupo("Iterador externo");
	no_puedo_crear_un_iterador_de_una_lista_inexistente();
	puedo_crear_un_iterador_con_una_lista_vacia();
	iterar_una_lista_vacia_me_devuelve_cero();
	itero_el_siguiente_elemento_a_la_ultima_posicion_de_la_lista_y_devuelve_null();
	lista_con_n_elementos_recorre_los_n_elementos();

	pa2m_nuevo_grupo("Pruebas pila");
	creo_una_pila_y_verifico_que_esta_vacia_y_que_no_tiene_tope();
	apilo_varios_elementos_y_el_tamanio_de_la_pila_coincide_con_la_cantidad_de_elementos_que_inserte();
	desapilo_y_el_tamanio_de_la_pila_decrece_hasta_que_no_hay_mas_elementos_y_el_tope_es_null();
	apilar_varias_veces_y_verificar_tope_cada_vez_y_desapilar_varias_veces_y_verificar_tope_cada_vez();

	pa2m_nuevo_grupo("Pruebas cola");
	creo_una_cola_y_verifico_que_esta_vacia_y_que_tiene_tamanio_cero();
	encolo_Y_desencolo_elementos_y_verifico_que_el_tamanio_de_la_cola_crece_y_decrece();
	encolo_y_desencolo_varios_elementos_y_verifico_que_el_frente_fue_el_ultimo_elemento_encolado();

	return pa2m_mostrar_reporte();
}

int elemento_es_igual_a(void *_a, void *_b)
{
	char *a = _a;
	char *b = _b;

	if (a && b && *a == *b)
		return 0;

	return -1;
}

bool numero_es_negativo(void *numero, void *contador)
{
	int *n = numero;

	if (!numero && !contador && *n < 0)
		(*(int *)contador)++;

	return true;
}

bool contar_elementos(void *elemento, void *contador)
{
	if (elemento && contador)
		(*(int *)contador)++;

	return true;
}

void creo_una_lista_y_es_valida()
{
	lista_t *lista = NULL;

	pa2m_afirmar((lista = lista_crear()) != NULL,
		     "La lista creada es valida");

	lista_destruir(lista);
}

void prueba_funcion_lista_vacia_con_una_lista_nula_y_no_explota()
{
	pa2m_afirmar(lista_vacia(NULL) == true,
		     "Una lista inexistente no tiene elementos");
}

void prueba_que_una_lista_recien_creada_esta_vacia_y_tiene_cero_elementos()
{
	lista_t *lista = lista_crear();

	pa2m_afirmar(lista_vacia(lista) == true,
		     "Una lista recien creada esta vacia");
	pa2m_afirmar(lista_tamanio(lista) == 0,
		     "Una lista recien creada tiene 0 elementos");

	lista_destruir(lista);
}

void no_se_puede_insertar_en_un_ninguna_posicion_de_una_lista_inexistente()
{
	char c = 'c', x = 'x';
	pa2m_afirmar(lista_insertar_en_posicion(NULL, &c, 0) == NULL &&
			     lista_insertar_en_posicion(NULL, &x, 4) == NULL,
		     "No puedo insertar elementos en una lista inexistente");
}

void prueba_insercion_de_una_lista_recien_creada_y_verifica_que_el_tamanio_crece()
{
	char elemento = 'x';
	lista_t *lista = lista_crear();

	pa2m_afirmar(lista_tamanio(lista) == 0,
		     "El tamanio de la lista recien creada es cero");

	lista_insertar(lista, &elemento);

	pa2m_afirmar(lista_tamanio(lista) == 1,
		     "Inserto un elemento y el tamanio es uno");

	lista_destruir(lista);
}

void se_inserta_un_elemento_en_una_lista_vacia_y_verifica_que_ese_elemento_sea_el_que_se_inserto()
{
	char *elemento = "Era por abajo Palacio";
	lista_t *lista = lista_crear();
	lista_insertar(lista, elemento);

	pa2m_afirmar(
		lista_primero(lista) == elemento,
		"El elemento que se almacenó en la lista vacía era el que insertó");

	lista_destruir(lista);
}

void se_puede_insertar_NULL_como_elemento_en_una_lista_puedo_devolver_ese_elemento_nulo()
{
	lista_t *lista = lista_crear();

	pa2m_afirmar(lista_insertar(lista, NULL) != NULL,
		     "puedo insertar NULL como elemento");
	pa2m_afirmar(lista_primero(lista) == NULL,
		     "Puedo devolver el elemento NULL anteriormente guardado");

	lista_destruir(lista);
}

void se_insertan_elementos_y_se_verifica_que_el_primer_elemento_insertado_y_el_ultimo_insertado_esten_en_correcta_posicion()
{
	lista_t *lista = lista_crear();
	char *primero = "Fenomenoide";
	char *ultimo = "pepito";
	lista_insertar(lista, primero);
	lista_insertar(lista, "HOLA");
	lista_insertar(lista, "prueba");
	lista_insertar(lista, "MUNDO");
	lista_insertar(lista, "prueba");
	lista_insertar(lista, ultimo);
	pa2m_afirmar(
		lista_primero(lista) == primero &&
			lista_ultimo(lista) == ultimo,
		"Inserto un elemento en una lista y vacia y luego inserto elementos al final y el primero y el último están correctamente ubicados");
	lista_destruir(lista);
}

void se_insertan_varios_elementos_antes_del_ultimo_elemento_en_una_lista_no_vacia_y_se_verifica_que_el_ultimo_elemento_sigue_siendo_el_ultimo()
{
	lista_t *lista = lista_crear();
	char *ultimo = "pepito";
	lista_insertar(lista, ultimo);
	lista_insertar_en_posicion(lista, "Arranca?", 0);
	lista_insertar_en_posicion(lista, "prueba", lista_tamanio(lista) - 2);
	lista_insertar_en_posicion(lista, "o no arranca?",
				   lista_tamanio(lista) - 2);
	lista_insertar_en_posicion(lista, "prueba", lista_tamanio(lista) - 2);

	pa2m_afirmar(
		lista_ultimo(lista) == ultimo,
		"Inserto varios elementos antes del último elemento en una lista no vacía y el último elemento sigue en la ùltima posición");

	lista_destruir(lista);
}

void se_insertan_varios_elementos_en_ultima_posicion_de_una_lista_no_vacia_y_se_verifica_que_el_ultimo_elemento_sigue_siendo_el_ultimo()
{
	lista_t *lista = lista_crear();
	char *primero = "Fenomenoide";
	char *ultimo = "pepito";
	lista_insertar(lista, primero);
	lista_insertar(lista, ultimo);
	lista_insertar_en_posicion(lista, "HOLA", lista_tamanio(lista) - 1);
	lista_insertar_en_posicion(lista, "prueba", lista_tamanio(lista) - 1);
	lista_insertar_en_posicion(lista, "MUNDO", lista_tamanio(lista) - 1);
	lista_insertar_en_posicion(lista, "prueba", lista_tamanio(lista) - 1);

	pa2m_afirmar(
		lista_ultimo(lista) == ultimo,
		"Inserto varios elementos justo en la ultima posición de una lista de dos elementos y el último elemento antes de todas las inserciones sigue en la última posición");

	lista_destruir(lista);
}

void se_inserta_un_elemento_en_una_posicion_mayor_al_tamanio_de_una_lista_no_vacia_y_se_verifica_que_lo_inserta_en_ultima_posicion()
{
	lista_t *lista = lista_crear();
	char *variable5000 = "1.21 GIGAWATTS?!";
	lista_insertar(lista, "Arranca siempre con bujias Herschel");
	lista_insertar_en_posicion(lista, variable5000, 5000);

	pa2m_afirmar(
		lista_ultimo(lista) == variable5000,
		"Inserto un elemento en una posicion mayor al tamaño de una lista no vacía y lo coloca en la última posición");

	lista_destruir(lista);
}

void se_insertan_varios_elementos_al_principio_de_una_lista_y_el_ultimo_insertado_en_primera_posicion_queda_en_la_primera_posicion()
{
	lista_t *lista = lista_crear();
	char *ultimo = "pepito";
	lista_insertar_en_posicion(lista, "HOLA", 0);
	lista_insertar_en_posicion(lista, "prueba", 0);
	lista_insertar_en_posicion(lista, "MUNDO", 0);
	lista_insertar_en_posicion(lista, ultimo, 0);

	pa2m_afirmar(
		lista_primero(lista) == ultimo,
		"Inserto varios elementos en la primera posición de una lista y en la primera posición se encuentra en último elemento ingresado");

	lista_destruir(lista);
}
void se_insertan_varios_elementos_en_distintas_posiciones_de_la_lista_y_al_recorrerla_cada_elemento_insertado_quedo_en_posicion_correcta()
{
	lista_t *lista = lista_crear();
	char a = 'a', b = 'b', c = 'c', d = 'd';

	printf("%s\n", "Inserto un elemento en una lista vacia");
	lista_insertar(lista, &a);
	printf("%s\n", "Inserto un elemento al principio de la lista");
	lista_insertar_en_posicion(lista, &b, 0);
	printf("%s\n",
	       "Inserto un elemento en una posicion mayor al tamanio de la lista");
	lista_insertar_en_posicion(lista, &d, 100);
	printf("%s\n", "Inserto un elemento en la posicion 2");
	lista_insertar_en_posicion(lista, &c, 2);

	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == &b,
		     "El primer elemento coincide en la pos 0");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 1) == &a,
		     "El segundo elemento coincide en la pos 1");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 2) == &c,
		     "El tercer elemento coincide en la pos 2");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 3) == &d,
		     "El cuarto elemento coincide en la pos 3");

	lista_destruir(lista);
}

void remover_elemento_de_lista_inexistente()
{
	pa2m_afirmar(lista_quitar_de_posicion(NULL, 0) == NULL &&
			     lista_quitar_de_posicion(NULL, 500) == NULL,
		     "No puedo quitar elementos de una lista inexistente");
}

void remover_elemento_de_lista_vacia()
{
	lista_t *lista = lista_crear();

	pa2m_afirmar(lista_quitar(lista) == NULL,
		     "No puedo quitar elementos de una lista vacía");

	lista_destruir(lista);
}

void remover_un_elemento_de_lista_de_un_elemento_deja_la_lista_vacia_y_me_devuelve_el_elemento()
{
	lista_t *lista = lista_crear();
	char *elemento = "HOLA";
	lista_insertar(lista, elemento);

	pa2m_afirmar(
		lista_quitar(lista) == elemento && lista_vacia(lista),
		"Remuevo el único elemento de una lista y ademas de devolverlo, deja la lista vacía");

	lista_destruir(lista);
}

void remover_el_ultimo_elemento_de_una_lista_de_tres_elementos_y_el_segundo_elemento_ahora_es_el_ultimo()
{
	lista_t *lista = lista_crear();
	char *elemento1 = "HOLA";
	char *elemento2 = "CHAU";

	lista_insertar(lista, "Primero a remover");
	lista_insertar(lista, elemento1);
	lista_insertar(lista, elemento2);
	lista_quitar(lista);
	pa2m_afirmar(
		lista_ultimo(lista) == elemento1,
		"Remuevo el último elemento de una lista de tres elementos y el segundo elemento ahora es el último");

	lista_destruir(lista);
}

void remover_el_primer_elemento_de_una_lista_de_tres_elementos_y_el_segundo_elemento_ahora_es_el_primero()
{
	lista_t *lista = lista_crear();
	char *elemento1 = "HOLA";
	char *elemento2 = "CHAU";

	lista_insertar(lista, "Primero a remover");
	lista_insertar(lista, elemento1);
	lista_insertar(lista, elemento2);
	lista_quitar_de_posicion(lista, 0);
	pa2m_afirmar(
		lista_primero(lista) == elemento1,
		"Remuevo el último elemento de una lista de tres elementos y el segundo elemento ahora es el primero");

	lista_destruir(lista);
}

void remover_una_posicion_mas_grande_que_el_tamanio_de_la_lista_remueve_la_ultima_posicion()
{
	lista_t *lista = lista_crear();
	char *ultimo = "Último elemento yo te elijo";
	lista_insertar(lista, "1");
	lista_insertar(lista, "2");
	lista_insertar(lista, ultimo);
	pa2m_afirmar(
		lista_quitar_de_posicion(lista, 500) == ultimo,
		"Intento remover una posición mas grande que la lista y me remueve el último elemento");

	lista_destruir(lista);
}

void no_puedo_buscar_elementos_en_una_lista_que_no_existe_o_que_esta_vacia()
{
	lista_t *lista = lista_crear();

	pa2m_afirmar(lista_elemento_en_posicion(NULL, 0) == NULL,
		     "No puedo buscar un elemento en una lista inexistente");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == NULL,
		     "No puedo buscar elementos en una lista vacía");

	lista_destruir(lista);
}

void no_puedo_buscar_elementos_que_estan_fuera_del_rango_de_mi_lista()
{
	lista_t *lista = lista_crear();
	lista_insertar(lista, "Habemus elemento");
	pa2m_afirmar(lista_elemento_en_posicion(lista, 100) == NULL,
		     "No puedo buscar un elemento fuera del rango de mi lista");

	lista_destruir(lista);
}

void verificar_que_en_una_lista_de_un_elemento_el_primero_y_el_ultimo_son_el_mismo()
{
	lista_t *lista = lista_crear();
	int elemento = 1;
	lista_insertar(lista, &elemento);
	pa2m_afirmar(
		lista_primero(lista) == &elemento &&
			lista_ultimo(lista) == &elemento,
		"En una lista de un elemento, el primero y el último son el mismo");

	lista_destruir(lista);
}

void no_puedo_buscar_elementos_en_una_lista_inexistente()
{
	char c = 'c';

	pa2m_afirmar(lista_buscar_elemento(NULL, elemento_es_igual_a, &c) ==
			     NULL,
		     "No puedo buscar elementos en una lista que no existe");
}

void buscar_un_elemento_con_una_funcion_nula_me_devuelve_null()
{
	lista_t *lista = lista_crear();
	char c = 'c';
	pa2m_afirmar(lista_buscar_elemento(lista, NULL, &c) == NULL,
		     "Buscar con una funcion nula devuelve null");

	lista_destruir(lista);
}

void buscar_en_una_lista_vacia_devuelve_null()
{
	lista_t *lista = lista_crear();
	char c = 'c';
	pa2m_afirmar(lista_buscar_elemento(lista, elemento_es_igual_a, &c) ==
			     NULL,
		     "Buscar en un lista vacía me devuelve null");

	lista_destruir(lista);
}

void iterar_todos_los_elementos_de_lista_con_it_interno_me_devuelve_todos_los_elementos_iterados()
{
	lista_t *lista = lista_crear();
	size_t elementos_recorridos = 0, contador = 0;
	int x = 4;
	lista_insertar(lista, &x);
	lista_insertar(lista, "HOLA");

	elementos_recorridos =
		lista_con_cada_elemento(lista, contar_elementos, &contador);
	pa2m_afirmar(
		elementos_recorridos == 2,
		"Recorrer una lista de dos elementos me devuelve dos elementos iterados");

	lista_destruir(lista);
}

void al_iterar_la_lista_con_el_it_interno_devuelve_todos_los_elementos_iterados_aunque_no_cumplan_con_la_condicion_de_la_funcion()
{
	lista_t *lista = lista_crear();
	size_t elementos_recorridos = 0, contador = 0;
	int x = 4, y = -4;
	lista_insertar(lista, &x);
	lista_insertar(lista, &y);

	elementos_recorridos =
		lista_con_cada_elemento(lista, numero_es_negativo, &contador);
	pa2m_afirmar(
		elementos_recorridos == 2,
		"Recorrer una lista de dos elementos me devuelve dos elementos iterados (otra vez)");

	lista_destruir(lista);
}

void no_puedo_crear_un_iterador_de_una_lista_inexistente()
{
	lista_t *lista = NULL;
	lista_iterador_t *it = lista_iterador_crear(lista);
	pa2m_afirmar(
		it == NULL,
		"Crear un iterador con una lista inexistente me devuelve NULL");
}

void puedo_crear_un_iterador_con_una_lista_vacia()
{
	lista_t *lista = lista_crear();
	lista_iterador_t *it = lista_iterador_crear(lista);
	pa2m_afirmar(it != NULL,
		     "Puedo crear un iterador a partir de una lista vacía");

	lista_iterador_destruir(it);
	lista_destruir(lista);
}

void iterar_una_lista_vacia_me_devuelve_cero()
{
	size_t i;
	lista_t *lista = lista_crear();
	lista_iterador_t *it = lista_iterador_crear(lista);
	for (i = 0; lista_iterador_tiene_siguiente(it);
	     lista_iterador_avanzar(it))
		i++;

	pa2m_afirmar(i == 0,
		     "Iterar una lista vacía me devuelve cero elementos");

	lista_iterador_destruir(it);
	lista_destruir(lista);
}

void itero_el_siguiente_elemento_a_la_ultima_posicion_de_la_lista_y_devuelve_null()
{
	lista_t *lista = lista_crear();

	lista_insertar(lista, "HOLA");
	lista_insertar(lista, "HOLA");

	lista_iterador_t *it = lista_iterador_crear(lista);
	for (; lista_iterador_tiene_siguiente(it); lista_iterador_avanzar(it))
		;

	// pa2m_afirmar(it->corriente == NULL, "al finalizar de recorrer la lista, el iterador queda en null");

	lista_iterador_destruir(it);
	lista_destruir(lista);
}

void lista_con_n_elementos_recorre_los_n_elementos()
{
	lista_t *lista = lista_crear();
	size_t contador = 0;

	char arr[6] = { '0', '1', '2', '3', '4', '5' };
	for (int i = 0; i <= 6; i++)
		lista_insertar(lista, &arr[i]);

	lista_iterador_t *it = lista_iterador_crear(lista);

	for (; lista_iterador_tiene_siguiente(it); lista_iterador_avanzar(it))
		contador++;

	pa2m_afirmar(
		contador == 7,
		"En una lista de siete elementos se recorrieron siete elementos");

	lista_iterador_destruir(it);
	lista_destruir(lista);
}

void creo_una_pila_y_verifico_que_esta_vacia_y_que_no_tiene_tope()
{
	pila_t *pila = pila_crear();
	pa2m_afirmar(pila_vacia(pila) && pila_tope(pila) == NULL,
		     "Una pila recién creada está vacía, y tiene tope null");

	pila_destruir(pila);
}

void apilo_varios_elementos_y_el_tamanio_de_la_pila_coincide_con_la_cantidad_de_elementos_que_inserte()
{
	int a = 1;
	pila_t *pila = pila_crear();
	pa2m_afirmar(pila_vacia(pila),
		     "La pila recién creada tiene cero elementos");
	pila_apilar(pila, &a);
	pa2m_afirmar(pila_tamanio(pila) == 1,
		     "Apilo un elemento y el tamanio de la pila es uno");
	pila_apilar(pila, &a);
	pa2m_afirmar(
		pila_tamanio(pila) == 2,
		"Apilo un segundo elemento y el tamanio de la pila es dos");
	pila_apilar(pila, &a);
	pa2m_afirmar(
		pila_tamanio(pila) == 3,
		"Apilo un tercer elemento y el tamanio de la pila es tres");

	pila_destruir(pila);
}

void desapilo_y_el_tamanio_de_la_pila_decrece_hasta_que_no_hay_mas_elementos_y_el_tope_es_null()
{
	int a = 1;
	pila_t *pila = pila_crear();
	pila_apilar(pila, &a);
	pila_apilar(pila, &a);
	pila_apilar(pila, &a);
	pa2m_afirmar(pila_tamanio(pila) == 3,
		     "Tengo una pila con tres elementos y desapilo");
	pila_desapilar(pila);
	pa2m_afirmar(pila_tamanio(pila) == 2,
		     "Desapilo un elemento y el tamanio de la pila es dos");
	pila_desapilar(pila);
	pa2m_afirmar(pila_tamanio(pila) == 1,
		     "Desapilo otro elemento y el tamanio de la pila es uno");
	pila_desapilar(pila);
	pa2m_afirmar(
		pila_tamanio(pila) == 0,
		"Desapilo el ultimo elemento y el tamanio de la pila es cero");
	pa2m_afirmar(pila_vacia(pila), "La pila está vacía");
	pa2m_afirmar(pila_tope(pila) == NULL, "El tope es null");

	pila_destruir(pila);
}

void apilar_varias_veces_y_verificar_tope_cada_vez_y_desapilar_varias_veces_y_verificar_tope_cada_vez()
{
	int a = 1, b = 2, c = 3;
	pila_t *pila = pila_crear();

	pa2m_afirmar(pila_apilar(pila, &a) != NULL && pila_tope(pila) == &a,
		     "Apilo '1' en la lista y es el tope");
	pa2m_afirmar(pila_apilar(pila, &b) != NULL && pila_tope(pila) == &b,
		     "Apilo '2' y es el tope");
	pa2m_afirmar(pila_apilar(pila, &c) != NULL && pila_tope(pila) == &c,
		     "Apilo '3' y es el tope");
	pila_desapilar(pila);
	pa2m_afirmar(pila_tope(pila) == &b, "desapilo y ahora '2' es el tope");
	pila_desapilar(pila);
	pa2m_afirmar(pila_tope(pila) == &a, "desapilo y ahora '1' es el tope");
	pila_desapilar(pila);
	pa2m_afirmar(pila_tope(pila) == NULL,
		     "desapilo el último elemento de la pila y tope es null");

	pila_destruir(pila);
}

void creo_una_cola_y_verifico_que_esta_vacia_y_que_tiene_tamanio_cero()
{
	cola_t *cola = cola_crear();

	pa2m_afirmar(cola_vacia(cola) && cola_tamanio(cola) == 0,
		     "La cola recién creada está vacía y no tiene elementos");

	cola_destruir(cola);
}

void encolo_Y_desencolo_elementos_y_verifico_que_el_tamanio_de_la_cola_crece_y_decrece()
{
	cola_t *cola = cola_crear();

	pa2m_afirmar(
		cola_encolar(cola, "1") != NULL && cola_tamanio(cola) == 1,
		"Encolo un elemento en una cola vacía y ahora el tamaño es 1");
	cola_desencolar(cola);
	pa2m_afirmar(cola_tamanio(cola) == 0,
		     "Desencolo un elemento y la cola tiene tamaño cero");

	cola_destruir(cola);
}

void encolo_y_desencolo_varios_elementos_y_verifico_que_el_frente_fue_el_ultimo_elemento_encolado()
{
	cola_t *cola = cola_crear();
	char *ultimo_elemento_encolado = "4";

	cola_encolar(cola, "elemento");
	cola_encolar(cola, "dos");
	cola_encolar(cola, "tres");
	cola_encolar(cola, ultimo_elemento_encolado);
	pa2m_afirmar(cola_tamanio(cola) == 4,
		     "Encolo cuatro elementos en una cola vacía");
	cola_desencolar(cola);
	cola_desencolar(cola);
	cola_desencolar(cola);
	pa2m_afirmar(
		cola_frente(cola) == ultimo_elemento_encolado,
		"Luego de desencolar tres veces el frente de la cola es el último elemento encolado");

	cola_destruir(cola);
}
