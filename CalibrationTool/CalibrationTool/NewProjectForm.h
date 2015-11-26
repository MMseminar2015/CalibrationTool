#pragma once
#include <string>

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
	private: System::Windows::Forms::PictureBox^  chessimg;


			 double c_size;



	public:
		NewProjectForm(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクター コードを追加します
			//
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


	private: System::Windows::Forms::GroupBox^  groupBox2;
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
			this->ChessSize = (gcnew System::Windows::Forms::NumericUpDown());
			this->ChessHeight = (gcnew System::Windows::Forms::NumericUpDown());
			this->ChessWidth = (gcnew System::Windows::Forms::NumericUpDown());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->OK_Button = (gcnew System::Windows::Forms::Button());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->BrowseButton = (gcnew System::Windows::Forms::Button());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->chessimg = (gcnew System::Windows::Forms::PictureBox());
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ChessSize))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ChessHeight))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ChessWidth))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chessimg))->BeginInit();
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
			this->groupBox1->Controls->Add(this->chessimg);
			this->groupBox1->Controls->Add(this->ChessSize);
			this->groupBox1->Controls->Add(this->ChessHeight);
			this->groupBox1->Controls->Add(this->ChessWidth);
			this->groupBox1->Controls->Add(this->label5);
			this->groupBox1->Controls->Add(this->label4);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->label1);
			this->groupBox1->Location = System::Drawing::Point(12, 268);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(419, 302);
			this->groupBox1->TabIndex = 3;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Chess Board";
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
			this->OK_Button->Location = System::Drawing::Point(355, 576);
			this->OK_Button->Name = L"OK_Button";
			this->OK_Button->Size = System::Drawing::Size(75, 23);
			this->OK_Button->TabIndex = 4;
			this->OK_Button->Text = L"OK";
			this->OK_Button->UseVisualStyleBackColor = true;
			this->OK_Button->Click += gcnew System::EventHandler(this, &NewProjectForm::OK_Button_Click);
			// 
			// groupBox2
			// 
			this->groupBox2->Location = System::Drawing::Point(12, 122);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(420, 124);
			this->groupBox2->TabIndex = 5;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Camera";
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
			// chessimg
			// 
			this->chessimg->Location = System::Drawing::Point(179, 16);
			this->chessimg->Name = L"chessimg";
			this->chessimg->Size = System::Drawing::Size(234, 280);
			this->chessimg->TabIndex = 12;
			this->chessimg->TabStop = false;
			// 
			// NewProjectForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(442, 611);
			this->Controls->Add(this->BrowseButton);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->OK_Button);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->SaveDir);
			this->Name = L"NewProjectForm";
			this->Text = L"NewProjectForm";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ChessSize))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ChessHeight))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->ChessWidth))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chessimg))->EndInit();
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

	this->Close();
}
		 public:
			 System::String^ GetSaveDirectory() { return dir; }
			 int GetChessWidth(){ return c_width; }
			 int GetChessHeight() { return c_height; }
			 double GetChessSize() { return c_size; }


private: System::Void Chess_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
}

private: System::Void DrawChessBoard() {
	//Bitmap^ canvas = gcnew Bitmap(chessimg->Width, chessimg->.Height);
	////ImageオブジェクトのGraphicsオブジェクトを作成する
	//Graphics^ g = Graphics::FromImage(canvas);

	//System::Drawing::Region^ rgn;
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


	////リソースを解放する
	//g->Dispose();

	////PictureBox1に表示する
	//chessimg->Image = canvas;

}

};
}
