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

#include "resolve_resource.h"
#include <vrtc/device/vrtd_node.h>
#include <vrtc/protocol-consts.h>
#include <vrtc/device_prims.h>
#include <string.h>


#define MAX_PATH_LEN	512
#define MAX_PATH_TERMS	 32

extern vrtd_node_t	root_node;

static char path_buf[MAX_PATH_LEN + 1];


static void
send_error(op_info_t *oi, int error_code, Expr_t *error_arg)
{
  expr_encode_and_free(vrtc_make_error(oi->inv_id, error_code, error_arg),
		       oi->dgbuf);
}

static void
send_reply(op_info_t *oi, Expr_t *reply)
{
  expr_encode_and_free(vrtc_make_reply(oi->inv_id, reply), oi->dgbuf);
}

static Expr_t *
leaf_seq(Expr_t *e)
{
  return expr_make_seq2(expr_make_int(vrtc_LEAF), e);
}

static Expr_t *
dir_seq(Expr_t *e)
{
  return expr_make_seq2(expr_make_int(vrtc_DIR), e);
}

static Expr_t *
get_childrens_path_terms(vrtd_node_t *node)
{
  Expr_t	*seq = expr_make_seq();
  vrtd_node_t 	*p;

  for (p = node->u.dir.first_child; p; p = p->sibling){
    seq = expr_seq_add_element(seq, expr_make_cstring(p->path_term));
  }
  return seq;
}

static void
apply_op(op_info_t *oi, vrtd_traversal_info_t *ti, vrtd_node_t *node)
{
  if (is_dir(node)){
    switch(oi->op_code){
    case opGET:
    case opGET_META:
      send_reply(oi, dir_seq(get_childrens_path_terms(node)));
      return;

    case opPUT:
      send_error(oi, vrtc_EC_NOT_PUTTABLE, expr_clone(oi->path));
      return;
    }
  }
  else {	// is_leaf
    switch(oi->op_code){
    case opGET:
    case opGET_META:
    case opPUT:
      send_error(oi, vrtc_EC_NOT_IMPLEMENTED, expr_clone(oi->path));
      return;
    }
  }
  send_error(oi, vrtc_EC_INTERNAL_ERROR, expr_clone(oi->path));
}

static void
search_node(op_info_t *oi, vrtd_traversal_info_t *ti, vrtd_node_t *node)
{
  // FIXME
}


static bool
split(char *p, unsigned int plen,
      unsigned int *vlen_, char **vpath)
{
  p[plen] = 0;	// null terminate path.

  int vlen;
  char *slash = 0;
  for (vlen = 0; vlen < MAX_PATH_TERMS; ){
    vpath[vlen++] = p;		// record start of <path-term>
    slash = strchr(p, '/');
    if (!slash)
      break;
    p = slash;
  }

  *vlen_ = vlen;
  return slash == 0;
}

/*
 * Find the specified resource if it exists, and apply the given
 * operation and arguments.
 *
 * This takes care of generating and sending the result or error information.
 */
void
resolve_resource(op_info_t *oi)
{
  vrtd_traversal_info_t	ti;
  memset(&ti, 0, sizeof(ti));

  char *vpath[MAX_PATH_TERMS];
  memset(vpath, 0, sizeof(vpath));
  ti.path = oi->path;
  ti.vpath = vpath;

  unsigned int slen = expr_string_len(oi->path);
  unsigned char *p = expr_string_ptr(oi->path);

  if (slen > MAX_PATH_LEN){
    send_error(oi, vrtc_EC_PATH_TOO_LONG, expr_clone(oi->path));
    return;
  }
  if (slen < 1 || *p != '/'){
    send_error(oi, vrtc_EC_INVALID_PATH, expr_clone(oi->path));
    return;
  }

  if (slen == 1){		// apply operator to root node
    apply_op(oi, &ti, &root_node);
  }
  else {
    p++;			// skip leading '/'
    slen--;

    // Make local copy so we can modify the string.
    memcpy(path_buf, p, slen);

    if (!split(path_buf, slen, &ti.vlen, ti.vpath)){
      send_error(oi, vrtc_EC_PATH_TOO_DEEP, expr_clone(oi->path));
    }

    search_node(oi, &ti, &root_node);
  }
}

