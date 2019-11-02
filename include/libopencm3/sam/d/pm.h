/*
 * This file is part of the libopencm3 project.
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

#ifndef LIBOPENCM3_PM_H
#define LIBOPENCM3_PM_H

#include <libopencm3/sam/memorymap.h>

/* --- Power Manager (PM) registers ----------------------- */

/* Control, Read/Write */
#define PM_CTRL				MMIO8(PM_BASE + 0x00)

/* Sleep, Read/Write */
#define PM_SLEEP			MMIO8(PM_BASE + 0x01)

/* CPU & PBx Clock Select, Read/Write */
#define PM_CKSEL(I)			MMIO8(PM_BASE + 0x08 + (I))

/* AHB & PBx Clock Mask, Read/Write */
#define PM_MASK(I)			MMIO32(PM_BASE + 0x14 + (0x04) * (I))

/* Interrupt Enable Clear Register INTENCLR Write-only */
#define PM_INTENCLR			MMIO8(PM_BASE + 0x34)

/* Interrupt Enable Set Register INTENSET Write-only */
#define PM_INTENSET			MMIO8(PM_BASE + 0x35)

/* Interrupt Flag Status Register INTFLAG Read-only */
#define PM_INTFLAG			MMIO8(PM_BASE + 0x36)

/* Reset Cause Register RCAUSE Read-only */
#define PM_RCAUSE			MMIO8(PM_BASE + 0x38)


/* --- Register contents --------------------------------------------------- */

#define PM_CKSEL_MASK			(0x7)

#define PM_INTFLAG_CKRDY		(0x1)
#define PM_INTFLAG_CLEAR		(PM_INTFLAG_CKRDY)

enum pm_cksel {
	PM_CKSEL_CPU = 0,
	PM_CKSEL_PBA,
	PM_CKSEL_PBB,
	PM_CKSEL_PBC,
};

/*
 * Ids are designed such that
 * PM_MASK(id/32) = (1 << id % 32)
 * would enable the peripheral clock.
 */
enum pm_peripheral {
	PM_PERIPHERAL_HPB0 = 0,
	PM_PERIPHERAL_HPB1,
	PM_PERIPHERAL_HPB2,
	PM_PERIPHERAL_HPB_DSU,
	PM_PERIPHERAL_HPB_NVMCTRL,
	PM_PERIPHERAL_HPB_DMAC,
	PM_PERIPHERAL_HPB_USB,
	PM_PERIPHERAL_PAC0 = 32,
	PM_PERIPHERAL_PM,
	PM_PERIPHERAL_SYSCTRL,
	PM_PERIPHERAL_GCLK,
	PM_PERIPHERAL_WDT,
	PM_PERIPHERAL_RTC,
	PM_PERIPHERAL_EIC,
	PM_PERIPHERAL_PAC1 = 64,
	PM_PERIPHERAL_DSU,
	PM_PERIPHERAL_NVMCTRL,
	PM_PERIPHERAL_PORT,
	PM_PERIPHERAL_DMAC,
	PM_PERIPHERAL_USB,
	PM_PERIPHERAL_PAC2 = 96,
	PM_PERIPHERAL_EVSYS,
	PM_PERIPHERAL_SERCOM0,
	PM_PERIPHERAL_SERCOM1,
	PM_PERIPHERAL_SERCOM2,
	PM_PERIPHERAL_SERCOM3,
	PM_PERIPHERAL_SERCOM4,
	PM_PERIPHERAL_SERCOM5,
	PM_PERIPHERAL_TCC0,
	PM_PERIPHERAL_TCC1,
	PM_PERIPHERAL_TCC2,
	PM_PERIPHERAL_TC3,
	PM_PERIPHERAL_TC4,
	PM_PERIPHERAL_TC5,
	PM_PERIPHERAL_TC6,
	PM_PERIPHERAL_TC7,
	PM_PERIPHERAL_ADC,
	PM_PERIPHERAL_AC,
	PM_PERIPHERAL_DAC,
	PM_PERIPHERAL_PTC,
	PM_PERIPHERAL_I2S,
	PM_PERIPHERAL_AC1,
	PM_PERIPHERAL_TCC3 = 120,

};

BEGIN_DECLS

void pm_enable_clock_div(enum pm_cksel sel_target, uint8_t div);
void pm_enable_peripheral_clock(enum pm_peripheral periph);
void pm_disable_peripheral_clock(enum pm_peripheral periph);

END_DECLS

#endif
