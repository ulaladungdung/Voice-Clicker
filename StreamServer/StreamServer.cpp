// StreamServer.cpp : Defines the exported functions for the DLL application.
//

#include"StreamServer.h"


StreamServer::StreamServer(boost::asio::io_context& io_context, Buffer* buffer, int port)
	: socket_(io_context, udp::endpoint(udp::v4(), port)) {

	buffer_ = buffer;
	start_receive();
}

StreamServer::~StreamServer()
{
}

void StreamServer::start_receive()
{
	socket_.async_receive_from(
		boost::asio::buffer(reinterpret_cast<char*>(buffer_->getWriterPointer()), 384), remote_endpoint_,
		boost::bind(&StreamServer::handle_receive, this,
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
}

void StreamServer::handle_receive(const boost::system::error_code& error,
	std::size_t /*bytes_transferred*/)
{
	if (!error)
	{
		start_receive();
	}
}

void StreamServer::handle_send(boost::shared_ptr<std::string> /*message*/,
	const boost::system::error_code& /*error*/,
	std::size_t /*bytes_transferred*/)
{
}

