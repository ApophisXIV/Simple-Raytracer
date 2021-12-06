/**
 * @file mesh.h
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @version 1.0
 * @date 2021-12-01
 *
 * @copyright Copyright (c) 2021
 *
 */

//TODO Agregar documentacion
//? TODO Revisar

#ifndef MESH_H
#define MESH_H

#include <stddef.h>

#include "vector.h"
#include "triangle.h"

struct malla;
typedef struct malla malla_t;

malla_t *malla_crear(const char* archivo_stl);

void malla_destruir(malla_t *malla);

#endif // MESH_H