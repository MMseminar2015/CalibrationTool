#include "MainForm.h"

using namespace CalibrationTool;

[STAThreadAttribute]
int main() {

	MainForm ^fm = gcnew MainForm();
	fm->ShowDialog();//
	return 0;

}