/**
 * @file sphere.h
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief TDA de esferas
 * @version 1.0
 * @date 2021-12-01
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "vector.h"

/* ----------------------------- Data structures ---------------------------- */

typedef struct {
    vector_t centro;
    float radio;
} esfera_t;

/* ------------------------------- Prototypes ------------------------------- */

//TODO Agregar a grupo con @defgroup o addgroup

/**
 * @brief  Creacion de una estructura esfera_t en memoria dinamica
 * @note   Los parametros que recibe la funcion son de tipo read-only.
 * @param  centro: Struct vector_t cuyo miembro es una terna ordenada. Centro de la esfera
 * @param  radio: Radio de la esfera
 * @param  color: Struct color_t cuyo miembro es una terna ordenada del tipo RGB. Color ambiente
 * @param  ka: Coeficiente de reflexion ambiental
 * @param  kd: Coeficiente de reflexion difusa
 * @retval P: Puntero a la estructura esfera_t creada
 * @retval NULL: Error en la creacion de la estructura esfera_t
 */
esfera_t *esfera_crear(const vector_t centro, const float radio);

/**
 * @brief  Libera la memoria dinamica de una estructura esfera_t
 * @param  *esfera_: Puntero a la estructura esfera_t a liberar
 * @retval None
 */
void esfera_destruir(esfera_t *esfera);
