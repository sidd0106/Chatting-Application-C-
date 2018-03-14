#include "Client.h"
bool Client::id_check(int id){
	for (unsigned int i = 0; i < (clientptr->id_store).size(); i++){
		if (id == (clientptr->id_store)[i])
			return true;
	}
	return false;
}

void Client::id_print(){
	for (unsigned int i = 0; i < (clientptr->id_store).size(); i++){
		cout << clientptr->id_store[i]<<"\t";
	}cout << endl;
}

wchar_t * Client::convertCharArrayToLPCWSTR(const char* charArray)
{
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
}

bool Client::ProcessPacketType(PacketType _PacketType)
{
	switch (_PacketType)
	{
	case PacketType::ChatMessage: //If PacketType is a chat message PacketType
	{
									  std::string Message; //string to store our message we received
									  if (!GetString(Message)) //Get the chat message and store it in variable: Message
										  return false; //If we do not properly get the chat message, return false
									  unsigned int i;
									  for (i = 0; i < Message.length(); i++){
										  if (Message[i] == ':')
											  break;
									  }
									  if ((clientptr->Reg_status == true || clientptr->Log_status) && i<Message.length()-2  && clientptr->Room_status)
										  std::cout << Message << std::endl; //Display the message to the user
									  break;
	}
	
	case PacketType::RequestChat:
	{
									std::string Message; //string to store our message we received
									if (!GetString(Message)) //Get the chat message and store it in variable: Message
										return false;
									
									wchar_t *argg = clientptr->convertCharArrayToLPCWSTR(Message.c_str());
									SHELLEXECUTEINFO ShRun = { 0 };
									ShRun.cbSize = sizeof(SHELLEXECUTEINFO);
									ShRun.fMask = SEE_MASK_NOCLOSEPROCESS;
									ShRun.hwnd = NULL;
									ShRun.lpVerb = NULL;
									ShRun.lpFile = L"C:\\Users\\LOKESH\\Documents\\Visual Studio 2013\\Projects\\final\\New folder\\Till Single Chat 2\\Chatting Consol\\Debug\\Chatting Consol.exe";
									ShRun.lpParameters = argg;
									ShRun.lpDirectory = L"C:\\Users\\LOKESH\\Documents\\Visual Studio 2013\\Projects\\final\\New folder\\Till Single Chat 2\\Chatting Consol\\Debug\\";
									ShRun.nShow = SW_SHOW;
									ShRun.hInstApp = NULL;

									// Execute the file with the parameters
									if (!ShellExecuteEx(&ShRun))
									{
										// Send error message
										//AfxMessageBox("Unable to open file!", MB_OK);
									}
									break;

	}
	case PacketType::FileTransferByteBuffer:
	{
											   int32_t buffersize; //buffer to hold size of buffer to write to file
											   if (!Getint32_t(buffersize)) //get size of buffer as integer
												   return false;
											   if (!recvall(file.buffer, buffersize)) //get buffer and store it in file.buffer
											   {
												   return false;
											   }
											   file.outfileStream.write(file.buffer, buffersize); //write buffer from file.buffer to our outfilestream
											   file.bytesWritten += buffersize; //increment byteswritten
											   std::cout << "Received byte buffer for file transfer of size: " << buffersize << std::endl;
											   if (!SendPacketType(PacketType::FileTransferRequestNextBuffer)) //send PacketType type to request next byte buffer (if one exists)
												   return false;
											   break;
	}
	case PacketType::FileTransfer_EndOfFile:
	{
											   std::cout << "File transfer completed. File received." << std::endl;
											   std::cout << "File Name: " << file.fileName << std::endl;
											   std::cout << "File Size(bytes): " << file.bytesWritten << std::endl;
											   file.bytesWritten = 0;
											   file.outfileStream.close(); //close file after we are done writing file
											   break;
	}
	case PacketType::ReplyRegister:
	{
									  std::string Message; //string to store our message we received
									  if (!GetString(Message)) //Get the chat message and store it in variable: Message
										  return false; //If we do not properly get the chat message, return false
									  std::cout << Message << std::endl; //Display the message to the user
									  if (Message == "Successfully Registered"){
										  clientptr->Reg_status = true;
									  }
									  break;
	}
	case PacketType::ReplyUserRequest:
	{
									  std::string Message; //string to store our message we received
									  if (!GetString(Message)) //Get the chat message and store it in variable: Message
										  return false; //If we do not properly get the chat message, return false
									  //cout << Message;
									  int l = Message.length();
									  if (l == 0){
										  cout << "Currently No other user is active" << endl;
									  }
									  //counter = 0;
									 // cout << counter << ": ";
									  else{
										  
										  string id = "";
										  for (int i = 0; i < l; i++){
											  if (Message[i] != '!'){
												  cout << Message[i];
											  }
											  else{
												  cout << endl;
											  }
											  if (Message[i] == '#')
											  {
												  i++;
												  while (i < l){
													  id += Message[i];
													  cout << id <<" ";
													  i++;
													  if (Message[i] == ' '){
														 // cout << "\n" << id << "Df"<<endl;
														  clientptr->id_store.push_back(stoi(id));
														  //cout << id << "IDDDD";
														  id = "";
														  break;
													  }
												  }

											  }

										  }
										  cout << endl;
									  }
									  //clientptr->id_print();
									  break;
	}
	
	case PacketType::ReplyLogin:
	{
								   std::string Message; //string to store our message we received
								   if (!GetString(Message)) //Get the chat message and store it in variable: Message
									   return false; //If we do not properly get the chat message, return false
								   std::cout << Message << std::endl; //Display the message to the user
								   if (Message == "Incorrect Username/Password"){
									   //cout << "Hello!";

								   }
								   else
									   clientptr->Log_status = true;
								   break;
	}
	default: //If PacketType type is not accounted for
		std::cout << "Unrecognized PacketType: " << (int32_t)_PacketType << std::endl; //Display that PacketType was not found
		break;
	}
	return true;
}

