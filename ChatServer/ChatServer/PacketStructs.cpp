#include "PacketStructs.h"
#include <Windows.h>
#include<stdint.h>

namespace PS
{
	ChatMessage::ChatMessage(std::string msg)
	{
		message = msg;
	}
	ReplyRegister::ReplyRegister(std::string msg){
		message = msg;
	}
	ReplyUserRequest::ReplyUserRequest(std::string msg){
		message = msg;
	}
	RequestChat::RequestChat(std::string msg){
		message = msg;
	}
	Packet ChatMessage::toPacket()
	{
		const int packetsize = sizeof(int32_t)* 2 + message.size()*sizeof(char); //Calculate total size of buffer for packet contents
		char * buffer = new char[packetsize]; //Create buffer big enough to hold all info for message
		int32_t packettype = htonl((int32_t)PacketType::ChatMessage); //Convert packet type (int32_t) to network byte order
		int32_t messagesize = htonl(message.size()); //Convert message size (int32_t) to network byte order
		memcpy(buffer, &packettype, sizeof(int32_t)); //Copy Packet Type to first 4 bytes of buffer
		memcpy(buffer + sizeof(int32_t), &messagesize, sizeof(int32_t)); //Copy size to next 4 bytes of buffer
		memcpy(buffer + sizeof(int32_t)* 2, message.c_str(), message.size()*sizeof(char)); //Copy message to fill the rest of the buffer
		Packet p(buffer, packetsize); //Create packet to be returned
		return p;
	}
	ReplyChat::ReplyChat(std::string msg){
		message = msg;
	}
	Packet ReplyChat::toPacket()
	{
		const int packetsize = sizeof(int32_t)* 2 + message.size()*sizeof(char); //Calculate total size of buffer for packet contents
		char * buffer = new char[packetsize]; //Create buffer big enough to hold all info for message
		int32_t packettype = htonl((int32_t)PacketType::ReplyChat); //Convert packet type (int32_t) to network byte order
		int32_t messagesize = htonl(message.size()); //Convert message size (int32_t) to network byte order
		memcpy(buffer, &packettype, sizeof(int32_t)); //Copy Packet Type to first 4 bytes of buffer
		memcpy(buffer + sizeof(int32_t), &messagesize, sizeof(int32_t)); //Copy size to next 4 bytes of buffer
		memcpy(buffer + sizeof(int32_t)* 2, message.c_str(), message.size()*sizeof(char)); //Copy message to fill the rest of the buffer
		Packet p(buffer, packetsize); //Create packet to be returned
		return p;
	}
	SingleChatMessage::SingleChatMessage(std::string msg){
		message = msg;
	}
	Packet SingleChatMessage::toPacket()
	{
		const int packetsize = sizeof(int32_t)* 2 + message.size()*sizeof(char); //Calculate total size of buffer for packet contents
		char * buffer = new char[packetsize]; //Create buffer big enough to hold all info for message
		int32_t packettype = htonl((int32_t)PacketType::SingleChatMessage); //Convert packet type (int32_t) to network byte order
		int32_t messagesize = htonl(message.size()); //Convert message size (int32_t) to network byte order
		memcpy(buffer, &packettype, sizeof(int32_t)); //Copy Packet Type to first 4 bytes of buffer
		memcpy(buffer + sizeof(int32_t), &messagesize, sizeof(int32_t)); //Copy size to next 4 bytes of buffer
		memcpy(buffer + sizeof(int32_t)* 2, message.c_str(), message.size()*sizeof(char)); //Copy message to fill the rest of the buffer
		Packet p(buffer, packetsize); //Create packet to be returned
		return p;
	}
	Packet RequestChat::toPacket()
	{
		const int packetsize = sizeof(int32_t)* 2 + message.size()*sizeof(char); //Calculate total size of buffer for packet contents
		char * buffer = new char[packetsize]; //Create buffer big enough to hold all info for message
		int32_t packettype = htonl((int32_t)PacketType::RequestChat); //Convert packet type (int32_t) to network byte order
		int32_t messagesize = htonl(message.size()); //Convert message size (int32_t) to network byte order
		memcpy(buffer, &packettype, sizeof(int32_t)); //Copy Packet Type to first 4 bytes of buffer
		memcpy(buffer + sizeof(int32_t), &messagesize, sizeof(int32_t)); //Copy size to next 4 bytes of buffer
		memcpy(buffer + sizeof(int32_t)* 2, message.c_str(), message.size()*sizeof(char)); //Copy message to fill the rest of the buffer
		Packet p(buffer, packetsize); //Create packet to be returned
		return p;
	}

