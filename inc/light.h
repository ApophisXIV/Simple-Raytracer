/**
 * @file light.h
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @author Johann L. Pollero (jpollero@fi.uba.ar)
 * @brief Estructura de luces
 * @version 1.0
 * @date 2021-12-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef LIGHT_H
#define LIGHT_H

#include <stdbool.h>

#include "vector.h"
#include "color.h"

/* ----------------------------- Data structures ---------------------------- */
typedef struct {
    vector_t posicion;    // Si es_puntual es una coordenada, si no una dirección
    color_t color;
    bool es_puntual;
} luz_t;

#endif // LIGHT_H