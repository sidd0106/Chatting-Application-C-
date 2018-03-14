#include "Client.h"


int main()
{
	Client myClient("172.16.7.140", 1111); //Create client to localhost ("127.0.0.1") on port 1111

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
	string v;
	while (!myClient.Reg_status && !myClient.Log_status){
		cout << "Please Enter:"<<endl<<"0 -> Login"<<endl<<"1 -> Register"<<endl;
		cin >> v;
		int var;
		try {
			var = stoi(v);
			if (var == 1){
				cout << "Enter username: ";
				cin >> user;
				cout << "Enter Password: ";
				HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
				DWORD mode = 0;
				GetConsoleMode(hStdin, &mode);
				SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
				cin >> pass;
				SetConsoleMode(hStdin, mode);
				cout << endl;
				myClient.RequestRegister(user + "!!" + pass);
				Sleep(500);
				//system("pause");

			}
			else if (var == 0){

				cout << "Enter username: ";
				cin >> user;
				cout << "Enter Password: ";
				HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
				DWORD mode = 0;
				GetConsoleMode(hStdin, &mode);
				SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));
				cin >> pass;
				SetConsoleMode(hStdin, mode);
				cout << endl;
				myClient.RequestLogin(user + "!!" + pass);
				Sleep(500);
			}
			else{
				cout << "Enter Valid choice" << endl;
				//char c=getchar();
				Sleep(500);
			}
		}
		catch (std::invalid_argument& e){
			cout << "Enter Valid choice" << endl;
		}
		catch (std::out_of_range& e){
			cout << "Enter Valid choice" << endl;
		}
		catch (...) {
			cout << "Enter Valid choice" << endl;
		}
		
	}
	string t;
	//int type;
	here:
	int type=1;
	while (type != 2){
		cout << "Enter \n1-> single chat \n2-> ChatRoom\n";
		cin >> t;
		int u_send;
		try
		{
			type = stoi(t);
			if (type == 1){
				cout << "Press -1 to refresh user list" << endl;
				do{
					cout << "****************************Active Users are*****************************" << endl << "ID Username" << endl;
					myClient.RequestUser(user);
					//cout << "Enter User ID" << endl;
					cin >> u_send;
				} while (u_send == -1);
				while (!clientptr->id_check(u_send)){
					cout << "Please enter correct user ID" << endl;
					cin >> u_send;
				}
				//char *ptr;
				string arg = user + "!!" + pass + " " + to_string(u_send);
				Sleep(5);
				//CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)NewConsole, NULL, NULL, NULL);
				/*HANDLE hProcess = NULL;
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
				&pi) == 0);*/
				wchar_t *argg = myClient.convertCharArrayToLPCWSTR(arg.c_str());
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
				//ShellExecute(0, L"open", L"C:\\Users\\LOKESH\\Documents\\Visual Studio 2013\\Projects\\final\\New folder\\New folder\\Chatting Consol\\Debug\\Chatting Consol.exe", arg, 0, SW_SHOWNORMAL);
				//int t;
				//WaitForSingleObject(pi.hProcess, INFINITE);
				//cin >> t;
				//CloseHandle(pi.hThread);
				//CloseHandle(pi.hProcess);
				Sleep(5);

				//return 0;

			}
		}
		catch (std::invalid_argument& e){
			cout << "Enter Valid choice" << endl;
		}
		catch (std::out_of_range& e){
			cout << "Enter Valid choice" << endl;
		}
		catch (...) {
			cout << "Enter Valid choice" << endl;
		}
		
	}
	myClient.Room_status = true;
	cout << "*************************Welcome to Chatroom*************************" << endl;
	cout << "Enter exit to exit from Chatroom" << endl;
	Sleep(5);

	while (true)
	{
		std::getline(std::cin, userinput); //Get line if user presses enter and fill the buffer
		if (userinput == "exit"){
			myClient.Room_status = false;
			goto here;
		}
		if (!myClient.SendString(userinput)) //Send string: userinput, If string fails to send... (Connection issue)
			break; //If send string failed (if connection was closed), leave this loop since we have lost connection to the server
		Sleep(10);
	}
	system("pause");
	return 0;
}

