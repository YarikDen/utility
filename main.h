//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.AppEvnts.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.Menus.hpp>
#include "Add.h"
#include "Settings.h"
#include "Show_logs.h"
#include "About.h"
#include "CFolderWatcher.h"
#include <list>
#include <iterator>

//---------------------------------------------------------------------------
class TForm_main : public TForm
{
__published:	// IDE-managed Components
	TMainMenu *MainMenu1;
	TPopupMenu *PopupMenu1;
	TTrayIcon *TrayIcon1;
	TApplicationEvents *ApplicationEvents1;
	TMenuItem *Nm_Addfolder;
	TMenuItem *Nm_Settings;
	TMenuItem *Nm_Show_logs;
	TMenuItem *Nm_About;
	TMenuItem *Np_Maximize;
	TMenuItem *Np_Exit;
	TMenuItem *Np_About;
	void __fastcall Np_MaximizeClick(TObject *Sender);
	void __fastcall ApplicationEvents1Minimize(TObject *Sender);
	void __fastcall Np_ExitClick(TObject *Sender);
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall Nm_SettingsClick(TObject *Sender);
	void __fastcall Nm_AddfolderClick(TObject *Sender);
	void __fastcall Nm_Show_logsClick(TObject *Sender);
	void __fastcall Np_AboutClick(TObject *Sender);
	void __fastcall Nm_AboutClick(TObject *Sender);
	void __fastcall FormClose(TObject *Sender, TCloseAction &Action);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall FormPaint(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm_main(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_main *Form_main;
extern std::list<CFolderWatcher> g_lst_FolderList;

typedef struct LogFolder{
	String wstr_Folder;
	String wstr_Logfile;
	BOOL B_SubFolder;
	DWORD dwFilter;
}SFolderLog;

/////////////////////////////////////////////
////////////////////////////////////////////
void Set_VertScroll(TListBox * ListBox){//set vertline
	int iMaxWidth = 0,
	ilength = 0;

	for (int i = 0; i < ListBox->Items->Count;i++){

		ilength = ListBox->Canvas->TextWidth(ListBox->Items->Strings[i]) + 3;
		if(ilength > iMaxWidth){
		   iMaxWidth = ilength;
		}
	}
	SendMessageA(ListBox->Handle,LB_SETHORIZONTALEXTENT,iMaxWidth, 0);//get hor scroll bar
}
//---------------------------------------------------------------------------
BOOL IsExistsLog(std::list<CFolderWatcher> lst_FolderList,String wstr_Log){ //check if log file is used by some folder watcher
	BOOL B_Success = FALSE;
	if(!lst_FolderList.empty()){
		std::list<CFolderWatcher>::iterator iter = lst_FolderList.begin();
		for (;iter != lst_FolderList.end();iter++){
			if( WideCompareText((*iter).GetLogfile(),wstr_Log) == 0){
				B_Success = TRUE;
				break;
			}
		}
	}
	return B_Success;
}



void SetList(std::list<CFolderWatcher> lst_FolderList,TListBox *  ListBox){ // set listbox
	if(!lst_FolderList.empty()){
		std::list<CFolderWatcher>::iterator iter = lst_FolderList.begin();
		ListBox->Items->Clear();
		for (;iter != lst_FolderList.end();iter++){
			ListBox->Items->Add((*iter).GetFolderName());
		}
	}
}
/////////////////////////////////////////////
////////////////////////////////////////////
BOOL ItemIsExist(std::list<CFolderWatcher> lst_List,String wstr_Item){//Check for existence
	BOOL B_Exist = FALSE;
	std::list<CFolderWatcher>::iterator iter = lst_List.begin();
	for (;iter != lst_List.end();iter++){
			if( WideCompareText((*iter).GetFolderName(),wstr_Item) == 0){
				B_Exist = TRUE;
				break;
			}
	}
	return B_Exist;
}
///////////////////////////////////////////
///////////////////////////////////////////
BOOL DeleteItem(TListBox *  ListBox,std::list<CFolderWatcher> * plst_List){//Delete Item of List
	BOOL B_Success = FALSE;
	if(!plst_List->empty()){
		String wstr_Item = ListBox->Items->Strings[ListBox->ItemIndex];
		std::list<CFolderWatcher>::iterator it = plst_List->begin();
		for (;it != plst_List->end();it++){

			if( WideCompareText((*it).GetFolderName(),wstr_Item) == 0){
				(*it).TerminateWatch();//interrupt watching
				plst_List->erase(it);//erase watcher
				ListBox->Items->Delete(ListBox->ItemIndex);
				B_Success = TRUE;
				break;
			}
		}

	}
    return B_Success;
}
///////////////////////////////////////
///////////////////////////////////////
DWORD SetFilterWatcher(TCheckListBox * CheckListBox){
	DWORD dwFilter = 0;
	for(int i = 0; i < CheckListBox->Items->Count;i++){
		if (CheckListBox->Checked[i]){
			switch(i){
				case 0:
					dwFilter |= FILE_NOTIFY_CHANGE_FILE_NAME;
					break;
				case 1:
					dwFilter |= FILE_NOTIFY_CHANGE_DIR_NAME;
					break;
				case 2:
					dwFilter |= FILE_NOTIFY_CHANGE_ATTRIBUTES;
					break;
				case 3:
					dwFilter |= FILE_NOTIFY_CHANGE_SIZE;
					break;
				case 4:
					dwFilter |= FILE_NOTIFY_CHANGE_LAST_WRITE;
					break;
				case 5:
					dwFilter |= FILE_NOTIFY_CHANGE_LAST_ACCESS;
					break;
				case 6:
					dwFilter |= FILE_NOTIFY_CHANGE_CREATION;
					break;
				case 7:
					dwFilter |= FILE_NOTIFY_CHANGE_SECURITY;
					break;
				default:
					break;
			}
		}
	}
	return dwFilter;
}
///////////////////////////////////////////
///////////////////////////////////////////
BOOL FolderExists(String wstr_File){//existence of folder
	HANDLE hFindFile;
	BOOL B_Exist = TRUE;
	WIN32_FIND_DATAW w_fd;
	hFindFile = FindFirstFileW(wstr_File.c_str(),&w_fd);
	if(hFindFile == INVALID_HANDLE_VALUE){//if file not exists
		B_Exist = FALSE;
	}else{
		if(w_fd.dwFileAttributes != FILE_ATTRIBUTE_DIRECTORY){
            B_Exist = FALSE;
		}
		FindClose(hFindFile);
	}
	return B_Exist;
}
////////////////////////////////////
///////////////////////////////////
void SetupElem(std::list<CFolderWatcher> * plst_FolderList,SFolderLog flLog){
	CFolderWatcher fwWatcher(flLog.wstr_Folder,flLog.wstr_Logfile,flLog.dwFilter,flLog.B_SubFolder);
	fwWatcher.InitThreadWatch();
	plst_FolderList->push_back(fwWatcher);
}
////////////////////////////////////////
////////////////////////////////////////
void ResumeWatcher(std::list<CFolderWatcher> * plst_FolderList,String wstr_Folder){//Resume Watcher
	if(!plst_FolderList->empty()){
		std::list<CFolderWatcher>::iterator it = plst_FolderList->begin();
		for (;it != plst_FolderList->end();it++){
			if( WideCompareText((*it).GetFolderName(),wstr_Folder) == 0){
				if((*it).GetState() == FALSE){
					(*it).ResumeWatch();//resume watching
					WaitForSingleObject((*it).GetHandleWatcher(),0);
					ShowMessage("Resume success!!!");
				}else{
					ShowMessage("This FolderWatcher is running now!!!");
				}
                break;
			}
		}
	}
}
/////////////////////////////////////////////
////////////////////////////////////////////
void StopWatcher(std::list<CFolderWatcher> * plst_FolderList,String wstr_Folder){//Stop Watcher
    if(!plst_FolderList->empty()){
		std::list<CFolderWatcher>::iterator it = plst_FolderList->begin();
		for (;it != plst_FolderList->end();it++){
			if( WideCompareText((*it).GetFolderName(),wstr_Folder) == 0){
				if((*it).GetState() == TRUE){
					(*it).StopWatch();//stop watching
					ShowMessage("Stop success!!!");
				}else{
					ShowMessage("This FolderWatcher is not running now!!!");
				}
				break;
			}
		}
	}
}
 ///////////////////////////////////////////////////
 ////////////////////////////////////////////////
 String ReadLogFile(std::list<CFolderWatcher> * plst_FolderList,String wstr_Folder){//ReadLog file
	CHAR c_ch = ' ';
	WCHAR w_ch = L' ';
	HANDLE hReadFile;
	DWORD dwRetReadBytes = 0;
	String wstr_LogFile = "",wstr_Data;
	DWORD dwsize = 0;
	if(!plst_FolderList->empty()){
		std::list<CFolderWatcher>::iterator it = plst_FolderList->begin();
		for (;it != plst_FolderList->end();it++){
			if( WideCompareText((*it).GetFolderName(),wstr_Folder) == 0){
				wstr_LogFile = (*it).GetLogfile();
				break;
			}
		}
		hReadFile = CreateFileW(wstr_LogFile.c_str(), //get file`s handle here write name of file where our records!!!!!!!!!!
									GENERIC_READ,
									0,
									NULL,
									OPEN_EXISTING,
									FILE_ATTRIBUTE_NORMAL ,
									NULL);

		if(hReadFile != INVALID_HANDLE_VALUE){

			SetFilePointer(hReadFile,-1,NULL,FILE_BEGIN);
			for(;;){
				ReadFile(hReadFile,&c_ch,sizeof(CHAR),&dwRetReadBytes,(LPOVERLAPPED)NULL);
				MultiByteToWideChar(GetACP(),0,&c_ch,-1,&w_ch,sizeof(WCHAR));//good
				if(dwRetReadBytes == 0){
                    break;
				}
				wstr_Data = Format("%s%s",ARRAYOFCONST((wstr_Data,w_ch)));
			 }
			CloseHandle(hReadFile);

		}else{
			wstr_Data = Format("LogFile <<%s>> was not found\r\n",ARRAYOFCONST((wstr_LogFile)));
		}
	}
    return wstr_Data;
 }
 ///////////////////////////////////////////////////
 ////////////////////////////////////////////////
 String GetFilter(std::list<CFolderWatcher> * plst_FolderList,String wstr_Folder){//Filter
	String wstr_Data = "";
    DWORD dwFilter = 0;
	if(!plst_FolderList->empty()){
        std::list<CFolderWatcher>::iterator it = plst_FolderList->begin();
		for (;it != plst_FolderList->end();it++){
			if( WideCompareText((*it).GetFolderName(),wstr_Folder) == 0){
				dwFilter = (*it).GetFilter();
				break;
			}
		}
		if(dwFilter & FILE_NOTIFY_CHANGE_FILE_NAME){
			wstr_Data = Format("1)FILE_NOTIFY_CHANGE_FILE_NAME ;\r\n",ARRAYOFCONST((wstr_Data)));
		}
		if(dwFilter & FILE_NOTIFY_CHANGE_DIR_NAME){
			wstr_Data = Format("%s2)FILE_NOTIFY_CHANGE_DIR_NAME ;\r\n",ARRAYOFCONST((wstr_Data)));
		}
		if(dwFilter & FILE_NOTIFY_CHANGE_ATTRIBUTES){
			wstr_Data = Format("%s3)FILE_NOTIFY_CHANGE_ATTRIBUTES ;\r\n",ARRAYOFCONST((wstr_Data)));
		}
		if(dwFilter & FILE_NOTIFY_CHANGE_SIZE){
			wstr_Data = Format("%s4)FILE_NOTIFY_CHANGE_SIZE ;\r\n",ARRAYOFCONST((wstr_Data)));
		}
		if(dwFilter & FILE_NOTIFY_CHANGE_LAST_WRITE){
			wstr_Data = Format("%s5)FILE_NOTIFY_CHANGE_LAST_WRITE ;\r\n",ARRAYOFCONST((wstr_Data)));
		}
		if(dwFilter & FILE_NOTIFY_CHANGE_LAST_ACCESS){
			wstr_Data = Format("%s6)FILE_NOTIFY_CHANGE_LAST_ACCESS ;\r\n",ARRAYOFCONST((wstr_Data)));
		}
		if(dwFilter & FILE_NOTIFY_CHANGE_CREATION){
			wstr_Data = Format("%s7)FILE_NOTIFY_CHANGE_CREATION ;\r\n",ARRAYOFCONST((wstr_Data)));
		}
		if(dwFilter & FILE_NOTIFY_CHANGE_SECURITY){
			wstr_Data = Format("%s8)FILE_NOTIFY_CHANGE_SECURITY ;\r\n",ARRAYOFCONST((wstr_Data)));
		}

	}
	return wstr_Data;
 }
 ////////////////////////////////////////////////
 ////////////////////////////////////////////////
void LoadFromFileFolderWatcher( std::list<CFolderWatcher> * plst_FolderList){//Load from file FolderWatchers objects
	CHAR c_ch = ' ';//char buffer
	WCHAR w_ch = L' ';//wide char of c_ch
	int i_Num = 0;

	String wstr_Data = "";
	SFolderLog fl = {"","",0,0};
	int iNewLines = 1;//number of lines
	DWORD dwRetReadBytes = 0;//returned bytes
	HANDLE hReadFile; //handle of file
	String wstr_FullFile = L"Folder_Watch.txt";
	hReadFile = CreateFileW(wstr_FullFile.c_str(), //get file`s handle here write name of file where our records!!!!!!!!!!
									GENERIC_READ,
									0,
									NULL,
									OPEN_EXISTING,
									FILE_ATTRIBUTE_NORMAL | FILE_FLAG_DELETE_ON_CLOSE , //after close this file will be deleted
									NULL);


	if(hReadFile != INVALID_HANDLE_VALUE){//check for correct handle
		SetFilePointer(hReadFile,-1,NULL,FILE_BEGIN);
		for(;;){
			ReadFile(hReadFile,&c_ch,sizeof(CHAR),&dwRetReadBytes,(LPOVERLAPPED)NULL);

			MultiByteToWideChar(GetACP(),0,&c_ch,-1,&w_ch,sizeof(WCHAR));//convert char to wchar_t

			 if(w_ch != L'\r' && w_ch != L'\n'){ //check for new line and \r
					wstr_Data = Format("%s%s",ARRAYOFCONST((wstr_Data,w_ch)));
			 }

			if(w_ch == L'\n'|| dwRetReadBytes == 0){
				if((iNewLines % 4) == 1 ){//set name of logfile
					fl.wstr_Logfile = wstr_Data;
				}else if((iNewLines % 4) == 2 ){//set name of folder
					fl.wstr_Folder = wstr_Data;
				}else {
					 i_Num = StrToInt(wstr_Data);
					 if((iNewLines % 4) == 3){//set filter
						fl.dwFilter = i_Num;
							if(fl.dwFilter == 0){
								fl.dwFilter = 3;
							}
					 }else if((iNewLines % 4) == 0){
						fl.B_SubFolder = (BOOL)i_Num;
						if(fl.B_SubFolder > 0){
							fl.B_SubFolder = TRUE;
						}
						if((FolderExists(fl.wstr_Folder)!= FALSE) && FileExists(fl.wstr_Logfile) && IsExistsLog((*plst_FolderList),fl.wstr_Logfile) == FALSE && ItemIsExist((*plst_FolderList),fl.wstr_Folder )== FALSE ){//check for existence of file and folder
							SetupElem(plst_FolderList,fl);
						}
					 }

				}
				iNewLines++;
				wstr_Data = "";
			}
			if(dwRetReadBytes == 0){//if EOF
				break;
			}

		}
		CloseHandle(hReadFile);
	}

}

//////////////////////////////////////////
///////////////////////////////////////////////
BOOL LoadToFile(std::list<CFolderWatcher> * plst_FolderList){//Load after close existing FolderWatchers
	BOOL B_Success = TRUE;
	String wstr_Str = "";
	String wstr_FullFile = "";
	if(!plst_FolderList->empty()){
		wstr_FullFile = L"Folder_Watch.txt";
		HANDLE hWriteFile = CreateFileW(wstr_FullFile.c_str(), //get file`s handle here write name of file where our records!!!!!!!!!!
									GENERIC_WRITE ,
									0,
									NULL,
									OPEN_ALWAYS,
									FILE_ATTRIBUTE_NORMAL,
									NULL);
		if(hWriteFile != INVALID_HANDLE_VALUE){

			std::list<CFolderWatcher>::iterator it = plst_FolderList->begin();
			for (;it != plst_FolderList->end();it++){
					SetFilePointer(hWriteFile,-1,NULL,FILE_END);
					wstr_Str = Format("%s\r\n%s\r\n%d\r\n%d\r\n",ARRAYOFCONST(((*it).GetLogfile(),(*it).GetFolderName(),(*it).GetFilter(),(*it).GetSubfolder())));
					WriteData(wstr_Str,hWriteFile);
					(*it).TerminateWatch();//interrupt watching
					plst_FolderList->erase(it);//erase watcher
			}
            CloseHandle(hWriteFile);
		}else{
            BOOL B_Success = FALSE;
		}
	}else{
		BOOL B_Success = FALSE;
	}
	return B_Success;
}
////////////////////////////////////////
#endif

