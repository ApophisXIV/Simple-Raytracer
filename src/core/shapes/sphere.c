/**
 * @file sphere.c
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief TDA Esfera
 * @version 1.0
 * @date 2021-12-05
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <stdlib.h>

#include "../../../inc/sphere.h"
#include "../../../inc/vector.h"

struct esfera {
	vector_t centro;
	float radio;
};

esfera_t *esfera_crear(const vector_t centro, const float radio) {

	esfera_t *esfera_h = malloc(sizeof(esfera_t));
	if (esfera_h == NULL)
		return NULL;

	esfera_h->centro = centro;
	esfera_h->radio = radio;

	return esfera_h;
}

void esfera_destruir(esfera_t *esfera) {
	free(esfera);
}

float esfera_distancia(const esfera_t *esfera, const vector_t o, const vector_t d, vector_t *punto, vector_t *normal) {

	const vector_t co = vector_resta(esfera->centro, o);
	const float cd = vector_producto_interno(co, d);
	const float delta = cd * cd - vector_producto_interno(co, co) + esfera->radio * esfera->radio;

	if ((delta >= 0) && (cd + sqrt(delta) > 0)) {	 // Corto circuito. Priorizo delta >= 0.

		const float sqrtDelta = sqrt(delta);
		const float t = cd - sqrtDelta > 0 ? cd - sqrtDelta : cd + sqrtDelta;

		if (punto != NULL && normal != NULL) {
			*punto = vector_interpolar_recta(o, d, t);
			*normal = vector_resta(*punto, esfera->centro);
			normal->x /= esfera->radio;
			normal->y /= esfera->radio;
			normal->z /= esfera->radio;
		}
		return t;
	}
	return INFINITO;
}