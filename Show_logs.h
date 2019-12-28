//---------------------------------------------------------------------------

#ifndef Show_logsH
#define Show_logsH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include "main.h"
//---------------------------------------------------------------------------
class TForm_Show_logs : public TForm
{
__published:	// IDE-managed Components
	TLabel *Label_ChooseWatcher;
	TLabel *Label1;
	TListBox *ListBox_FolderWatcher;
	TMemo *Memo_Log;
	TButton *Button_Choose;
	void __fastcall FormActivate(TObject *Sender);
	void __fastcall Button_ChooseClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm_Show_logs(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_Show_logs *Form_Show_logs;
//---------------------------------------------------------------------------
#endif