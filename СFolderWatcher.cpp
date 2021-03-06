#include "CFolderWatcher.h"

    void WriteData(String wstrSrc,HANDLE hFile ){//Write data to file
		DWORD dwret = 0,size = 0;
		CHAR * pch = NULL;
		size = WideCharToMultiByte(GetACP(),0,wstrSrc.c_str(),-1,NULL,0,NULL,NULL);//convert char to wchar_t
		if(size != 0){
			pch = new CHAR[size+1];
			WideCharToMultiByte(GetACP(),0,wstrSrc.c_str(),-1,pch,size,NULL,NULL);
			WriteFile(hFile,pch,size,&dwret,NULL);
			delete [] pch;
		}

	}

	CFolderWatcher::CFolderWatcher(String wstrNameFolder ,String wstr_Logfile ,DWORD dwFilter ,BOOL BSubfolder){//default constructor
		this->Log.wstr_Folder = wstrNameFolder;
		this->Log.wstr_LogFile = wstr_Logfile;
		this->Log.dw_Filter = dwFilter;
		this->h_Thread = NULL;
		this->Log.h_Folder = NULL;
		this->dw_id = 0;
		this->B_State = FALSE;
		this->Log.B_Subfolder = BSubfolder;
	}

	void CFolderWatcher::StopWatch(){// stop
		if(this->h_Thread != NULL){
			SuspendThread(this->h_Thread);
			this->B_State = FALSE;
		}
	}

	void CFolderWatcher::ResumeWatch(){ //resume
		if(this->h_Thread != NULL){
			ResumeThread(this->h_Thread);
			this->B_State = TRUE;
        }
	}

	void CFolderWatcher::TerminateWatch(){//terminate
		DWORD exit_code = 0;
		if(this->h_Thread != NULL){
            TerminateThread(this->h_Thread,exit_code);
			CloseHandle(this->h_Thread);
            if(this->Log.h_Folder != INVALID_HANDLE_VALUE )
				CloseHandle(this->Log.h_Folder);
		}
	}

	BOOL CFolderWatcher::GetState(void){//get state
		return this->B_State;
	}

	String CFolderWatcher::GetFolderName(void){//get folder name
		return this->Log.wstr_Folder;
	}

	DWORD CFolderWatcher::GetFilter(void){ //get value of filter
		return this->Log.dw_Filter;
	}

	BOOL CFolderWatcher::GetSubfolder(void){ //get value of subfolder
		return this->Log.B_Subfolder;
	}

	String CFolderWatcher::GetLogfile(void){//get name of log file
		return this->Log.wstr_LogFile;
	}

	HANDLE CFolderWatcher::GetHandleWatcher(){
        this->h_Thread;
	}

	void CFolderWatcher::SetFilter(DWORD dwFilter){ //set filter
		this->Log.dw_Filter = dwFilter;
	}

	void CFolderWatcher::SetFolderName(String wstrName){ //set folder name
		this->Log.wstr_Folder=wstrName;
	}

	void CFolderWatcher::SetSubfolder(BOOL BSubfolder){//set follow subfilders
		this->Log.B_Subfolder = BSubfolder;
	}

	void CFolderWatcher::SetLogfile(String wstr_Log){//set name of file where will be written changes
		this->Log.wstr_LogFile = wstr_Log;
	}



	void CFolderWatcher::InitThreadWatch(void){//Initialize Folder Watcher
		DWORD id = 0;
		this->Log.h_Folder = CreateFileW( //open folder
			this->Log.wstr_Folder.c_str(),
			FILE_LIST_DIRECTORY ,FILE_SHARE_WRITE | FILE_SHARE_READ | FILE_SHARE_DELETE,
			NULL,
			OPEN_EXISTING,
			FILE_FLAG_BACKUP_SEMANTICS,
			NULL);
		LogInfo * pLog = new LogInfo[1];
        (*pLog) = this->Log;
		this->h_Thread =  CreateThread(NULL,0,&ThreadNotificator,pLog,CREATE_SUSPENDED,&id);
		this->dw_id = id;
		if(this->h_Thread == NULL){
			ExitProcess(0);
		}
		SetThreadPriority(this->h_Thread,THREAD_PRIORITY_IDLE);
	}

	

	DWORD WINAPI ThreadNotificator( LPVOID lpParam ){ //Thread Function

		//LogInfo * pData = (LogInfo *)lpParam;//reinterpret_cast<PArgs>(lpParam);
		LogInfo pData =  *((LogInfo *)lpParam);
		delete [] ((LogInfo *)lpParam); //free space that we gave for object in the class
		String wstr_FileName;
		String wstr_Change;
		if (pData.h_Folder == INVALID_HANDLE_VALUE)//if couldnt open file
			return GetLastError();

		BYTE byBuffer[1024];//1Kb
		DWORD dwOffset = 0;//number of record
		DWORD dwAction = 0;
		PFILE_NOTIFY_INFORMATION  pstrFileNotifyInfo; //special structure that help us to get certain info about change and place where it was
		DWORD dwBytesReturned = 0,
		dwRetWriteByte = 0;
		WIN32_FIND_DATAW fd;
		HANDLE hFindFile,
		hWriteFile;
		time_t tTime;//time of change

		while(true)//Monitoring
		{
			if( ReadDirectoryChangesW( pData.h_Folder,byBuffer, sizeof(byBuffer), pData.B_Subfolder,pData.dw_Filter, &dwBytesReturned, NULL, NULL) )
			{   tTime = time(NULL);
				while(true){
					pstrFileNotifyInfo = (PFILE_NOTIFY_INFORMATION)&byBuffer[dwOffset];
					dwOffset += pstrFileNotifyInfo->NextEntryOffset;
					dwAction = pstrFileNotifyInfo->Action;
					wstr_FileName = Format("%s\\%s",ARRAYOFCONST((pData.wstr_Folder,WideCharToString(pstrFileNotifyInfo->FileName))));
					if(dwAction != FILE_ACTION_REMOVED){
						if(dwAction != FILE_ACTION_RENAMED_OLD_NAME){
							hFindFile = FindFirstFileW(wstr_FileName.c_str(),&fd);
						}
						}
						if(dwAction == FILE_ACTION_ADDED){
							 if(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){ //if file is a folder
								wstr_Change = Format("Time:<<%s>>; Name of file:<<%s>>; Change: <<Folder was added>>;\r\n\r\n",ARRAYOFCONST((ctime(&tTime),wstr_FileName)));
							 }else{
								wstr_Change = Format("Time:<<%s>>; Name of file:<<%s>>; Change: <<File was added>>;\r\n\r\n",ARRAYOFCONST((ctime(&tTime),wstr_FileName)));
							 }
						}else if(dwAction == FILE_ACTION_REMOVED){
							wstr_Change = Format("Time:<<%s>>; Name of file or folder:<<%s>>; Change: <<File or folder was deleted>>;\r\n\r\n",ARRAYOFCONST((ctime(&tTime),wstr_FileName)));
						}else if(dwAction == FILE_ACTION_MODIFIED){
							if(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
								wstr_Change = Format("Time:<<%s>>; Name of file:<<%s>>; Change: <<Folder was modified>>;\r\n\r\n",ARRAYOFCONST((ctime(&tTime),wstr_FileName)));
							 }else{
								wstr_Change = Format("Time:<<%s>>; Name of file:<<%s>>; Change: <<File was modified>>;\r\n\r\n",ARRAYOFCONST((ctime(&tTime),wstr_FileName)));
							 }
						}else if(dwAction == FILE_ACTION_RENAMED_OLD_NAME){
							wstr_Change = Format("Time:<<%s>>; Change: <<Renamed>>; Old Name of file or folder:<<%s>>; ",ARRAYOFCONST((ctime(&tTime),wstr_FileName)));
						}else if(dwAction == FILE_ACTION_RENAMED_NEW_NAME){
							wstr_Change = Format("%sNew Name of file or folder:<<%s>>;\r\n\r\n",ARRAYOFCONST((wstr_Change,wstr_FileName)));
						}

						if(dwAction != FILE_ACTION_RENAMED_OLD_NAME && dwAction != FILE_ACTION_REMOVED){
							FindClose(hFindFile);
						}

						if(dwAction != FILE_ACTION_RENAMED_OLD_NAME){
							hWriteFile = CreateFileW(pData.wstr_LogFile.c_str(),GENERIC_WRITE,0,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);
							if(hWriteFile != INVALID_HANDLE_VALUE){
								SetFilePointer(hWriteFile,-1,NULL,FILE_END);
								WriteData(wstr_Change,hWriteFile);
								CloseHandle(hWriteFile);
							}
						}

						if(!pstrFileNotifyInfo->NextEntryOffset){
							break;
						}
					}
					ZeroMemory(&byBuffer,sizeof(byBuffer));
					dwOffset = 0;
					pstrFileNotifyInfo = NULL;
			}
		}


		return 0;
	}
