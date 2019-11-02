/** @addtogroup nvmctrl
 *
 * @brief <b>Access functions for the SAMD Non Volatile Memory Controller (NVMCTRL)</b>
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

#include <libopencm3/sam/nvmctrl.h>

void nvmctrl_set_wait_states(uint8_t wait)
{
	NVMCTRL_CTRLB(NVMCTRL) = (NVMCTRL_CTRLB(NVMCTRL) & ~(NVMCTRL_RWS_MASK)) | (wait << 1);
}

void nvmctrl_enable_auto_write(void)
{
	NVMCTRL_CTRLB(NVMCTRL) &= ~(NVMCTRL_MANW);
}

void nvmctrl_disable_auto_write(void)
{
	NVMCTRL_CTRLB(NVMCTRL) |= NVMCTRL_MANW;
}
