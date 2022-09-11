/**
 * @file core.c
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief App core
 * @version 1.0
 * @date 2021-11-19
 *
 * @copyright Copyright (c) 2021
 *
 */

/** @addtogroup Core
 *  @{
 */

/* -------------------------------- Includes -------------------------------- */
#include <math.h>
#include "../../inc/core.h"
#include "../../inc/dynamic_array.h"
#include "../../inc/lights.h"
#include "../../inc/object.h"
#include "../../inc/progress_bar.h"
#include "../../inc/vector.h"

/* ---------------------- Private constants and macros ---------------------- */
#define PI 3.1415927f

#define EPSILON 10E-4f

#define FOV 90
#define NEGRO (color_t){0,0,0}
#define SIN_APORTE NEGRO

/* -------------------- Private prototypes implementation ------------------- */
/**
 * @brief       Suma de dos colores
 * @pre         c y m deben ser una estructura color_t valida. RGB [0 - 1]
 * @param[in]   c: Color 1
 * @param[in]   m: Color 2
 * @param[in]   p: Coeficiente que multiplica al color 2 para sumarlo al color 1
 * @retval      Color resultante
 */
static color_t color_sumar(const color_t c, const color_t m, const float p) {
	return (color_t){c.r + p * m.r, c.g + p * m.g, c.b + p * m.b};
}

/**
 * @brief       Computa la absorcion de dos colores
 * @pre         b y c deben ser una estructura color_t valida. RGB [0 - 1]
 * @param[in]   b: Color 1
 * @param[in]   c: Color 2
 * @retval      Color resultante
 */
static color_t color_absorber(const color_t b, const color_t c) {
	return (color_t){b.r * c.r, b.g * c.g, b.b * c.b};
}

/**
 * @brief       Computa la intensidad de luz sobre un determinado punto de impacto en formato RGB
 *              [0,1] para un determinado rayo d disparado desde un origen O sobre n objetos de
 *              la escena.
 * @pre         objetos debe estar creado previamente e inicializado.
 * @pre         luces debe estar creado previamente e inicializado.
 * @note        Si la profundidad de recusión es 0, la componente especular y reflectiva no son computadas
 * @param[in]   profundidad: Profundidad de recursión
 * @param[in]   *objetos: Arreglo de objetos de la escena
 * @param[in]   *luces: Arreglo de luces de la escena
 * @param[in]   ambiente: Color ambiente de la escena
 * @param[in]   o: Origen del rayo
 * @param[in]   d: Dirección del rayo
 * @retval      Color resultante
 * @retval      NEGRO: Se devuelve negro (0,0,0) en caso de que el rayo no impacte contra ningun objeto
 */
static color_t computar_intensidad(int profundidad, arreglo_t *objetos, arreglo_t *luces, color_t ambiente, vector_t o, vector_t d) {

	float t_min = INFINITO;
	size_t n_objeto_min_Z;
	vector_t p_min;
	vector_t n_min;

	for (size_t i = 0; i < objetos->n; i++) {

		vector_t p, n;
		const float t = objeto_distancia(objetos->v[i], o, d, &p, &n);

		if (t < t_min) {
			t_min = t;
			n_objeto_min_Z = i;
			p_min = p;
			n_min = n;
		}
	}

	if (t_min == INFINITO)
		return NEGRO;

	const objeto_t *obj_min = objetos->v[n_objeto_min_Z];
	const float d_n = vector_producto_interno(d, n_min);
	const vector_t r = vector_resta(d, (vector_t){n_min.x * 2 * d_n, n_min.y * 2 * d_n, n_min.z * 2 * d_n});
	color_t c_difusa = SIN_APORTE;

	for (size_t k = 0; k < luces->n; k++) {

		const luz_t *l_prueba = luces->v[k];
		vector_t l_luz = l_prueba->posicion;

		if (l_prueba->es_puntual)
			l_luz = vector_normalizar(vector_resta(l_prueba->posicion, p_min));

		float t_luz = INFINITO;

		for (size_t j = 0; j < objetos->n; j++)
			if (n_objeto_min_Z != j) {
				t_luz = objeto_distancia(objetos->v[j], p_min, l_luz, NULL, NULL);
				if (t_luz != INFINITO)
					break;
			}

		if (t_luz == INFINITO) {
			const color_t i_luz_cm = color_absorber(l_prueba->color, obj_min->color);
			const float l_n = vector_producto_interno(l_luz, n_min);
			const float l_r = vector_producto_interno(l_luz, r);
			c_difusa = color_sumar(c_difusa, i_luz_cm, obj_min->kd * (l_n < 0 ? 0 : l_n) + obj_min->ks * pow((l_r < 0 ? 0 : l_r), 10));
		}
	}

	color_t c = color_sumar(c_difusa, ambiente, obj_min->ka);

	if (profundidad > 0) {
		const vector_t p_min_offset = (vector_t){p_min.x + r.x * EPSILON, p_min.y + r.y * EPSILON, p_min.z + r.z * EPSILON};
		const color_t c_reflejado = computar_intensidad(profundidad - 1, objetos, luces, ambiente, p_min_offset, r);
		c = color_sumar(c, c_reflejado, obj_min->kr);
	}

	return c;
}

/* -------------------- Public prototypes implementation -------------------- */
bool generar_escena(escena_t *escena, imagen_t *imagen) {

    //TODO Evitar hardcodeo de ambiente y origen, y dejarlo configurable por el usuario en el archivo de configuración

	const color_t ambiente = {.05, .05, .05};
	const vector_t origen = {0, 5, -20};

	const float z = escena->ancho / 2 / tan(FOV / 2 * PI / 180);

	const int y_max = escena->alto / 2;
	const int x_max = escena->ancho / 2;

	for (int y = y_max; y > -y_max; y--) {

        progress_bar(1 + (y_max - y) * 50 / y_max, '#');

        for (int x = -x_max; x < x_max; x++) {

			color_t c = computar_intensidad(escena->iteraciones, escena->objetos, escena->luces, ambiente, origen, vector_normalizar((vector_t){x, y, z}));
			if (!imagen_set_pixel(imagen, x + x_max, y + y_max - 1, c))
				return false;
		}
	}

	return true;
}

/** @} */
