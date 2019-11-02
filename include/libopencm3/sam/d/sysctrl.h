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

#ifndef LIBOPENCM3_SYSCTRL_H
#define LIBOPENCM3_SYSCTRL_H

#include <libopencm3/sam/memorymap.h>

/* --- Convenience macros ------------------------------------------------ */
#define SYSCTRL				SYSCTRL_BASE

/* --- System Controller (SYSCTRL) registers --------------- */
#define SYSCTRL_INTENCLR			MMIO32(SYSCTRL_BASE + 0x00)
#define SYSCTRL_INTENSET			MMIO32(SYSCTRL_BASE + 0x04)
#define SYSCTRL_INTFLAG				MMIO32(SYSCTRL_BASE + 0x08)
#define SYSCTRL_PCLKSR				MMIO32(SYSCTRL_BASE + 0x0C)
#define SYSCTRL_XOSC				MMIO16(SYSCTRL_BASE + 0x10)
#define SYSCTRL_XOSC32K				MMIO16(SYSCTRL_BASE + 0x14)
#define SYSCTRL_OSC32K				MMIO32(SYSCTRL_BASE + 0x18)
#define SYSCTRL_OSCULP32K			MMIO8(SYSCTRL_BASE + 0x1C)
#define SYSCTRL_OSC8M				MMIO32(SYSCTRL_BASE + 0x20)
#define SYSCTRL_DFLLCTRL			MMIO16(SYSCTRL_BASE + 0x24)
#define SYSCTRL_DFLLVAL				MMIO32(SYSCTRL_BASE + 0x28)
#define SYSCTRL_DFLLMUL				MMIO32(SYSCTRL_BASE + 0x2C)
#define SYSCTRL_DFLLSYNC			MMIO8(SYSCTRL_BASE + 0x30)
#define SYSCTRL_BOD33				MMIO32(SYSCTRL_BASE + 0x34)
#define SYSCTRL_VREG				MMIO16(SYSCTRL_BASE + 0x3C)
#define SYSCTRL_VREF				MMIO32(SYSCTRL_BASE + 0x40)
#define SYSCTRL_DPLLCTRLA			MMIO8(SYSCTRL_BASE + 0x44)
#define SYSCTRL_DPLLRATIO			MMIO32(SYSCTRL_BASE + 0x48)
#define SYSCTRL_DPLLCTRLB			MMIO32(SYSCTRL_BASE + 0x4C)
#define SYSCTRL_DPLLSTATUS			MMIO8(SYSCTRL_BASE + 0x50)

/* Clock Status Register (SYSCTRL_PCLKSR), Read-only */
#define SYSCTRL_PCLKSR_XOSCRDY		(0x1 << 0)
#define SYSCTRL_PCLKSR_XOSC32KRDY	(0x1 << 1)
#define SYSCTRL_PCLKSR_OSC32KRDY	(0x1 << 2)
#define SYSCTRL_PCLKSR_OSC8MRDY		(0x1 << 3)
#define SYSCTRL_PCLKSR_DFLLRDY		(0x1 << 4)
#define SYSCTRL_PCLKSR_DFLLOOB		(0x1 << 5)
#define SYSCTRL_PCLKSR_DFLLLCKF		(0x1 << 6)
#define SYSCTRL_PCLKSR_DFLLLCKC		(0x1 << 7)

/* 32kHz External Crystal Oscillator (XOSC32K) Control, Read/Write */
#define SYSCTRL_XOSC32K_ENABLE		(0x1 << 1)
#define SYSCTRL_XOSC32K_XTALEN		(0x1 << 2)
#define SYSCTRL_XOSC32K_EN32K		(0x1 << 3)
#define SYSCTRL_XOSC32K_RUNSTDBY	(0x1 << 6)
#define SYSCTRL_XOSC32K_ONDEMAND	(0x1 << 7)

#define SYSCTRL_XOSC32K_STARTUP(T)	(((T) & 0x07) << 8)

/* 8MHz Internal Oscillator (OSC8M) Control, Read/Write */
#define SYSCTRL_OSC8M_ENABLE		(0x1 << 1)
#define SYSCTRL_OSC8M_RUNSTDBY		(0x1 << 6)
#define SYSCTRL_OSC8M_ONDEMAND		(0x1 << 7)

#define SYSCTRL_OSC8M_PRESC(P)		(((P) & 0x03) << 8)
#define SYSCTRL_OSC8M_CALIB(C)		(((C) & 0xFFF) << 16)
#define SYSCTRL_OSC8M_FREQ_RANGE(R)	(((R) & 0x03) << 30)

#define SYSCTRL_OSC8M_PRESC_MASK	(0x03 << 8)

/* DFLL48M Control (DFLLCTRL), Read/Write */
#define SYSCTRL_DFLLCTRL_ENABLE		(0x1 << 1)
#define SYSCTRL_DFLLCTRL_OPENLOOP	(0x0 << 2)
#define SYSCTRL_DFLLCTRL_CLOSEDLOOP	(0x1 << 2)
#define SYSCTRL_DFLLCTRL_USBCRM		(0x1 << 6)
#define SYSCTRL_DFLLCTRL_ONDEMAND	(0x1 << 7)
#define SYSCTRL_DFLLCTRL_WAITLOCK	(0x1 << 11)
#define SYSCTRL_DFLLCTRL_QLDIS		(0x1 << 9)

/* DFLL48M Multiplier (DFLLMUL), Read/Write */
#define SYSCTRL_DFLLMUL_CSTEP(C)	(((C) & 0x3F) << 26)
#define SYSCTRL_DFLLMUL_FSTEP(F)	(((F) & 0x3FF) << 16)
#define SYSCTRL_DFLLMUL_MUL(M)		((M) & 0xFFFF)

enum sysctrl_ll_mode {
	SYSCTRL_LL_OPEN_LOOP = 0,
	SYSCTRL_LL_CLOSED_LOOP,
};

enum sysctrl_osc8m_presc {
	SYSCTRL_OSC8M_PRESCALER_1X = 0,
	SYSCTRL_OSC8M_PRESCALER_2X,
	SYSCTRL_OSC8M_PRESCALER_4X,
	SYSCTRL_OSC8M_PRESCALER_8X,
};

BEGIN_DECLS

void sysctrl_enable_xosc32k(uint8_t startup_time);
void sysctrl_dfll_enable_ondemand(void);
void sysctrl_dfll_disable_ondemand(void);
void sysctrl_dfll_setup_multiplier(uint16_t coarse, uint16_t fine, uint16_t mul);
void sysctrl_dfll_enable(enum sysctrl_ll_mode mode, bool wait_lock, bool quick_lock);
void sysctrl_osc8m_set_prescaler(enum sysctrl_osc8m_presc presc);
void sysctrl_osc8m_enable_ondemand(void);
void sysctrl_osc8m_disable_ondemand(void);

END_DECLS

#endif
