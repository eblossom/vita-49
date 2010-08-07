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

#include <vrtc/host_prims.h>
#include <vrtc/protocol-consts.h>

/* Routines used only by host code */

static Expr_t *
_vrtc_make_call(int invocation_id, Expr_t *opcode_and_args)
{
  return expr_make_seq3(expr_make_int(vrtc_CALL),
			expr_make_int(invocation_id),
			opcode_and_args);
}

static Expr_t *
_vrtc_make_get_helper(int invocation_id, const char *path, int opcode)
{
  return _vrtc_make_call(invocation_id, 
			 expr_make_seq2(expr_make_int(opcode),
					expr_make_cstring(path)));
}

Expr_t *
vrtc_make_get(int invocation_id, const char *path)
{
  return _vrtc_make_get_helper(invocation_id, path, vrtc_GET);
}

Expr_t *
vrtc_make_get_meta(int invocation_id, const char *path)
{
  return _vrtc_make_get_helper(invocation_id, path, vrtc_GET_META);
}

Expr_t *
vrtc_make_put(int invocation_id, const char *path, Expr_t *v)
{
  return _vrtc_make_call(invocation_id, 
			 expr_make_seq3(expr_make_int(vrtc_PUT),
					expr_make_cstring(path),
					v));
}
