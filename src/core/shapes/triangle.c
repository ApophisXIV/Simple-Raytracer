/**
 * @file triangle.c
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief TDA Triangulo
 * @version 1.0
 * @date 2021-12-06
 *
 * @copyright Copyright (c) 2021
 *
 */

/** @addtogroup Triangle
 *  @{
 */

/* -------------------------------- Includes -------------------------------- */
#include <stdbool.h>
#include <stdlib.h>
#include "../../../inc/triangle.h"

/* ---------------------- Private constants and macros ---------------------- */
#define EPSILON 10E-4f

/* ------------------------- Private data structures ------------------------ */
struct triangulo {
	vector_t p1;
	vector_t p2;
	vector_t p3;
	vector_t normal;
};

/* -------------------- Public prototypes implementation -------------------- */
triangulo_t *triangulo_crear(const vector_t p1, const vector_t p2, const vector_t p3, vector_t *nm) {

	triangulo_t *triangulo_ptr = malloc(sizeof(triangulo_t));

	if (triangulo_ptr == NULL)
		return NULL;

	triangulo_ptr->p1 = p1;
	triangulo_ptr->p2 = p2;
	triangulo_ptr->p3 = p3;


	if (nm == NULL) {
		const vector_t arista_1 = vector_resta(p2, p1);
		const vector_t arista_2 = vector_resta(p3, p1);
		triangulo_ptr->normal = vector_normalizar(vector_producto_vectorial(arista_1, arista_2));
	} else{
		triangulo_ptr->normal = *nm;
    }

	return triangulo_ptr;
}

void triangulo_destruir(void *triangulo) {
	free((triangulo_t *) triangulo);
}

float triangulo_distancia(const void *triangulo, const vector_t o, const vector_t d, vector_t *punto, vector_t *normal) {

    const triangulo_t *_triangulo = triangulo;

	const vector_t arista_1 = vector_resta(_triangulo->p2, _triangulo->p1);
	const vector_t arista_2 = vector_resta(_triangulo->p3, _triangulo->p1);

	const vector_t h = vector_producto_vectorial(d, arista_2);
	const float a = vector_producto_interno(arista_1, h);

	if (a > -EPSILON && a < EPSILON)
		return INFINITO;

	const vector_t s = vector_resta(o, _triangulo->p1);
	const float u = (vector_producto_interno(s, h) / a);

	const vector_t q = vector_producto_vectorial(s, arista_1);
	const float v = (vector_producto_interno(d, q) / a);

	if (u < 0 || v < 0 || u + v > 1)
		return INFINITO;

	const float t = (vector_producto_interno(arista_2, q) / a);
	if (t > EPSILON) {
		if (punto != NULL && normal != NULL) {
			*normal = _triangulo->normal;
			*punto = vector_interpolar_recta(o, d, t);
		}
		return t;
	}
	return INFINITO;
}

/** @} */
