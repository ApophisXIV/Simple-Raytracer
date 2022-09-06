/**
 * @file progress_bar.h
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief Barra de progreso
 * @version 1.0
 * @date 2021-12-01
 *
 * @copyright Copyright (c) 2021
 *
 */

/** @addtogroup Utils
 *  @{
 */

/** @defgroup Progress_bar Progress bar
 *  Lista de funciones primitivas para la barra de progreso
 *  @{
 */

#ifndef PROGRESS_BAR_H
#define PROGRESS_BAR_H

/* ---------------------------- Public prototypes --------------------------- */
/**
 * @brief  	Genera una barra de progreso en la salida estandar de error (stderr)
 * @note   	La barra de progreso se actualiza cada vez que se llama a esta funcion
 *			Se utiliza stderr dado que esta salida no esta bufferizada. En caso de
 *         	utilizar stdout, la barra de progreso no se actualizaria hasta que se
 *          llame a fflush(stdout), la cual puede producir un resultado inesperado
 * 			y a su vez no es parte del estandar.
 * @param  	p: Progreso actual
 * @retval 	None
 */
void progress_bar(unsigned int p, char c);

/** @} */
/** @} */

#endif    // PROGRESS_BAR_H
