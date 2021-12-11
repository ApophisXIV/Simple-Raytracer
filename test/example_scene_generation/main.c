/**
 * @file main.c
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @version 1.0
 * @date 2021-11-13
 *
 * @copyright Copyright (c) 2021
 *
 */

#include <stdio.h>
#include <assert.h>

#include "../inc/core.h"

#include "../inc/color.h"
#include "../inc/lights.h"
#include "../inc/object.h"
#include "../inc/plane.h"
#include "../inc/sphere.h"

#include "../inc/bmp.h"
#include "../inc/ppm.h"

#include "../inc/parser.h"
#include "../inc/dynamic_array.h"


int main(int argc, char *argv[]) {

    //--Entrada----------------------
    escena_t escena;
    file_type_t file_type;

    escena.ancho = 640;
    escena.alto = 480;
    escena.iteraciones = 5;

    // Arreglos de objetos y luces
    arreglo_t objetos = {NULL, 0};
    arreglo_t luces = {NULL, 0};

    // Luces
    assert(arreglo_agregar(&luces, luz_crear(vector_normalizar((vector_t){0, 1, 0}), (color_t){.2, .2, .2}, false)));
    assert(arreglo_agregar(&luces, luz_crear((vector_t){-2, 10, 2.5}, (color_t){.9, 0, 0}, true)));
    assert(arreglo_agregar(&luces, luz_crear((vector_t){2, 10, 2.5}, (color_t){0, .9, 0}, true)));
    assert(arreglo_agregar(&luces, luz_crear((vector_t){0, 10, 5}, (color_t){0, 0, .9}, true)));

    assert(luces.n == 4);
    for (size_t i = 0; i < luces.n; i++)
        assert(luces.v[i] != NULL);

    // Objetos
    assert(arreglo_agregar(&objetos, objeto_crear(esfera_crear((vector_t){0, 1, 2.4}, .3), OBJECT_SPHERE, (color_t){1, 1, 1}, 1, 1, 0.6, .33)));
    assert(arreglo_agregar(&objetos, objeto_crear(esfera_crear((vector_t){0, -.4, 3}, 1), OBJECT_SPHERE, (color_t){1, 1, 1}, 1, 1, 0.6, .33)));

    assert(arreglo_agregar(&objetos, objeto_crear(esfera_crear((vector_t){-2, -.6, 3}, .3), OBJECT_SPHERE, (color_t){1, 0, 0}, 1, .8, 0.6, .33)));
    assert(arreglo_agregar(&objetos, objeto_crear(esfera_crear((vector_t){-1.73, -.6, 2}, .3), OBJECT_SPHERE, (color_t){1, 1, 0}, 1, 1, 0.6, .33)));
    assert(arreglo_agregar(&objetos, objeto_crear(esfera_crear((vector_t){-1, -.6, 1.26}, .3), OBJECT_SPHERE, (color_t){0, 1, 0}, 1, 1, 0.6, .33)));
    assert(arreglo_agregar(&objetos, objeto_crear(esfera_crear((vector_t){0, -.6, 1}, .3), OBJECT_SPHERE, (color_t){1, 1, 1}, 1, 1, 0.6, .33)));
    assert(arreglo_agregar(&objetos, objeto_crear(esfera_crear((vector_t){1, -.6, 1.26}, .3), OBJECT_SPHERE, (color_t){0, 1, 1}, 1, 1, 0.6, .33)));
    assert(arreglo_agregar(&objetos, objeto_crear(esfera_crear((vector_t){1.73, -.6, 2}, .3), OBJECT_SPHERE, (color_t){0, 0, 1}, 1, 1, 0.6, .33)));
    assert(arreglo_agregar(&objetos, objeto_crear(esfera_crear((vector_t){2, -.6, 3}, .3), OBJECT_SPHERE, (color_t){1, 0, 1}, 1, 1, 0.6, .33)));

    assert(arreglo_agregar(&objetos, objeto_crear(esfera_crear((vector_t){-3, 2.5, 4.3}, .3), OBJECT_SPHERE, (color_t){1, 1, 1}, 1, 0, 0.6, .33)));
    assert(arreglo_agregar(&objetos, objeto_crear(esfera_crear((vector_t){-2, 2.5, 4.3}, .3), OBJECT_SPHERE, (color_t){1, 1, 1}, 1, .16, 0.6, .33)));
    assert(arreglo_agregar(&objetos, objeto_crear(esfera_crear((vector_t){-1, 2.5, 4.3}, .3), OBJECT_SPHERE, (color_t){1, 1, 1}, 1, .33, 0.6, .33)));
    assert(arreglo_agregar(&objetos, objeto_crear(esfera_crear((vector_t){0, 2.5, 4.3}, .3), OBJECT_SPHERE, (color_t){1, 1, 1}, 1, .5, 0.6, .33)));
    assert(arreglo_agregar(&objetos, objeto_crear(esfera_crear((vector_t){1, 2.5, 4.3}, .3), OBJECT_SPHERE, (color_t){1, 1, 1}, 1, .66, 0.6, .33)));
    assert(arreglo_agregar(&objetos, objeto_crear(esfera_crear((vector_t){2, 2.5, 4.3}, .3), OBJECT_SPHERE, (color_t){1, 1, 1}, 1, .83, 0.6, .33)));
    assert(arreglo_agregar(&objetos, objeto_crear(esfera_crear((vector_t){3, 2.5, 4.3}, .3), OBJECT_SPHERE, (color_t){1, 1, 1}, 1, 1, 0.6, .33)));

    assert(arreglo_agregar(&objetos, objeto_crear(esfera_crear((vector_t){-3, 1.5, 4}, .3), OBJECT_SPHERE, (color_t){1, 1, 1}, 0, 1, 0.6, .33)));
    assert(arreglo_agregar(&objetos, objeto_crear(esfera_crear((vector_t){-2, 1.5, 4}, .3), OBJECT_SPHERE, (color_t){1, 1, 1}, .16, 1, 0.6, .33)));
    assert(arreglo_agregar(&objetos, objeto_crear(esfera_crear((vector_t){-1, 1.5, 4}, .3), OBJECT_SPHERE, (color_t){1, 1, 1}, .33, 1, 0.6, .33)));
    assert(arreglo_agregar(&objetos, objeto_crear(esfera_crear((vector_t){0, 1.5, 4}, .3), OBJECT_SPHERE, (color_t){1, 1, 1}, .5, 1, 0.6, .33)));
    assert(arreglo_agregar(&objetos, objeto_crear(esfera_crear((vector_t){1, 1.5, 4}, .3), OBJECT_SPHERE, (color_t){1, 1, 1}, .66, 1, 0.6, .33)));
    assert(arreglo_agregar(&objetos, objeto_crear(esfera_crear((vector_t){2, 1.5, 4}, .3), OBJECT_SPHERE, (color_t){1, 1, 1}, .83, 1, 0.6, .33)));
    assert(arreglo_agregar(&objetos, objeto_crear(esfera_crear((vector_t){3, 1.5, 4}, .3), OBJECT_SPHERE, (color_t){1, 1, 1}, 1, 1, 0.6, .33)));

    assert(objetos.n == 23);
    for (size_t i = 0; i < objetos.n; i++)
        assert(objetos.v[i] != NULL);

    //--Procesamiento----------------
    imagen_t *img = imagen_crear(escena.ancho, escena.alto);
    if (img == NULL) {
        fprintf(stderr, "Error al crear la imagen\n");
        return 1;
    }

    escena.objetos = &objetos;
    escena.luces = &luces;

    if (!generar_escena(&escena, img)) {
        imagen_destruir(img);
        fprintf(stderr, "Error al generar la imagen\n");
        return 1;
    }

    //--Salida-----------------------
    // TODO Mejorar con tablas de busqueda
    switch (file_type) {

    case FT_PPM: {
        FILE *img_ppm = fopen(argv[4], "w");
        if (img_ppm == NULL) {
            imagen_destruir(img);
            fprintf(stderr, "Error al abrir el archivo\n");
            return 1;
        }
        escribir_PPM(img, img_ppm);
        fclose(img_ppm);
    } break;

    case FT_BMP: {
        FILE *img_bmp = fopen(argv[4], "wb");
        if (img_bmp == NULL) {
            imagen_destruir(img);
            fprintf(stderr, "Error al abrir el archivo\n");
            return 1;
        }
        escribir_BMP(img, img_bmp);
        fclose(img_bmp);
    } break;

    default: {
        imagen_destruir(img);
        return 1;
    }
    }

    //--Extras-----------------------
    imagen_destruir(img);

    return 0;
}
