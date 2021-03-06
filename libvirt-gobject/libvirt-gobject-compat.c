/*
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

#include <config.h>

#include "libvirt-gobject-compat.h"

GMutex *gvir_mutex_new(void)
{
    GMutex *mutex;

    mutex = g_new(GMutex, 1);
    g_mutex_init(mutex);

    return mutex;
}

void gvir_mutex_free(GMutex *mutex)
{
    g_mutex_clear(mutex);
    g_free(mutex);
}
