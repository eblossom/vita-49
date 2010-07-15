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
#ifndef INCLUDED_VRT_ASN1_LITE_H
#define INCLUDED_VRT_ASN1_LITE_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>


#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
  struct al_obj_tag   **p;	/* pointers to elements */
  size_t		len;	/* # of elements */
} al_seq;

typedef struct {
  const unsigned char *p;
  size_t	       len;	/* # of chars */
} al_string;

typedef struct {
  int32_t	re;
  int32_t	im;
} al_complex_int;

typedef struct {
  float		re;
  float		im;
} al_complex_float;

typedef enum {
  AT_FREE = 0,
  AT_SEQ,
  AT_NULL,
  AT_BOOL,
  AT_INT,
  AT_STRING,
  AT_FLOAT,
  AT_COMPLEX_INT,
  AT_COMPLEX_FLOAT,
} al_obj_type;

/* al_obj flag values */
#define ALF_STATIC	0x1	// static allocation


typedef struct al_obj_tag {
  uint8_t	type;		// al_obj_type
  uint8_t	refcnt;
  uint8_t	flags;
  uint8_t	__pad__;
  union {
    struct al_obj_tag  *next;	// freelist, etc
    al_seq	    	seq_v;
    bool	    	bool_v;
    int32_t	    	int_v;
    al_string        	string_v;
    float		float_v;
    al_complex_int   	complex_int_v;
    al_complex_float 	complex_float_v;
  } u;
} al_obj;


/*! One time call to initialize subsystem */
void al_init(void);

/*! Increment reference count */
void al_incref(al_obj *obj);

/*! Decrement reference count.  Free obj if result is zero */
void al_decref(al_obj *obj);

al_obj *al_new_seq(size_t len);
al_obj *al_new_null(void);
al_obj *al_new_bool(bool v);
al_obj *al_new_int(int32_t v);
al_obj *al_new_string(const unsigned char *p, size_t len);
al_obj *al_new_static_string(const unsigned char *p, size_t len);
al_obj *al_new_float(float v);
al_obj *al_new_complex_int(int32_t re, int32_t im);
al_obj *al_new_complex_float(float re, float im);

static inline al_is_seq(al_obj *x){ return x->type == AT_SEQ; }
static inline al_is_null(al_obj *x){ return x->type == AT_NULL; }
static inline al_is_bool(al_obj *x){ return x->type == AT_BOOL; }
static inline al_is_int(al_obj *x){ return x->type == AT_INT; }
static inline al_is_string(al_obj *x){ return x->type == AT_STRING; }
static inline al_is_float(al_obj *x){ return x->type == AT_FLOAT; }
static inline al_is_complex_int(al_obj *x){ return x->type == AT_COMPLEX_INT; }
static inline al_is_complex_float(al_obj *x){ return x->type == AT_COMPLEX_FLOAT; }



#ifdef  __cplusplus
}
#endif
#endif /* INCLUDED_VRT_ASN1_LITE_H */
