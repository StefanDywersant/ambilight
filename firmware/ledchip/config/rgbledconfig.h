/**
 * Ambilight
 * Aktywne podświetlenie monitora.
 *
 * Copyright: (c) 2010 by Karol Maciaszek
 * E-mail   : <karol.maciaszek@gmail.com>
 * WWW      : http://www.czystybeton.pl/
 *
 * $Id$
 */


#ifndef RGBLEDCONFIG_H_
#define RGBLEDCONFIG_H_

#include <avr/io.h>

#define LEDS_COUNT		20		// liczba diód
#define FILL_LEVELS		40		// liczba poziomów wypełnienia poszczególnej składowej

// mapa portów/pinów dla linii danych
#define D0_PORT			B
#define D0_PIN			0
#define D1_PORT			B
#define D1_PIN			1
#define D2_PORT			C
#define D2_PIN			0
#define D3_PORT			C
#define D3_PIN			1
#define D4_PORT			C
#define D4_PIN			2
#define D5_PORT			C
#define D5_PIN			3
#define D6_PORT			C
#define D6_PIN			4
#define D7_PORT			C
#define D7_PIN			5

// mapa portów/pinów dla linii adresowych
#define A0_PORT			D
#define A0_PIN			2
#define A1_PORT			D
#define A1_PIN			3
#define A2_PORT			D
#define A2_PIN			4
#define A3_PORT			D
#define A3_PIN			5
#define A4_PORT			D
#define A4_PIN			6
#define A5_PORT			D
#define A5_PIN			7
#define A6_PORT			D
#define A6_PIN			0
#define A7_PORT			D
#define A7_PIN			1

#endif /* RGBLEDCONFIG_H_ */
