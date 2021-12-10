/**
 * @file mesh.c
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief TDA Malla
 * @version 1.0
 * @date 2021-12-06
 *
 * @copyright Copyright (c) 2021
 *
 */

// TODO Implementar el TDA Malla

#include "../../../inc/mesh.h"
#include "../../../inc/dynamic_array.h"
#include "../../../inc/triangle.h"

#include <stdio.h>

// TODO Ver de como seria la estructura de malla

struct malla {
    triangulo_t **tr;
    size_t n;
};

malla_t *malla_crear(const char *archivo_stl){
    FILE *p = fopen("archivo.stl", "rb");
    if(p == NULL) 
        return NULL;

}

void malla_destruir(malla_t *malla){
    free(malla);
}

float malla_distancia(const malla_t *malla, const vector_t o, const vector_t d, vector_t *punto, vector_t *normal){

}

/*
Es posible construir una malla como un arreglo de triángulos, donde la distancia 
estará dada por la intersección más cercana entre el rayo y todos 
los triángulos de la misma y la normal será la de ese triángulo.
*/