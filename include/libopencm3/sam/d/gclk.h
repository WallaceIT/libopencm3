/*
 * This file is part of the libopencm3 project.
 *
 * Copyright (C) 2019 Francesco Valla <valla.francesco@gmail.com>
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

#ifndef LIBOPENCM3_GCLK_H
#define LIBOPENCM3_GCLK_H

#include <libopencm3/sam/memorymap.h>

/* --- Convenience macros ------------------------------------------------ */
#define GCLK				GCLK_BASE

/* --- Generic Clock Controller (GCLK) registers --------------- */
#define GCLK_CTRL					MMIO8(GCLK_BASE + 0x00)
#define GCLK_STATUS					MMIO8(GCLK_BASE + 0x01)
#define GCLK_CLKCTRL				MMIO16(GCLK_BASE + 0x02)
#define GCLK_GENCTRL				MMIO32(GCLK_BASE + 0x04)
#define GCLK_GENDIV					MMIO32(GCLK_BASE + 0x08)


/* Generic Clock Controller Control Register (GCLK_CTRL), Read/Write */
#define GCLK_CTRL_SWRST				(0x1 << 0)

/* Generic Clock Controller Status Register (GCLK_STATUS), Read-only */
#define GCLK_STATUS_SYNCBUSY		(0x1 << 7)

/* Generic Clock Control Register (GCLK_CLKCTRL), Read/Write */
#define GCLK_CLKCTRL_ID(I)			((I) & 0x3F)
#define GCLK_CLKCTRL_GEN(G)			(((G) & 0xF) << 8)
#define GCLK_CLKCTRL_CLKEN			(0x1 << 14)
#define GCLK_CLKCTRL_WRTLOCK		(0x1 << 15)

/* Generic Clock Generator Control Register (GCLK_GENCTRL), Read/Write */
#define GCLK_GENCTRL_ID(I)			((I) & 0xF)
#define GCLK_GENCTRL_SRC(S)			(((S) & 0x1F) << 8)
#define GCLK_GENCTRL_GENEN			(0x1 << 16)
#define GCLK_GENCTRL_IDC			(0x1 << 17)
#define GCLK_GENCTRL_OOV			(0x1 << 18)
#define GCLK_GENCTRL_OE				(0x1 << 19)
#define GCLK_GENCTRL_DIVSEL			(0x1 << 20)
#define GCLK_GENCTRL_RUNSTBY		(0x1 << 21)

/* Generic Clock Generator Division Register (GCLK_GENDIV), Read/Write */
#define GCLK_GENDIV_ID(I)			((I) & 0xF)
#define GCLK_GENDIV_DIV(D)			(((D) & 0xFF) << 8)

/* Generic Clock ID */
enum gclk_id {
	GCLK_DFLL48M_REF = 0x00,
	GCLK_DPLL,
	GCLK_DPLL_32K,
	GCLK_WDT,
	GCLK_RTC,
	GCLK_EIC,
	GCLK_USB,
	GCLK_EVSYS_CHANNEL_0,
	GCLK_EVSYS_CHANNEL_1,
	GCLK_EVSYS_CHANNEL_2,
	GCLK_EVSYS_CHANNEL_3,
	GCLK_EVSYS_CHANNEL_4,
	GCLK_EVSYS_CHANNEL_5,
	GCLK_EVSYS_CHANNEL_6,
	GCLK_EVSYS_CHANNEL_7,
	GCLK_EVSYS_CHANNEL_8,
	GCLK_EVSYS_CHANNEL_9,
	GCLK_EVSYS_CHANNEL_10,
	GCLK_EVSYS_CHANNEL_11,
	GCLK_SERCOMx_SLOW,
	GCLK_SERCOM0_CORE,
	GCLK_SERCOM1_CORE,
	GCLK_SERCOM2_CORE,
	GCLK_SERCOM3_CORE,
	GCLK_SERCOM4_CORE,
	GCLK_SERCOM5_CORE,
	GCLK_TCC0,
	GCLK_TCC1 = GCLK_TCC0,
	GCLK_TCC2,
	GCLK_TC3 = GCLK_TCC2,
	GCLK_TC4,
	GCLK_TC5 = GCLK_TC4,
	GCLK_TC6,
	GCLK_TC7 = GCLK_TC6,
	GCLK_ADC,
	GCLK_AC_DIG,
	GCLK_AC1_DIG = GCLK_AC_DIG,
	GCLK_AC_ANA,
	GCLK_AC1_ANA = GCLK_AC_ANA,
	GCLK_DAC,
	GCLK_PTC,
	GCLK_I2S_0,
	GCLK_I2S_1,
	GCLK_TCC3,
};

/* Generic Clock Source */
enum gclk_src {
	GCLK_SRC_XOSC,
	GCLK_SRC_GCLKIN,
	GCLK_SRC_GCLKGEN1,
	GCLK_SRC_OSCULP32K,
	GCLK_SRC_OSC32K,
	GCLK_SRC_XOSC32K,
	GCLK_SRC_OSC8M,
	GCLK_SRC_DFLL48M,
	GCLK_SRC_FDPLL96M,
};

enum generic_clock {
	GENERIC_CLOCK0 = 0,
	GENERIC_CLOCK1,
	GENERIC_CLOCK2,
	GENERIC_CLOCK3,
	GENERIC_CLOCK4,
	GENERIC_CLOCK5,
	GENERIC_CLOCK6,
	GENERIC_CLOCK7,
	GENERIC_CLOCK8,
};

enum gclk_opt {
	GCLK_OPT_NONE = 0,
	GCLK_OPT_IDC = (1 << 0),
	GCLK_OPT_OOV = (1 << 1),
	GCLK_OPT_OE = (1 << 2),
	GCLK_OPT_DIVSEL = (1 << 3),
	GCLK_OPT_RUNSTDBY = (1 << 4),
};

BEGIN_DECLS

void gclk_swreset(void);
void gclk_enable_gclk(enum generic_clock gclk, enum gclk_src source_clock,
					  uint16_t div, enum gclk_opt opts);
void gclk_route_gclk(enum generic_clock gclk, enum gclk_id clk);

END_DECLS

#endif
