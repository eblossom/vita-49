/* -*- c++ -*- */
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

#ifndef INCLUDED_UDP_CONNECTION_H
#define INCLUDED_UDP_CONNECTION_H

#include "max_payload.h"

namespace vrtc {

using boost::asio::ip::udp;

#define STRINGIFY(x) _STRINGIFY(x)
#define _STRINGIFY(x) #x

class udp_connection
{
  udp::socket			d_socket;

public:
  udp_connection(boost::asio::io_service &io, const std::string &hostname) :
    d_socket(io, udp::v4())
  { 
    udp::resolver resolver(io);
    udp::resolver::query query(udp::v4(), hostname, STRINGIFY(VRTC_UDP_CTRL_PORT));
    udp::endpoint remote_endpoint = *resolver.resolve(query);
    d_socket.connect(remote_endpoint);
  }

  template<typename MutableBufferSequence, typename RecvHandler>
  void async_receive(const MutableBufferSequence &buffers, RecvHandler recv_handler)
  {
    d_socket.async_receive(buffers, recv_handler);
  }

  template<typename ConstBufferSequence>
  std::size_t send(const ConstBufferSequence &buffers,
		   boost::system::error_code &error)
  {
    return d_socket.send(buffers, 0, error);
  }

  template<typename ConstBufferSequence, typename WriteHandler>
  void async_send(const ConstBufferSequence &buffers,
		  WriteHandler handler)
  {
    d_socket.async_send(buffers, 0, handler);
  }

};

} /* namespace vrtc */

#endif /* INCLUDED_UDP_CONNECTION_H */
