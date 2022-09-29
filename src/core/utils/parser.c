/**
 * @file parser.c
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief Parser de entrada de datos y escena
 * @version 1.0
 * @date 2021-11-13
 *
 * @copyright Copyright (c) 2021
 *
 */

/** @addtogroup Parser
 *  @{
 */

/* -------------------------------- Includes -------------------------------- */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../../inc/parser.h"

/* -------------------- Private prototypes implementation ------------------- */
/**
 * @brief   Imprime por consola una breve ayuda sobre como usar el programa.
 * @retval None
 */
static void print_usage_help() {

	printf("\n=============================== Ayuda ==============================\n");
	putchar('\n');
	printf("Uso: ./main <ancho> <alto> <profundidad> <nombre_archivo_salida>\n");
	putchar('\n');
	printf("\t<ancho>\t\t\tAncho de la imagen\n");
	printf("\t<alto>\t\t\tAlto de la imagen\n");
	printf("\t<profundidad>\t\tProfundidad de recursión\n");
	printf("\t<nombre_archivo>\tNombre del archivo a generar\n");
	putchar('\n');
	printf("Las extensiones de archivo validas son:\n");
	printf("\t.ppm\n");
	printf("\t.bmp\n");
	putchar('\n');
	printf("Ejemplo:\n");
	printf("\t./main 640 480 imagen.ppm\n");
	printf("\t./main 640 480 imagen.bmp\n");
	printf("\n====================================================================\n");
}

/**
 * @brief   Verifica que la extension del archivo sea valida.
 * @param  *raw_data: Puntero a un arreglo de caracteres que contiene el nombre del archivo.
 * @param  *ppm_bmp: Puntero a un entero donde se almacenara el tipo de archivo.
 * @retval bool: True si la extension es valida, False en caso contrario.
 */
static bool is_a_valid_extension(const char *raw_data, file_type_t *ppm_bmp) {

	if (raw_data[0] == '.') {
		print_usage_help();
		fprintf(stderr, "\nError: El nombre de archivo no puede iniciar con un punto\n");
		return false;
	}

	size_t dot_pos = 0;
	size_t dot_cnt = 0;
	for (size_t i = 0; raw_data[i] && dot_cnt < 2; i++) {

		if (raw_data[i] == '.') {
			dot_cnt++;
			dot_pos = i;
		}

		if (!isalnum(raw_data[i]) && raw_data[i] != '.' && raw_data[i] != '_') {
			print_usage_help();
			fprintf(stderr, "\nError: El nombre de archivo no puede contener caracteres especiales\n");
			return false;
		}
	}

	if (dot_cnt != 1) {
		print_usage_help();
		fprintf(stderr, "\nError: El nombre de archivo debe contener un unico punto\n");
		return false;
	}

	char ext_aux[4];

	for (size_t i = dot_pos + 1; raw_data[i]; i++) {	// dot_pos + 1 -> Siguiente caracter al .
		if (i - dot_pos > 3) {
			print_usage_help();
			fprintf(stderr, "\nError: La extension es demasiado larga. Solo se admite .ppm o .bmp\n");
			return false;
		}
		ext_aux[i - dot_pos - 1] = raw_data[i];
	}
	ext_aux[3] = '\0';

    //TODO Mejorar con tablas de busqueda
	if (strcmp(ext_aux, "ppm") == 0) {
		*ppm_bmp = FT_PPM;
		return true;
	}

	if (strcmp(ext_aux, "bmp") == 0) {
		*ppm_bmp = FT_BMP;
		return true;
	}

	print_usage_help();
	fprintf(stderr, "\nError: La extension es invalida. Solo se admite .ppm o .bmp\n");
	return false;
}

//TODO Completar parser de escena
// static bool is_a_valid_scene(const char* scene_file, escena_t *escena) {

//     FILE *f_escena = fopen(scene_file, "r");
//     if (f_escena == NULL) {
//         fprintf(stderr, "\nError: No se pudo abrir el archivo %s\n", scene_file);
//         return false;
//     }

// }

bool is_a_valid_input(int argc, char *argv[], escena_t *escena, file_type_t *extension) {

	if (argc != 5) {
		print_usage_help();
		fprintf(stderr, "\nError: Cantidad de argumentos incorrecta\n");
		return false;
	}

	char *errPtr;

	// Ancho
	escena->ancho = strtol(argv[1], &errPtr, 10);
	if (*errPtr != '\0') {
		print_usage_help();
		fprintf(stderr, "\nError: El ancho de la imagen no es un numero\n");
		return false;
	}

	// Alto
	escena->alto = strtol(argv[2], &errPtr, 10);
	if (*errPtr != '\0') {
		print_usage_help();
		fprintf(stderr, "\nError: El alto de la imagen no es un numero\n");
		return false;
	}

	if (escena->ancho <= 0 || escena->alto <= 0) {
		print_usage_help();
		fprintf(stderr, "\nError: Las dimensiones de la imagen deben ser un numero positivo\n");
		return false;
	}

    // Iteraciones
    escena->iteraciones = strtol(argv[1], &errPtr, 10);
    if (*errPtr != '\0') {
        fprintf(stderr, "\nError: El valor de iteraciones no es valido\n");
        return false;
    }

    if (escena->iteraciones < 0) {
        fprintf(stderr, "\nError: El valor de iteraciones no puede ser negativo\n");
        return false;
    }

	// Extension
	if (!is_a_valid_extension(argv[4], extension))
		return false;

    // Escena
    // if (!is_a_valid_scene(argv[5], escena))
    //     return false;

	return true;
}

/** @} */
