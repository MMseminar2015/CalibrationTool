#include "MainForm.h"

using namespace CalibrationTool;

[STAThreadAttribute]
int main() {

	MainForm ^fm = gcnew MainForm();
	fm->ShowDialog();//form�̕\��
	return 0;

}