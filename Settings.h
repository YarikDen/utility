//---------------------------------------------------------------------------

#ifndef SettingsH
#define SettingsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "main.h"
#include <Vcl.ExtCtrls.hpp>
#include <Vcl.CheckLst.hpp>
//---------------------------------------------------------------------------
class TForm_Settings : public TForm
{
__published:	// IDE-managed Components
	TGroupBox *GroupBox1;
	TLabel *Label_ChooseWatcher;
	TLabel *Label_Filter;
	TButton *Button_Start;
	TButton *Button_Delete;
	TButton *Button_Stop;
	TButton *Button_ShowFilter;
	TMemo *Memo_Filter;
	TListBox *ListBox_Folder;
	TButton *Button_Log;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall Button_DeleteClick(TObject *Sender);
	void __fastcall Button_StopClick(TObject *Sender);
	void __fastcall Button_StartClick(TObject *Sender);
	void __fastcall Button_ShowFilterClick(TObject *Sender);
	void __fastcall Button_LogClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm_Settings(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_Settings *Form_Settings;
//---------------------------------------------------------------------------
#endif
