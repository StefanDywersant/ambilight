/**
 * AVRLibs
 * Atmel AVR libraries
 *
 * Copyright: (c) 2010 by Karol Maciaszek
 * E-mail   : <karol.maciaszek@gmail.com>
 * WWW      : http://www.czystybeton.pl/
 *
 * $Id$
 */


#ifndef HWSPICONFIG_SAMPLE_H_
#define HWSPICONFIG_SAMPLE_H_


// SPI Serial Transfer Complete interrupt vector
#define HWSPI_STC_VECT	SPI_STC_vect

// SPI port
#define HWSPI_PORT		B

// MISO pin (Master Input Slave Output)
#define HWSPI_MISO_PIN	4

// MOSI pin (Master Output Slave Input)
#define HWSPI_MOSI_PIN	3

// SCK pin (Clock)
#define HWSPI_SCK_PIN	5

// CSN pin (Chip Select)
#define HWSPI_CSN_PIN	2

// double speed
#define HWSPI_SPI2X		0

// speed register 0
#define HWSPI_SPR0		0

// speed register 1
#define HWSPI_SPR1		0


#endif /* HWSPICONFIG_SAMPLE_H_ */
