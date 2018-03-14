#include "Client.h"

int main(int argc, char* argv[])
{
	Client myClient("172.16.7.140", 1111); //Create client to localhost ("127.0.0.1") on port 1111
	
	if (!myClient.Connect()) //If client fails to connect...
	{
		std::cout << "Failed to connect to server..." << std::endl;
		system("pause");
		return 1;
	}
	//cout << argc << endl;
	//cout << argv[0];
	if (argc == 3){
		//cout << argv[0] << endl;
		//cout << argv[1] << endl; //username!!password
		//cout << argv[2] << endl; //reciever's id
		//	cout << argv[3] << endl; //reciever's id
		string arg(argv[1]);
		arg = arg + "/";
		//cout << "\nSID";
		while (!myClient.Log_status){
			myClient.RequestLogin(arg);
			Sleep(500);
		}
		myClient.Log_status = false;
		myClient.RequestChat(argv[2]);
	}
	else if (argc == 4){
		//cout << argv[1] << endl; 
		//cout << argv[2] << endl; 
		//cout << "YE WALA bhi\n";
		string arg = argv[2];
		arg = arg + "/";
		while (!myClient.Log_status){
			myClient.RequestLogin(arg);
			Sleep(500);
		}
		int id = stoi(argv[1]);
		myClient.set_id(id);
		myClient.Log_status = false;
		myClient.ReplyChat(argv[1]);

	}
	//cout << "Welcome to APM ChatRoom!" << endl;
	//myClient.RequestFile("donald.jpg");
	std::string userinput; //holds the user's chat message
	//string user, pass;
	//myClient.RequestLogin(user + "!!" + pass);
	Sleep(5);
	//cout << "first\n";
	//myClient.Log_status = true; myClient.global_id = 11;
	//cout << &myClient << " "<<clientptr << endl;
	//cout << "second\n";
	while (true)
	{
		std::getline(std::cin, userinput); //Get line if user presses enter and fill the buffer
		if (!myClient.SendString(userinput)) //Send string: userinput, If string fails to send... (Connection issue)
			break; //If send string failed (if connection was closed), leave this loop since we have lost connection to the server
		
		if (!myClient.SendStringID(false)) //Send string: userinput, If string fails to send... (Connection issue)
			break; //If send string failed (if connection was closed), leave this loop since we have lost connection to the server
		Sleep(10);
	}

	system("pause");
	return 0;
}

