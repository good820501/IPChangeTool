object Form7: TForm7
  Left = 498
  Top = 201
  BorderStyle = bsDialog
  Caption = #25968#25454#22791#20221#19982#24674#22797
  ClientHeight = 234
  ClientWidth = 504
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 489
    Height = 81
    Caption = #25968#25454#22791#20221
    TabOrder = 0
    object Label1: TLabel
      Left = 16
      Top = 24
      Width = 97
      Height = 13
      AutoSize = False
      Caption = #22791#20221#25968#25454#25991#20214#21040
    end
    object Edit1: TEdit
      Left = 120
      Top = 16
      Width = 281
      Height = 21
      ReadOnly = True
      TabOrder = 0
    end
    object Button1: TButton
      Left = 416
      Top = 16
      Width = 65
      Height = 25
      Caption = #27983'    '#35272'(&B)'
      TabOrder = 1
      OnClick = Button1Click
    end
    object Button2: TButton
      Left = 120
      Top = 48
      Width = 89
      Height = 25
      Caption = #24320#22987#22791#20221'(&A)'
      TabOrder = 2
      OnClick = Button2Click
    end
  end
  object GroupBox2: TGroupBox
    Left = 7
    Top = 104
    Width = 489
    Height = 89
    Caption = #25968#25454#24674#22797
    TabOrder = 1
    object Label2: TLabel
      Left = 8
      Top = 24
      Width = 113
      Height = 13
      AutoSize = False
      Caption = #38656#35201#24674#22797#25968#25454#25991#20214
    end
    object Edit2: TEdit
      Left = 120
      Top = 16
      Width = 281
      Height = 21
      TabOrder = 0
    end
    object Button4: TButton
      Left = 416
      Top = 16
      Width = 65
      Height = 25
      Caption = #27983'    '#35272'(&W)'
      TabOrder = 1
      OnClick = Button4Click
    end
    object Button5: TButton
      Left = 120
      Top = 48
      Width = 89
      Height = 25
      Caption = #24320#22987#24674#22797'(&R)'
      TabOrder = 2
      OnClick = Button5Click
    end
  end
  object Button3: TButton
    Left = 128
    Top = 200
    Width = 89
    Height = 25
    Caption = #20851'    '#38381'(&C)'
    TabOrder = 2
    OnClick = Button3Click
  end
  object OpenDialog1: TOpenDialog
    DefaultExt = 'D:\'
    Filter = #29028#28845#25968#25454#25991#20214'(*.bak)|*.bak'
    Left = 272
    Top = 200
  end
end
