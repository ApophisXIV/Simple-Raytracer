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

/** @addtogroup Sphere
 *  @{
 */

/* -------------------------------- Includes -------------------------------- */
#include <math.h>
#include <stdlib.h>
#include "../../../inc/sphere.h"
#include "../../../inc/vector.h"

/* ------------------------- Private data structures ------------------------ */
struct esfera {
	vector_t centro;
	float radio;
};

/* -------------------- Public prototypes implementation -------------------- */
esfera_t *esfera_crear(const vector_t centro, const float radio) {

	esfera_t *esfera_h = malloc(sizeof(esfera_t));
	if (esfera_h == NULL)
		return NULL;

	esfera_h->centro = centro;
	esfera_h->radio = radio;

	return esfera_h;
}

void esfera_destruir(void *esfera) {
	free((esfera_t *)esfera);
}

float esfera_distancia(const void *esfera, const vector_t o, const vector_t d, vector_t *punto, vector_t *normal) {

    const esfera_t *_esfera = esfera;

	const vector_t co = vector_resta(_esfera->centro, o);
	const float cd = vector_producto_interno(co, d);
	const float delta = cd * cd - vector_producto_interno(co, co) + _esfera->radio * _esfera->radio;

	if ((delta >= 0) && (cd + sqrt(delta) > 0)) {	 // Corto circuito. Priorizo delta >= 0.

		const float sqrtDelta = sqrt(delta);
		const float t = cd - sqrtDelta > 0 ? cd - sqrtDelta : cd + sqrtDelta;

		if (punto != NULL && normal != NULL) {
			*punto = vector_interpolar_recta(o, d, t);
			*normal = vector_resta(*punto, _esfera->centro);
			normal->x /= _esfera->radio;
			normal->y /= _esfera->radio;
			normal->z /= _esfera->radio;
		}
		return t;
	}
	return INFINITO;
}

/** @} */
