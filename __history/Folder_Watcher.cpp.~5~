//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include <tchar.h>
//---------------------------------------------------------------------------
USEFORM("Show_logs.cpp", Form_Show_logs);
USEFORM("Settings.cpp", Form_Settings);
USEFORM("Add.cpp", Form_Add_folder);
USEFORM("About.cpp", Form_Info);
USEFORM("main.cpp", Form_main);
//---------------------------------------------------------------------------
int WINAPI _tWinMain(HINSTANCE, HINSTANCE, LPTSTR, int)
{   ////Code for control  of other program instances
	HANDLE hMutex;
	hMutex = CreateMutexA(NULL,TRUE,"UNIQUE MUTEX");
    if(GetLastError() == ERROR_ALREADY_EXISTS){
        ShowMessage ("This program is running now");
        Application->Terminate();
    }
    ReleaseMutex(hMutex);

	try
	{
		Application->Initialize();
		Application->MainFormOnTaskBar = true;
		Application->CreateForm(__classid(TForm_main), &Form_main);
		Application->CreateForm(__classid(TForm_Info), &Form_Info);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	catch (...)
	{
		try
		{
			throw Exception("");
		}
		catch (Exception &exception)
		{
			Application->ShowException(&exception);
		}
	}
	return 0;
}
//---------------------------------------------------------------------------
