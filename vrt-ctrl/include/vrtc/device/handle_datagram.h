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
#ifndef INCLUDED_VRTC_DEVICE_HANDLE_DATAGRAM_H
#define INCLUDED_VRTC_DEVICE_HANDLE_DATAGRAM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>	/* size_t */

  typedef void *send_datagram_handle_t;
  /* Pointer to function that will send a datagram reply */
  typedef void (*send_datagram_t)(send_datagram_handle_t handle,
				  const void *buf, size_t len);

  /*
   * \brief Entry point to device control protocol handler.
   *
   * \param[in] buf contains the incoming datagram
   * \param[in] len is the length of \p buf
   * \param[in] send is used to send one or more reply datagrams
   * \param[in] handle is the first argument to \p send
   * \param[in] is the maximum number of bytes which may be sent in one call
   */
  void vrtcd_handle_incoming_datagram(void *buf, size_t len,
				      send_datagram_t send, send_datagram_handle_t handle,
				      size_t max_send_len);
			  

#ifdef __cplusplus
}
#endif

#endif /* INCLUDED_VRTC_DEVICE_HANDLE_DATAGRAM_H */
