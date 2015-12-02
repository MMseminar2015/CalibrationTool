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





	private: bool recflg;
			 double fps;// = 1;
			 bool saveflg;
			 bool newflg;
			 bool endflg;
			 int nfindthread;


	private: System::Windows::Forms::ToolStripMenuItem^  lineToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  rectifiedToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  viewResultToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  algorToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  bMToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  sGBMToolStripMenuItem;

			 Configurations^ conf;
	

	public:
		MainForm(void)
		{
			InitializeComponent();

			fps = 1;
			//
			//TODO: ここにコンストラクター コードを追加します
			//
			//conf->chess_height=7;
			//conf->chess_width=10;
			//conf->chess_size=16.8;
			conf = Configurations::Load("conf.xml");
			if(conf->numimg<10)
				conf=gcnew Configurations(7, 10, 16.8, "", 20);

			recthread = gcnew Thread(gcnew ThreadStart(this, &MainForm::RecordThread));
			recthread->IsBackground = true;// バックグラウンド化してから起動
			recthread->Start();
			recflg = false;
			saveflg = false;
			newflg = false;
			endflg = false;


		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~MainForm()
		{
			endflg = true;
			recthread->Join();

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

	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox2;



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
			this->calibrationToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->lineToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rectifiedToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->stereoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->viewResultToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->algorToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->bMToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->sGBMToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->progressBar1 = (gcnew System::Windows::Forms::ProgressBar());
			this->MessageLabel = (gcnew System::Windows::Forms::Label());
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
			this->menuStrip1->Size = System::Drawing::Size(1283, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// fileToolStripMenuItem
			// 
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->newProjectToolStripMenuItem,
					this->openProjectToolStripMenuItem
			});
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			this->fileToolStripMenuItem->Size = System::Drawing::Size(39, 20);
			this->fileToolStripMenuItem->Text = L"File";
			// 
			// newProjectToolStripMenuItem
			// 
			this->newProjectToolStripMenuItem->Name = L"newProjectToolStripMenuItem";
			this->newProjectToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->newProjectToolStripMenuItem->Text = L"New Project";
			this->newProjectToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::newProjectToolStripMenuItem_Click);
			// 
			// openProjectToolStripMenuItem
			// 
			this->openProjectToolStripMenuItem->Name = L"openProjectToolStripMenuItem";
			this->openProjectToolStripMenuItem->Size = System::Drawing::Size(152, 22);
			this->openProjectToolStripMenuItem->Text = L"Load Project";
			this->openProjectToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainForm::openProjectToolStripMenuItem_Click);
			// 
			// calibrationToolStripMenuItem
			// 
			this->calibrationToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->lineToolStripMenuItem,
					this->rectifiedToolStripMenuItem
			});
			this->calibrationToolStripMenuItem->Name = L"calibrationToolStripMenuItem";
			this->calibrationToolStripMenuItem->Size = System::Drawing::Size(81, 20);
			this->calibrationToolStripMenuItem->Text = L"Calibration";
			// 
			// lineToolStripMenuItem
			// 
			this->lineToolStripMenuItem->CheckOnClick = true;
			this->lineToolStripMenuItem->Name = L"lineToolStripMenuItem";
			this->lineToolStripMenuItem->Size = System::Drawing::Size(124, 22);
			this->lineToolStripMenuItem->Text = L"Line";
			// 
			// rectifiedToolStripMenuItem
			// 
			this->rectifiedToolStripMenuItem->Checked = true;
			this->rectifiedToolStripMenuItem->CheckOnClick = true;
			this->rectifiedToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->rectifiedToolStripMenuItem->Name = L"rectifiedToolStripMenuItem";
			this->rectifiedToolStripMenuItem->Size = System::Drawing::Size(124, 22);
			this->rectifiedToolStripMenuItem->Text = L"Rectified";
			// 
			// stereoToolStripMenuItem
			// 
			this->stereoToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->viewResultToolStripMenuItem,
					this->algorToolStripMenuItem
			});
			this->stereoToolStripMenuItem->Name = L"stereoToolStripMenuItem";
			this->stereoToolStripMenuItem->Size = System::Drawing::Size(114, 20);
			this->stereoToolStripMenuItem->Text = L"Stereo Matching";
			// 
			// viewResultToolStripMenuItem
			// 
			this->viewResultToolStripMenuItem->CheckOnClick = true;
			this->viewResultToolStripMenuItem->Name = L"viewResultToolStripMenuItem";
			this->viewResultToolStripMenuItem->Size = System::Drawing::Size(142, 22);
			this->viewResultToolStripMenuItem->Text = L"View Result";
			// 
			// algorToolStripMenuItem
			// 
			this->algorToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->bMToolStripMenuItem,
					this->sGBMToolStripMenuItem
			});
			this->algorToolStripMenuItem->Name = L"algorToolStripMenuItem";
			this->algorToolStripMenuItem->Size = System::Drawing::Size(142, 22);
			this->algorToolStripMenuItem->Text = L"Algorithm";
			// 
			// bMToolStripMenuItem
			// 
			this->bMToolStripMenuItem->Checked = true;
			this->bMToolStripMenuItem->CheckOnClick = true;
			this->bMToolStripMenuItem->CheckState = System::Windows::Forms::CheckState::Checked;
			this->bMToolStripMenuItem->Enabled = false;
			this->bMToolStripMenuItem->Name = L"bMToolStripMenuItem";
			this->bMToolStripMenuItem->Size = System::Drawing::Size(109, 22);
			this->bMToolStripMenuItem->Text = L"BM";
			this->bMToolStripMenuItem->CheckedChanged += gcnew System::EventHandler(this, &MainForm::bMToolStripMenuItem_CheckedChanged);
			// 
			// sGBMToolStripMenuItem
			// 
			this->sGBMToolStripMenuItem->CheckOnClick = true;
			this->sGBMToolStripMenuItem->Name = L"sGBMToolStripMenuItem";
			this->sGBMToolStripMenuItem->Size = System::Drawing::Size(109, 22);
			this->sGBMToolStripMenuItem->Text = L"SGBM";
			this->sGBMToolStripMenuItem->CheckedChanged += gcnew System::EventHandler(this, &MainForm::sGBMToolStripMenuItem_CheckedChanged);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(0, 0);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(640, 480);
			this->pictureBox1->TabIndex = 1;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Click += gcnew System::EventHandler(this, &MainForm::pictureBox_Click);
			// 
			// pictureBox2
			// 
			this->pictureBox2->Location = System::Drawing::Point(640, 0);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(640, 480);
			this->pictureBox2->TabIndex = 2;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->Click += gcnew System::EventHandler(this, &MainForm::pictureBox_Click);
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->progressBar1);
			this->panel1->Controls->Add(this->pictureBox1);
			this->panel1->Controls->Add(this->pictureBox2);
			this->panel1->Location = System::Drawing::Point(0, 25);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(1280, 480);
			this->panel1->TabIndex = 4;
			// 
			// progressBar1
			// 
			this->progressBar1->Location = System::Drawing::Point(12, 440);
			this->progressBar1->Name = L"progressBar1";
			this->progressBar1->Size = System::Drawing::Size(1259, 23);
			this->progressBar1->TabIndex = 6;
			this->progressBar1->Visible = false;
			// 
			// MessageLabel
			// 
			this->MessageLabel->AutoSize = true;
			this->MessageLabel->Location = System::Drawing::Point(10, 508);
			this->MessageLabel->Name = L"MessageLabel";
			this->MessageLabel->Size = System::Drawing::Size(50, 12);
			this->MessageLabel->TabIndex = 5;
			this->MessageLabel->Text = L"message";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1283, 529);
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

			 System::Void initialize();

	private: System::Void newProjectToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) {
		
		newflg = true;

		NewProjectForm ^fm = gcnew NewProjectForm(conf);
		fm->ShowDialog();
		if (fm->DialogResult == System::Windows::Forms::DialogResult::OK) {
			conf->savedir = fm->GetSaveDirectory();
			conf->chess_height = fm->GetChessHeight();
			conf->chess_width = fm->GetChessWidth();
			conf->chess_size = fm->GetChessSize();
			conf->numimg = fm->GetNumImg();
			Configurations::Save("conf.xml", conf);
		}

		while (nfindthread != 0) {}
		initialize();
		newflg = false;

		//recthread = gcnew Thread(gcnew ThreadStart(this, &MainForm::RecordThread));
		//recthread->IsBackground = true;// バックグラウンド化してから起動
		//recthread->Start();

	}

	 private: System::Void pictureBox_Click(System::Object^  sender, System::EventArgs^  e) {
			 saveflg = true;
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


private: System::Void openProjectToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
};


}
