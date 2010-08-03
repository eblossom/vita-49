#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <vrtc/ports.h>

using boost::asio::ip::udp;

enum { MAX_PAYLOAD = 1500 - 28 };	// MAX UDP payload on typical ethernet

#define STRINGIFY(x) _STRINGIFY(x)
#define _STRINGIFY(x) #x

struct ctrl_state {
  ctrl_state(boost::asio::io_service &io) :
    socket(io, udp::v4()) { }
  udp::socket	socket;
  udp::endpoint remote_endpoint;
};

extern "C" {
  void dev_sim_send_datagram(void *handle, const void *buf, size_t len)
  {
    ctrl_state *us = (ctrl_state *) handle;
    boost::system::error_code ignored_error;
    us->socket.send_to(boost::asio::buffer(buf, len),
		       us->remote_endpoint, 0, ignored_error);
  }
}

int main(int argc, char* argv[])
{
  try {
    if (argc != 2)
      {
	std::cerr << "Usage: client <host>" << std::endl;
	return 1;
      }

    boost::asio::io_service io_service;

    udp::resolver resolver(io_service);
    udp::resolver::query query(udp::v4(), argv[1], STRINGIFY(VRTC_UDP_CTRL_PORT));
    
    ctrl_state us(io_service);
    us.remote_endpoint = *resolver.resolve(query);
    us.socket.connect(us.remote_endpoint);
    //std::cout << "remote port = " << us.remote_endpoint.port() << std::endl;

    while (1){
      //boost::array<char, 1> send_buf  = { 0 };
      //socket.send_to(boost::asio::buffer(send_buf), remote_endpoint);
      //us.socket.send_to(boost::asio::buffer(std::string("Hello VRTC!\n")), us.remote_endpoint);
      us.socket.send(boost::asio::buffer(std::string("Hello VRTC!\n")));

      boost::array<char, 1024> recv_buf;
      udp::endpoint local_endpoint;
      //size_t len = us.socket.receive_from(boost::asio::buffer(recv_buf), local_endpoint);
      size_t len = us.socket.receive(boost::asio::buffer(recv_buf));
      //std::cerr << "vrtc-ping: recv len = " << len << std::endl;

      std::cout.write(recv_buf.data(), len);
    }
  }
  catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
