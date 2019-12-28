//---------------------------------------------------------------------------

#ifndef AboutH
#define AboutH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
//---------------------------------------------------------------------------
class TForm_Info : public TForm
{
__published:	// IDE-managed Components
	TMemo *Memo_Info;
private:	// User declarations
public:		// User declarations
	__fastcall TForm_Info(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm_Info *Form_Info;
//---------------------------------------------------------------------------
#endif
