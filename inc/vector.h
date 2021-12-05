/**
 * @file vector.h
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief TDA Vector
 * @version 1.0
 * @date 2021-12-01
 *
 * @copyright Copyright (c) 2021
 *
 */

#ifndef VECTOR_H
#define VECTOR_H

#include <float.h>

/** @addtogroup Shapes
 *  @{
 */

/** @defgroup Algebra Algebra
 *  Operaciones con vectores
 *  @{
 */

/* -------------------------------- Constants ------------------------------- */
#define INFINITO FLT_MAX

/* ----------------------------- Data structures ---------------------------- */
typedef struct {
	float	x;
	float	y;
	float	z;
} vector_t;

/* ------------------------------- Prototypes ------------------------------- */
/**
 * @brief		Calcula el producto interno de los vectores provistos a partir de sus componentes individuales
 * @param[in]	a: Struct vector_t cuyo miembro es una terna ordenada A
 * @param[in]	b: Struct vector_t cuyo miembro es una terna ordenada B
 * @retval		Resultado del producto interno del vector a y b
 */
float			vector_producto_interno(const vector_t a, const vector_t b);

/**
 * @brief		Calcula la norma del vector provisto a partir de sus componentes
 * @param[in]   a: Struct vector_t cuyo miembro es una terna ordenada A
 * @retval  	Resultado de la norma del vector provisto
 */
float 			vector_norma(const vector_t a);

/**
 * @brief		Computa el versor asociado al vector provisto
 * @param[in]	a: Struct vector_t cuyo miembro es una terna ordenada A
 * @retval  	Vector normalizado
 */
vector_t 		vector_normalizar(const vector_t a);

/**
 * @brief		Calcula las coordenadas del punto en el que un determinado rayo impacto para una
 *				distancia t desde un origen o
 * @pre			El rayo d debe ser un versor
 * @param[in]	o: Struct vector_t cuyo miembro es una terna ordenada. Coordenadas de origen desde las que el rayo es disparado
 * @param[in]	d: Struct vector_t cuyo miembro es una terna ordenada. Versor asociado al rayo a disparar al objetivo.
 * @param[in]	t: Distancia a la cual el rayo d impacto sobre el objetivo
 * @retval		Coordenadas del punto en el que el rayo impacto para una distancia t desde un origen o
 */
vector_t		vector_interpolar_recta(const vector_t o, const vector_t d, const float t);

/**
 * @brief  		Calcula la resta entre el vector a y b.
 * @param[in]   a: Struct vector_t cuyo miembro es una terna ordenada A
 * @param[in]   b: Struct vector_t cuyo miembro es una terna ordenada B
 * @retval 		Resultado de la resta entre el vector a y b
 */
vector_t 		vector_resta(const vector_t a, const vector_t b);

/** @} */
/** @} */

#endif	// VECTOR_H