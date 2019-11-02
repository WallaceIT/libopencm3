/** @addtogroup pm
 *
 * @brief <b>Access functions for the SAMD Power Manager (PM)</b>
 * @ingroup SAMD
 * LGPL License Terms @ref lgpl_license
 * @author @htmlonly &copy; @endhtmlonly 2019
 * Francesco Valla <valla.francesco@gmail.com>
 *
 */

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

#include <libopencm3/sam/pm.h>

void pm_enable_clock_div(enum pm_cksel sel_target, uint8_t div)
{
	PM_INTFLAG = PM_INTFLAG_CLEAR;

	uint32_t reg = (div & PM_CKSEL_MASK);
	PM_CKSEL(sel_target) = reg;

	while (!(PM_INTFLAG & PM_INTFLAG_CKRDY)) {
		/* wait for clock ready */
	}
	PM_INTFLAG = PM_INTFLAG_CLEAR;
}

static void set_peripheral_clock_status(enum pm_peripheral periph, bool on)
{
	uint8_t reg_id = periph/32;
	uint8_t bit_offset = periph % 32;
	uint32_t reg_mask = PM_MASK(reg_id);
	if (on) {
		reg_mask |= (1 << bit_offset);
	} else {
		reg_mask &= ~(1 << bit_offset);
	}
	PM_MASK(reg_id) = reg_mask;
}

void pm_enable_peripheral_clock(enum pm_peripheral periph)
{
	set_peripheral_clock_status(periph, true);
}

void pm_disable_peripheral_clock(enum pm_peripheral periph)
{
	set_peripheral_clock_status(periph, false);
}
