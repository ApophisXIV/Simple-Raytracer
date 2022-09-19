/**
 * @file object.h
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief TDA Objeto
 * @version 1.0
 * @date 2021-12-02
 *
 * @copyright Copyright (c) 2021
 *
 */

/** @addtogroup Scene
 *  @{
 */

/** @defgroup Scene_objects Scene objects
 *  Lista de funciones primitivas de objetos de la escena
 *  @{
 */

#ifndef OBJECT_H
#define OBJECT_H

/* -------------------------------- Includes -------------------------------- */
#include "color.h"
#include "vector.h"

/* ------------------------------ Public enums ------------------------------ */
enum geometria {
	OBJECT_SPHERE,
	OBJECT_PLANE,
	OBJECT_TRIANGLE,
	OBJECT_MESH,
	OBJECT_UNKNOWN
};

/* ------------------------- Public data structures ------------------------- */
struct objeto {
	void           *g_ptr;
	enum geometria  g_type;
	float           ka;
	float           kd;
	float           ks;
	float           kr;
	color_t         color;
};

/* ----------------------------- Public typedefs ---------------------------- */
typedef struct objeto objeto_t;
typedef enum geometria geometria_t;

/* ---------------------------- Public prototypes --------------------------- */
/**
 * @brief       Constructor de objeto_t (crea un objeto con una geometria asociada,
 *              coeficientes de iluminacion y color en memoria dinamica)
 * @param[in]   *geometria_ptr: Puntero a la geometria del objeto
 * @param[in]   ka: Coeficiente ambiental
 * @param[in]   kd: Coeficiente difuso
 * @param[in]   ks: Coeficiente especular
 * @param[in]   kr: Coeficiente reflexion
 * @retval      objeto_t*: Puntero a la estructura objeto_t creada
 * @retval      NULL: Error en la creacion de la estructura objeto_t
 */
objeto_t       *objeto_crear(void *geometria_ptr, const geometria_t g_tipo,
			     const color_t color, const float ka, const float kd,
			     const float ks, const float kr);

/**
 * @brief       Destructor de la estructura objeto_t reservada en memoria dinamica
 * @pre         Objeto debe ser un puntero a una estructura objeto_t valida
 * @param[in]   *objeto: Puntero a la estructura objeto_t a destruir
 * @return      None
 */
void            objeto_destruir(void *objeto);

/**
 * @brief       Computa la distancia a la que está un punto de un objeto desde el origen a partir del impacto de un rayo
 * @pre         El objeto debe ser un puntero a una estructura objeto_t valida
 * @pre         La geometria del objeto debe implementar una funcion propia para calcular la distancia a un punto
 * @pre         El rayo d debe ser un versor
 * @param[in]   *objeto: Puntero a una estructura objeto_t
 * @param[in]   o: Coordenadas de origen desde las que el rayo es disparado
 * @param[in]   d: Versor asociado al rayo a disparar contra la esfera
 * @param[out]  *punto: Punto de impacto.
 * @param[out]  *normal: Normal de la esfera en el punto de impacto.
 * @retval      float: Distancia calculada
 * @retval      INFINITO: El rayo no impacto sobre la esfera
 */
float           objeto_distancia(const objeto_t * objeto, const vector_t o,
				 const vector_t d, vector_t * punto,
				 vector_t * normal);

/** @} */
/** @} */

#endif				// OBJECT_H
