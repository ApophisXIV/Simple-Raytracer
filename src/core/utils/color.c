/**
 * @file color.c
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief TDA Color
 * @version 1.0
 * @date 2021-12-26
 *
 * @copyright Copyright (c) 2021
 *
 */

/** @addtogroup Color
 *  @{
 */

/* -------------------------------- Includes -------------------------------- */
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../../../inc/color.h"

/* -------------------- Public prototypes implementation -------------------- */
color_t color_random() {

	static bool seed_esta_inicializada = false;
	if (!seed_esta_inicializada) {
		srand(time(NULL));
		seed_esta_inicializada = true;
    }
    
	return (color_t){
		.r = (double)rand() / (double)RAND_MAX,
		.g = (double)rand() / (double)RAND_MAX,
		.b = (double)rand() / (double)RAND_MAX
	};
}

/** @} */
