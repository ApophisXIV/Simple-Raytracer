/**
 * @file sphere.h
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief TDA Esfera
 * @version 1.0
 * @date 2021-12-01
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef SPHERE_H
#define SPHERE_H

#include "vector.h"

/* ----------------------------- Data structures ---------------------------- */
typedef struct {
	vector_t    centro;
	float       radio;
} esfera_t;

/* ------------------------------- Prototypes ------------------------------- */

// TODO Agregar a grupo con @defgroup o addgroup

/**
 * @brief       Constructor de esfera_t (crea una esfera a partir de un centro y un radio en memoria dinámica)
 * @param[in]   centro: Centro de la esfera
 * @param[in]   radio: Radio de la esfera
 * @retval      esfera_t*: Puntero a la estructura esfera_t creada
 * @retval      NULL: Error en la creacion de la estructura esfera_t
 */
esfera_t        *esfera_crear(const vector_t centro, const float radio);

/**
 * @brief       Destructor de la estructura esfera_t reservada en memoria dinamica
 * @param[in]   esfera: Puntero a la estructura esfera_t a destruir
 * @retval      None
 */
void            esfera_destruir(esfera_t *esfera);

/**
 * @brief       Computa la distancia a la que se encuentra desde un determinado origen el
 *              primer impacto de un rayo sobre una esfera
 * @pre         La esfera debe ser un puntero a una estructura esfera_t valida
 * @pre         El rayo d debe ser un versor.
 * @param[in]   esfera: Puntero a una estructura esfera_t
 * @param[in]   o: Coordenadas de origen desde las que el rayo es disparado
 * @param[in]   d: Versor asociado al rayo a disparar contra la esfera
 * @param[out]  punto: Punto de impacto.
 * @param[out]  normal: Normal de la esfera en el punto de impacto.
 * @retval      float: Distancia calculada
 * @retval      INFINITO: El rayo no impacto sobre la esfera
 */
float           esfera_distancia(const esfera_t *esfera, const vector_t o, const vector_t d, vector_t *punto, vector_t *normal);

#endif  // SPHERE_H