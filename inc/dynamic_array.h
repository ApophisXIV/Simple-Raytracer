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

/** @addtogroup Utils
 *  @{
 */

/** @defgroup Dynamic_array Dynamic array
 *  Lista de funciones primitivas para manejar arreglos dinamicos.
 *  @{
 */

#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

/* -------------------------------- Includes -------------------------------- */
#include <stdbool.h>
#include <stddef.h>

/* ------------------------- Public data structures ------------------------- */
struct arreglo {
	void          **v;
	size_t          n;
};

/* ----------------------------- Public typedefs ---------------------------- */
typedef struct arreglo arreglo_t;

/* ---------------------------- Public prototypes --------------------------- */
/**
 * @brief       Agrega un nuevo elemento al arreglo dinamico.
 * @param[in]   *a: Puntero al arreglo dinamico.
 * @param[in]   *e: Puntero al elemento a almacenar.
 * @retval      bool: True si se pudo agregar el elemento, False en caso contrario.
 */
bool            arreglo_agregar(arreglo_t * a, void *e);

/**
 * @brief       Destructor del arreglo dinamico.
 * @pre         El arreglo debe estar inicializado
 * @param[in]   *a: Puntero al arreglo dinamico.
 * @param[in]   *destruir_elemento: Puntero a la funcion que destruye un elemento.
 * @retval      None
 */
void            arreglo_destruir(arreglo_t * a, void (*destruir_elemento)(void *));

/** @} */
/** @} */

#endif				// DYNAMIC_ARRAY_H
