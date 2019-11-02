/** @addtogroup gclk
 *
 * @brief <b>Access functions for the SAMD Generic Clock Controller (GCLK)</b>
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
 * along with this library. If not, see <http://www.gnu.org/licenses/>.
 */
#include <libopencm3/sam/gclk.h>

/** @brief Reset Generic Clock Controller
 */
void gclk_swreset(void)
{
	GCLK_CTRL = GCLK_CTRL_SWRST;

	while ((GCLK_CTRL & GCLK_CTRL_SWRST) && (GCLK_STATUS & GCLK_STATUS_SYNCBUSY)) {
		/* Wait for reset to complete */
	}
}

/** @brief Configure and enable Generic Clock
 *
 *	@param[in] gclk enum generic_clock: Generic Clock to configure and enable.
 *	@param[in] source_clock enum gclk_src: Source Clock for this Generic Clock.
 *	@param[in] div uint16_t: Division Factor. If 0, clock is undivided.
 *	@param[in] opts enum gclk_opt: Additional options for the Genric Clock Generator.
 */
void gclk_enable_gclk(enum generic_clock gclk, enum gclk_src source_clock,
					  uint16_t div, enum gclk_opt opts)
{
	GCLK_GENDIV = GCLK_GENDIV_ID(gclk) | GCLK_GENDIV_DIV(div);
	while (GCLK_STATUS & GCLK_STATUS_SYNCBUSY) {
		/* Wait for synchronization */
	}

	uint32_t gen_val = GCLK_GENCTRL_ID(gclk) |
					   GCLK_GENCTRL_SRC(source_clock) |
					   GCLK_GENCTRL_GENEN;

	if (opts & GCLK_OPT_IDC) {
		gen_val |= GCLK_GENCTRL_IDC;
	}

	if (opts & GCLK_OPT_OOV) {
		gen_val |= GCLK_GENCTRL_OOV;
	}

	if (opts & GCLK_OPT_OE) {
		gen_val |= GCLK_GENCTRL_OE;
	}

	if (opts & GCLK_OPT_DIVSEL) {
		gen_val |= GCLK_GENCTRL_DIVSEL;
	}

	if (opts & GCLK_OPT_RUNSTDBY) {
		gen_val |= GCLK_GENCTRL_RUNSTBY;
	}

	/* Write Generic Clock Generator configuration */
	GCLK_GENCTRL = gen_val;
	while (GCLK_STATUS & GCLK_STATUS_SYNCBUSY) {
		/* Wait for synchronization */
	}
}

/** @brief Route Generic Clock
 *
 *	@param[in] gclk enum generic_clock: Generic Clock to configure and enable.
 *	@param[in] clk enum gclk_id: Target Clock for this Generic Clock.
 */
void gclk_route_gclk(enum generic_clock gclk, enum gclk_id clk)
{
	GCLK_CLKCTRL = GCLK_CLKCTRL_ID(clk) |
				   GCLK_CLKCTRL_GEN(gclk) |
				   GCLK_CLKCTRL_CLKEN ;

	while (GCLK_STATUS & GCLK_STATUS_SYNCBUSY) {
		/* Wait for synchronization */
	}
}
