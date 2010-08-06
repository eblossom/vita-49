/* -*- c++ -*- */
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
#ifndef INCLUDED_VRTC_DEVICE_PRIMS_H
#define INCLUDED_VRTC_DEVICE_PRIMS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <vrtc/expr.h>

Expr_t *vrtc_make_reply(int invocation_id, Expr_t *v);
Expr_t *vrtc_make_error(int invocation_id, int error_code, Expr_t *error_arg);
Expr_t *vrtc_make_reject(int error_code);
Expr_t *vrtc_make_reject2(int error_code, Expr_t *error_arg);
Expr_t *vrtc_make_note(int note_kind, Expr_t *note_arg);

Expr_t *vrtc_make_error_info(int error_code);
Expr_t *vrtc_make_error_info2(int error_code, Expr_t *error_arg);


#ifdef __cplusplus
}
#endif

#endif /* INCLUDED_VRTC_DEVICE_PRIMS_H */
