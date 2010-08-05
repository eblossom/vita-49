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
#ifndef INCLUDED_VRTC_HOST_H
#define INCLUDED_VRTC_HOST_H

#ifdef __cplusplus
extern "C" {
#endif

#include <vrtc/expr.h>

Expr_t *vrtc_make_get(int invocation_id, const char *path);
Expr_t *vrtc_make_get_meta(int invocation_id, const char *path);
Expr_t *vrtc_make_put(int invocation_id, const char *path, Expr_t *v);

#ifdef __cplusplus
}
#endif

#endif /* INCLUDED_VRTC_HOST_H */
