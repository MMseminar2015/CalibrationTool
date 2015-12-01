#include "Configurations.h"
#include "opencv2\opencv.hpp"

using namespace System::IO;
using namespace System::Xml::Serialization;
using namespace System::Runtime::InteropServices;

Configurations::Configurations()
{
}
Configurations::Configurations(int chess_width, int chess_height, double chess_size, System::String^ savedir,int numimg) {
	this->chess_width = chess_width;
	this->chess_height = chess_height;
	this->chess_size = chess_size;
	this->savedir = savedir;
	this->numimg = numimg;
}


Configurations^ Configurations::Load(System::String^ configFile) {
	try {
		XmlSerializer^ serializer = gcnew XmlSerializer(Configurations::typeid);
		FileStream^ fs = gcnew FileStream(configFile, FileMode::Open);
		Configurations^ ret = (Configurations^)serializer->Deserialize(fs);
		fs->Close();
		return ret;
	}
	catch (System::Exception^ e) {
		return gcnew Configurations(7, 10, 16.8, "", 20);
	}
}

System::Void Configurations::Save(System::String^ configFile, Configurations^ conf) {
	XmlSerializer^ serializer = gcnew XmlSerializer(Configurations::typeid);
	FileStream^ fs = gcnew FileStream(configFile, FileMode::OpenOrCreate);
	serializer->Serialize(fs, conf);
	fs->Close();
}