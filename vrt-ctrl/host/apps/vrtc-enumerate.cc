#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <vrtc/ports.h>

using boost::asio::ip::udp;

enum { MAX_PAYLOAD = 1500 - 28 };	// MAX UDP payload on typical ethernet

#define STRINGIFY(x) _STRINGIFY(x)
#define _STRINGIFY(x) #x

class connection
{
public:
  connection(boost::asio::io_service &io, const std::string &hostname) :
    d_socket(io, udp::v4())
  { 
    udp::resolver resolver(io);
    udp::resolver::query query(udp::v4(), hostname, STRINGIFY(VRTC_UDP_CTRL_PORT));
    d_remote_endpoint = *resolver.resolve(query);
    d_socket.connect(d_remote_endpoint);
  }
  udp::socket	d_socket;
  udp::endpoint d_remote_endpoint;
};

extern "C" {
  void dev_sim_send_datagram(void *handle, const void *buf, size_t len)
  {
    connection *conn = (connection *) handle;
    boost::system::error_code ignored_error;
    conn->d_socket.send(boost::asio::buffer(buf, len), 0, ignored_error);
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
    connection conn(io_service, argv[1]);

    while (1){
      conn.d_socket.send(boost::asio::buffer(std::string("Hello VRTC!\n")));

      boost::array<char, 1024> recv_buf;
      size_t len = conn.d_socket.receive(boost::asio::buffer(recv_buf));
      //std::cerr << "vrtc-ping: recv len = " << len << std::endl;

      std::cout.write(recv_buf.data(), len);
    }
  }
  catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
