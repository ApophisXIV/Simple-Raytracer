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

#include <stdlib.h>

#include "../../../inc/plane.h"
#include "../../../inc/vector.h"

plano_t *plano_crear(const vector_t punto, const vector_t normal) {

	plano_t *plano = malloc(sizeof(plano_t));
	if (plano == NULL)
		return NULL;

	plano->punto = punto;
	plano->normal = normal;

	return plano;
}

void plano_destruir(plano_t *plano) {
	free(plano);
}

float plano_distancia(const plano_t *plano, const vector_t o, const vector_t d, vector_t *punto, vector_t *normal) {

	// Verifico que el vector d no sea ortogonal a la normal del plano
	if (vector_producto_escalar(d, plano->normal) == 0)
		return INFINITO;

	const float t = vector_producto_interno(vector_resta(o, plano->punto), plano->normal) / vector_producto_interno(d, plano->normal);

	if (punto != NULL && normal != NULL) {
		*punto = vector_interpolar_recta(o, d, t);
		*normal = plano->normal;
	}

	return t;
}
