//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Show_logs.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm_Show_logs *Form_Show_logs;
extern std::list<CFolderWatcher> g_lst_FolderList;

//---------------------------------------------------------------------------
__fastcall TForm_Show_logs::TForm_Show_logs(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm_Show_logs::FormActivate(TObject *Sender)
{
	if(!g_lst_FolderList.empty()){
	   SetList(g_lst_FolderList, ListBox_FolderWatcher);
	   Set_VertScroll(Form_Show_logs->ListBox_FolderWatcher);
	}else{
		ListBox_FolderWatcher->Items->Clear();
	}

	Form_Settings->Refresh();
}
//---------------------------------------------------------------------------

void __fastcall TForm_Show_logs::Button_ChooseClick(TObject *Sender)
{   String wstr_Data = "";
	if(!g_lst_FolderList.empty()&& ListBox_FolderWatcher->ItemIndex != -1){
		wstr_Data = ReadLogFile(&g_lst_FolderList,ListBox_FolderWatcher->Items->Strings[ListBox_FolderWatcher->ItemIndex]);
		Memo_Log->Text = wstr_Data;
	}else{
		ShowMessage("Please,Choose item or add (if List is empty)!!!");
	}
}
//---------------------------------------------------------------------------

