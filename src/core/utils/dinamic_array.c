/**
 * @file dynamic_array.c
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief TDA Arreglo dinamico
 * @version 0.1
 * @date 2021-12-02
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "../../../inc/dynamic_array.h"
#include "../../../inc/object.h"

bool arreglo_agregar(arreglo_t *a, const void *e) {

	void *a_aux = realloc(a->v, (a->n + 1) * sizeof(void *));

	if (a_aux == NULL)
		return false;

	a->v = a_aux;
	a->v[a->n++] = e;

	return true;
}

void arreglo_destruir(arreglo_t *a) {

	for (size_t i = 0; i < a->n; i++)
		objeto_destruir(a->v[i]);

	free(a->v);
}
