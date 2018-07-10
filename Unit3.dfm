object Form3: TForm3
  Left = 707
  Top = 313
  BorderStyle = bsDialog
  Caption = #29289#21697#31181#31867#32534#36753
  ClientHeight = 397
  ClientWidth = 341
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 185
    Height = 385
    Caption = #29616#26377#29289#21697#31181#31867
    TabOrder = 0
    object ListBox1: TListBox
      Left = 8
      Top = 16
      Width = 169
      Height = 361
      ItemHeight = 13
      TabOrder = 0
      OnClick = ListBox1Click
      OnDblClick = ListBox1DblClick
    end
  end
  object Button1: TButton
    Left = 224
    Top = 32
    Width = 89
    Height = 25
    Caption = #28155'    '#21152'(&A)'
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 224
    Top = 88
    Width = 89
    Height = 25
    Caption = #20462'    '#25913'(&E)'
    Enabled = False
    TabOrder = 2
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 224
    Top = 152
    Width = 89
    Height = 25
    Caption = #21024'    '#38500'(&D)'
    Enabled = False
    TabOrder = 3
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 224
    Top = 328
    Width = 89
    Height = 25
    Caption = #30830'    '#23450'(&O)'
    TabOrder = 4
    OnClick = Button4Click
  end
end
