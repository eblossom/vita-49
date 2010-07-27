//
// dev-sim-main.cc -- blocking UDP server that serves as top level of device-simulator
//
// Copyright 2010 Free Software Foundation, Inc.
//
//
// Derived from:
//
// server.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2010 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <ctime>
#include <iostream>
#include <string>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <vrtc/device/handle_datagram.h>

using boost::asio::ip::udp;

std::string make_daytime_string()
{
  using namespace std; // For time_t, time and ctime;
  time_t now = time(0);
  return ctime(&now);
}


enum { DEV_SIM_CTRL_PORT = 4795 };
enum { MAX_BUFFER = 1500 };

struct server_state {
  server_state(boost::asio::io_service &io) :
    socket(io, udp::v4())
  {
  }
  udp::socket	socket;
  udp::endpoint remote_endpoint;

};

extern "C" {
  void dev_sim_send_dgram(void *handle, const void *buf, size_t len)
  {
    server_state *ss = (server_state *) handle;
    boost::system::error_code ignored_error;
    ss->socket.send_to(boost::asio::buffer(buf, len),
		       ss->remote_endpoint, 0, ignored_error);
  }
}

int main()
{
  try
  {
    boost::asio::io_service io_service;
    server_state st(io_service);
    boost::system::error_code ec;

    st.socket.bind(udp::endpoint(udp::v4(), DEV_SIM_CTRL_PORT), ec);
    if (ec){
      std::cerr << ec.message() << ": Failed to bind udp socket on port "
		<< DEV_SIM_CTRL_PORT << std::endl;
      return 0;
    }

    for (;;)
    {
      boost::array<char, MAX_BUFFER> recv_buf;
      boost::system::error_code error;
      st.socket.receive_from(boost::asio::buffer(recv_buf),
			     st.remote_endpoint, 0, error);

      if (error && error != boost::asio::error::message_size)
        throw boost::system::system_error(error);

      std::string message = make_daytime_string();

      boost::system::error_code ignored_error;
      st.socket.send_to(boost::asio::buffer(message),
			st.remote_endpoint, 0, ignored_error);
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
