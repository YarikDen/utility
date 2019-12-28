object Form_Add_folder: TForm_Add_folder
  Left = 0
  Top = 0
  Align = alCustom
  BorderIcons = []
  BorderStyle = bsSingle
  Caption = 'Add folder'
  ClientHeight = 422
  ClientWidth = 569
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  FormStyle = fsMDIChild
  OldCreateOrder = False
  Position = poDesigned
  Visible = True
  PixelsPerInch = 96
  TextHeight = 13
  object Label_Filter: TLabel
    Left = 308
    Top = 30
    Width = 145
    Height = 16
    Caption = 'Choose Notificaton filter :'
    Color = clMenuHighlight
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentColor = False
    ParentFont = False
  end
  object Label_ChooseWatcher: TLabel
    Left = 23
    Top = 30
    Width = 91
    Height = 16
    Caption = 'Choose Folder :'
    Color = clMenuHighlight
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentColor = False
    ParentFont = False
  end
  object DriveComboBox1: TDriveComboBox
    Left = 23
    Top = 52
    Width = 273
    Height = 23
    Color = clInactiveCaption
    DirList = DirectoryListBox1
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Times New Roman'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    TextCase = tcUpperCase
  end
  object DirectoryListBox1: TDirectoryListBox
    Left = 23
    Top = 81
    Width = 273
    Height = 149
    Cursor = crHandPoint
    Color = clMoneyGreen
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = []
    ItemHeight = 18
    ParentFont = False
    ParentShowHint = False
    ShowHint = True
    TabOrder = 1
    OnDblClick = DirectoryListBox1DblClick
  end
  object Button_Create: TButton
    Left = 200
    Top = 256
    Width = 160
    Height = 65
    Caption = 'Create Folder Watcher'
    Font.Charset = RUSSIAN_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Times New Roman'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    OnClick = Button_CreateClick
  end
  object CheckListBox_Filter: TCheckListBox
    Left = 308
    Top = 52
    Width = 232
    Height = 155
    Cursor = crHandPoint
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = []
    HeaderBackgroundColor = clMoneyGreen
    ItemHeight = 18
    Items.Strings = (
      '1) Notify Change File Name ;'
      '2) Notify Change Folder Name ;'
      '3) Notify Change Attributes ;'
      '4) Notify Change Size ;'
      '5) Notify Change Last Write ;'
      '6) Notify Change Last Access ;'
      '7) Notify Change Creation ;'
      '8) Notify Change Security ;')
    ParentFont = False
    TabOrder = 3
  end
  object CheckBox_Subfolder: TCheckBox
    Left = 307
    Top = 213
    Width = 117
    Height = 17
    Cursor = crHandPoint
    Caption = 'Check subfolders'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clBlack
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
  end
  object OpenDialog_FileLog: TOpenDialog
    Filter = 'Text1|*.txt|Text2|*.TXT'
    Options = [ofReadOnly, ofHideReadOnly, ofPathMustExist, ofFileMustExist, ofEnableSizing]
    Title = 'Select file for saving folder changes :'
  end
end
