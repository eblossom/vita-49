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
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef INCLUDED_RESOLVE_RESOURCE_H
#define INCLUDED_RESOLVE_RESOURCE_H

#include <vrtc/expr.h>
#include <vrtc/datagram_buffer.h>

typedef enum {
  opGET, opGET_META, opPUT
} op_code_t;

typedef struct {
  datagram_buffer_t	*dgbuf;
  op_code_t		op_code;
  int			inv_id;
  Expr_t		*path;
  Expr_t		*value;
  Expr_t		*when;
} op_info_t;

static inline void
init_op_info(op_info_t *oi, datagram_buffer_t *dgbuf,
	     op_code_t op_code, int inv_id, Expr_t *path)
{
  oi->dgbuf = dgbuf;
  oi->op_code = op_code;
  oi->inv_id = inv_id;
  oi->path = path;
  oi->value = 0;
  oi->when = 0;
}

/*!
 * \brief Find the specified resource if it exists, and apply
 *  the given operation and arguments.
 *
 * This takes care of generating and sending the result or error information.
 */
void
resolve_resource(op_info_t *oi);

#endif /* INCLUDED_RESOLVE_RESOURCE_H */
