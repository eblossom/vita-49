#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <vrtc/ports.h>

using boost::asio::ip::udp;

enum { MAX_PAYLOAD = 1500 - 28 };	// MAX UDP payload on typical ethernet

#define STRINGIFY(x) _STRINGIFY(x)
#define _STRINGIFY(x) #x

class connection
{
  udp::socket			d_socket;
  char 				d_data[MAX_PAYLOAD];

  boost::function<void (const boost::system::error_code &error,
			const void *buffer,
			std::size_t bytes_transfered)> d_recv_handler;
  
  void handle_receive(const boost::system::error_code &error,
		      std::size_t bytes_transfered)
  {
    d_recv_handler(error, d_data, bytes_transfered);
    d_socket.async_receive(boost::asio::buffer(d_data, MAX_PAYLOAD),
			   boost::bind(&connection::handle_receive, this,
				       boost::asio::placeholders::error,
				       boost::asio::placeholders::bytes_transferred));
  }

public:
  connection(boost::asio::io_service &io, const std::string &hostname) :
    d_socket(io, udp::v4())
  { 
    udp::resolver resolver(io);
    udp::resolver::query query(udp::v4(), hostname, STRINGIFY(VRTC_UDP_CTRL_PORT));
    udp::endpoint remote_endpoint = *resolver.resolve(query);
    d_socket.connect(remote_endpoint);
  }

  template<typename RecvHandler>
  void start_receive(RecvHandler recv_handler)
  {
    d_recv_handler = recv_handler;
    d_socket.async_receive(boost::asio::buffer(d_data, MAX_PAYLOAD),
			   boost::bind(&connection::handle_receive, this,
				       boost::asio::placeholders::error,
				       boost::asio::placeholders::bytes_transferred));
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

extern "C" {
  void dev_sim_send_datagram(void *handle, const void *buf, size_t len)
  {
    connection *conn = (connection *) handle;
    boost::system::error_code ignored_error;
    conn->send(boost::asio::buffer(buf, len), ignored_error);
  }
}

// ------------------------------------------------------------------------

class control {
  connection d_conn;

public:
  control(boost::asio::io_service &io_service,
	  const std::string &hostname)
    : d_conn(io_service, hostname)
  {
    d_conn.start_receive(boost::bind(&control::handle_rcvd_control_pkt, this,
				     _1, _2, _3));
    send_packet();
  }

  void
  send_packet()
  {
    boost::system::error_code ignored_error;
    d_conn.send(boost::asio::buffer(std::string("Hello VRTC!\n")), ignored_error);
  }

  void
  handle_rcvd_control_pkt(const boost::system::error_code &error,
			  const void *buffer, std::size_t bytes_transferred)
  {
    //std::cout << "vrtc-enumerate: recv len = " << bytes_transferred << std::endl;
    std::cout.write((const char *) buffer, bytes_transferred);
    send_packet();
  }
};

int main(int argc, char* argv[])
{
  try {
    if (argc != 2)
      {
	std::cerr << "Usage: client <host>" << std::endl;
	return 1;
      }

    boost::asio::io_service io_service;
    control ctrl(io_service, argv[1]);

    io_service.run();
  }
  catch (std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
