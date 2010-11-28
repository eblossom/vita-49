/* -*- c -*- */
/*
 * Copyright 2010 Free Software Foundation, Inc.
 * 
 * This file is part of GNU Radio
 * 
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#ifndef INCLUDED_HANDLE_OP_H
#define INCLUDED_HANDLE_OP_H

#include <vrtc/expr.h>
#include <vrtc/datagram_buffer.h>

/* path is known to be a string */
void handle_get(datagram_buffer_t *dgbuf, int inv_id, Expr_t *path);

/* path is known to be a string */
void handle_get_meta(datagram_buffer_t *dgbuf, int inv_id, Expr_t *path);

/* path is known to be a string */
void handle_put(datagram_buffer_t *dgbuf,
		int inv_id, Expr_t *path, Expr_t *value, Expr_t *when);

#endif /* INCLUDED_HANDLE_OP_H */
