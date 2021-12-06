/**
 * @file core.c
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief App core
 * @version 1.0
 * @date 2021-11-19
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <math.h>

#include "../../inc/core.h"
#include "../../inc/dynamic_array.h"
#include "../../inc/vector.h"

/* -------------------------------- Constants ------------------------------- */
#define PI 3.1415927f
#define FOV 90

color_t computar_intensidad(int profundidad, const arreglo_t *objetos, const arreglo_t *luces, color_t ambiente, vector_t o, vector_t d) {

	// TODO Implementar
}

bool generar_escena(escena_t *escena, imagen_t *imagen) {

	const color_t ambiente = {.05, .05, .05};
	const vector_t origen = {0, 0, 0};

	const float z = escena->ancho / 2 / tan(FOV / 2 * PI / 180);

	const int y_max = escena->alto / 2;
	const int x_max = escena->ancho / 2;

	for (int y = y_max; y > -y_max; y--)
		for (int x = -x_max; x < x_max; x++) {

            // TODO Testear
			const color_t c = computar_intensidad(escena->iteraciones, escena->objetos, escena->luces, ambiente, origen, vector_normalizar((vector_t){x, y, z}));

			if (!imagen_set_pixel(imagen, x + x_max, y + y_max - 1, c))
				return false;
		}

	return true;
}
