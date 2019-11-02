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

#ifndef LIBOPENCM3_GPIO_H
#define LIBOPENCM3_GPIO_H

#include <libopencm3/sam/memorymap.h>
#include <libopencm3/sam/common/gpio_common_all.h>

/* flags may be or'd together, but only contain one of
 * GPINPUT, GPOUTPUT and PERIPHx and one of
 * GPIO_FLAG_GPOUTLO and GPIO_FLAG_GPOUTHI */
enum gpio_flags {
	GPIO_FLAG_GPINPUT = 0,
	GPIO_FLAG_GPOUTPUT = 1,
	GPIO_FLAG_PERIPHA = 2,
	GPIO_FLAG_PERIPHB = 3,
	GPIO_FLAG_PERIPHC = 4,
	GPIO_FLAG_PERIPHD = 5,
	GPIO_FLAG_PERIPHE = 6,
	GPIO_FLAG_PERIPHF = 7,
	GPIO_FLAG_PERIPHG = 8,
	GPIO_FLAG_PERIPHH = 9,
	GPIO_FLAG_PERIPHI = 10,
	GPIO_FLAG_PULL_UP = (1 << 4),
	GPIO_FLAG_DRVSTRG = (1 << 5),
	GPIO_FLAG_GPOUTLO = (1 << 6),
	GPIO_FLAG_GPOUTHI = (1 << 7),
};

#define GPIO0			(1 << 0)
#define GPIO1			(1 << 1)
#define GPIO2			(1 << 2)
#define GPIO3			(1 << 3)
#define GPIO4			(1 << 4)
#define GPIO5			(1 << 5)
#define GPIO6			(1 << 6)
#define GPIO7			(1 << 7)
#define GPIO8			(1 << 8)
#define GPIO9			(1 << 9)
#define GPIO10			(1 << 10)
#define GPIO11			(1 << 11)
#define GPIO12			(1 << 12)
#define GPIO13			(1 << 13)
#define GPIO14			(1 << 14)
#define GPIO15			(1 << 15)
#define GPIO16			(1 << 16)
#define GPIO17			(1 << 17)
#define GPIO18			(1 << 18)
#define GPIO19			(1 << 19)
#define GPIO20			(1 << 20)
#define GPIO21			(1 << 21)
#define GPIO22			(1 << 22)
#define GPIO23			(1 << 23)
#define GPIO24			(1 << 24)
#define GPIO25			(1 << 25)
#define GPIO26			(1 << 26)
#define GPIO27			(1 << 27)
#define GPIO28			(1 << 28)
#define GPIO29			(1 << 29)
#define GPIO30			(1 << 30)
#define GPIO31			(1 << 31)


BEGIN_DECLS

void gpio_init(uint32_t gpioport, uint32_t pins, enum gpio_flags flags);
bool gpio_get(uint32_t gpioport, uint32_t gpios);
void gpio_disable(uint32_t gpioport, uint32_t gpios);

END_DECLS

#endif
