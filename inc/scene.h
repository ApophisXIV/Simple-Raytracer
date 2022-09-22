/**
 * @file scene.h
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief TDA Escena
 * @version 1.0
 * @date 2021-12-06
 *
 * @copyright Copyright (c) 2021
 *
 */

/** @addtogroup Scene
 *  @{
 */

/** @defgroup Scene_struct Scene struct
 *  Estructura de la escena
 *  @{
 */

#ifndef SCENE_H
#define SCENE_H

/* ------------------------- Public data structures ------------------------- */
struct escena {
	int             ancho;
	int             alto;
	int             iteraciones;
	void           *objetos, *luces;
	void           *ambiente;
	void           *o, *d;
};

/* ----------------------------- Public typedefs ---------------------------- */
typedef struct escena escena_t;

/** @} */
/** @} */

#endif				// SCENE_H
