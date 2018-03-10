#include "Server.h"
int main()
{
	Server MyServer(1111, true); //Create server on port 100
	Database dm;
	for (int i = 0; i < 100; i++) //Up to 100 times...
	{
		MyServer.ListenForNewConnection(); //Accept new connection (if someones trying to connect)
	}
	system("pause");
	return 0;
}