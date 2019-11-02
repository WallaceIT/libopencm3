/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2016 Karl Palsson <karlp@tweak.net.au>
 *
 * This library is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <libopencm3/cm3/common.h>

/* --- Convenience macros ------------------------------------------------ */

#define PORTA				(PORT_BASE + 0)
#define PORTB				(PORT_BASE + 0x80)

#define PINCFG_MUXEN        (1 << 0)
#define PINCFG_INEN         (1 << 1)
#define PINCFG_PULLEN       (1 << 2)
#define PINCFG_STRONG       (1 << 6)

#define WRCONFIG_MUXEN      (1 << 16)
#define WRCONFIG_INEN       (1 << 17)
#define WRCONFIG_PULLEN     (1 << 18)

#define WRCONFIG_PMUXA      (0 << 24)
#define WRCONFIG_PMUXB      (1 << 24)
#define WRCONFIG_PMUXC      (2 << 24)
#define WRCONFIG_PMUXD      (3 << 24)
#define WRCONFIG_PMUXE      (4 << 24)
#define WRCONFIG_PMUXF      (5 << 24)
#define WRCONFIG_PMUXG      (6 << 24)
#define WRCONFIG_PMUXH      (7 << 24)
#define WRCONFIG_PMUXI      (8 << 24)

#define WRCONFIG_WRPINMUX   (1 << 28)
#define WRCONFIG_WRPINCFG   (1 << 30)
#define WRCONFIG_HWSEL      (1 << 31)

/* --- PORT registers ----------------------------------------------------- */

/* Direction register */
#define PORT_DIR(port)			MMIO32((port) + 0x0000)

/* Direction clear register */
#define PORT_DIRCLR(port)		MMIO32((port) + 0x0004)

/* Direction set register */
#define PORT_DIRSET(port)		MMIO32((port) + 0x0008)

/* Direction toggle register */
#define PORT_DIRTGL(port)		MMIO32((port) + 0x000c)

/* output register */
#define PORT_OUT(port)			MMIO32((port) + 0x0010)

/* output clear register */
#define PORT_OUTCLR(port)		MMIO32((port) + 0x0014)

/* output set register */
#define PORT_OUTSET(port)		MMIO32((port) + 0x0018)

/* output toggle register */
#define PORT_OUTTGL(port)		MMIO32((port) + 0x001c)

/* input register */
#define PORT_IN(port)			MMIO32((port) + 0x0020)

/* Control register */
#define PORT_CTRL(port)			MMIO32((port) + 0x0024)

/* Write configuration register */
#define PORT_WRCONFIG(port)		MMIO32((port) + 0x0028)

/* Peripheral multiplexing registers */
#define PORT_PMUX(port, n)		MMIO8((port) + 0x0030 + (n))

/* Pin configuration registers */
#define PORT_PINCFG(port, n)		MMIO8((port) + 0x0040 + (n))
