#pragma once
#include <string>
//#include <thread>
#include "RecordCamera.h"
#include "NewProjectForm.h"

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
	private: double fps;// = 1;

	public:
		MainForm(void)
		{
			InitializeComponent();
			fps = 1;
			//
			//TODO: ここにコンストラクター コードを追加します
			//


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
			this->stereoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->button_record = (gcnew System::Windows::Forms::Button());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->MessageLabel = (gcnew System::Windows::Forms::Label());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->fileToolStripMenuItem,
					this->calibrationToolStripMenuItem, this->stereoToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1309, 24);
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
			this->fileToolStripMenuItem->Size = System::Drawing::Size(39, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// newProjectToolStripMenuItem
			// 
			this->newProjectToolStripMenuItem->Name = L"newProjectToolStripMenuItem";
			this->newProjectToolStripMenuItem->Size = System::Drawing::Size(149, 22);
			this->newProjectToolStripMenuItem->Text = L"New Project";
			this->newProjectToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::newProjectToolStripMenuItem_Click);
			// 
			// openProjectToolStripMenuItem
			// 
			this->openProjectToolStripMenuItem->Name = L"openProjectToolStripMenuItem";
			this->openProjectToolStripMenuItem->Size = System::Drawing::Size(149, 22);
			this->openProjectToolStripMenuItem->Text = L"Open Project";
			// 
			// saveToolStripMenuItem
			// 
			this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
			this->saveToolStripMenuItem->Size = System::Drawing::Size(149, 22);
			this->saveToolStripMenuItem->Text = L"Save";
			// 
			// calibrationToolStripMenuItem
			// 
			this->calibrationToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->conditionToolStripMenuItem });
			this->calibrationToolStripMenuItem->Name = L"calibrationToolStripMenuItem";
			this->calibrationToolStripMenuItem->Size = System::Drawing::Size(81, 20);
			this->calibrationToolStripMenuItem->Text = L"Calibration";
			// 
			// conditionToolStripMenuItem
			// 
			this->conditionToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->numberToolStripMenuItem,
					this->distributionToolStripMenuItem, this->reprojectionErrorToolStripMenuItem
			});
			this->conditionToolStripMenuItem->Name = L"conditionToolStripMenuItem";
			this->conditionToolStripMenuItem->Size = System::Drawing::Size(128, 22);
			this->conditionToolStripMenuItem->Text = L"Condition";
			// 
			// numberToolStripMenuItem
			// 
			this->numberToolStripMenuItem->Checked = true;
			this->numberToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->numberToolStripMenuItem->Name = L"numberToolStripMenuItem";
			this->numberToolStripMenuItem->Size = System::Drawing::Size(184, 22);
			this->numberToolStripMenuItem->Text = L"Number of Images";
			// 
			// distributionToolStripMenuItem
			// 
			this->distributionToolStripMenuItem->Name = L"distributionToolStripMenuItem";
			this->distributionToolStripMenuItem->Size = System::Drawing::Size(184, 22);
			this->distributionToolStripMenuItem->Text = L"Distribution";
			// 
			// reprojectionErrorToolStripMenuItem
			// 
			this->reprojectionErrorToolStripMenuItem->Name = L"reprojectionErrorToolStripMenuItem";
			this->reprojectionErrorToolStripMenuItem->Size = System::Drawing::Size(184, 22);
			this->reprojectionErrorToolStripMenuItem->Text = L"Reprojection Error";
			// 
			// stereoToolStripMenuItem
			// 
			this->stereoToolStripMenuItem->Name = L"stereoToolStripMenuItem";
			this->stereoToolStripMenuItem->Size = System::Drawing::Size(114, 20);
			this->stereoToolStripMenuItem->Text = L"Stereo Matching";
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(3, 3);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(640, 480);
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Location = System::Drawing::Point(649, 3);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(640, 480);
			this->pictureBox2->TabIndex = 2;
			this->pictureBox2->TabStop = false;
			// 
			// button_record
			// 
			this->button_record->Location = System::Drawing::Point(1214, 489);
			this->button_record->Name = L"button_record";
			this->button_record->Size = System::Drawing::Size(75, 23);
			this->button_record->TabIndex = 3;
			this->button_record->Text = L"Record";
			this->button_record->UseVisualStyleBackColor = true;
			this->button_record->Click += gcnew System::EventHandler(this, &MainForm::button_record_Click);
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->pictureBox1);
			this->panel1->Controls->Add(this->pictureBox2);
			this->panel1->Controls->Add(this->button_record);
			this->panel1->Location = System::Drawing::Point(12, 27);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(1294, 545);
			this->panel1->TabIndex = 4;
			// 
			// MessageLabel
			// 
			this->MessageLabel->AutoSize = true;
			this->MessageLabel->Location = System::Drawing::Point(3, 618);
			this->MessageLabel->Name = L"MessageLabel";
			this->MessageLabel->Size = System::Drawing::Size(50, 12);
			this->MessageLabel->TabIndex = 5;
			this->MessageLabel->Text = L"message";
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(15, 592);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(1291, 23);
			this->progressBar1->TabIndex = 6;
			this->progressBar1->Visible = false;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1309, 636);
			this->Controls->Add(this->progressBar1);
			this->Controls->Add(this->MessageLabel);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
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
			recthread = gcnew Thread(gcnew ThreadStart(this, &MainForm::RecordThread));
			recthread->IsBackground = true;// バックグラウンド化してから起動
			recthread->Start();
			recflg = true;
		}
		else
		{
			button_record->Text = "Record";
			recflg = false;

			MainForm::progressBar1->Visible = true;

			Thread^ calbt = gcnew Thread(gcnew ThreadStart(this, &MainForm::CalibrateThread));
			calbt->IsBackground = true;
			calbt->Start();
		}

	}
	private: System::Void RecordThread();
	private: delegate System::Void DisplayDelegate();
	private: System::Void Display();

	private: System::Void CalibrateThread();
	private: delegate System::Void ProgressDelegate(int num);
	private: System::Void Progress(int num);
	  
  

private: System::Void newProjectToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
	NewProjectForm ^fm = gcnew NewProjectForm();
	fm->ShowDialog();
	MessageLabel->Text = fm->GetSaveDirectory();
}
};
}
