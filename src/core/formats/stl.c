/**
 * @file stl.c
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief TDA stl
 * @version 1.0
 * @date 2021-12-06
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "../../../inc/endianess.h"
#include "../../../inc/imagen.h"

#include <stdio.h>

//TODO completar
//TODO revisar

/* ------------------------ Encabezado de Archivo STL ----------------------- */
#define STL_FILE_HEADER_TYPE 0x4D42    //"BM"
#define STL_FILE_TRIANGLES_NUMBER 0 //TODO Verificar numero

/* ------------------------ Para cada Triangulo ------------------------ */
#define TRIANGLE_NORMAL_VECTOR 12
#define TRIANGLE_VERTEX_1 12
#define TRIANGLE_VERTEX_2 12
#define TRIANGLE_VERTEX_3 12
#define ATTRIBUTE_BYTE_COUNT 2

/* ------------------------
UINT8[80]    – Header                 -     80 bytes                           
UINT32       – Number of triangles    -      4 bytes

foreach triangle                      - 50 bytes:
    REAL32[3] – Normal vector             - 12 bytes
    REAL32[3] – Vertex 1                  - 12 bytes
    REAL32[3] – Vertex 2                  - 12 bytes
    REAL32[3] – Vertex 3                  - 12 bytes
    UINT16    – Attribute byte count      -  2 bytes
end
------------------------ */

void escribir_STL(const imagen_t *imagen, FILE *f){

    // STL File Header
    
    __escribir_int32_little_endian(f, STL_FILE_TRIANGLES_NUMBER);

    // Foreach Triangle
    __escribir_int32_little_endian(f, TRIANGLE_NORMAL_VECTOR);
    __escribir_int32_little_endian(f, TRIANGLE_VERTEX_1);
    __escribir_int32_little_endian(f, TRIANGLE_VERTEX_2);
    __escribir_int32_little_endian(f, TRIANGLE_VERTEX_3);
    __escribir_int16_little_endian(f, ATTRIBUTE_BYTE_COUNT);
}