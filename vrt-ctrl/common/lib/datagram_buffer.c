/* -*- c -*- */
/*
 * Copyright 2010 Free Software Foundation, Inc.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <vrtc/datagram_buffer.h>
#include <string.h>

bool 
datagram_buffer_ensure_room(datagram_buffer_t *self, size_t needed)
{
  if (needed > self->len)	// will never fit
    return false;

  if (needed > self->len - self->nused)
    datagram_buffer_flush(self);

  return true;
}

bool 
datagram_buffer_write(datagram_buffer_t *self, const void *buf, size_t size)
{
  if (!datagram_buffer_ensure_room(self, size))
    return false;

  memcpy(&self->buf[self->nused], buf, size);
  self->nused += size;
  if (self->nused == self->len)
    datagram_buffer_flush(self);

  return true;
}

bool 
datagram_buffer_flush(datagram_buffer_t *self)
{
  if (self->nused > 0){
    self->send(self->handle, self->buf, self->nused);
    self->nused = 0;
  }
  return true;
}

void
datagram_buffer_init(datagram_buffer_t *self, void *buf, size_t len,
		     send_datagram_t send, send_datagram_handle_t handle)
{
  memset(self, 0, sizeof(*self));
  self->buf = buf;
  self->len = len;
  self->nused = 0;
  self->send = send;
  self->handle = handle;
}
