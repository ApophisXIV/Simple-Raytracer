/**
 * @file bmp.c
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief BMP
 * @version 1.0
 * @date 2021-11-19
 *
 * @copyright Copyright (c) 2021
 *
 */

/** @addtogroup BMP
 *  @{
 */

/* -------------------------------- Includes -------------------------------- */
#include <stdint.h>
#include "../../../inc/bmp.h"

/* ---------------------- Private constants and macros ---------------------- */

// ---- Encabezado de Archivo BMP
#define BMP_FILE_HEADER_TYPE 0x4D42    //"BM"
#define BMP_FILE_HEADER_RESERVED_1 0
#define BMP_FILE_HEADER_RESERVED_2 0
#define BMP_FILE_HEADER_OFFSET 54

// ---- Encabezado de Imagen BMP
#define BMP_IMAGE_HEADER_SIZE 40
#define BMP_IMAGE_HEADER_PLANES 1
#define BMP_IMAGE_HEADER_COLOR_DEPTH_24 24
#define BMP_IMAGE_HEADER_COMPRESSION 0
#define BMP_IMAGE_HEADER_IMAGE_SIZE 0
#define BMP_IMAGE_HEADER_RESOLUTION_X 0
#define BMP_IMAGE_HEADER_RESOLUTION_Y 0
#define BMP_IMAGE_HEADER_COLOR_TABLES 0
#define BMP_IMAGE_HEADER_IMPORTANT_COLORS 0

// ---- Extras
#define BMP_FILE_HEADER_SIZE_BYTES 14
#define BMP_PADDING_BYTE 0

/* -------------------- Private prototypes implementation ------------------- */
/**
 * @brief Escritura de 2 bytes en formato little endian
 * @pre   El archivo debe estar abierto
 * @param  *f: Descriptor de archivo
 * @param  v: Valor a escribir
 * @retval None
 */
static void escribir_int16_little_endian(FILE *f, int16_t v) {

    uint8_t v_little_endian[2];
    v_little_endian[0] = (uint8_t)v;
    v_little_endian[1] = (uint8_t)(v >> 8);

    fwrite(v_little_endian, sizeof(uint8_t), 2, f);
}

/**
 * @brief Escritura de 4 bytes en formato little endian
 * @pre   El archivo debe estar abierto
 * @param  *f: Descriptor de archivo
 * @param  v: Valor a escribir
 * @retval None
 */
static void escribir_int32_little_endian(FILE *f, int32_t v) {

    uint8_t v_little_endian[4];
    v_little_endian[0] = (uint8_t)v;
    v_little_endian[1] = (uint8_t)(v >> 8);
    v_little_endian[2] = (uint8_t)(v >> 16);
    v_little_endian[3] = (uint8_t)(v >> 24);

    fwrite(v_little_endian, sizeof(uint8_t), 4, f);
}

/**
 * @brief Calculo del tamaño de una imagen BMP con padding bytes
 * @pre   El ancho y alto de la imagen deben ser mayores a 0
 * @param  ancho: Ancho de la imagen
 * @param  alto: Alto de la imagen
 * @retval size_t: Tamaño de la imagen en bytes
 */
static size_t file_size_w_padding(size_t ancho, size_t alto) {
    return BMP_FILE_HEADER_SIZE_BYTES + BMP_IMAGE_HEADER_SIZE + alto * (ancho * 3 + 4 - (((ancho * 3) % 4)? ((ancho * 3) % 4) : 4));
}

/**
 * @brief Escritura de un color RGB en formato little endian
 * @pre   El archivo debe estar abierto y el color debe estar en formato RGB
 * @param  c: Color a escribir
 * @param  *f: Descriptor de archivo
 * @retval None
 */
static void file_color_imprimir(const color_t c, FILE *f) {

    uint8_t r = (uint8_t)(c.r > 1 ? 255 : c.r * 255);
    uint8_t g = (uint8_t)(c.g > 1 ? 255 : c.g * 255);
    uint8_t b = (uint8_t)(c.b > 1 ? 255 : c.b * 255);

    fwrite(&b, sizeof(uint8_t), 1, f);
    fwrite(&g, sizeof(uint8_t), 1, f);
    fwrite(&r, sizeof(uint8_t), 1, f);
}

/* -------------------- Public prototypes implementation -------------------- */
void escribir_BMP(const imagen_t *imagen, FILE *f) {

    size_t ancho, alto;
    imagen_dimensiones(imagen, &ancho, &alto);

    // BMP File Header
    escribir_int16_little_endian(f, BMP_FILE_HEADER_TYPE);
    escribir_int32_little_endian(f, file_size_w_padding(ancho, alto));
    escribir_int16_little_endian(f, BMP_FILE_HEADER_RESERVED_1);
    escribir_int16_little_endian(f, BMP_FILE_HEADER_RESERVED_2);
    escribir_int32_little_endian(f, BMP_FILE_HEADER_OFFSET);

    // BMP Image Header
    escribir_int32_little_endian(f, BMP_IMAGE_HEADER_SIZE);
    escribir_int32_little_endian(f, ancho);
    escribir_int32_little_endian(f, alto);
    escribir_int16_little_endian(f, BMP_IMAGE_HEADER_PLANES);
    escribir_int16_little_endian(f, BMP_IMAGE_HEADER_COLOR_DEPTH_24);
    escribir_int32_little_endian(f, BMP_IMAGE_HEADER_COMPRESSION);
    escribir_int32_little_endian(f, BMP_IMAGE_HEADER_IMAGE_SIZE);
    escribir_int32_little_endian(f, BMP_IMAGE_HEADER_RESOLUTION_X);
    escribir_int32_little_endian(f, BMP_IMAGE_HEADER_RESOLUTION_Y);
    escribir_int32_little_endian(f, BMP_IMAGE_HEADER_COLOR_TABLES);
    escribir_int32_little_endian(f, BMP_IMAGE_HEADER_IMPORTANT_COLORS);

    // Image Data
    for (size_t y = 0; y < alto; y++) {

        for (size_t x = 0; x < ancho; x++)
            file_color_imprimir(imagen_get_pixel(imagen, x, y), f);

        //Padding
        for (size_t p = 0; p < ancho % 4; p++)
            fwrite(&(uint8_t){BMP_PADDING_BYTE}, sizeof(uint8_t), 1, f);
    }
}

/** @} */
