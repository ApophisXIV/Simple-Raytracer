/**
 * @file core.h
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief App core
 * @version 1.0
 * @date 2021-12-06
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef CORE_H
#define CORE_H

/* -------------------------------- Includes -------------------------------- */
#include <stdbool.h>

#include "imagen.h"
#include "scene.h"

/** @defgroup Core Core
 *  @{
 */

/* ------------------------------- Prototypes ------------------------------- */
/**
 * @brief  Genera una escena con los datos dados.
 * @pre    Escena debe apuntar a una miembros validos de la estructura escena_t.
 * @param  *escena: Puntero a la escena a generar.
 * @param  *imagen: Puntero a la imagen a renderizar.
 * @retval True si la escena fue generada con exito, false en caso contrario.
 */
bool generar_escena(escena_t *escena, imagen_t *imagen);

/** @} */

/** @addtogroup Core
 *  @{
 */
/** @defgroup Shapes Shapes */
/** @defgroup Canvas Canvas */
/** @defgroup Output Output */
/** @} */

#endif	  // CORE_H