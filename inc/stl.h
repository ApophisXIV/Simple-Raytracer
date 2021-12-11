/**
 * @file stl.h
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief BMP
 * @version 1.0
 * @date 2021-11-19
 *
 * @copyright Copyright (c) 2021
 *
 */

//TODO revisar

#ifndef BMP_H
#define BMP_H

/* -------------------------------- Includes -------------------------------- */
#include <stdio.h>
#include "imagen.h"

/** @addtogroup Output
 *  @{
 */

/** @defgroup STL STL
 *  Generación de archivos STL
 *  @{
 */

/* ------------------------------- Prototypes ------------------------------- */
/**
 * @brief  Crea un archivo de extension STL y almacena la imagen en el mismo.
 * @pre    La imagen debe estar creada previamente.
 * @pre    El archivo debe estar abierto en modo escritura binaria.
 * @pre    El archivo debe ser de tipo STL.
 * @param  *imagen: Puntero a la imagen a almacenar.
 * @param  *f: Descriptor de archivo donde se almacenara la imagen en formato STL.
 * @retval None
 */
void escribir_STL(const imagen_t *imagen, FILE *f);

/** @} */
/** @} */

#endif    // STL_H