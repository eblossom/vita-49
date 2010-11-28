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

#include "resource-implementations.h"
#include <vrtc/protocol-consts.h>
#include <vrtc/device_prims.h>


Expr_t *
error_not_implemented(vrtd_node_t *self, vrtd_traversal_info_t *ti)
{
  return vrtc_make_error_info2(vrtc_EC_NOT_IMPLEMENTED, expr_clone(ti->path));
}

// Get-ers

Expr_t *
example_get_freq(vrtd_node_t *self, vrtd_traversal_info_t *ti)
{
  return error_not_implemented(self, ti);
}
   
Expr_t *
example_get_gain(vrtd_node_t *self, vrtd_traversal_info_t *ti)
{
  return error_not_implemented(self, ti);
}

Expr_t *
example_get_temp(vrtd_node_t *self, vrtd_traversal_info_t *ti)
{
  return error_not_implemented(self, ti);
}

Expr_t *
example_get_data_fmt(vrtd_node_t *self, vrtd_traversal_info_t *ti)
{
  return error_not_implemented(self, ti);
}

Expr_t *
example_get_sample_rate(vrtd_node_t *self, vrtd_traversal_info_t *ti)
{
  return error_not_implemented(self, ti);
}

// Get-meta-ers

Expr_t *
default_get_meta(vrtd_node_t *self, vrtd_traversal_info_t *ti)
{
  return error_not_implemented(self, ti);
}


// Put-ers
Expr_t *
example_put_freq(vrtd_node_t *self, vrtd_traversal_info_t *ti,
		 Expr_t *value, Expr_t *when)
{
  return error_not_implemented(self, ti);
}


Expr_t *
example_put_gain(vrtd_node_t *self, vrtd_traversal_info_t *ti,
		 Expr_t *value, Expr_t *when)
{
  return error_not_implemented(self, ti);
}

Expr_t *
example_put_rx_ctrl(vrtd_node_t *self, vrtd_traversal_info_t *ti,
		    Expr_t *value, Expr_t *when)
{
  return error_not_implemented(self, ti);
}
