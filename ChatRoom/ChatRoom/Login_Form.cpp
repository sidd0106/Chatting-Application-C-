#include "Login_Form.h"
using namespace System;
using namespace System::Windows::Forms;
[STAThread]
void login(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	ChatRoom::Login_Form form;
	Application::Run(%form);
}

