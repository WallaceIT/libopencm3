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

#ifndef LIBOPENCM3_NVMCTRL_H
#define LIBOPENCM3_NVMCTRL_H

#include <libopencm3/sam/memorymap.h>

/* --- Convenience macros ------------------------------------------------ */
#define NVMCTRL				NVMCTRL_BASE

/* --- Non Volatile Memory Controller (NVMCTRL) registers --------------- */
#define NVMCTRL_CTRLA(port)			MMIO32((port) + 0x00)
#define NVMCTRL_CTRLB(port)			MMIO32((port) + 0x04)
#define NVMCTRL_PARAM(port)			MMIO32((port) + 0x08)
#define NVMCTRL_NTENCLR(port)		MMIO32((port) + 0x0C)
#define NVMCTRL_INTENSET(port)		MMIO32((port) + 0x10)
#define NVMCTRL_INTFLAG(port)		MMIO32((port) + 0x14)
#define NVMCTRL_STATUS(port)		MMIO32((port) + 0x18)
#define NVMCTRL_ADDR(port)			MMIO32((port) + 0x1C)
#define NVMCTRL_LOCK(port)			MMIO32((port) + 0x20)

/* NVMCTRL Control B Register (NVMCTRL_CTRLB) */
#define NVMCTRL_RWS_MASK			(0xF << 1)
#define NVMCTRL_MANW				(0x1 << 7)

BEGIN_DECLS

void nvmctrl_set_wait_states(uint8_t wait);
void nvmctrl_enable_auto_write(void);
void nvmctrl_disable_auto_write(void);

END_DECLS

#endif
