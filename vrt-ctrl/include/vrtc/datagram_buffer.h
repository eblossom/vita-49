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
#ifndef INCLUDED_VRTC_DATAGRAM_BUFFER_H
#define INCLUDED_VRTC_DATAGRAM_BUFFER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <vrtc/send_datagram.h>  
#include <stdbool.h>

  struct datagram_buffer {
    // private:
    unsigned char		*buf;
    size_t			len;	// allocated length of buf
    size_t			nused;	// # of bytes used

    send_datagram_t		send;	// function to send a datagram
    send_datagram_handle_t	handle;	// first arg for send
  };
  typedef struct datagram_buffer datagram_buffer_t;

  void datagram_buffer_init(datagram_buffer_t *self,
			    void *buf, size_t len,
			    send_datagram_t send,
			    send_datagram_handle_t handle);

  bool datagram_buffer_ensure_room(datagram_buffer_t *self, size_t needed);
  bool datagram_buffer_write(datagram_buffer_t *self, const void *buf, size_t size);
  bool datagram_buffer_flush(datagram_buffer_t *self);


#ifdef __cplusplus
}
#endif
#endif /* INCLUDED_VRTC_DATAGRAM_BUFFER_H */
