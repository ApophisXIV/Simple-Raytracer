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

/** @addtogroup Shapes
 *  @{
 */

/** @defgroup Poligonal_mesh Poligonal mesh
 *  Lista de funciones primitivas de una malla
 *  @{
 */

#ifndef MESH_H
#define MESH_H

/* -------------------------------- Includes -------------------------------- */
#include <stddef.h>
#include "triangle.h"
#include "vector.h"
#include "dynamic_array.h"

/* ----------------------------- Public typedefs ---------------------------- */
typedef arreglo_t malla_t;

/* ---------------------------- Public prototypes --------------------------- */
/**
 * @brief       Crea una malla vacia
 * @param[in]   *archivo_stl: Nombre del archivo .stl
 * @retval      malla_t*: Malla vacia
 */
malla_t        *malla_crear(const char *archivo_stl);

/**
 * @brief       Destruye una malla
 * @pre         Malla debe ser un puntero a una estructura malla_t valida
 * @param[in]   *malla: Puntero a la estructura malla_t a destruir
 * @retval      None
 */
void            malla_destruir(void *malla);

/**
 * @brief       Computa la distancia a la que está un punto de un triangulo de la malla desde el
 *              origen a partir del impacto de un rayo
 * @pre         Malla debe ser un puntero a una estructura malla_t valida
 * @pre         El rayo d debe ser un versor.
 * @param[in]   *malla: Puntero a una estructura malla_t
 * @param[in]   o: Coordenadas de origen desde las que el rayo es disparado
 * @param[in]   d: Versor asociado al rayo a disparar contra la malla
 * @param[out]  *punto: Punto de impacto.
 * @param[out]  *normal: Normal del tringulo sobre la que impacto el rayo.
 * @retval      float: Distancia calculada
 * @retval      INFINITO: El rayo no impacto sobre la malla
 */
float           malla_distancia(const void *malla, const vector_t o,
				const vector_t d, vector_t * punto,
				vector_t * normal);

/** @} */
/** @} */

#endif				// MESH_H
