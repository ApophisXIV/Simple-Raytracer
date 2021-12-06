/**
 * @file triangle.h
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief TDA Triangulo
 * @version 1.0
 * @date 2021-12-01
 *
 * @copyright Copyright (c) 2021
 *
 */

//TODO Agregar documentacion

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vector.h"

struct triangulo;
typedef struct triangulo triangulo_t;

triangulo_t *triangulo_crear(const vector_t p1, const vector_t p2, const vector_t p3);

void triangulo_destruir(triangulo_t *triangulo);

float triangulo_distancia(const triangulo_t *triangulo, const vector_t o, const vector_t d, vector_t *punto, vector_t *normal);

#endif	  // TRIANGLE_H