/**
 * @file mesh.c
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief TDA Malla
 * @version 1.0
 * @date 2021-12-06
 *
 * @copyright Copyright (c) 2021
 *
 */

/** @addtogroup Poligonal_mesh
 *  @{
 */

/* -------------------------------- Includes -------------------------------- */
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../../inc/dynamic_array.h"
#include "../../../inc/mesh.h"
#include "../../../inc/triangle.h"

/* ---------------------- Private constants and macros ---------------------- */

// ---- Estructura Archivo STL
#define STL_FILE_HEADER_SIZE 80
#define STL_TRIANGLES_COUNT
#define STL_TRIANGLE_NORMAL
#define STL_TRIANGLE_VERTEX_1
#define STL_TRIANGLE_VERTEX_2
#define STL_TRIANGLE_VERTEX_3
#define STL_ATTRIBUTE_BYTE_COUNT 2

/* -------------------- Private prototypes implementation ------------------- */
/**
 * @brief       Lectura de 4 bytes en formato little endian de un archivo
 * @pre         El archivo debe estar abierto
 * @param[in]   *f: Descriptor de archivo
 * @param[out]  *v: Puntero a variable donde se guarda el valor leido
 * @retval      True si pudo leer, False si hubo error
 */
static bool leer_uint32_little_endian(FILE *f, uint32_t *v) {
	return fread(v, sizeof(uint32_t), 1, f) == 1;
}

/**
 * @brief		Lectura de un vector de 3 floats en formato little endian de un archivo binario
 * @pre			El archivo debe estar abierto
 * @param[in]	*f: Descriptor de archivo
 * @param[out]	*v: Puntero a variable donde se guarda el valor leido
 * @retval		True si pudo leer, False si hubo error
 */
static bool leer_vector_little_endian(FILE *f, vector_t *v) {
	return fread(v, sizeof(float), 3, f) == 3;
}

/* -------------------- Public prototypes implementation -------------------- */
malla_t *malla_crear(const char *filename) {

	malla_t *malla = malloc(sizeof(malla_t));
	if (malla == NULL) {
		return NULL;
	}

	malla->v = NULL;
	malla->n = 0;

	FILE *f = fopen(filename, "rb");
	if (f == NULL) {
		fprintf(stderr, "Error al abrir el archivo %s\n", filename);
		arreglo_destruir(malla, triangulo_destruir);
		return NULL;
	}

	if (fseek(f, STL_FILE_HEADER_SIZE, SEEK_SET) != 0) {
		fclose(f);
		arreglo_destruir(malla, triangulo_destruir);
		return NULL;
	}

	uint32_t num_triangles;
	if (!leer_uint32_little_endian(f, &num_triangles)) {
		fclose(f);
		arreglo_destruir(malla, triangulo_destruir);
		return NULL;
	}

	printf("Malla (Triangulos): %u [Nombre: %s]\n", num_triangles, filename);

	for (size_t i = 0; i < num_triangles; i++) {

		vector_t normal;
		if (!leer_vector_little_endian(f, &normal)) {
			fclose(f);
			arreglo_destruir(malla, triangulo_destruir);
			return NULL;
		}

		vector_t v1, v2, v3;
		if (!leer_vector_little_endian(f, &v1) || !leer_vector_little_endian(f, &v2) || !leer_vector_little_endian(f, &v3)) {
			fclose(f);
			arreglo_destruir(malla, triangulo_destruir);
			return NULL;
		}

		if (fseek(f, STL_ATTRIBUTE_BYTE_COUNT, SEEK_CUR) != 0) {
			fclose(f);
			arreglo_destruir(malla, triangulo_destruir);
			return NULL;
		}

		triangulo_t *triangulo = triangulo_crear(v1, v2, v3, &normal);
		if (triangulo == NULL) {
			fclose(f);
			arreglo_destruir(malla, triangulo_destruir);
			return NULL;
		}

		if (!arreglo_agregar(malla, triangulo)) {
			fclose(f);
			arreglo_destruir(malla, triangulo_destruir);
			return NULL;
		}
	}

	fclose(f);

	return malla;
}

void malla_destruir(void *malla) {
	arreglo_destruir((arreglo_t *)malla, triangulo_destruir);
    free((malla_t *)malla);
}

float malla_distancia(const void *malla, const vector_t o, const vector_t d, vector_t *punto, vector_t *normal) {

	const malla_t *_malla = malla;

	float t_min = INFINITO;
	vector_t p_min;
	vector_t n_min;

	for (size_t i = 0; i < _malla->n; i++) {

		const float t = triangulo_distancia(_malla->v[i], o, d, &p_min, &n_min);

		if (t < t_min) {
			t_min = t;
			if (punto != NULL)
				*punto = p_min;
			if (normal != NULL)
				*normal = n_min;
		}
	}

	if (t_min == INFINITO)
		return INFINITO;

	return t_min;
}

/** @} */
