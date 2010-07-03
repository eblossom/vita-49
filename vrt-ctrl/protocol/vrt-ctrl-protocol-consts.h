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

/* protocol-msg constants */

#define vrtc_CALL	0
#define	vrtc_REPLY	1
#define	vrtc_ERROR	2
#define vrtc_REJECT	3
#define vrtc_NOTE	4

/* opcode-and-args constants */

#define vrtc_GET	0
#define	vrtc_GET_META	1
#define vrtc_PUT	2

/* note-kind constants */

#define	vrtc_DEBUG_OUTPUT	0
#define vrtc_TX_UNDERRUN	1
#define	vrtc_RX_OVERRUN		2
#define vrtc_INTERNAL_ERROR	3

#define	vrtc_VENDOR_NOTE	1024
