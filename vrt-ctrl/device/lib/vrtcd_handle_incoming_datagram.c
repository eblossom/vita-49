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

/* decode Expr_t's in buf, and dispatch them */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#include <vrtc/device/handle_datagram.h>
#include <vrtc/device_prims.h>
#include <vrtc/protocol-consts.h>
#include <assert.h>


#define MAX_PAYLOAD (1500 - 28)	/* Maximum UDP payload on typically ethernet */


#if 0
bool
msg_is_call(Expr_t *msg, int *inv_id, Expr_t **opcode_and_args)
{
  bool ok = (true
	     && vrtc_is_seq(msg)
	     && vrtc_seq_len(msg) == 3
	     && vrtc_is_int(vrtc_seq_ref(1)));

  if (ok){
    *inv_id = vrtc_get_int(vrtc_seq_ref(1));
    *opcode_and_args = vrtc_seq_ref(2);
  }
  return ok;
}

void
vrtcd_handle_expr(Expr_t *e, datagram_buffer_t *dgbuf)
{
  int invocation_id;
  Expr_t *opcode_and_args = 0;
  Expr_t *path = 0;
  Expr_t *v = 0;

  if (!msg_is_call(e), &invocation_id, &opcode_and_args){
  unrecognized_msg:
    expr_encode_and_free(vrtc_make_reject2(vrtc_EC_UNRECOGNIZED_MSG,
					   expr_clone(e)),
			 dgbuf);
    return;
  }
  
  if (op_is_get(opcode_and_args, &path))
    handle_get(path, dgbuf);
  else if (op_is_get_meta(opcode_and_args, &path))
    handle_get_meta(path, dgbuf);
  else if (op_is_put(opcode_and_args, &path, &v))
    handle_put(path, v, dgbuf);
  else
    goto unrecognized_msg;
}
#endif

void
vrtcd_handle_incoming_datagram(void *buf, size_t len,
			       send_datagram_t send, send_datagram_handle_t handle,
			       size_t max_send_len)
{
  char tx_buffer[MAX_PAYLOAD];
  datagram_buffer_t	dgbuf;
  datagram_buffer_init(&dgbuf, tx_buffer, sizeof(tx_buffer), send, handle);

  const unsigned char *payload = (unsigned char *) buf;
  while (len != 0){
    Expr_t *e = 0;
    expr_dec_rval_t rval = expr_decode(&e, payload, len);
    if (rval.code == RC_OK){
      // vrtcd_handle_expr(e, &dgbuf);
      expr_free(e);
      assert(rval.consumed <= len);
      payload += rval.consumed;
      len -= rval.consumed;
    }
    else {
      /* Something's hosed with the payload.  Send a REJECT */
      expr_encode_and_free(vrtc_make_reject(vrtc_EC_CANT_DECODE), &dgbuf);
      break;
    }
  }
  datagram_buffer_flush(&dgbuf);
}

