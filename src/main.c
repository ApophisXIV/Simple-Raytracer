/**
 * @file main.c
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief main
 * @version 1.0
 * @date 2021-11-13
 *
 * @copyright Copyright (c) 2021z
 *
 */

/* -------------------------------- Includes -------------------------------- */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "../inc/core.h"

#include "../inc/color.h"
#include "../inc/lights.h"
#include "../inc/mesh.h"
#include "../inc/object.h"
#include "../inc/plane.h"
#include "../inc/sphere.h"
#include "../inc/triangle.h"

#include "../inc/bmp.h"
#include "../inc/ppm.h"

#include "../inc/dynamic_array.h"
#include "../inc/parser.h"

int main(int argc, char *argv[]) {

	//--Entrada----------------------
	escena_t escena;
	file_type_t file_type = FT_PPM;

	if (!is_a_valid_input(argc, argv, &escena, &file_type))
		return 1;

	// Arreglos de objetos y luces
	arreglo_t objetos = {NULL, 0};
	arreglo_t luces = {NULL, 0};

	// Luces
	assert(arreglo_agregar(&luces, luz_crear(vector_normalizar((vector_t){0, 100, 0}), (color_t){0.8, 0.8, 0.8}, false)));
	assert(arreglo_agregar(&luces, luz_crear((vector_t){-2, 100, 2.5}, (color_t){.9, 0, 0}, true)));
	assert(arreglo_agregar(&luces, luz_crear((vector_t){2, 100, 2.5}, (color_t){0, .9, 0}, true)));
	assert(arreglo_agregar(&luces, luz_crear((vector_t){0, 100, 5}, (color_t){0, 0, .9}, true)));
	assert(arreglo_agregar(&luces, luz_crear((vector_t){-51, 60, -80}, (color_t){0.8, 0.2, 0.2}, true)));

	for (int i = 0; i < 120; i++)
		assert(arreglo_agregar(&objetos, objeto_crear(esfera_crear(vector_random((vector_t){-80.0, 1.0, 58.0}, (vector_t){80.0, 60.0, 58.0}), 0.32), OBJECT_SPHERE, color_random(), 1, 1, 1, .99)));

	assert(luces.n == 5);
	for (size_t i = 0; i < luces.n; i++)
		assert(luces.v[i] != NULL);

	/* -------------------------------------------------------------------------- */
	// Luna roja y agujero negro
	assert(arreglo_agregar(&objetos, objeto_crear(esfera_crear((vector_t){0, 25, 30}, 5.5), OBJECT_SPHERE, (color_t){0, 0, 0}, 1, 0, 0, 0)));
	assert(arreglo_agregar(&objetos, objeto_crear(esfera_crear((vector_t){10, 18, 2.4}, 2.5), OBJECT_SPHERE, (color_t){1, 0.3, 0.3}, 1, 1, 1, .05)));

	/* -------------------------------------------------------------------------- */
	// Suelo
	assert(arreglo_agregar(&objetos, objeto_crear(plano_crear((vector_t){0, 0, 0}, (vector_t){0, 1, 0}), OBJECT_PLANE, (color_t){0.0, 0.22, 0.0}, 0.9, 0.3, 0, 0.0)));

	/* -------------------------------------------------------------------------- */
	// Espejos
	assert(arreglo_agregar(&objetos, objeto_crear(plano_crear((vector_t){0, 100, 60}, (vector_t){0, 0, -1}), OBJECT_PLANE, (color_t){0.8, 0.8, 0}, 1, 0.0, 0.3, 1)));
	assert(arreglo_agregar(&objetos, objeto_crear(triangulo_crear((vector_t){9.072651, 0.300000, -4.205592}, (vector_t){-1.228175, 0.783287, -13.460830}, (vector_t){-4.102066, 0.183287, 0.059765}, NULL), OBJECT_TRIANGLE, (color_t){0.5, 0.6, 0.4}, 0.5, 0.5, 0.5, 1)));
	assert(arreglo_agregar(&objetos, objeto_crear(malla_crear("./assets/espejo_curvo_fondo.stl"), OBJECT_MESH, (color_t){0.06, 0.06, 0.06}, 1, 0, 0.3, 1)));

	/* -------------------------------------------------------------------------- */
	// Bosque (Copas + troncos)
	assert(arreglo_agregar(&objetos, objeto_crear(malla_crear("./assets/copas_bosque_verde.stl"), OBJECT_MESH, (color_t){0.06, 0.62, 0.35}, 1, 0.5, 0.5, 0.5)));
	assert(arreglo_agregar(&objetos, objeto_crear(malla_crear("./assets/troncos_bosque_verde.stl"), OBJECT_MESH, (color_t){0.43, 0.32, 0.18}, 1, 0.5, 0.01, 0.05)));

	assert(arreglo_agregar(&objetos, objeto_crear(malla_crear("./assets/copas_bosque_rojo.stl"), OBJECT_MESH, (color_t){1, 0.2, 0.15}, 1, 0.5, 0.5, 0.5)));
	assert(arreglo_agregar(&objetos, objeto_crear(malla_crear("./assets/troncos_bosque_rojo.stl"), OBJECT_MESH, (color_t){0.43, 0.32, 0.18}, 1, 0.5, 0.01, 0.05)));

	/* -------------------------------------------------------------------------- */
	// Lobo
	assert(arreglo_agregar(&objetos, objeto_crear(malla_crear("./assets/lobo.stl"), OBJECT_MESH, (color_t){1, 0.6, 0.35}, 1, 0.8, 1, 0.6)));

	/* -------------------------------------------------------------------------- */
	// Auto
	assert(arreglo_agregar(&objetos, objeto_crear(malla_crear("./assets/auto_low_poly.stl"), OBJECT_MESH, (color_t){0, 0.5, 1}, 1, 0.8, 1, 0.6)));

	for (size_t i = 0; i < objetos.n; i++)
		assert(objetos.v[i] != NULL);

	//--Procesamiento----------------
	imagen_t *img = imagen_crear(escena.ancho, escena.alto);
	if (img == NULL) {
		fprintf(stderr, "Error al crear la imagen\n");
		return 1;
	}

	escena.objetos = &objetos;
	escena.luces = &luces;

	if (!generar_escena(&escena, img)) {
		imagen_destruir(img);
		fprintf(stderr, "Error al generar la imagen\n");
		return 1;
	}

	//--Salida-----------------------
	switch (file_type) {

	case FT_PPM: {
		FILE *img_ppm = fopen(argv[4], "w");
		if (img_ppm == NULL) {
			imagen_destruir(img);
			fprintf(stderr, "Error al abrir el archivo\n");
			return 1;
		}
		escribir_PPM(img, img_ppm);
		fclose(img_ppm);
	} break;

	case FT_BMP: {
		FILE *img_bmp = fopen(argv[4], "wb");
		if (img_bmp == NULL) {
			imagen_destruir(img);
			fprintf(stderr, "Error al abrir el archivo\n");
			return 1;
		}
		escribir_BMP(img, img_bmp);
		fclose(img_bmp);
	} break;

	default: {
		imagen_destruir(img);
		return 1;
	}
	}

	//--Extras-----------------------
	imagen_destruir(img);

	arreglo_destruir(&objetos, objeto_destruir);
	arreglo_destruir(&luces, luz_destruir);

	return 0;
}