	Packet FileDataBuffer::toPacket()
	{
		const int packetsize = sizeof(int32_t)* 2 + size; //Calcualte total size for of buffer for packet contents
		char * buffer = new char[packetsize]; //Create buffer big enough to hold all filedatabuffer contents
		int32_t packettype = htonl((int32_t)PacketType::FileTransferByteBuffer); //Convert packet type (int32_t) to network byte order
		int32_t buffersize = htonl(size); //Convert buffer size to network byte order
		memcpy(buffer, &packettype, sizeof(int32_t)); //Copy packet type to first 4 bytes
		memcpy(buffer + sizeof(int32_t), &buffersize, sizeof(int32_t)); //Copy buffersize to next 4 bytes of buffer
		memcpy(buffer + sizeof(int32_t)* 2, databuffer, size); //Copy data to buffer that was stored upon construction
		Packet p(buffer, packetsize); //Create packet to be returned so it can be appended to the Packet Manager
		return p;
	}
	Packet ReplyRegister::toPacket(){
		const int packetsize = sizeof(int32_t)* 2 + message.size()*sizeof(char); //Calculate total size of buffer for packet contents
		char * buffer = new char[packetsize]; //Create buffer big enough to hold all info for message
		int32_t packettype = htonl((int32_t)PacketType::ReplyRegister); //Convert packet type (int32_t) to network byte order
		int32_t messagesize = htonl(message.size()); //Convert message size (int32_t) to network byte order
		memcpy(buffer, &packettype, sizeof(int32_t)); //Copy Packet Type to first 4 bytes of buffer
		memcpy(buffer + sizeof(int32_t), &messagesize, sizeof(int32_t)); //Copy size to next 4 bytes of buffer
		memcpy(buffer + sizeof(int32_t)* 2, message.c_str(), message.size()*sizeof(char)); //Copy message to fill the rest of the buffer
		Packet p(buffer, packetsize); //Create packet to be returned
		return p;
	}
	ReplyLogin::ReplyLogin(std::string msg){
		message = msg;
	}
	Packet ReplyLogin::toPacket()
	{
		const int packetsize = sizeof(int32_t)* 2 + message.size()*sizeof(char); //Calculate total size of buffer for packet contents
		char * buffer = new char[packetsize]; //Create buffer big enough to hold all info for message
		int32_t packettype = htonl((int32_t)PacketType::ReplyLogin); //Convert packet type (int32_t) to network byte order
		int32_t messagesize = htonl(message.size()); //Convert message size (int32_t) to network byte order
		memcpy(buffer, &packettype, sizeof(int32_t)); //Copy Packet Type to first 4 bytes of buffer
		memcpy(buffer + sizeof(int32_t), &messagesize, sizeof(int32_t)); //Copy size to next 4 bytes of buffer
		memcpy(buffer + sizeof(int32_t)* 2, message.c_str(), message.size()*sizeof(char)); //Copy message to fill the rest of the buffer
		Packet p(buffer, packetsize); //Create packet to be returned
		return p;
	}
	Packet ReplyUserRequest::toPacket()
	{
		const int packetsize = sizeof(int32_t)* 2 + message.size()*sizeof(char); //Calculate total size of buffer for packet contents
		char * buffer = new char[packetsize]; //Create buffer big enough to hold all info for message
		int32_t packettype = htonl((int32_t)PacketType::ReplyUserRequest); //Convert packet type (int32_t) to network byte order
		int32_t messagesize = htonl(message.size()); //Convert message size (int32_t) to network byte order
		memcpy(buffer, &packettype, sizeof(int32_t)); //Copy Packet Type to first 4 bytes of buffer
		memcpy(buffer + sizeof(int32_t), &messagesize, sizeof(int32_t)); //Copy size to next 4 bytes of buffer
		memcpy(buffer + sizeof(int32_t)* 2, message.c_str(), message.size()*sizeof(char)); //Copy message to fill the rest of the buffer
		Packet p(buffer, packetsize); //Create packet to be returned
		return p;
	}
}