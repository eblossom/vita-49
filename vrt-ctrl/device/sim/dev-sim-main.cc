/* -*- c++ -*- */
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

/*
 * Blocking UDP server that serves as top level of device-simulator
 */

#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <vrtc/device/handle_datagram.h>
#include <vrtc/ports.h>

using boost::asio::ip::udp;


enum { MAX_PAYLOAD = 1500 - 28 };	// MAX UDP payload on typical ethernet

struct udp_state {
  udp_state(boost::asio::io_service &io) :
    socket(io, udp::v4()) { }
  udp::socket	socket;
  udp::endpoint remote_endpoint;
};

extern "C" {
  void dev_sim_send_datagram(void *handle, const void *buf, size_t len)
  {
    udp_state *us = (udp_state *) handle;
    boost::system::error_code ignored_error;
    us->socket.send_to(boost::asio::buffer(buf, len),
		       us->remote_endpoint, 0, ignored_error);
  }
}

int main()
{
  try
  {
    boost::asio::io_service io_service;
    udp_state us(io_service);
    boost::system::error_code ec;

    us.socket.bind(udp::endpoint(udp::v4(), VRTC_UDP_CTRL_PORT), ec);
    if (ec){
      std::cerr << ec.message() << ": Failed to bind udp socket on port "
		<< VRTC_UDP_CTRL_PORT << std::endl;
      return 0;
    }

    while (1)
    {
      boost::array<char, MAX_PAYLOAD> recv_buf;
      boost::system::error_code error;
      size_t len = us.socket.receive_from(boost::asio::buffer(recv_buf),
					  us.remote_endpoint, 0, error);

      if (error && error != boost::asio::error::message_size)
        throw boost::system::system_error(error);

      //std::cerr << "dev-sim: recv len = " << len << std::endl;
      vrtcd_handle_incoming_datagram(&recv_buf[0], len,
				     dev_sim_send_datagram, &us, MAX_PAYLOAD);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
