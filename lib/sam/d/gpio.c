/** @addtogroup gpio_defines
 *
 * @brief <b>Access functions for the SAMD I/O Controller</b>
 * @ingroup SAMD
 * LGPL License Terms @ref lgpl_license
 * @author @htmlonly &copy; @endhtmlonly 2019
 * Francesco Valla <valla.francesco@gmail.com>
 *
 */
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

#include <libopencm3/sam/gpio.h>
#include <libopencm3/sam/d/port.h>

/** @brief Initialize GPIO pins
 *
 * @param[in] port uint32_t: GPIO Port base address
 * @param[in] pins uint32_t: Mask of pins to be set
 * @param[in] flags enum gpio_flags
 */
void gpio_init(uint32_t port, uint32_t pins, enum gpio_flags flags)
{
	uint32_t wrconfig = WRCONFIG_WRPINCFG;
	uint8_t i = 0;

	switch (flags & 0xF) {
	case GPIO_FLAG_GPINPUT:
		PORT_DIRCLR(port) = pins;
		wrconfig |= WRCONFIG_INEN;
		break;
	case GPIO_FLAG_GPOUTPUT:
		if (flags & GPIO_FLAG_GPOUTLO) {
			PORT_OUTCLR(port) = pins;
		} else if (flags & GPIO_FLAG_GPOUTHI) {
			PORT_OUTSET(port) = pins;
		}
		PORT_DIRSET(port) = pins;
		break;
	case GPIO_FLAG_PERIPHA:
		wrconfig |= WRCONFIG_MUXEN | WRCONFIG_WRPINMUX | WRCONFIG_PMUXA;
		break;
	case GPIO_FLAG_PERIPHB:
		wrconfig |= WRCONFIG_MUXEN | WRCONFIG_WRPINMUX | WRCONFIG_PMUXB;
		break;
	case GPIO_FLAG_PERIPHC:
		wrconfig |= WRCONFIG_MUXEN | WRCONFIG_WRPINMUX | WRCONFIG_PMUXC;
		break;
	case GPIO_FLAG_PERIPHD:
		wrconfig |= WRCONFIG_MUXEN | WRCONFIG_WRPINMUX | WRCONFIG_PMUXD;
		break;
	case GPIO_FLAG_PERIPHE:
		wrconfig |= WRCONFIG_MUXEN | WRCONFIG_WRPINMUX | WRCONFIG_PMUXE;
		break;
	case GPIO_FLAG_PERIPHF:
		wrconfig |= WRCONFIG_MUXEN | WRCONFIG_WRPINMUX | WRCONFIG_PMUXF;
		break;
	case GPIO_FLAG_PERIPHG:
		wrconfig |= WRCONFIG_MUXEN | WRCONFIG_WRPINMUX | WRCONFIG_PMUXG;
		break;
	case GPIO_FLAG_PERIPHH:
		wrconfig |= WRCONFIG_MUXEN | WRCONFIG_WRPINMUX | WRCONFIG_PMUXH;
		break;
	case GPIO_FLAG_PERIPHI:
		wrconfig |= WRCONFIG_MUXEN | WRCONFIG_WRPINMUX | WRCONFIG_PMUXI;
		break;
	default:
		break;
	}

	if (flags & GPIO_FLAG_PULL_UP) {
		wrconfig |= WRCONFIG_PULLEN;
	}

	if ((pins & 0x0000FFFF) != 0) {
		PORT_WRCONFIG(port) = (wrconfig | (pins & 0x0000FFFF));
	}

	if ((pins & 0xFFFF0000) != 0) {
		PORT_WRCONFIG(port) = (wrconfig | (pins >> 16) | WRCONFIG_HWSEL);
	}

	if (flags & GPIO_FLAG_DRVSTRG) {
		for (i = 0; i < 32; i++) {
			if (pins & (1 << i)) {
				PORT_PINCFG(port, i) |= PINCFG_STRONG;
			}
		}
	}
}

/** @brief Atomic set output
 *
 * @param[in] gpioport uint32_t: GPIO Port base address
 * @param[in] gpios uint32_t
 */
void gpio_set(uint32_t gpioport, uint32_t gpios)
{
	PORT_OUTSET(gpioport) = gpios;
}

/** @brief Atomic clear output
 *
 * @param[in] gpioport uint32_t: GPIO Port base address
 * @param[in] gpios uint32_t
 */
void gpio_clear(uint32_t gpioport, uint32_t gpios)
{
	PORT_OUTCLR(gpioport) = gpios;
}

/** @brief Atomic toggle output
 *
 * @param[in] gpioport uint32_t: GPIO Port base address
 * @param[in] gpios uint32_t
 */
void gpio_toggle(uint32_t gpioport, uint32_t gpios)
{
	PORT_OUTTGL(gpioport) = gpios;
}

/** @brief Get GPIO level
 *
 * @param[in] gpioport uint32_t: GPIO Port base address
 * @param[in] gpios uint32_t
 */
bool gpio_get(uint32_t gpioport, uint32_t gpios)
{
	return !!(PORT_IN(gpioport) & gpios);
}

/** @brief Disable pins.
 *
 * Only the ones where bits are set to "1" are touched, everything else
 * remains in the old state.
 *
 * @param[in] gpioport uint32_t: GPIO Port base address
 * @param[in] gpios uint32_t
 */
void gpio_disable(uint32_t gpioport, uint32_t gpios)
{
	PORT_DIRCLR(gpioport) = gpios;
	uint8_t i = 0;
	for (i = 0; i < 32; i++) {
		if (gpios & (1 << i))
			PORT_PINCFG(gpioport, i) = 0;
	}
}
