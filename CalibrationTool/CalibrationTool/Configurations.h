#pragma once
#include <string>

public ref class Configurations
{
public:
	int chess_width;
	int chess_height;
	double chess_size;
	System::String^ savedir;
	int numimg;


public:
	Configurations();
	Configurations(int chess_width, int chess_height, double chess_size, System::String^ savedir,int numimg);


public: static Configurations^ Load(System::String^ configFile);
public: static System::Void Save(System::String^ configFile, Configurations^ conf);
};

