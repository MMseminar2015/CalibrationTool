#pragma once
#include <string>
#include "Configurations.h"

namespace CalibrationTool {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// NewProjectForm の概要
	/// </summary>
	public ref class NewProjectForm : public System::Windows::Forms::Form
	{
	private:
		System::String^ dir;
		int c_width;
		int c_height;
		int numimg;
	private: System::Windows::Forms::PictureBox^  chessimg;
	private: System::Windows::Forms::NumericUpDown^  NumImgnumericUpDown;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Label^  label7;


			 double c_size;



	public:
		NewProjectForm(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクター コードを追加します
			//
		}

		NewProjectForm(Configurations^ conf)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクター コードを追加します
			//
			SaveDir->Text = conf->savedir;
			ChessHeight->Value = conf->chess_height;
			ChessWidth->Value = conf->chess_width;
			ChessSize->Value = (Decimal)conf->chess_size;

			DrawChessBoard();
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~NewProjectForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  SaveDir;
	protected:

	protected:


	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;

	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::NumericUpDown^  ChessSize;

	private: System::Windows::Forms::NumericUpDown^  ChessHeight;

	private: System::Windows::Forms::NumericUpDown^  ChessWidth;
	private: System::Windows::Forms::Button^  OK_Button;



	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Button^  BrowseButton;
	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog1;

	private:
		/// <summary>
		/// 必要なデザイナー変数です。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナー サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディターで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->SaveDir = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->NumImgnumericUpDown = (gcnew System::Windows::Forms::NumericUpDown());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->chessimg = (gcnew System::Windows::Forms::PictureBox());
			this->ChessSize = (gcnew System::Windows::Forms::NumericUpDown());
			this->ChessHeight = (gcnew System::Windows::Forms::NumericUpDown());
			this->ChessWidth = (gcnew System::Windows::Forms::NumericUpDown());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->OK_Button = (gcnew System::Windows::Forms::Button());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->BrowseButton = (gcnew System::Windows::Forms::Button());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NumImgnumericUpDown))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chessimg))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ChessSize))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ChessHeight))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ChessWidth))->BeginInit();
			this->SuspendLayout();
			// 
			// SaveDir
			// 
			this->SaveDir->Location = System::Drawing::Point(12, 34);
			this->SaveDir->Name = L"SaveDir";
			this->SaveDir->Size = System::Drawing::Size(419, 19);
			this->SaveDir->TabIndex = 0;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->NumImgnumericUpDown);
			this->groupBox1->Controls->Add(this->label8);
			this->groupBox1->Controls->Add(this->label7);
			this->groupBox1->Controls->Add(this->chessimg);
			this->groupBox1->Controls->Add(this->ChessSize);
			this->groupBox1->Controls->Add(this->ChessHeight);
			this->groupBox1->Controls->Add(this->ChessWidth);
			this->groupBox1->Controls->Add(this->label5);
			this->groupBox1->Controls->Add(this->label4);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Location = System::Drawing::Point(12, 88);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(419, 302);
			this->groupBox1->TabIndex = 3;
			this->groupBox1->TabStop = false;
			// 
			// NumImgnumericUpDown
			// 
			this->NumImgnumericUpDown->Location = System::Drawing::Point(27, 180);
			this->NumImgnumericUpDown->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->NumImgnumericUpDown->Name = L"NumImgnumericUpDown";
			this->NumImgnumericUpDown->Size = System::Drawing::Size(70, 19);
			this->NumImgnumericUpDown->TabIndex = 15;
			this->NumImgnumericUpDown->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 20, 0, 0, 0 });
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(8, 165);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(92, 12);
			this->label8->TabIndex = 14;
			this->label8->Text = L"Number of Image";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(8, 16);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(71, 12);
			this->label7->TabIndex = 13;
			this->label7->Text = L"Chess Board";
			// 
			// chessimg
			// 
			this->chessimg->Location = System::Drawing::Point(179, 16);
			this->chessimg->Name = L"chessimg";
			this->chessimg->Size = System::Drawing::Size(234, 280);
			this->chessimg->TabIndex = 12;
			this->chessimg->TabStop = false;
			// 
			// ChessSize
			// 
			this->ChessSize->DecimalPlaces = 1;
			this->ChessSize->Increment = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1, 0, 0, 65536 });
			this->ChessSize->Location = System::Drawing::Point(9, 109);
			this->ChessSize->Name = L"ChessSize";
			this->ChessSize->Size = System::Drawing::Size(70, 19);
			this->ChessSize->TabIndex = 11;
			this->ChessSize->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 168, 0, 0, 65536 });
			// 
			// ChessHeight
			// 
			this->ChessHeight->Location = System::Drawing::Point(103, 51);
			this->ChessHeight->Name = L"ChessHeight";
			this->ChessHeight->Size = System::Drawing::Size(70, 19);
			this->ChessHeight->TabIndex = 10;
			this->ChessHeight->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->ChessHeight->ValueChanged += gcnew System::EventHandler(this, &NewProjectForm::Chess_ValueChanged);
			// 
			// ChessWidth
			// 
			this->ChessWidth->Location = System::Drawing::Point(9, 51);
			this->ChessWidth->Name = L"ChessWidth";
			this->ChessWidth->Size = System::Drawing::Size(70, 19);
			this->ChessWidth->TabIndex = 9;
			this->ChessWidth->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 7, 0, 0, 0 });
			this->ChessWidth->ValueChanged += gcnew System::EventHandler(this, &NewProjectForm::Chess_ValueChanged);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(101, 36);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(38, 12);
			this->label5->TabIndex = 8;
			this->label5->Text = L"Height";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(7, 36);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(33, 12);
			this->label4->TabIndex = 7;
			this->label4->Text = L"Width";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(7, 91);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(26, 12);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Size";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(85, 111);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(20, 12);
			this->label2->TabIndex = 5;
			this->label2->Text = L"cm";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(85, 54);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(12, 12);
			this->label1->TabIndex = 3;
			this->label1->Text = L"X";
			// 
			// OK_Button
			// 
			this->OK_Button->Location = System::Drawing::Point(356, 396);
			this->OK_Button->Name = L"OK_Button";
			this->OK_Button->Size = System::Drawing::Size(75, 23);
			this->OK_Button->TabIndex = 4;
			this->OK_Button->Text = L"OK";
			this->OK_Button->UseVisualStyleBackColor = true;
			this->OK_Button->Click += gcnew System::EventHandler(this, &NewProjectForm::OK_Button_Click);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(10, 16);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(81, 12);
			this->label6->TabIndex = 6;
			this->label6->Text = L"Save Directory";
			// 
			// BrowseButton
			// 
			this->BrowseButton->Location = System::Drawing::Point(356, 59);
			this->BrowseButton->Name = L"BrowseButton";
			this->BrowseButton->Size = System::Drawing::Size(75, 23);
			this->BrowseButton->TabIndex = 7;
			this->BrowseButton->Text = L"Browse";
			this->BrowseButton->UseVisualStyleBackColor = true;
			this->BrowseButton->Click += gcnew System::EventHandler(this, &NewProjectForm::BrowseButton_Click);
			// 
			// NewProjectForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(442, 422);
			this->Controls->Add(this->BrowseButton);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->OK_Button);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->SaveDir);
			this->Name = L"NewProjectForm";
			this->Text = L"NewProjectForm";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->NumImgnumericUpDown))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chessimg))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ChessSize))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ChessHeight))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ChessWidth))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void BrowseButton_Click(System::Object^  sender, System::EventArgs^  e) {
		folderBrowserDialog1->ShowNewFolderButton = true;
		if (folderBrowserDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			SaveDir->Text = folderBrowserDialog1->SelectedPath;

		}
	}
