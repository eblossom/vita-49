/* -*- c -*- */
/*
 * Copyright 2010 Free Software Foundation, Inc.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <vrtc/expr.h>
#include <stdio.h>

void
expr_fprint(Expr_t *x, FILE *fp)
{
  int i;

  if (expr_is_null(x))
    fputs("NULL", fp);

  else if (expr_is_bool(x))
    fputs(expr_get_bool(x) ? "#t" : "#f", fp);

  else if (expr_is_int(x))
    fprintf(fp, "%d", (int) expr_get_int(x));

  else if (expr_is_string(x)){
    const unsigned char *p = expr_string_ptr(x);
    int len = expr_string_len(x);
    fputc('"', fp);
    for (i = 0; i < len; i++)
      fputc(p[i], fp);		/* FIXME escape */
    fputc('"', fp);
  }

  else if (expr_is_float(x))
    fprintf(fp, "<float>");

  else if (expr_is_complex_float(x))
    fprintf(fp, "<complex-float>");

  else if (expr_is_complex_int(x))
    fprintf(fp, "<%d, %d>", 0, 0); /* FIXME */

  else if (expr_is_seq(x)){
    int L = expr_seq_len(x);
    fputc('{', fp);
    for (i = 0; i < L; i++){
      fputc(' ', fp);
      expr_fprint(expr_seq_ref(x, i), fp);
    }
    fputc(' ', fp);
    fputc('}', fp);
  }
  else {
    fprintf(fp, "<unimplemented-type>");
  }
}

void
expr_print(Expr_t *x)
{
  expr_fprint(x, stdout);
}
