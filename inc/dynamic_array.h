/**
 * @file dynamic_array.h
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief TDA Arreglo dinamico
 * @version 1.0
 * @date 2021-12-02
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdbool.h>
#include <stddef.h>

//TODO Ver si se puede privatizar esta estructura evitando exponer los miembros
typedef struct {
	void **v;
	size_t n;
} arreglo_t;

/**
 * @brief       Agrega un nuevo elemento al arreglo dinamico.
 * @param[in]   *a: Puntero al arreglo dinamico.
 * @param[in]   *e: Puntero al elemento a almacenar.
 * @retval      bool: True si se pudo agregar el elemento, False en caso contrario.
 */
bool    arreglo_agregar(arreglo_t *a, const void *e);

/**
 * @brief       Destructor del arreglo dinamico.
 * @pre         El arreglo debe estar inicializado
 * @param[in]   *a: Puntero al arreglo dinamico.
 * @retval      None
 */
void    arreglo_destruir(arreglo_t *a);

#endif	  // DYNAMIC_ARRAY_H