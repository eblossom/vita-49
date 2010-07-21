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
#ifndef INCLUDED_VRTC_EXPR_H
#define INCLUDED_VRTC_EXPR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stddef.h>
#include <stdbool.h>
#include <vrtc/asn1c/Expr.h>

/*! 
 * \brief Free Expr_t \p p and any contained elements 
 * If \p is 0, nothing is done.
 */
void vrtc_free_expr(Expr_t *p);

/*! \returns a "null" expr if successful, else 0. */
Expr_t *vrtc_make_null(void);

/*! \returns a "bool" expr if successful, else 0. */
Expr_t * vrtc_make_bool(bool v);

/*! \returns a "integer" expr if successful, else 0. */
Expr_t * vrtc_make_int(int v);

/*! 
 * \returns a "string" expr if successful, else 0.
 * \param[in] p pointer to bytes to copy into expr
 * \param[in] len number of bytes to copy
 */
Expr_t *vrtc_make_string(const char *p, size_t len);

/*!
 * \Returns a "string" expr if successful, else 0.
 * \param[in] p pointer to zero-terminated string
 */
Expr_t * vrtc_make_cstring(const char *p);

/*! \Returns a sequence with 0 elements if successful, else 0. */
Expr_t *vrtc_make_seq0(void);

/*! 
 * \brief Returns a sequence with 1 element \p x0 if successful, else 0.
 * If any args are zero, free all non-zero args and return 0.
 */
Expr_t *vrtc_make_seq1(Expr_t *x0);

/*! 
 * \brief Returns a sequence with 2 elements \p x0, \p x1 if successful, else 0.
 * If any args are zero, free all non-zero args and return 0.
 */
Expr_t *vrtc_make_seq2(Expr_t *x0, Expr_t *x1);

/*! 
 * \brief Returns a sequence with 3 elements \p x0, \p x1, \p x2 if successful, else 0.
 * If any args are zero, free all non-zero args and return 0.
 */
Expr_t *vrtc_make_seq3(Expr_t *x0, Expr_t *x1, Expr_t *x2);

/*! 
 * \brief Returns a sequence with 4 elements \p x0, \p x1,\p x2, \p x3 if successful, else 0.
 * If any args are zero, free all non-zero args and return 0.
 */
Expr_t *vrtc_make_seq4(Expr_t *x0, Expr_t *x1, Expr_t *x2, Expr_t *x3);


/*
 * -------------------------------------------------------------------------
 * Routines to encode and decode between Expr_t's and the on-the-wire format
 * -------------------------------------------------------------------------
 */

typedef asn_enc_rval_t	vrtc_enc_rval_t;
typedef asn_dec_rval_t  vrtc_dec_rval_t;
typedef asn_app_consume_bytes_f vrtc_app_consume_bytes_t;

/*!
 * \brief encode an Expr_t into the on-the-wire format
 *
 * \param[input] e is the Expr_t to be encoded
 * \param consume_bytes_cb is the function to receive the bytes generated
 * \param cb_arg is the additional argument passed to the callback
 */
vrtc_enc_rval_t
vrtc_encode(Expr_t *e,
	    vrtc_app_consume_bytes_t *consume_bytes_cb,
	    void *cb_arg);

/*!
 * \brief decode on-the-wire format into an Expr_t
 *
 * \param[output] e is the decoded Expr_t
 * \param[input] buffer is the data to be decoded
 * \param[input] size is the number of bytes in \p buffer
 */
vrtc_dec_rval_t
vrtc_decode(Expr_t **e,
	    const void *buffer,
	    size_t size);

#ifdef __cplusplus
}
#endif
#endif /* INCLUDED_VRTC_EXPR_H */
