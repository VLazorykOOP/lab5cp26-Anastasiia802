#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	// Важливо: замініть 'Lab5_Graphics' на назву вашого проекту, якщо вона інша
	Lab5_Graphics::MyForm form;
	Application::Run(% form);
}