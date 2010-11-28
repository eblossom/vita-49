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

/*
 * This is the resource tree used by the simulator.
 *
 * In an actual device, this file would define the real resources.
 */

#include <vrtc/device/vrtd_node.h>

/*
 * /freq				r/w
 *
 * /is/0x0/beamformer-coeffs/{0,1,2,3}	r/w
 * /is/0x0/data-fmt			r
 * /is/0x0/rx-ctrl			w
 * /is/0x0/sample-rate			r
 *
 * /is/0x8/data-fmt			r
 * /is/0x8/rx-ctrl			w
 * /is/0x8/sample-rate			r
 *
 * /rf-in/{0,1,2,3}/gain		r/w
 * /rf-in/{0,1,2,3}/temp		r
 */

#include "resource-impl.h"

extern vrtd_node_t root_node;
extern vrtd_node_t freq_node;
extern vrtd_node_t is_node;
extern vrtd_node_t rf_in_node;
extern vrtd_node_t is_0x0_node;
extern vrtd_node_t data_fmt_node;
extern vrtd_node_t rx_ctrl_node;
extern vrtd_node_t sample_rate_node;
extern vrtd_node_t rf_in_0x0_node;
extern vrtd_node_t rf_in_0x1_node;
extern vrtd_node_t rf_in_0x2_node;
extern vrtd_node_t rf_in_0x3_node;
extern vrtd_node_t gain_node;
extern vrtd_node_t temp_node;


vrtd_node_t root_node = {
  .path_term = "",
  .u.dir.first_child = &freq_node
};

vrtd_node_t freq_node = {
  .path_term = "freq",
  .flags = NF_LEAF | NF_GET | NF_PUT,
  .sibling = &is_node,
  .u.leaf.get = &example_get_freq,
  .u.leaf.get_meta = &default_get_meta,
  .u.leaf.put = &example_put_freq,
};

vrtd_node_t is_node = {
  .path_term = "is",
  .sibling = &rf_in_node,
  .u.dir.first_child = &is_0x0_node
};

vrtd_node_t rf_in_node = {
  .path_term = "rf-in",
  .u.dir.first_child = &rf_in_0x0_node
};

vrtd_node_t is_0x0_node = {
  .path_term = "0x0",
  .numeric_path_value = 0,
  .flags = NF_NUMERIC,
  .u.dir.first_child = &data_fmt_node,
};

vrtd_node_t data_fmt_node = {
  .path_term = "data-fmt",
  .flags = NF_LEAF | NF_GET,
  .sibling = &rx_ctrl_node,
  .u.leaf.get = &example_get_data_fmt,
  .u.leaf.get_meta = &default_get_meta,
};

vrtd_node_t rx_ctrl_node = {
  .path_term = "rx-ctrl",
  .flags = NF_LEAF | NF_PUT,
  .sibling = &sample_rate_node,
  .u.leaf.get_meta = &default_get_meta,
  .u.leaf.put = &example_put_rx_ctrl
};

vrtd_node_t sample_rate_node = {
  .path_term = "sample-rate",
  .flags = NF_LEAF | NF_GET,
  .sibling = 0,
  .u.leaf.get = &example_get_sample_rate,
  .u.leaf.get_meta = &default_get_meta,
};

vrtd_node_t rf_in_0x0_node = {
  .path_term = "0x0",
  .numeric_path_value = 0x0,
  .sibling = &rf_in_0x1_node,
  .flags = NF_NUMERIC,
  .u.dir.first_child = &gain_node
};

vrtd_node_t rf_in_0x1_node = {
  .path_term = "0x1",
  .numeric_path_value = 0x1,
  .sibling = &rf_in_0x2_node,
  .flags = NF_NUMERIC,
  .u.dir.first_child = &gain_node
};

vrtd_node_t rf_in_0x2_node = {
  .path_term = "0x2",
  .numeric_path_value = 0x2,
  .sibling = &rf_in_0x3_node,
  .flags = NF_NUMERIC,
  .u.dir.first_child = &gain_node
};

vrtd_node_t rf_in_0x3_node = {
  .path_term = "0x3",
  .numeric_path_value = 0x3,
  .sibling = 0,
  .flags = NF_NUMERIC,
  .u.dir.first_child = &gain_node
};

vrtd_node_t gain_node = {
  .path_term = "gain",
  .flags = NF_LEAF | NF_PUT | NF_GET,
  .sibling = &temp_node,
  .u.leaf.get = &example_get_gain,
  .u.leaf.get_meta = &default_get_meta,
  .u.leaf.put = &example_put_gain,
};

vrtd_node_t temp_node = {
  .path_term = "temp",
  .flags = NF_LEAF | NF_GET,
  .sibling = 0,
  .u.leaf.get = &example_get_temp,
  .u.leaf.get_meta = &default_get_meta,
  .u.leaf.put = 0
};
