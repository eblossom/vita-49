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
#include <vrtc/device_prims.h>

#define VERBOSE 1

void
handle_get(int inv_id, Expr_t *path, datagram_buffer_t *dgbuf)
{
  if (VERBOSE){
    printf("handle_get: ");
    expr_print(path);
    printf("\n");
  }

  expr_encode_and_free(vrtc_make_reply(inv_id,
				       expr_make_seq3(expr_make_cstring("abc"),
						      expr_make_cstring("def"),
						      expr_make_cstring("ghi"))),
		       dgbuf);
}

void
handle_get_meta(int inv_id, Expr_t *path, datagram_buffer_t *dgbuf)
{
  if (VERBOSE){
    printf("handle_get_meta: ");
    expr_print(path);
    printf("\n");
  }
}

void
handle_put(int inv_id, Expr_t *path, Expr_t *value, datagram_buffer_t *dgbuf)
{
  if (VERBOSE){
    printf("handle_put: ");
    expr_print(path);
    printf(" ");
    expr_print(value);
    printf("\n");
  }
}
