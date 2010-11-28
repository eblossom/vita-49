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
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include "handle_op.h"
#include "resolve_resource.h"
#include <vrtc/device_prims.h>

#define VERBOSE 1

void
handle_get(datagram_buffer_t *dgbuf, int inv_id, Expr_t *path)
{
  op_info_t	oi;
  init_op_info(&oi, dgbuf, opGET, inv_id, path);
  resolve_resource(&oi);
}

void
handle_get_meta(datagram_buffer_t *dgbuf, int inv_id, Expr_t *path)
{
  op_info_t	oi;
  init_op_info(&oi, dgbuf, opGET_META, inv_id, path);
  resolve_resource(&oi);
}

void
handle_put(datagram_buffer_t *dgbuf, int inv_id, Expr_t *path,
	   Expr_t *value, Expr_t *when)
{
  op_info_t	oi;
  init_op_info(&oi, dgbuf, opPUT, inv_id, path);
  oi.value = value;
  oi.when = when;
  resolve_resource(&oi);
}
