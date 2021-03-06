//---------------------------------------------------------------------------

#ifndef AddH
#define AddH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.FileCtrl.hpp>
#include <Vcl.CheckLst.hpp>
#include <Vcl.Dialogs.hpp>
#include "main.h"
//---------------------------------------------------------------------------
class TForm_Add_folder : public TForm
{
__published:	// IDE-managed Components
	TDriveComboBox *DriveComboBox1;
	TDirectoryListBox *DirectoryListBox1;
	TButton *Button_Create;
	TCheckListBox *CheckListBox_Filter;
	TCheckBox *CheckBox_Subfolder;
	TLabel *Label_Filter;
	TLabel *Label_ChooseWatcher;
	TOpenDialog *OpenDialog_FileLog;
	void __fastcall Button_CreateClick(TObject *Sender);
	void __fastcall DirectoryListBox1DblClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	__fastcall TForm_Add_folder(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_Add_folder *Form_Add_folder;
//---------------------------------------------------------------------------
#endif
