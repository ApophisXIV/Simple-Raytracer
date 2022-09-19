/**
 * @file dynamic_array.c
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief TDA Arreglo dinamico
 * @version 1.0
 * @date 2021-12-02
 *
 * @copyright Copyright (c) 2021
 *
 */

/** @addtogroup Dynamic_array
 *  @{
 */

/* -------------------------------- Includes -------------------------------- */
#include <stdlib.h>
#include "../../../inc/object.h"
#include "../../../inc/dynamic_array.h"

/* -------------------- Public prototypes implementation -------------------- */
bool arreglo_agregar(arreglo_t *a, void *e) {

	void *a_aux = realloc(a->v, (a->n + 1) * sizeof(void *));

	if (a_aux == NULL)
		return false;

	a->v = a_aux;
	a->v[a->n++] = e;

	return true;
}

void arreglo_destruir(arreglo_t *a, void (*destruir_elemento)(void *)) {

	for (size_t i = 0; i < a->n; i++)
        destruir_elemento(a->v[i]);

	free(a->v);
}

/** @} */
