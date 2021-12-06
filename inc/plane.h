/**
 * @file plane.h
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief TDA Plano
 * @version 1.0
 * @date 2021-12-01
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef PLANE_H
#define PLANE_H

#include "vector.h"

/* ----------------------------- Data structures ---------------------------- */
struct plano;
typedef struct plano plano_t;

/* ------------------------------- Prototypes ------------------------------- */

// TODO Agregar a grupo con @defgroup o addgroup

/**
 * @brief       Constructor de plano_t (crea un plano a partir de un punto y una normal en memoria dinamica)
 * @pre         La normal debe ser un versor
 * @param[in]   punto: Punto del plano
 * @param[in]   normal: Normal del plano
 * @retval      plano_t*: Puntero a la estructura plano_t creada
 * @retval      NULL: Error en la creacion de la estructura plano_t
 */
plano_t         *plano_crear(const vector_t punto, const vector_t normal);

/**
 * @brief       Destructor de la estructura plano_t reservada en memoria dinámica
 * @param[in]   plano: Puntero a la estructura plano_t a destruir
 * @retval      None
 */
void            plano_destruir(void *plano);

/**
 * @brief       Computa la distancia a la que está un punto de un plano desde el origen a partir del impacto de un rayo
 * @pre         La plano debe ser un puntero a una estructura plano_t valida
 * @pre         El rayo d debe ser un versor.
 * @param[in]   plano: Puntero a una estructura plano_t
 * @param[in]   o: Coordenadas de origen desde las que el rayo es disparado
 * @param[in]   d: Versor asociado al rayo a disparar contra el plano
 * @param[out]  *punto: Punto de impacto.
 * @param[out]  *normal: Normal del plano.
 * @retval      float: Distancia calculada
 * @retval      INFINITO: El rayo no impacto sobre el plano
 */
float           plano_distancia(const plano_t *plano, const vector_t o, const vector_t d, vector_t *punto, vector_t *normal);

#endif  // PLANE_H