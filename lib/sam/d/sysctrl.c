/** @addtogroup sysctrl
 *
 * @brief <b>Access functions for the SAMD System Controller (SYSCTRL)</b>
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

#include <libopencm3/sam/sysctrl.h>

void sysctrl_enable_xosc32k(uint8_t startup_time)
{
	/* cf table 15.10 of product datasheet in chapter 15.8.6 */
	SYSCTRL_XOSC32K = SYSCTRL_XOSC32K_STARTUP(startup_time) |
					  SYSCTRL_XOSC32K_XTALEN | SYSCTRL_XOSC32K_EN32K;

	/* separate call, as described in chapter 15.6.3 */
	SYSCTRL_XOSC32K |= SYSCTRL_XOSC32K_ENABLE;

	while (!(SYSCTRL_PCLKSR & SYSCTRL_PCLKSR_XOSC32KRDY)) {
		/* Wait for oscillator stabilization */
	}
}

void sysctrl_osc8m_set_prescaler(enum sysctrl_osc8m_presc presc)
{
	uint32_t val = SYSCTRL_OSC8M;

	val &= ~(SYSCTRL_OSC8M_PRESC_MASK);
	val |= SYSCTRL_OSC8M_PRESC(presc);

	SYSCTRL_OSC8M = val;
}

void sysctrl_osc8m_enable_ondemand(void)
{
	SYSCTRL_OSC8M |= SYSCTRL_DFLLCTRL_ONDEMAND;
	while (!(SYSCTRL_PCLKSR & SYSCTRL_PCLKSR_OSC8MRDY)) {
		/* Wait for synchronization */
	}
}

void sysctrl_osc8m_disable_ondemand(void)
{
	SYSCTRL_OSC8M &= ~(SYSCTRL_DFLLCTRL_ONDEMAND);
	while (!(SYSCTRL_PCLKSR & SYSCTRL_PCLKSR_OSC8MRDY)) {
		/* Wait for synchronization */
	}
}

void sysctrl_dfll_enable_ondemand(void)
{
	SYSCTRL_DFLLCTRL |= SYSCTRL_DFLLCTRL_ONDEMAND;
	while (!(SYSCTRL_PCLKSR & SYSCTRL_PCLKSR_DFLLRDY)) {
		/* Wait for synchronization */
	}
}

void sysctrl_dfll_disable_ondemand(void)
{
	SYSCTRL_DFLLCTRL &= ~(SYSCTRL_DFLLCTRL_ONDEMAND);
	while (!(SYSCTRL_PCLKSR & SYSCTRL_PCLKSR_DFLLRDY)) {
		/* Wait for synchronization */
	}
}

void sysctrl_dfll_setup_multiplier(uint16_t coarse, uint16_t fine, uint16_t mul)
{
	SYSCTRL_DFLLMUL = SYSCTRL_DFLLMUL_CSTEP(coarse) |
					  SYSCTRL_DFLLMUL_FSTEP(fine) |
					  SYSCTRL_DFLLMUL_MUL(mul);

	while (!(SYSCTRL_PCLKSR & SYSCTRL_PCLKSR_DFLLRDY)) {
		/* Wait for synchronization */
	}
}

void sysctrl_dfll_enable(enum sysctrl_ll_mode mode, bool wait_lock, bool quick_lock)
{
	uint32_t val = SYSCTRL_DFLLCTRL;

	if (mode == SYSCTRL_LL_CLOSED_LOOP) {
		val |= SYSCTRL_DFLLCTRL_CLOSEDLOOP;
	} else {
		val &= ~(SYSCTRL_DFLLCTRL_CLOSEDLOOP);
	}

	if (wait_lock) {
		val |= SYSCTRL_DFLLCTRL_WAITLOCK;
	} else {
		val &= ~(SYSCTRL_DFLLCTRL_WAITLOCK);
	}

	if (quick_lock) {
		val &= ~(SYSCTRL_DFLLCTRL_QLDIS);
	} else {
		val |= SYSCTRL_DFLLCTRL_QLDIS;
	}

	/* Write full configuration to DFLL control register */
	SYSCTRL_DFLLCTRL = val; /* Disable Quick lock */

	while (!(SYSCTRL_PCLKSR & SYSCTRL_PCLKSR_DFLLRDY)) {
		/* Wait for synchronization */
	}

	/* Enable the DFLL */
	SYSCTRL_DFLLCTRL |= SYSCTRL_DFLLCTRL_ENABLE;

	while (!(SYSCTRL_PCLKSR & SYSCTRL_PCLKSR_DFLLLCKC) ||
		   !(SYSCTRL_PCLKSR & SYSCTRL_PCLKSR_DFLLLCKF))
	{
		/* Wait for locks flags */
	}

	while (!(SYSCTRL_PCLKSR & SYSCTRL_PCLKSR_DFLLRDY)) {
		/* Wait for synchronization */
	}
}
