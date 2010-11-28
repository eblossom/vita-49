#include <vrtc/expr.h>
#include <vrtc/protocol-consts.h>

/* Routines used by both host and device code */

static void *
_alloc_expr(void)
{
  /* FIXME linked pool? */
  return calloc(1, sizeof(Expr_t));
}

void
expr_free(Expr_t *p)
{
  ASN_STRUCT_FREE(asn_DEF_Expr, p);
}

Expr_t *
expr_make_null(void)
{
  Expr_t *expr = _alloc_expr();
  if (!expr)
    return 0;
  expr->present = Expr_PR_null;
  return expr;
}

Expr_t *
expr_make_bool(bool v)
{
  Expr_t *expr = _alloc_expr();
  if (!expr)
    return 0;
  expr->present = Expr_PR_boolean;
  expr->choice.boolean = v ? 0xff : 0;
  return expr;
}

Expr_t *
expr_make_int(long v)
{
  Expr_t *expr = _alloc_expr();
  if (!expr)
    return 0;
  expr->present = Expr_PR_integer;
  expr->choice.integer = v;
  return expr;
}

Expr_t *
expr_make_string(const char *p, size_t len)
{
  Expr_t *expr = _alloc_expr();
  if (!expr)
    return 0;
  expr->present = Expr_PR_string;
  if (OCTET_STRING_fromBuf(&expr->choice.string, p, len) == -1){
    expr_free(expr);
    return 0;
  }
  return expr;
}

Expr_t *
expr_make_cstring(const char *p)
{
  size_t len = 0;
  if (p)
    len = strlen(p);
  return expr_make_string(p, len);
}

Expr_t *
vrtc_make_seq(void)
{
  Expr_t *expr = _alloc_expr();
  if (!expr)
    return 0;
  expr->present = Expr_PR_seq;
  return expr;
}

bool
vrtc_seq_add(Expr_t *seq, Expr_t *element)
{
  return ASN_SEQUENCE_ADD(&seq->choice.seq, element) == 0;
}

Expr_t *
expr_seq_add_element(Expr_t *seq, Expr_t *element)
{
  if (element == 0){
    expr_free(seq);
    return 0;
  }

  if (!vrtc_seq_add(seq, element)){
    expr_free(seq);
    expr_free(element);
    return 0;
  }

  return seq;
}

Expr_t *
expr_make_seq0(void)
{
  return vrtc_make_seq();
}

Expr_t *
expr_make_seq1(Expr_t *x0)
{
  if (x0 == 0){
  free_and_fail:
    expr_free(x0);
    return 0;
  }

  Expr_t *seq = vrtc_make_seq();
  if (seq == 0)
    goto free_and_fail;
    
  if (vrtc_seq_add(seq, x0))
    return seq;

  expr_free(seq);	// free seq and contents
  return 0;
}

Expr_t *
expr_make_seq2(Expr_t *x0, Expr_t *x1)
{
  if (x0 == 0 || x1 == 0){
  free_and_fail:
    expr_free(x0);
    expr_free(x1);
    return 0;
  }

  Expr_t *seq = vrtc_make_seq();
  if (seq == 0)
    goto free_and_fail;

  if (vrtc_seq_add(seq, x0) && vrtc_seq_add(seq, x1))
    return seq;

  expr_free(seq);	// free seq and contents
  return 0;
}

Expr_t *
expr_make_seq3(Expr_t *x0, Expr_t *x1, Expr_t *x2)
{
  if (x0 == 0 || x1 == 0 || x2 == 0){
  free_and_fail:
    expr_free(x0);
    expr_free(x1);
    expr_free(x2);
    return 0;
  }

  Expr_t *seq = vrtc_make_seq();
  if (seq == 0)
    goto free_and_fail;

  if (vrtc_seq_add(seq, x0) && vrtc_seq_add(seq, x1) && vrtc_seq_add(seq, x2))
    return seq;

  expr_free(seq);	// free seq and contents
  return 0;
}

Expr_t *
expr_make_seq4(Expr_t *x0, Expr_t *x1, Expr_t *x2, Expr_t *x3)
{
  if (x0 == 0 || x1 == 0 || x2 == 0 || x3 == 0){
  free_and_fail:
    expr_free(x0);
    expr_free(x1);
    expr_free(x2);
    expr_free(x3);
    return 0;
  }

  Expr_t *seq = vrtc_make_seq();
  if (seq == 0)
    goto free_and_fail;

  if (vrtc_seq_add(seq, x0) && vrtc_seq_add(seq, x1)
      && vrtc_seq_add(seq, x2) && vrtc_seq_add(seq, x3))
    return seq;

  expr_free(seq);	// free seq and contents
  return 0;
}


Expr_t *
expr_clone(Expr_t *x)
{
  // FIXME decode(encode(x)) or equivalent
  return expr_make_int(99999);
}

static int 
der_encoder_write_shim(const void *buf, size_t size, void *app_key)
{
  datagram_buffer_t *dest = (datagram_buffer_t *) app_key;
  return datagram_buffer_write(dest, buf, size) ? 0 : -1;
}

bool
expr_encode(Expr_t *e, datagram_buffer_t *dest)
{
  asn_enc_rval_t rval;

  // Determine number of bytes required to represent e.
  rval = der_encode(&asn_DEF_Expr, e, 0, 0);
  if (rval.encoded == -1){	// some kind of problem
    // FIXME figure out what's wrong (trouble with expr?)
    return false;
  }

  size_t len = rval.encoded;
  if (!datagram_buffer_ensure_room(dest, len))	// won't fit
    return false;

  rval = der_encode(&asn_DEF_Expr, e, der_encoder_write_shim, dest);
  if (rval.encoded == -1){	// some kind of problem
    // FIXME figure out what's wrong
    return false;
  }
  return true;
}

bool
expr_encode_and_free(Expr_t *e, datagram_buffer_t *dest)
{
  bool r = expr_encode(e, dest);
  expr_free(e);
  return r;
}


expr_dec_rval_t
expr_decode(Expr_t **e,
	    const void *buffer,
	    size_t size)
{
  expr_dec_rval_t rval;
  rval = ber_decode(0, &asn_DEF_Expr, (void **)e, buffer, size);
  return rval;
}
