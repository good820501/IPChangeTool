object Form5: TForm5
  Left = 480
  Top = 362
  BorderStyle = bsDialog
  Caption = #29289#21697#31181#31867#21517#31216
  ClientHeight = 148
  ClientWidth = 348
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
  object Label1: TLabel
    Left = 40
    Top = 24
    Width = 145
    Height = 13
    AutoSize = False
    Caption = #35831#36755#20837#29289#21697#31181#31867#21517#31216':'
  end
  object Edit1: TEdit
    Left = 40
    Top = 48
    Width = 225
    Height = 21
    TabOrder = 0
    OnKeyDown = Edit1KeyDown
  end
  object Button1: TButton
    Left = 40
    Top = 104
    Width = 75
    Height = 25
    Caption = #30830'   '#23450'(&O)'
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 192
    Top = 104
    Width = 75
    Height = 25
    Caption = #21462'    '#28040'(&C)'
    TabOrder = 2
    OnClick = Button2Click
  end
end
