/**
 * @file parser.h
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief Parser de entrada de datos y escena
 * @version 1.0
 * @date 2021-11-19
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef PARSER_H
#define PARSER_H

/* -------------------------------- Includes -------------------------------- */
#include <stdbool.h>
#include <stdint.h>

#include "scene.h"

/* ---------------------------------- Enums --------------------------------- */
typedef enum {
    FT_BMP,
    FT_PPM
} file_type_t;

/* ------------------------------- Prototypes ------------------------------- */
/**
 * @brief   Verifica si la entrada de datos es valida.
 * @param   argc: Cantidad de argumentos pasados por linea de comandos.
 * @param   *argv[]: Puntero a un arreglo de punteros a cadenas de caracteres pasados por linea de comandos.
 * @param   *scene: Puntero a una estructura de tipo scene_t.
 * @param   *extension: Puntero a un entero donde se almacenara el tipo de archivo.
 * @retval  bool: True si la entrada es valida, false en caso contrario.
 */
bool is_a_valid_input(int argc, char *argv[], escena_t *escena, file_type_t *extension);

#endif // PARSER_H