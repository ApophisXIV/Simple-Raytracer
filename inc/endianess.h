/**
 * @file mesh.h
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief TDA Malla
 * @version 1.0
 * @date 2021-12-01
 *
 * @copyright Copyright (c) 2021
 *
 */

// TODO Agregar documentacion
//? TODO Revisar

#ifndef ENDIANESS_H
#define ENDIANESS_H

#include <stddef.h>
#include <stdint.h>

void escribir_int16_little_endian(FILE *f, int16_t v); 

void escribir_int32_little_endian(FILE *f, int32_t v);

#endif	  // ENDIANESS_H