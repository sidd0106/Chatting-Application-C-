#include "Client.h"

int main(int argc, char* argv[])
{
	Client myClient("127.0.0.1", 1111); //Create client to localhost ("127.0.0.1") on port 1111

	if (!myClient.Connect()) //If client fails to connect...
	{
		std::cout << "Failed to connect to server..." << std::endl;
		system("pause");
		return 1;
	}
	cout << argc << endl;
	//cout << argv[0];
	cout << argv[0] << endl;
	//cout << argv[1]<<endl;

	cout << "\nSID";
	//cout << "Welcome to APM ChatRoom!" << endl;
	//myClient.RequestFile("donald.jpg");
	std::string userinput; //holds the user's chat message
	//string user, pass;
	//myClient.RequestLogin(user + "!!" + pass);
	Sleep(5);

	while (true)
	{
		std::getline(std::cin, userinput); //Get line if user presses enter and fill the buffer
		if (!myClient.SendString(userinput)) //Send string: userinput, If string fails to send... (Connection issue)
			break; //If send string failed (if connection was closed), leave this loop since we have lost connection to the server
		Sleep(10);
	}

	system("pause");
	return 0;
}

