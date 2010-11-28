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
#ifndef INCLUDED_RESOURCE_IMPLEMENTATIONS_H
#define INCLUDED_RESOURCE_IMPLEMENTATIONS_H

#include <vrtc/device/vrtd_node.h>

// Get-ers
Expr_t *example_get_freq(vrtd_node_t *self, vrtd_traversal_info_t *);
Expr_t *example_get_gain(vrtd_node_t *self, vrtd_traversal_info_t *);
Expr_t *example_get_temp(vrtd_node_t *self, vrtd_traversal_info_t *);
Expr_t *example_get_data_fmt(vrtd_node_t *self, vrtd_traversal_info_t *);
Expr_t *example_get_sample_rate(vrtd_node_t *self, vrtd_traversal_info_t *);

// Get-meta-ers
Expr_t *default_get_meta(vrtd_node_t *self, vrtd_traversal_info_t *);

// Put-ers
Expr_t *example_put_freq(vrtd_node_t *self, vrtd_traversal_info_t *,
			 Expr_t *value, Expr_t *when);

Expr_t *example_put_gain(vrtd_node_t *self, vrtd_traversal_info_t *,
			 Expr_t *value, Expr_t *when);

Expr_t *example_put_rx_ctrl(vrtd_node_t *self, vrtd_traversal_info_t *,
			    Expr_t *value, Expr_t *when);


#endif /* INCLUDED_RESOURCE_IMPLEMENTATIONS_H */
