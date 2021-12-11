/**
 * @file lights.h
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @author Johann L. Pollero (jpollero@fi.uba.ar)
 * @brief TDA Luces
 * @version 1.0
 * @date 2021-12-08
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <stdlib.h>

#include "../../../inc/lights.h"

luz_t *luz_crear(const vector_t posicion, const color_t color, const bool es_puntual) {

    luz_t *luz_h = malloc(sizeof(luz_t));
    if (luz_h == NULL)
        return NULL;

    luz_h->posicion = posicion;
    luz_h->color = color;
    luz_h->es_puntual = es_puntual;

    return luz_h;
}

void luz_destruir(luz_t *luz) {
    free(luz);
}