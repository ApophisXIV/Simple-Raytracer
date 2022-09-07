/**
 * @file color.h
 * @author Sebastian Santisi
 * @brief TDA Color
 * @version 1.0
 * @date 2021-11-19
 *
 * @copyright Copyright (c) 2021
 *
 */

/** @addtogroup Utils
 *  @{
 */

/** @defgroup Color Color
 *  Lista de funciones primitivas de color y estructura
 *  @{
 */

#ifndef COLOR_H
#define COLOR_H

/* ------------------------- Public data structures ------------------------- */
struct color {
	double          r, g, b;
};

/* ----------------------------- Public typedefs ---------------------------- */
typedef struct color color_t;

/* ---------------------------- Public prototypes --------------------------- */
/**
 * @brief  Genera un color aleatorio.
 * @retval Color aleatorio.
 */
color_t         color_random();

/** @} */
/** @} */

#endif
