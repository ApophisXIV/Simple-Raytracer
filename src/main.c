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

#include "../include/parser.h"

#include "../include/core.h"

#include "../include/bmp.h"
#include "../include/ppm.h"

int main(int argc, char *argv[]) {

	//--Entrada----------------------
	int ancho;
	int alto;
	int file_type = FT_PPM;

	if (!is_a_valid_input(argc, argv, &ancho, &alto, &file_type))
		return 1;

	//--Procesamiento----------------
	imagen_t *img = imagen_crear(ancho, alto);
	if (img == NULL) {
		fprintf(stderr, "Error al crear la imagen\n");
		return 1;
	}



	if (!fill_img_w_shape(img, ancho, alto, MANDELBROT)) {
        imagen_destruir(img);
		fprintf(stderr, "Error al generar la imagen\n");
		return 1;
	}

	//--Salida-----------------------
	switch (file_type) {

		case FT_PPM: {
			FILE *img_ppm = fopen(argv[3], "w");
            if (img_ppm == NULL) {
                imagen_destruir(img);
                fprintf(stderr, "Error al abrir el archivo\n");
                return 1;
            }
			escribir_PPM(img, img_ppm);
			fclose(img_ppm);
		} break;

		case FT_BMP: {
			FILE *img_bmp = fopen(argv[3], "wb");
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
