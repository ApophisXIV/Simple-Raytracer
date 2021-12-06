/**
 * @file scene.h
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief Estructura Escena
 * @version 1.0
 * @date 2021-12-06
 *
 * @copyright Copyright (c) 2021
 *
 */


#ifndef SCENE_H
#define SCENE_H

/* ----------------------------- Data structures ---------------------------- */
typedef struct {
    int ancho;
    int alto;
    int iteraciones;
    void *objetos, *luces;
    void *ambiente;
    void *o, *d;
} escena_t;

#endif // SCENE_H