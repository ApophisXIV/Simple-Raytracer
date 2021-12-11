/**
 * @file light.h
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @author Johann L. Pollero (jpollero@fi.uba.ar)
 * @brief TDA Luces
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

/* ---------------------------- Public Prototypes --------------------------- */
/**
 * @brief       Constructor de luz_t (crea una luz a partir de un vector, un color y un 
 *              booleano que indica si es puntual o no)
 * @pre         La posición de la luz debe ser un versor si es_puntual es false
 * @param[in]   posicion: Posición de la luz 
 * @param[in]   color: Color de la luz
 * @param[in]   es_puntual: Si es_puntual es una coordenada, si no una dirección (versor)
 * @retval      luz_t*: Puntero a la estructura luz_t creada
 * @retval      NULL: Error en la creacion de la estructura luz_t
 */
luz_t *luz_crear(const vector_t posicion, const color_t color, const bool es_puntual);

/**
 * @brief       Destructor de la estructura luz_t reservada en memoria dinámica
 * @pre         Luz debe ser un puntero a una estructura luz_t valida
 * @param[in]   luz: Puntero a la estructura luz_t a destruir
 * @retval      None
 */
void luz_destruir(luz_t *luz);

#endif // LIGHT_H