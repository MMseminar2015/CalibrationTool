#pragma once
#include <string>
//#include <thread>
#include "RecordCamera.h"
#include "NewProjectForm.h"
#include "StereoMatching.h"
#include "Configurations.h"

namespace CalibrationTool {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;

	/// <summary>
	/// MainForm の概要
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{

	private: Thread^ recthread;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Label^  MessageLabel;
	private: System::Windows::Forms::ProgressBar^  progressBar1;


	private: System::Windows::Forms::ToolStripMenuItem^  calibrationToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  stereoToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  conditionToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  numberToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  distributionToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  reprojectionErrorToolStripMenuItem;

	private: bool recflg;
			 double fps;// = 1;
			 bool refreshflg;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::ToolStripMenuItem^  lineToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  rectifiedToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  viewResultToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  algorToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  bMToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  sGBMToolStripMenuItem;

			 Configurations conf;
	

	public:
		MainForm(void)
		{
			InitializeComponent();
			fps = 1;
			//
			//TODO: ここにコンストラクター コードを追加します
			//
			conf.chess_height=7;
			conf.chess_width=10;
			conf.chess_size=16.8;

			recthread = gcnew Thread(gcnew ThreadStart(this, &MainForm::RecordThread));
			recthread->IsBackground = true;// バックグラウンド化してから起動
			recthread->Start();
			recflg = false;
			refreshflg = true;

		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}


	private:
		void ReloadPicture();
		delegate void ReloadPictureDelegate();



	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	protected:
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  newProjectToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  openProjectToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveToolStripMenuItem;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::Button^  button_record;


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
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->newProjectToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openProjectToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->calibrationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->conditionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->numberToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->distributionToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->reprojectionErrorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->lineToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rectifiedToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->stereoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->viewResultToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->algorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bMToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->sGBMToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->button_record = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->MessageLabel = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(24, 24);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->fileToolStripMenuItem,
					this->calibrationToolStripMenuItem, this->stereoToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Padding = System::Windows::Forms::Padding(10, 3, 0, 3);
			this->menuStrip1->Size = System::Drawing::Size(2138, 34);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->newProjectToolStripMenuItem,
					this->openProjectToolStripMenuItem, this->saveToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(52, 28);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// newProjectToolStripMenuItem
			// 
			this->newProjectToolStripMenuItem->Name = L"newProjectToolStripMenuItem";
			this->newProjectToolStripMenuItem->Size = System::Drawing::Size(206, 30);
			this->newProjectToolStripMenuItem->Text = L"New Project";
			this->newProjectToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::newProjectToolStripMenuItem_Click);
			// 
			// openProjectToolStripMenuItem
			// 
			this->openProjectToolStripMenuItem->Name = L"openProjectToolStripMenuItem";
			this->openProjectToolStripMenuItem->Size = System::Drawing::Size(206, 30);
			this->openProjectToolStripMenuItem->Text = L"Open Project";
			// 
			// saveToolStripMenuItem
			// 
			this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
			this->saveToolStripMenuItem->Size = System::Drawing::Size(206, 30);
			this->saveToolStripMenuItem->Text = L"Save";
			// 
			// calibrationToolStripMenuItem
			// 
			this->calibrationToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->conditionToolStripMenuItem,
					this->lineToolStripMenuItem, this->rectifiedToolStripMenuItem
			});
			this->calibrationToolStripMenuItem->Name = L"calibrationToolStripMenuItem";
			this->calibrationToolStripMenuItem->Size = System::Drawing::Size(116, 28);
			this->calibrationToolStripMenuItem->Text = L"Calibration";
			// 
			// conditionToolStripMenuItem
			// 
			this->conditionToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->numberToolStripMenuItem,
					this->distributionToolStripMenuItem, this->reprojectionErrorToolStripMenuItem
			});
			this->conditionToolStripMenuItem->Name = L"conditionToolStripMenuItem";
			this->conditionToolStripMenuItem->Size = System::Drawing::Size(177, 30);
			this->conditionToolStripMenuItem->Text = L"Condition";
			// 
			// numberToolStripMenuItem
			// 
			this->numberToolStripMenuItem->Checked = true;
			this->numberToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->numberToolStripMenuItem->Name = L"numberToolStripMenuItem";
			this->numberToolStripMenuItem->Size = System::Drawing::Size(255, 30);
			this->numberToolStripMenuItem->Text = L"Number of Images";
			// 
			// distributionToolStripMenuItem
			// 
			this->distributionToolStripMenuItem->Name = L"distributionToolStripMenuItem";
			this->distributionToolStripMenuItem->Size = System::Drawing::Size(255, 30);
			this->distributionToolStripMenuItem->Text = L"Distribution";
			// 
			// reprojectionErrorToolStripMenuItem
			// 
			this->reprojectionErrorToolStripMenuItem->Name = L"reprojectionErrorToolStripMenuItem";
			this->reprojectionErrorToolStripMenuItem->Size = System::Drawing::Size(255, 30);
			this->reprojectionErrorToolStripMenuItem->Text = L"Reprojection Error";
			// 
			// lineToolStripMenuItem
			// 
			this->lineToolStripMenuItem->CheckOnClick = true;
			this->lineToolStripMenuItem->Name = L"lineToolStripMenuItem";
			this->lineToolStripMenuItem->Size = System::Drawing::Size(177, 30);
			this->lineToolStripMenuItem->Text = L"Line";
			// 
			// rectifiedToolStripMenuItem
			// 
			this->rectifiedToolStripMenuItem->Checked = true;
			this->rectifiedToolStripMenuItem->CheckOnClick = true;
			this->rectifiedToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->rectifiedToolStripMenuItem->Name = L"rectifiedToolStripMenuItem";
			this->rectifiedToolStripMenuItem->Size = System::Drawing::Size(177, 30);
			this->rectifiedToolStripMenuItem->Text = L"Rectified";
			// 
			// stereoToolStripMenuItem
			// 
			this->stereoToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->viewResultToolStripMenuItem,
					this->algorToolStripMenuItem
			});
			this->stereoToolStripMenuItem->Name = L"stereoToolStripMenuItem";
			this->stereoToolStripMenuItem->Size = System::Drawing::Size(163, 28);
			this->stereoToolStripMenuItem->Text = L"Stereo Matching";
			// 
			// viewResultToolStripMenuItem
			// 
			this->viewResultToolStripMenuItem->CheckOnClick = true;
			this->viewResultToolStripMenuItem->Name = L"viewResultToolStripMenuItem";
			this->viewResultToolStripMenuItem->Size = System::Drawing::Size(211, 30);
			this->viewResultToolStripMenuItem->Text = L"View Result";
			// 
			// algorToolStripMenuItem
			// 
			this->algorToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->bMToolStripMenuItem,
					this->sGBMToolStripMenuItem
			});
			this->algorToolStripMenuItem->Name = L"algorToolStripMenuItem";
			this->algorToolStripMenuItem->Size = System::Drawing::Size(211, 30);
			this->algorToolStripMenuItem->Text = L"Algorithm";
			// 
			// bMToolStripMenuItem
			// 
			this->bMToolStripMenuItem->Checked = true;
			this->bMToolStripMenuItem->CheckOnClick = true;
			this->bMToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->bMToolStripMenuItem->Enabled = false;
			this->bMToolStripMenuItem->Name = L"bMToolStripMenuItem";
			this->bMToolStripMenuItem->Size = System::Drawing::Size(211, 30);
			this->bMToolStripMenuItem->Text = L"BM";
			this->bMToolStripMenuItem->CheckedChanged += gcnew System::EventHandler(this, &MainForm::bMToolStripMenuItem_CheckedChanged);
			// 
			// sGBMToolStripMenuItem
			// 
			this->sGBMToolStripMenuItem->CheckOnClick = true;
			this->sGBMToolStripMenuItem->Name = L"sGBMToolStripMenuItem";
			this->sGBMToolStripMenuItem->Size = System::Drawing::Size(211, 30);
			this->sGBMToolStripMenuItem->Text = L"SGBM";
			this->sGBMToolStripMenuItem->CheckedChanged += gcnew System::EventHandler(this, &MainForm::sGBMToolStripMenuItem_CheckedChanged);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Margin = System::Windows::Forms::Padding(5, 4, 5, 4);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(1067, 720);
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Location = System::Drawing::Point(1067, 0);
			this->pictureBox2->Margin = System::Windows::Forms::Padding(5, 4, 5, 4);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(1067, 720);
			this->pictureBox2->TabIndex = 2;
			this->pictureBox2->TabStop = false;
			// 
			// button_record
			// 
			this->button_record->Location = System::Drawing::Point(2003, 2);
			this->button_record->Margin = System::Windows::Forms::Padding(5, 4, 5, 4);
			this->button_record->Name = L"button_record";
			this->button_record->Size = System::Drawing::Size(125, 34);
			this->button_record->TabIndex = 3;
			this->button_record->Text = L"Record";
			this->button_record->UseVisualStyleBackColor = true;
			this->button_record->Click += gcnew System::EventHandler(this, &MainForm::button_record_Click);
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->progressBar1);
			this->panel1->Controls->Add(this->pictureBox1);
			this->panel1->Controls->Add(this->pictureBox2);
			this->panel1->Location = System::Drawing::Point(0, 38);
			this->panel1->Margin = System::Windows::Forms::Padding(5, 4, 5, 4);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(2133, 720);
			this->panel1->TabIndex = 4;
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(20, 660);
			this->progressBar1->Margin = System::Windows::Forms::Padding(5, 4, 5, 4);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(2098, 34);
			this->progressBar1->TabIndex = 6;
			this->progressBar1->Visible = false;
			// 
			// MessageLabel
			// 
			this->MessageLabel->AutoSize = true;
			this->MessageLabel->Location = System::Drawing::Point(17, 762);
			this->MessageLabel->Margin = System::Windows::Forms::Padding(5, 0, 5, 0);
			this->MessageLabel->Name = L"MessageLabel";
			this->MessageLabel->Size = System::Drawing::Size(72, 18);
			this->MessageLabel->TabIndex = 5;
			this->MessageLabel->Text = L"message";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(953, 8);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(101, 25);
			this->textBox1->TabIndex = 7;
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(1078, 8);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(101, 25);
			this->textBox2->TabIndex = 8;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(10, 18);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(2138, 794);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->MessageLabel);
			this->Controls->Add(this->button_record);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(5, 4, 5, 4);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			this->panel1->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button_record_Click(System::Object^  sender, System::EventArgs^  e) {
		if (button_record->Text != "Stop") {
			button_record->Text = "Stop";
			//recthread = gcnew Thread(gcnew ThreadStart(this, &MainForm::RecordThread));
			//recthread->IsBackground = true;// バックグラウンド化してから起動
			//recthread->Start();
			recflg = true;
			//RecordThread();
		}
		else
		{
			button_record->Text = "Record";
			recflg = false;

			//WriteImages();

			MainForm::progressBar1->Visible = true;

			Thread^ calbt = gcnew Thread(gcnew ThreadStart(this, &MainForm::CalibrateThread));
			calbt->IsBackground = true;
			calbt->Start();
		}

	}
	private: void WriteImages();

	private: System::Void RecordThread();
	private: delegate System::Void DisplayDelegate();
	private: System::Void Display();

	private: System::Void CalibrateThread();

	private: System::Void CalcReprojectionThread();

	private: System::Void ProgressThread();
	private: delegate System::Void ProgressDelegate(int num);
	private: System::Void Progress(int num);
	private: System::Void ProgressEnd(int num);
	  
	private: System::Void FindChessboardThread(Object^ o);
	private: System::Void StereoMatchingThread(Object^ o);

	private: System::Void newProjectToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		NewProjectForm ^fm = gcnew NewProjectForm();
		fm->ShowDialog();
		MessageLabel->Text = fm->GetSaveDirectory();
	}
	 private: System::Void pictureBox_Click(System::Object^  sender, System::EventArgs^  e) {
		 if (refreshflg)
			 refreshflg = false;
		 else
			 refreshflg = true;
	 }


private: System::Void bMToolStripMenuItem_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	if (bMToolStripMenuItem->Checked) {
		sGBMToolStripMenuItem->Checked = false;
		sGBMToolStripMenuItem->Enabled = true;
		bMToolStripMenuItem->Enabled = false;
	}
}
private: System::Void sGBMToolStripMenuItem_CheckedChanged(System::Object^  sender, System::EventArgs^  e) {
	if (sGBMToolStripMenuItem->Checked) {
		bMToolStripMenuItem->Checked = false;
		bMToolStripMenuItem->Enabled = true;
		sGBMToolStripMenuItem->Enabled = false;
	}
}


};

}