void Client::ClientThread()
{
	PacketType PacketType;
	while (true)
	{
		if (!clientptr->GetPacketType(PacketType)) //Get PacketType type
			break; //If there is an issue getting the PacketType type, exit this loop
		if (!clientptr->ProcessPacketType(PacketType)) //Process PacketType (PacketType type)
			break; //If there is an issue processing the PacketType, exit this loop
	}
	std::cout << "Lost connection to the server." << std::endl;
	if (clientptr->CloseConnection()) //Try to close socket connection..., If connection socket was closed properly
	{
		std::cout << "Socket to the server was closed successfuly." << std::endl;
	}
	else //If connection socket was not closed properly for some reason from our function
	{
		std::cout << "Socket was not able to be closed." << std::endl;
	}
}

bool Client::RequestFile(std::string FileName)
{
	file.outfileStream.open(FileName, std::ios::binary); //open file to write file to
	file.fileName = FileName; //save file name
	file.bytesWritten = 0; //reset byteswritten to 0 since we are working with a new file
	if (!file.outfileStream.is_open()) //if file failed to open...
	{
		std::cout << "ERROR: Function(Client::RequestFile) - Unable to open file: " << FileName << " for writing.\n";
		return false;
	}
	std::cout << "Requesting file from server: " << FileName << std::endl;
	if (!SendPacketType(PacketType::FileTransferRequestFile)) //send file transfer request PacketType
		return false;
	if (!SendString(FileName, false)) //send file name
		return false;
	return true;
}

bool Client::RequestRegister(string user){
	std::cout << "Requesting For Registration " << std::endl;
	if (!SendPacketType(PacketType::RegisterPacket)) //send file transfer request PacketType
		return false;
	if (!SendString(user, false)) //send file name
		return false;
	return true;
}

bool Client::RequestLogin(string user){
	//std::cout << "Requesting For Registration " << user << std::endl;
	if (!SendPacketType(PacketType::LoginPacket)) //send file transfer request PacketType
		return false;
	if (!SendString(user, false)) //send file name
		return false;
	return true;
}

bool Client::RequestUser(string user){
	//std::cout << "Requesting For Registration " << user << std::endl;
	if (!SendPacketType(PacketType::RequestUser)) //send file transfer request PacketType
		return false;
	if (!SendString(user, false)) //send file name
		return false;
	return true;
}

Client::Client(std::string IP, int PORT)
{
	//Winsock Startup
	WSAData wsaData;
	WORD DllVersion = MAKEWORD(2, 1);
	if (WSAStartup(DllVersion, &wsaData) != 0)
	{
		MessageBoxA(NULL, "Winsock startup failed", "Error", MB_OK | MB_ICONERROR);
		exit(0);
	}

	addr.sin_addr.s_addr = inet_addr(IP.c_str()); //Address (127.0.0.1) = localhost (this pc)
	addr.sin_port = htons(PORT); //Port 
	addr.sin_family = AF_INET; //IPv4 Socket
	clientptr = this; //Update ptr to the client which will be used by our client thread
}

bool Client::Connect()
{
	Connection = socket(AF_INET, SOCK_STREAM, NULL); //Set Connection socket
	if (connect(Connection, (SOCKADDR*)&addr, sizeofaddr) != 0) //If we are unable to connect...
	{
		MessageBoxA(NULL, "Failed to Connect", "Error", MB_OK | MB_ICONERROR);
		return false;
	}

	std::cout << "Welcome to RLS ChatBOX!" << std::endl;
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientThread, NULL, NULL, NULL); //Create the client thread that will receive any data that the server sends.
	return true;
}

bool Client::CloseConnection()
{
	if (closesocket(Connection) == SOCKET_ERROR)
	{
		if (WSAGetLastError() == WSAENOTSOCK) //If socket error is that operation is not performed on a socket (This happens when the socket has already been closed)
			return true; //return true since connection has already been closed

		std::string ErrorMessage = "Failed to close the socket. Winsock Error: " + std::to_string(WSAGetLastError()) + ".";
		MessageBoxA(NULL, ErrorMessage.c_str(), "Error", MB_OK | MB_ICONERROR);
		return false;
	}
	return true;
}