private: System::Void OK_Button_Click(System::Object^  sender, System::EventArgs^  e) {
	dir = SaveDir->Text;
	c_width = int(ChessWidth->Value);
	c_height = int(ChessHeight->Value);
	c_size = double(ChessSize->Value);
	numimg = int(NumImgnumericUpDown->Value);

	this->Close();
}
		 public:
			 System::String^ GetSaveDirectory() { return dir; }
			 int GetChessWidth(){ return c_width; }
			 int GetChessHeight() { return c_height; }
			 double GetChessSize() { return c_size; }
			 int GetNumImg() { return numimg; }


private: System::Void Chess_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
	DrawChessBoard();
}

private: System::Void DrawChessBoard() {
	Bitmap^ canvas = gcnew Bitmap(chessimg->Width, chessimg->Height);
	//ImageオブジェクトのGraphicsオブジェクトを作成する
	Graphics^ g = Graphics::FromImage(canvas);

	System::Drawing::Region^ rgn= gcnew System::Drawing::Region();

	int size = chessimg->Width / int(ChessWidth->Value);
	if (size > chessimg->Height / int(ChessHeight->Value))
		size = chessimg->Height / int(ChessHeight->Value);

	for (int i = 0; i < int(ChessWidth->Value); i++) {
		for (int j = 0; j < int(ChessHeight->Value); j++) {
			System::Drawing::Rectangle^ rect=gcnew System::Drawing::Rectangle(size*i, size*j, size, size);
			if((i+j)%2==0)
				g->FillRectangle(Brushes::Black, *rect);
			else
				g->FillRectangle(Brushes::White, *rect);
			

		}
	}
	//System::Drawing::Rectangle^ rect1;
	//System::Drawing::Rectangle^ rect2;

	////Regionで使用する2つの領域
	//rect1 = gcnew System::Drawing::Rectangle(0, 0, 40, 40);
	//rect2 = gcnew System::Drawing::Rectangle(20, 20, 40, 40);

	////rect1を青で塗る
	//g->FillRectangle(Brushes::Blue, *rect1);
	////rect2を緑で塗る
	//g->FillRectangle(Brushes::Green, *rect2);
	////rect1でRegionを作成
	//rgn = gcnew System::Drawing::Region(*rect1);
	////Union(和集合)によりrect2を追加
	//rgn->Union(*rect2);
	////出来上がったRegionを黒で描画
	//g->FillRegion(Brushes::Black, rgn);


	//リソースを解放する
	//g->Dispose();

	//PictureBox1に表示する
	chessimg->Image = canvas;

}

};
}
