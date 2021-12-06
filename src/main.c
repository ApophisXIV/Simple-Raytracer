/**
 * @file main.c
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @version 1.0
 * @date 2021-11-13
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <stdio.h>

#include "../inc/parser.h"

#include "../inc/core.h"
#include "../inc/scene.h"

#include "../inc/bmp.h"
#include "../inc/ppm.h"

int main(int argc, char *argv[]) {

	//--Entrada----------------------
	escena_t escena;
	file_type_t file_type;

	if (!is_a_valid_input(argc, argv, &escena, &file_type))
		return 1;

	//--Procesamiento----------------
	imagen_t *img = imagen_crear(escena.ancho, escena.alto);
	if (img == NULL) {
		fprintf(stderr, "Error al crear la imagen\n");
		return 1;
	}

	if (!generar_escena(&escena, img)) {
		imagen_destruir(img);
		fprintf(stderr, "Error al generar la imagen\n");
		return 1;
	}

	//--Salida-----------------------
	// TODO Mejorar con tablas de busqueda
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

	return 0;
}
