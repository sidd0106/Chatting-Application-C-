#include "Register_Form.h"
using namespace System;
using namespace System::Windows::Forms;
[STAThread]
void register_form(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	ChatRoom::Register_Form form;
	Application::Run(%form);
}

