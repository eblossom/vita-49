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
#ifndef INCLUDED_VRTC_DEVICE_VRTD_NODE_H
#define INCLUDED_VRTC_DEVICE_VRTD_NODE_H

/*
 * This file contains the structures that define the mapping from a
 * path to the routines that implement the resource specific GET,
 * GET-META and PUT operations.
 */

#include <stdint.h>
#include <stdbool.h>
#include <vrtc/expr.h>


struct vrtd_node;
typedef struct vrtd_node vrtd_node_t;


// Maximum number of numeric path terms in a single path
#define MAX_NUMERIC_PATH_TERMS		8

typedef struct {
  Expr_t	*path;		// path from off the wire
  char 		**vpath;	// vector of ptrs to null terminated path-terms
  unsigned int	vlen;		// length of pathv
  unsigned int	vi;		// current index into pathv
  int32_t	npt[MAX_NUMERIC_PATH_TERMS];
  unsigned int	nptlen;		// # of items in npt
} vrtd_traversal_info_t;

/*!
 * \brief The function type called to implement a GET on a leaf.
 *
 * \Returns:
 * <pre>
 *    <error-info>
 *  | { <LEAF> <expr> }
 * </pre>
 */
typedef Expr_t *(*vrtcd_op_get_t)(vrtd_node_t *self,
				  vrtd_traversal_info_t *);

/*!
 * \brief The function type called to implement a GET-META on a leaf.
 *
 * \Returns:
 * <pre>
 *    <error-info>
 *  | { <LEAF> <sequence-of-metadata> }
 * </pre>
 */
typedef Expr_t *(*vrtcd_op_get_meta_t)(vrtd_node_t *self,
				       vrtd_traversal_info_t *);

/*!
 * \brief The function type called to implement a PUT on a leaf.
 *
 * \Returns:
 * <pre>
 *    <error-info>
 *  | { <LEAF> <expr> }
 * </pre>
 */
typedef Expr_t *(*vrtcd_op_put_t)(vrtd_node_t *self,
				  vrtd_traversal_info_t *,
				  Expr_t *value,
				  Expr_t *when);


struct vrtd_node
{
  const char	       	*path_term;
  int32_t		numeric_path_value;	// valid if NF_NUMERIC in flags
  struct vrtd_node	*sibling;
  uint16_t		flags;
  union {
    struct {
      vrtcd_op_get_t		get;		// implements GET
      vrtcd_op_get_meta_t	get_meta;	// implements GET-META
      vrtcd_op_put_t		put;		// implements PUT
      void			*op_arg;
      Expr_t		        *metadata;
    } leaf;
    struct {
      struct vrtd_node		*first_child;
    } dir;
  } u;
};


// Flags: node type
#define NF_LEAF			0x0001	// else DIR
#define NF_NUMERIC		0x0002	// else <alpha-path-term>

// Flags: standard metadata
#define NF_GET			0x0010
#define	NF_PUT			0x0020
#define	NF_HONORS_WHEN		0x0040

static inline bool
is_leaf(vrtd_node_t *n)
{
  return (n->flags & NF_LEAF) != 0;
}

static inline bool
is_dir(vrtd_node_t *n)
{
  return !is_leaf(n);
}

static inline bool
is_numeric_path_term(vrtd_node_t *n)
{
  return (n->flags & NF_NUMERIC) != 0;
}

#endif /* INCLUDED_VRTC_DEVICE_VRTD_NODE_H */
