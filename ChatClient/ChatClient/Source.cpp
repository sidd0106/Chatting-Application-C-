#include "Client.h"


int main()
{
	Client myClient("127.0.0.1", 1111); //Create client to localhost ("127.0.0.1") on port 1111

	if (!myClient.Connect()) //If client fails to connect...
	{
		std::cout << "Failed to connect to server..." << std::endl;
		system("pause");
		return 1;
	}
	//cout << "Welcome to APM ChatRoom!" << endl;
	//myClient.RequestFile("donald.jpg");
	std::string userinput; //holds the user's chat message
	string user, pass;
	while (!myClient.Reg_status && !myClient.Log_status){
		cout << "Please Enter:"<<endl<<"0 -> Login"<<endl<<"1 -> Register"<<endl;
		int var;
		cin >> var;
		if (var){
			cout << "Enter username: ";
			cin >> user;
			cout << "Enter Password: ";
			cin >> pass;
			myClient.RequestRegister(user + "!!" + pass);
			Sleep(500);
			//system("pause");

		}
		else{
			
			cout << "Enter username: ";
			cin >> user;
			cout << "Enter Password: ";
			cin >> pass;
			myClient.RequestLogin(user + "!!" + pass);
			Sleep(500);
		}
	}
	int type=1;
	while (type != 2){
		cout << "Enter \n1-> single chat \n2-> ChatRoom\n";
		cin >> type;
		int u_send;
		int flag = 1;
		if (type == 1){
			cout << "User's active are" << endl;
			myClient.RequestUser(user);
			cout << "Enter User ID" << endl;
			cin >> u_send;
			while (clientptr->id_check(u_send)){
				cout << "Please enter correct user ID" << endl;
				cin >> u_send;
			}
			//char *ptr;
			string arg = user + " " + pass + " " + to_string(u_send) ;
			Sleep(5);
			//CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)NewConsole, NULL, NULL, NULL);
			HANDLE hProcess = NULL;
			HANDLE hThread = NULL;
			STARTUPINFO si;
			PROCESS_INFORMATION pi;
			si.cb = sizeof(si);
			ZeroMemory(&si, sizeof(si));
			ZeroMemory(&pi, sizeof(pi));
			while (CreateProcess(L"C:\\Users\\LOKESH\\Documents\\Visual Studio 2013\\Projects\\final\\New folder\\New folder\\Chatting Consol\\Debug\\Chatting Consol.exe",
				(TCHAR*)("SIDD id"),
				NULL,
				NULL,
				false,
				CREATE_NEW_CONSOLE,
				NULL,
				NULL,
				&si,
				&pi) == 0);
			int t;
			//WaitForSingleObject(pi.hProcess, INFINITE);
			cin >> t;
			//CloseHandle(pi.hThread);
			//CloseHandle(pi.hProcess);
			Sleep(5);

			//return 0;

		}
	}
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

