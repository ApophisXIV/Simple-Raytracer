/**
 * @file vector.c
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief TDA Vector
 * @version 1.0
 * @date 2021-12-01
 *
 * @copyright Copyright (c) 2021
 *
 */

/** @addtogroup Algebra
 *  @{
 */

/* -------------------------------- Includes -------------------------------- */
#include <time.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../../inc/vector.h"

/* -------------------- Public prototypes implementation -------------------- */
float vector_producto_interno(const vector_t a, const vector_t b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

float vector_norma(const vector_t a) {
	return sqrt(vector_producto_interno(a, a));
}

vector_t vector_normalizar(const vector_t a) {
	const float n_aux = vector_norma(a);
	return (vector_t){a.x / n_aux, a.y / n_aux, a.z / n_aux};
}

vector_t vector_interpolar_recta(const vector_t o, const vector_t d, const float t) {
	return (vector_t){d.x * t + o.x, d.y * t + o.y, d.z * t + o.z};
}

vector_t vector_resta(const vector_t a, const vector_t b) {
	return (vector_t){a.x - b.x, a.y - b.y, a.z - b.z};
}

vector_t vector_producto_vectorial(const vector_t a, const vector_t b) {
	return (vector_t){
		a.y * b.z - a.z * b.y,
		a.z * b.x - a.x * b.z,
		a.x * b.y - a.y * b.x};
}

vector_t vector_invertir(const vector_t a) {
	return (vector_t){-a.x, -a.y, -a.z};
}

vector_t vector_random(const vector_t min, const vector_t max) {

	static bool seed_esta_inicializado = false;
	if (!seed_esta_inicializado) {
		srand(time(NULL));
		seed_esta_inicializado = true;
	}

	return (vector_t){
		(float)rand() / RAND_MAX * (max.x - min.x) + min.x,
		(float)rand() / RAND_MAX * (max.y - min.y) + min.y,
		(float)rand() / RAND_MAX * (max.z - min.z) + min.z
    };
}

/** @} */
