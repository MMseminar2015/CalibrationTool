#include "MainForm.h"

using namespace CalibrationTool;

[STAThreadAttribute]
int main() {
	//MainForm ^fm = gcnew MainForm();
	//fm->ShowDialog();
	//return 0;
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew CalibrationTool::MainForm());
	return 0;
}