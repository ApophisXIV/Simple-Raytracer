/**
 * @file object.h
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief TDA Objeto
 * @version 1.0
 * @date 2021-12-02
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <stdlib.h>

#include "../../../inc/object.h"
#include "../../../inc/vector.h"

#include "../../../inc/mesh.h"
#include "../../../inc/plane.h"
#include "../../../inc/sphere.h"
#include "../../../inc/triangle.h"

struct objeto {
	void *g_ptr;
	geometria_t g_type;
	float ka;
	float kd;
	float ks;
	float kr;
	color_t rgb;
};

objeto_t *objeto_crear(const void *geometria_ptr, const geometria_t g_tipo, const float ka, const float kd, const float ks, const float kr, const color_t rgb) {

	objeto_t *objeto_ptr = malloc(sizeof(objeto_t));

	if (objeto_ptr == NULL)
		return NULL;

	objeto_ptr->g_ptr = geometria_ptr;
	objeto_ptr->g_type = g_tipo;
	objeto_ptr->ka = ka;
	objeto_ptr->kd = kd;
	objeto_ptr->ks = ks;
	objeto_ptr->kr = kr;

	return objeto_ptr;
}

typedef void (*destructor_t)(void *);

void objeto_destruir(objeto_t *objeto) {

	const destructor_t geometry_destructors_handlers[] = {
		esfera_destruir,
		plano_destruir,
		triangulo_destruir,
		malla_destruir};

	if (objeto->g_type == OBJECT_UNKNOWN)
		return;

	geometry_destructors_handlers[objeto->g_type](objeto->g_ptr);

	free(objeto);
}

typedef float (*distancia_t)(const void *, const vector_t, const vector_t, const vector_t *, const vector_t *);

float objeto_distancia(const objeto_t *objeto, vector_t o, vector_t d, vector_t *punto, vector_t *normal) {

	const distancia_t geometry_distance_handlers[] = {
		esfera_distancia,
		plano_distancia,
		// TODO triangulo_distancia,
		// TODO malla_distancia
	};

	return geometry_distance_handlers[objeto->g_type](objeto->g_ptr, o, d, punto, normal);
}
