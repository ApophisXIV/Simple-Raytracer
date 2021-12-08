/**
 * @file endianess.c
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief TDA Endian
 * @version 1.0
 * @date 2021-12-01
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "..\..\..\inc\endianess.h"

#include <stdint.h>
#include <stdio.h>

/**
 * @brief Escritura de 2 bytes en formato little endian
 * @pre   El archivo debe estar abierto
 * @param  *f: Descriptor de archivo
 * @param  v: Valor a escribir
 * @retval None
 */
static void escribir_int16_little_endian(FILE *f, int16_t v) {

    uint8_t v_little_endian[2];
    v_little_endian[0] = (uint8_t)v;
    v_little_endian[1] = (uint8_t)(v >> 8);

    fwrite(v_little_endian, sizeof(uint8_t), 2, f);
}

/**
 * @brief Escritura de 4 bytes en formato little endian
 * @pre   El archivo debe estar abierto
 * @param  *f: Descriptor de archivo
 * @param  v: Valor a escribir
 * @retval None
 */
static void escribir_int32_little_endian(FILE *f, int32_t v) {

    uint8_t v_little_endian[4];
    v_little_endian[0] = (uint8_t)v;
    v_little_endian[1] = (uint8_t)(v >> 8);
    v_little_endian[2] = (uint8_t)(v >> 16);
    v_little_endian[3] = (uint8_t)(v >> 24);

    fwrite(v_little_endian, sizeof(uint8_t), 4, f);
}