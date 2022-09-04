# Trabajo práctico final

<div align="center" width="800">
   <img align="center" width="800" src="https://user-images.githubusercontent.com/42053774/147417284-32dd7185-d07b-4b95-8d41-e81429c4df5f.png" />
</div>

Este ejercicio corresponde al trabajo práctico final de la cátedra Algoritmos y programación 1 - 95.11 - Essaya.
En este ejercicio se trabaja con la implementación "bare metal" de un raytracer en C basado en el modelo de Phong.
A su vez se trabaja con archivos STL para la representación de objetos.
En la imagen serán trazados diferentes objetos en un lienzo de resolución VGA.

## Compilando

``` make
make
```

**Observación:** Los flags utilizados para la compilación son -Wall -Werror -std=c99 -pedantic -g -lm. Es importante mencionar que el flag -g es utilizado unicamente en la fase de desarrollo del proyecto para la depuración del mismo.

## Ejecutando

Al momento de ejecutar el programa se puede hacer de forma manual o automatica mediante una regla en el archivo `Makefile`.

### Manual

```bash
./raytracer 640 480 5 imagen.ppm
```

```bash
./raytracer 640 480 5 imagen.bmp
```

### Automática

El programa es capaz de generar 2 formatos de imagen: ppm y bmp.

```bash
make run_ppm
```

```bash
make run_bmp
```

**Observación:** La resolución de imagen de ejemplo es VGA, la profundidad de recursión es de 5 y el archivo de salida es de formato ppm. Todos estos parámetros pueden ser cambiados desde el archivo Makefile. Ejemplo:

```Makefile
PROGRAM_IMG_DIMENSIONS = 1920 1080
RECURSION_DEPTH = 10
PROGRAM_OUTPUT_IMAGE_PPM = foo.ppm
PROGRAM_OUTPUT_IMAGE_BMP = bar.bmp
```

## Resultado

<p align="center" width="500">
   <img align="center" width="300" src="imagen.png"/>
</p>

## Documentación
[Trabajo Práctico Final](https://tp-final-algo-9511.netlify.app/)

## Datos personales

- **Alumno:** Guido E. Rodriguez
- **Número de padrón:** 108723
- **Contacto:** guerodrigue@fi.uba.ar
- **Fecha de entrega:** 2021-12-26
- **Copyright** Copyright (c) 2021

</p>