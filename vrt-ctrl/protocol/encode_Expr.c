#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdbool.h>
#include "Expr.h"
#include "vrt-ctrl-protocol-consts.h"

void
die(const char *msg)
{
  fprintf(stderr, "\ndie: %s\n", msg);
  exit(1);
}

void *
safe_calloc(size_t nmemb, size_t size)
{
  void *p = calloc(nmemb, size);
  if (!p){
    perror("calloc");
    exit(1);
  }
}

static int
write_out(const void *buffer, size_t size, void *app_key)
{
  FILE *out_fp = app_key;
  size_t wrote;

  wrote = fwrite(buffer, 1, size, out_fp);
  return (wrote == size) ? 0 : -1;
}

Expr_t *
vrtc_make_null(void)
{
  Expr_t *expr = safe_calloc(1, sizeof(Expr_t));
  expr->present = Expr_PR_null;
  return expr;
}

Expr_t *
vrtc_make_bool(bool v)
{
  Expr_t *expr = safe_calloc(1, sizeof(Expr_t));
  expr->present = Expr_PR_boolean;
  expr->choice.boolean = v ? 0xff : 0;
  return expr;
}

Expr_t *
vrtc_make_int(int v)
{
  Expr_t *expr = safe_calloc(1, sizeof(Expr_t));
  expr->present = Expr_PR_integer;
  expr->choice.integer = v;
  return expr;
}

Expr_t *
vrtc_make_string(const char *p, size_t len)
{
  Expr_t *expr = safe_calloc(1, sizeof(Expr_t));
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
  Expr_t *expr = safe_calloc(1, sizeof(Expr_t));
  expr->present = Expr_PR_seq;
  return expr;
}

bool
vrtc_seq_add(Expr_t *seq, Expr_t *element)
{
  int ret = ASN_SEQUENCE_ADD(&seq->choice.seq, element);
  return ret == 0;
}

void
vrtc_free_expr(Expr_t *p)
{
  ASN_STRUCT_FREE(asn_DEF_Expr, p);
}


// ------------------------------------------------------------------------

Expr_t *
vrtc_make_call(int invocation_id, Expr_t *opcode_and_args)
{
  Expr_t *call = vrtc_make_seq();
  vrtc_seq_add(call, vrtc_make_int(vrtc_CALL));
  vrtc_seq_add(call, vrtc_make_int(invocation_id));
  vrtc_seq_add(call, opcode_and_args);
  return call;
}

Expr_t *
vrtc_make_get(int invocation_id, const char *path)
{
  Expr_t *op_and_args = vrtc_make_seq();
  vrtc_seq_add(op_and_args, vrtc_make_int(vrtc_GET));
  vrtc_seq_add(op_and_args, vrtc_make_cstring(path));
  return vrtc_make_call(invocation_id, op_and_args);
}

// ------------------------------------------------------------------------

void 
handle_Expr(Expr_t *e, FILE *fp)
{
  if (fp){
    asn_enc_rval_t	ec;
    ec = der_encode(&asn_DEF_Expr, e, write_out, fp);
    if (ec.encoded == -1){
      fprintf(stderr, "Count not encode Expr (at %s)\n",
	      ec.failed_type ? ec.failed_type->name : "unknown");
      exit(1);
    }
  }
  xer_fprint(stdout, &asn_DEF_Expr, e);
}

int
main(int ac, char **av)
{
  FILE *fp = 0;

  if (ac < 2){
    fprintf(stderr, "Specify filename for BER output\n");
  }
  else {
    const char *filename = av[1];
    fp = fopen(filename, "wb");
    if (!fp){
      perror(filename);
      exit(1);
    }
  }
    
  Expr_t *expr;

  expr = vrtc_make_null();
  handle_Expr(expr, fp);
  vrtc_free_expr(expr);

  expr = vrtc_make_int(1);
  handle_Expr(expr, fp);
  vrtc_free_expr(expr);

  expr = vrtc_make_int(-1);
  handle_Expr(expr, fp);
  vrtc_free_expr(expr);

  expr = vrtc_make_cstring("Hello VRT");
  handle_Expr(expr, fp);
  vrtc_free_expr(expr);

  expr = vrtc_make_get(1024, "/unit/0x7/freq");
  handle_Expr(expr, fp);
  vrtc_free_expr(expr);


  return 0;
}
