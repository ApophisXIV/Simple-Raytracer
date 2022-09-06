/**
 * @file progress_bar.c
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief Barra de progreso
 * @version 1.0
 * @date 2021-12-17
 *
 * @copyright Copyright (c) 2021
 *
 */

/** @addtogroup Progress_bar
 *  @{
 */

/* -------------------------------- Includes -------------------------------- */
#include <time.h>
#include <stdio.h>
#include "../../../inc/progress_bar.h"

/* ---------------------- Private constants and macros ---------------------- */
#define PROGRESS_BAR_WIDTH 30
#define MAX_STR 50

/* -------------------- Public prototypes implementation -------------------- */
void progress_bar(unsigned int p, char c) {

	static time_t tiempo_inicial = 0;

	if (p == 1)
		tiempo_inicial = time(NULL);

	const double tiempo_transcurrido = difftime(time(NULL), tiempo_inicial);
	const double tiempo_estimado = (tiempo_transcurrido / p) * (100 - p);

	// Horas, minutos y segundos
	const int h = (int)(tiempo_transcurrido / 3600);
	const int m = (int)(tiempo_transcurrido / 60) % 60;
	const int s = (int)tiempo_transcurrido % 60;

	const int h_estimada = (int)(tiempo_estimado / 3600);
	const int m_estimada = (int)(tiempo_estimado / 60) % 60;
	const int s_estimada = (int)tiempo_estimado % 60;

    const unsigned int c_p = p * PROGRESS_BAR_WIDTH / 100;

	fprintf(stderr, "\r[");

	for (unsigned int  i = 0; i < c_p; i++)
		fprintf(stderr, "%c", c);

	for (unsigned int  i = c_p; i < PROGRESS_BAR_WIDTH; i++)
		fprintf(stderr, " ");


	fprintf(stderr, "] %u%% [T: %02d:%02d:%02d] [Termina en: %02d:%02d:%02d]", p, h, m, s, h_estimada, m_estimada, s_estimada);

}

/** @} */
