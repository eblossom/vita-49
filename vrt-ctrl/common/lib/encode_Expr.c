#include <vrtc/expr.h>
#include <vrtc/host_prims.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <assert.h>

void
die(const char *msg)
{
  fprintf(stderr, "\ndie: %s\n", msg);
  exit(1);
}

static int
write_out(const void *buffer, size_t size, void *app_key)
{
  FILE *out_fp = app_key;
  size_t wrote;

  wrote = fwrite(buffer, 1, size, out_fp);
  return (wrote == size) ? 0 : -1;
}

// ------------------------------------------------------------------------

void 
handle_Expr(Expr_t *e, FILE *fp)
{
  if (fp){
    vrtc_enc_rval_t	ec;
    ec = vrtc_encode(e, write_out, fp);
    if (ec.encoded == -1){
      fprintf(stderr, "Count not encode Expr (at %s)\n",
	      ec.failed_type ? ec.failed_type->name : "unknown");
      exit(1);
    }
  }
  // xer_fprint(stdout, &asn_DEF_Expr, e);
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
  assert(expr);
  handle_Expr(expr, fp);
  vrtc_free_expr(expr);

  expr = vrtc_make_int(1);
  assert(expr);
  handle_Expr(expr, fp);
  vrtc_free_expr(expr);

  expr = vrtc_make_int(-1);
  assert(expr);
  handle_Expr(expr, fp);
  vrtc_free_expr(expr);

  expr = vrtc_make_cstring("Hello VRT");
  assert(expr);
  handle_Expr(expr, fp);
  vrtc_free_expr(expr);

  expr = vrtc_make_get(1024, "/unit/0x7/freq");
  assert(expr);
  handle_Expr(expr, fp);
  vrtc_free_expr(expr);


  return 0;
}
