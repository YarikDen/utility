object Form_Show_logs: TForm_Show_logs
  Left = 0
  Top = 0
  Align = alCustom
  BorderIcons = []
  BorderStyle = bsSingle
  Caption = 'Show logs'
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
  OnActivate = FormActivate
  PixelsPerInch = 96
  TextHeight = 13
  object Label_ChooseWatcher: TLabel
    Left = 56
    Top = 32
    Width = 162
    Height = 18
    Caption = 'Choose Folder Watcher :'
    Color = clMenuHighlight
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentColor = False
    ParentFont = False
  end
  object Label1: TLabel
    Left = 360
    Top = 32
    Width = 58
    Height = 18
    Caption = 'Log File :'
    Color = clMenuHighlight
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentColor = False
    ParentFont = False
  end
  object ListBox_FolderWatcher: TListBox
    Left = 16
    Top = 56
    Width = 233
    Height = 241
    Cursor = crHandPoint
    Hint = 'Choose Folder Watcher'
    Color = 9494828
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -12
    Font.Name = 'Tahoma'
    Font.Style = []
    ItemHeight = 14
    ParentFont = False
    ParentShowHint = False
    ShowHint = True
    Sorted = True
    TabOrder = 0
  end
  object Memo_Log: TMemo
    Left = 280
    Top = 56
    Width = 273
    Height = 241
    Color = clWindowFrame
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWhite
    Font.Height = -13
    Font.Name = 'Tahoma'
    Font.Style = []
    ParentFont = False
    ReadOnly = True
    ScrollBars = ssBoth
    TabOrder = 1
  end
  object Button_Choose: TButton
    Left = 192
    Top = 328
    Width = 153
    Height = 57
    Cursor = crHandPoint
    Caption = 'Choose Folder'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clInfoText
    Font.Height = -19
    Font.Name = 'Times New Roman'
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    OnClick = Button_ChooseClick
  end
end
