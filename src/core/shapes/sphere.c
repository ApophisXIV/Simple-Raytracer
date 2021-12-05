/**
 * @file sphere.c
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief TDA de esferas
 * @version 1.0
 * @date 2021-12-05
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <stdlib.h>

#include "../../../inc/sphere.h"

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
