/**
 * @file plane.c
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief TDA Plano
 * @version 1.0
 * @date 2021-12-05
 *
 * @copyright Copyright (c) 2021
 *
 */

/** @addtogroup Plane
 *  @{
 */

/* -------------------------------- Includes -------------------------------- */
#include <stdlib.h>
#include "../../../inc/plane.h"
#include "../../../inc/vector.h"

/* ------------------------- Private data structures ------------------------ */
struct plano {
	vector_t punto;
	vector_t normal;
};

/* -------------------- Public prototypes implementation -------------------- */
plano_t *plano_crear(const vector_t punto, const vector_t normal) {

	plano_t *plano = malloc(sizeof(plano_t));
	if (plano == NULL)
		return NULL;

	plano->punto = punto;
	plano->normal = vector_normalizar(normal);

	return plano;
}

void plano_destruir(void *plano) {
	free((plano_t *)plano);
}

float plano_distancia(const void *plano, const vector_t o, const vector_t d, vector_t *punto, vector_t *normal) {

	const plano_t *_plano = plano;

	// Verifico que el vector d no sea ortogonal a la normal del plano
	if (vector_producto_interno(d, _plano->normal) == 0)
		return INFINITO;

	const float t = vector_producto_interno(vector_resta(_plano->punto, o), _plano->normal) / vector_producto_interno(d, _plano->normal);

	if (t < 0) {
		return INFINITO;
	}

	if (punto != NULL)
		*punto = vector_interpolar_recta(o, d, t);

	if (normal != NULL){

		if (vector_producto_interno(_plano->normal, d) < 0)
			*normal = _plano->normal;
		else
			*normal = vector_invertir(_plano->normal);
    }

	return t;
}

/** @} */
