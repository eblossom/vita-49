#include "vrtc_expr.h"
#include "vrt-ctrl-protocol-consts.h"

static void *
_alloc_expr(void)
{
  /* FIXME linked pool? */
  return calloc(1, sizeof(Expr_t));
}

void
vrtc_free_expr(Expr_t *p)
{
  ASN_STRUCT_FREE(asn_DEF_Expr, p);
}

Expr_t *
vrtc_make_null(void)
{
  Expr_t *expr = _alloc_expr();
  if (!expr)
    return 0;
  expr->present = Expr_PR_null;
  return expr;
}

Expr_t *
vrtc_make_bool(bool v)
{
  Expr_t *expr = _alloc_expr();
  if (!expr)
    return 0;
  expr->present = Expr_PR_boolean;
  expr->choice.boolean = v ? 0xff : 0;
  return expr;
}

Expr_t *
vrtc_make_int(int v)
{
  Expr_t *expr = _alloc_expr();
  if (!expr)
    return 0;
  expr->present = Expr_PR_integer;
  expr->choice.integer = v;
  return expr;
}

Expr_t *
vrtc_make_string(const char *p, size_t len)
{
  Expr_t *expr = _alloc_expr();
  if (!expr)
    return 0;
  expr->present = Expr_PR_string;
  if (OCTET_STRING_fromBuf(&expr->choice.string, p, len) == -1){
    free(expr);
    die("OCTET_STRING_fromBuf");
  }
  return expr;
}

Expr_t *
vrtc_make_cstring(const char *p)
{
  size_t len = 0;
  if (p)
    len = strlen(p);
  return vrtc_make_string(p, len);
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
vrtc_make_seq0(void)
{
  return vrtc_make_seq();
}

Expr_t *
vrtc_make_seq1(Expr_t *x0)
{
  if (x0 == 0){
  free_and_fail:
    vrtc_free_expr(x0);
    return 0;
  }

  Expr_t *seq = vrtc_make_seq();
  if (seq == 0)
    goto free_and_fail;
    
  if (vrtc_seq_add(seq, x0))
    return seq;

  vrtc_free_expr(seq);	// free seq and contents
  return 0;
}

Expr_t *
vrtc_make_seq2(Expr_t *x0, Expr_t *x1)
{
  if (x0 == 0 || x1 == 0){
  free_and_fail:
    vrtc_free_expr(x0);
    vrtc_free_expr(x1);
    return 0;
  }

  Expr_t *seq = vrtc_make_seq();
  if (seq == 0)
    goto free_and_fail;

  if (vrtc_seq_add(seq, x0) && vrtc_seq_add(seq, x1))
    return seq;

  vrtc_free_expr(seq);	// free seq and contents
  return 0;
}

Expr_t *
vrtc_make_seq3(Expr_t *x0, Expr_t *x1, Expr_t *x2)
{
  if (x0 == 0 || x1 == 0 || x2 == 0){
  free_and_fail:
    vrtc_free_expr(x0);
    vrtc_free_expr(x1);
    vrtc_free_expr(x2);
    return 0;
  }

  Expr_t *seq = vrtc_make_seq();
  if (seq == 0)
    goto free_and_fail;

  if (vrtc_seq_add(seq, x0) && vrtc_seq_add(seq, x1) && vrtc_seq_add(seq, x2))
    return seq;

  vrtc_free_expr(seq);	// free seq and contents
  return 0;
}

Expr_t *
vrtc_make_seq4(Expr_t *x0, Expr_t *x1, Expr_t *x2, Expr_t *x3)
{
  if (x0 == 0 || x1 == 0 || x2 == 0 || x3 == 0){
  free_and_fail:
    vrtc_free_expr(x0);
    vrtc_free_expr(x1);
    vrtc_free_expr(x2);
    vrtc_free_expr(x3);
    return 0;
  }

  Expr_t *seq = vrtc_make_seq();
  if (seq == 0)
    goto free_and_fail;

  if (vrtc_seq_add(seq, x0) && vrtc_seq_add(seq, x1)
      && vrtc_seq_add(seq, x2) && vrtc_seq_add(seq, x3))
    return seq;

  vrtc_free_expr(seq);	// free seq and contents
  return 0;
}

// ------------------------------------------------------------------------

static Expr_t *
_vrtc_make_call(int invocation_id, Expr_t *opcode_and_args)
{
  return vrtc_make_seq3(vrtc_make_int(vrtc_CALL),
			vrtc_make_int(invocation_id),
			opcode_and_args);
}

static Expr_t *
_vrtc_make_get_helper(int invocation_id, const char *path, int opcode)
{
  return _vrtc_make_call(invocation_id, 
			 vrtc_make_seq2(vrtc_make_int(opcode),
					vrtc_make_cstring(path)));
}

Expr_t *
vrtc_make_get(int invocation_id, const char *path)
{
  return _vrtc_make_get_helper(invocation_id, path, vrtc_GET);
}

Expr_t *
vrtc_make_get_meta(int invocation_id, const char *path)
{
  return _vrtc_make_get_helper(invocation_id, path, vrtc_GET_META);
}

Expr_t *
vrtc_make_put(int invocation_id, const char *path, Expr_t *v)
{
  return _vrtc_make_call(invocation_id, 
			 vrtc_make_seq3(vrtc_make_int(vrtc_PUT),
					vrtc_make_cstring(path),
					v));
}

