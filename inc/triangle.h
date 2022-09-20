/**
 * @file triangle.h
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief TDA Triangulo
 * @version 1.0
 * @date 2021-12-01
 *
 * @copyright Copyright (c) 2021
 *
 */

/** @addtogroup Shapes
 *  @{
 */

/** @defgroup Triangle Triangle
 *  Lista de funciones primitivas de un triangulo
 *  @{
 */

#ifndef TRIANGLE_H
#define TRIANGLE_H

/* -------------------------------- Includes -------------------------------- */
#include "vector.h"

/* ------------------------- Public data structures ------------------------- */
struct triangulo;

/* ----------------------------- Public typedefs ---------------------------- */
typedef struct triangulo triangulo_t;

/* ---------------------------- Public prototypes --------------------------- */
/**
 * @brief       Constructor de triangulo_t (crea un triangulo a partir de 3 puntos y una normal (opcional))
 * @note        En caso de que *nm sea NULL, se calcula la normal del triangulo con los puntos p1, p2 y p3
 * @pre         En caso de que *nm sea distinto de NULL, la normal debe ser un versor
 * @param[in]   p1: Punto 1 del triangulo
 * @param[in]   p2: Punto 2 del triangulo
 * @param[in]   p3: Punto 3 del triangulo
 * @param[in]   *nm: Puntero a un vector normalizado que representa la normal del triangulo
 * @retval      triangulo_t*: Puntero a la estructura triangulo_t creada
 * @retval      NULL: Error en la creacion de la estructura triangulo_t
 */
triangulo_t     *triangulo_crear(const vector_t p1, const vector_t p2, const vector_t p3, vector_t *nm);

/**
 * @brief       Destructor de la estructura triangulo_t reservada en memoria dinamica
 * @pre         Triangulo debe ser un puntero a una estructura triangulo_t valida
 * @param[in]   *triangulo: Puntero a la estructura triangulo_t a destruir
 * @retval      None
 */
void            triangulo_destruir(void *triangulo);

/**
 * @brief       Computa la distancia a la que se encuentra desde un determinado origen el
 *              primer impacto de un rayo sobre un triangulo
 * @pre         Triangulo debe ser un puntero a una estructura triangulo_t valida
 * @pre         El rayo d debe ser un versor.
 * @param[in]   *triangulo: Puntero a una estructura triangulo_t
 * @param[in]   o: Coordenadas de origen desde las que el rayo es disparado
 * @param[in]   d: Versor asociado al rayo a disparar contra el triangulo
 * @param[out]  *punto: Punto de impacto.
 * @param[out]  *normal: Normal del triangulo.
 * @retval      float: Distancia calculada
 * @retval      INFINITO: El rayo no impacto sobre el triangulo
 */
float           triangulo_distancia(const void *triangulo, const vector_t o, const vector_t d, vector_t *punto, vector_t *normal);

/** @} */
/** @} */

#endif	  // TRIANGLE_H