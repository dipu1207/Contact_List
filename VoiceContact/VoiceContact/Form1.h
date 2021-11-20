#pragma once
#include <Windows.h>
#include "stdafx.h"
#include<string.h>
#include "hmm.h"
//#include <tchar.h>
#include<iostream>
#include <stdio.h>
//#include<AclAPI.h>

using namespace std;
namespace VoiceContact {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	protected: 
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Button^  button2;

	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Button^  button3;
	private: System::Windows::Forms::TextBox^  textBox3;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::TextBox^  textBox2;
	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::Label^  label5;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(7, 110);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(198, 51);
			this->button1->TabIndex = 0;
			this->button1->Tag = L"PressToRecord";
			this->button1->Text = L"PressToRecord";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::label1_Click);
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::SystemColors::ButtonShadow;
			this->label1->Location = System::Drawing::Point(7, 68);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(198, 39);
			this->label1->TabIndex = 1;
			this->label1->Click += gcnew System::EventHandler(this, &Form1::label1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(13, 54);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(181, 22);
			this->textBox1->TabIndex = 2;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &Form1::textBox1_TextChanged);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(13, 110);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(181, 51);
			this->button2->TabIndex = 3;
			this->button2->Text = L"Start Recording";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->textBox3);
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->label2);
			this->groupBox1->Controls->Add(this->textBox2);
			this->groupBox1->Controls->Add(this->button3);
			this->groupBox1->Location = System::Drawing::Point(40, 233);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(476, 169);
			this->groupBox1->TabIndex = 5;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Add New Contact";
			this->groupBox1->Enter += gcnew System::EventHandler(this, &Form1::groupBox1_Enter);
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(237, 75);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(154, 22);
			this->textBox3->TabIndex = 4;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(30, 75);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(148, 17);
			this->label3->TabIndex = 3;
			this->label3->Text = L"Enter Contact Number";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(30, 45);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(83, 17);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Enter Name";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(237, 40);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(154, 22);
			this->textBox2->TabIndex = 1;
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(130, 108);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(168, 33);
			this->button3->TabIndex = 0;
			this->button3->Text = L"Start Rec New Contact";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::button3_Click_1);
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->label4);
			this->groupBox2->Controls->Add(this->textBox1);
			this->groupBox2->Controls->Add(this->button2);
			this->groupBox2->Location = System::Drawing::Point(40, 52);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(242, 175);
			this->groupBox2->TabIndex = 6;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"ReRecord Old Contact";
			this->groupBox2->Enter += gcnew System::EventHandler(this, &Form1::groupBox2_Enter);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(12, 34);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(224, 17);
			this->label4->TabIndex = 4;
			this->label4->Text = L"Enter Contact Name To ReRecord";
			this->label4->Click += gcnew System::EventHandler(this, &Form1::label4_Click);
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->label5);
			this->groupBox3->Controls->Add(this->label1);
			this->groupBox3->Controls->Add(this->button1);
			this->groupBox3->Location = System::Drawing::Point(288, 52);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(228, 175);
			this->groupBox3->TabIndex = 7;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Search Contact By Voice";
			// 
			// label5
			// 
			this->label5->Location = System::Drawing::Point(7, 34);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(198, 17);
			this->label5->TabIndex = 2;
			this->label5->Text = L"Status will be displayed here";
			this->label5->Click += gcnew System::EventHandler(this, &Form1::label5_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(544, 407);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Name = L"Form1";
			this->Text = L"Voice Controlled Contact List";
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
					this->label1->Text="Recording started";
				 //system("Recording_Module.exe 10 input_file.wav input_file.txt");
					STARTUPINFOA si;
					PROCESS_INFORMATION pi;
					ZeroMemory( &si, sizeof(si) );
					si.cb = sizeof(si);
					ZeroMemory( &pi, sizeof(pi) );
					// Start Recording
					if(!CreateProcessA( NULL,     // No module name (use command line)
					"Recording_Module.exe 3 d.wav d.txt", // Command line
					NULL,           // Process handle not inheritable
					NULL,           // Thread handle not inheritable
					FALSE,          // Set handle inheritance to FALSE
					0,              // No creation flags
					NULL,           // Use parent's environment block
					NULL,           // Use parent's starting directory 
					&si,            // Pointer to STARTUPINFO structure
					&pi )           // Pointer to PROCESS_INFORMATION structure
					) 
					{
						printf( "CreateProcess failed (%d).\n", GetLastError() );
						this->label1->Text="failed";
						return;
					}

				  // Wait until child process exits.
				  WaitForSingleObject( pi.hProcess, INFINITE );

				  // Close process and thread handles. 
				  CloseHandle( pi.hProcess );
				  CloseHandle( pi.hThread );
								 //detect word
								 //show word detected
								 //show its details
				  this->label1->Text="Recording stopped";
				  char res[100];
				//  sprintf(res,"%s",getNumber());
				  //get number will read sample file and return result as string
				  String ^ n=gcnew String(getNumber());
				  this->label1->Text=n;
						//getnumber() ->will read the already generated 
				 
			 }
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
				 String^ word=this->textBox1->Text;
				 char command[200];
				 for(int sample=1;sample<=20;sample++){
					 sprintf(command,"Recording_Module.exe 3 d.wav Training\\%s_%d.txt",word,sample);
					STARTUPINFOA si;
					PROCESS_INFORMATION pi;
					ZeroMemory( &si, sizeof(si) );
					si.cb = sizeof(si);
					ZeroMemory( &pi, sizeof(pi) );
					// Start Recording
					if(!CreateProcessA( NULL,     // No module name (use command line)
					command, // Command line
					NULL,           // Process handle not inheritable
					NULL,           // Thread handle not inheritable
					FALSE,          // Set handle inheritance to FALSE
					0,              // No creation flags
					NULL,           // Use parent's environment block
					NULL,           // Use parent's starting directory 
					&si,            // Pointer to STARTUPINFO structure
					&pi )           // Pointer to PROCESS_INFORMATION structure
					) 
					{
						printf( "CreateProcess failed (%d).\n", GetLastError() );
						this->label1->Text="failed";
						return;
					}

				  // Wait until child process exits.
				  WaitForSingleObject( pi.hProcess, INFINITE );

				  // Close process and thread handles. 
				  CloseHandle( pi.hProcess );
				  CloseHandle( pi.hThread );
								 //detect word
								 //show word detected
								 //show its details
				  this->label1->Text="Recording stopped";
				 
				 
			}
				
			this->label1->Text="Starting training for lambda";
			char w[100];
			cout<<"starting to print\n"<<endl;
			sprintf(w,"%s",word);
			createLambda(w);//Create lambda of the new recording files
			this->label1->Text="Lambda has been generated for the file now you can proceed with testing";

			
		}
	private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void groupBox1_Enter(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void groupBox2_Enter(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void label4_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void label5_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void button3_Click_1(System::Object^  sender, System::EventArgs^  e) {
			 String^ word=this->textBox2->Text;
			 String^ num=this->textBox3->Text;
			 char name[100],presName[100],presNumber[100];
			 sprintf(name,"%s",word);
			 FILE* cp=fopen("list.txt","r");
			 int flag=0;
			 while(!feof(cp)){
				 fscanf(cp,"%s\t%s\n",&presName,&presNumber);
				 if(strcmp (name, presName)==0){
					MessageBox::Show( "ERROR", "Contact name already exists!",    MessageBoxButtons::OK, MessageBoxIcon::Exclamation );
					flag=1;
				 } 
				
			 }
			 fclose(cp);
			 if(flag==0){
				 cp=fopen("list.txt","a");
				 fprintf(cp,"%s\t%s\n",word,num);
				 fclose(cp);
				 char command[200];
				 for(int sample=1;sample<=20;sample++){
						sprintf(command,"Recording_Module.exe 3 d.wav Training\\%s_%d.txt",word,sample);
						STARTUPINFOA si;
						PROCESS_INFORMATION pi;
						ZeroMemory( &si, sizeof(si) );
						si.cb = sizeof(si);
						ZeroMemory( &pi, sizeof(pi) );
						// Start the child process. 
						if(!CreateProcessA( NULL,     // No module name (use command line)
						command, // Command line
						NULL,           // Process handle not inheritable
						NULL,           // Thread handle not inheritable
						FALSE,          // Set handle inheritance to FALSE
						0,              // No creation flags
						NULL,           // Use parent's environment block
						NULL,           // Use parent's starting directory 
						&si,            // Pointer to STARTUPINFO structure
						&pi )           // Pointer to PROCESS_INFORMATION structure
						) 
						{
							printf( "CreateProcess failed (%d).\n", GetLastError() );
							this->label1->Text="failed";
							return;
						}

						// Wait until child process exits.
						WaitForSingleObject( pi.hProcess, INFINITE );

						// Close process and thread handles. 
						CloseHandle( pi.hProcess );
						CloseHandle( pi.hThread );
										//detect word
										//show word detected
										//show its details
						this->label1->Text="Recording stopped";
				 
				 
				}
				
				this->label1->Text="Starting training for lambda";
				char w[100];
				cout<<"starting to print\n"<<endl;
				sprintf(w,"%s",word);
				createLambda(w);//Create lambda for new contact
				this->label1->Text="Lambda has been generated for the file now you can proceed with testing";
				MessageBox::Show( "Contact saved sucessfully.Lambda is  generated succesfully", "SUCESS",    MessageBoxButtons::OK, MessageBoxIcon::Exclamation );
					


			}
			

				
	}
};
}

