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

#include <vrtc/device_prims.h>
#include <vrtc/protocol-consts.h>

/* Routines used only by device code */

Expr_t *
vrtc_make_reply(int invocation_id, Expr_t *v)
{
  return expr_make_seq3(expr_make_int(vrtc_REPLY),
			expr_make_int(invocation_id),
			v);
}

Expr_t *
vrtc_make_error(int invocation_id, int error_code, Expr_t *error_arg)
{
  return expr_make_seq3(expr_make_int(vrtc_ERROR),
			expr_make_int(invocation_id),
			vrtc_make_error_info2(error_code, error_arg));
}

Expr_t *
vrtc_make_reject(int error_code)
{
  return expr_make_seq2(expr_make_int(vrtc_REJECT),
			vrtc_make_error_info(error_code));
}

Expr_t *
vrtc_make_reject2(int error_code, Expr_t *error_arg)
{
  return expr_make_seq2(expr_make_int(vrtc_REJECT),
			vrtc_make_error_info2(error_code, error_arg));
}


Expr_t *
vrtc_make_note(int note_kind, Expr_t *note_arg)
{
  return expr_make_seq3(expr_make_int(vrtc_NOTE),
			expr_make_int(note_kind),
			note_arg);
}

Expr_t *
vrtc_make_error_info(int error_code)
{
   return vrtc_make_error_info2(error_code, expr_make_null());
}

Expr_t *
vrtc_make_error_info2(int error_code, Expr_t *error_arg)
{
  return expr_make_seq2(expr_make_int(error_code), error_arg);
}

