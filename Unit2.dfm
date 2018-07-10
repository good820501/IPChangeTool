object Form2: TForm2
  Left = 279
  Top = 195
  BorderStyle = bsNone
  Caption = #38144#21806#25253#34920
  ClientHeight = 565
  ClientWidth = 833
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 344
    Top = 0
    Width = 233
    Height = 33
    AutoSize = False
    Caption = #38144#21806#32479#35745#25253#34920
    Font.Charset = GB2312_CHARSET
    Font.Color = clWindowText
    Font.Height = -29
    Font.Name = #38582#20070
    Font.Style = [fsBold]
    ParentFont = False
  end
  object GroupBox1: TGroupBox
    Left = 64
    Top = 40
    Width = 721
    Height = 89
    Caption = #22635#25253#20107#39033
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = #23435#20307
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 0
    object Label2: TLabel
      Left = 8
      Top = 24
      Width = 65
      Height = 13
      AutoSize = False
      Caption = #22635#25253#21333#20301
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #23435#20307
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label3: TLabel
      Left = 232
      Top = 24
      Width = 49
      Height = 13
      AutoSize = False
      Caption = #22635#25253#20154
      Font.Charset = GB2312_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #23435#20307
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label4: TLabel
      Left = 464
      Top = 24
      Width = 65
      Height = 13
      AutoSize = False
      Caption = #22635#25253#26085#26399
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #23435#20307
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Edit1: TEdit
      Left = 80
      Top = 16
      Width = 121
      Height = 21
      TabOrder = 0
    end
    object Edit2: TEdit
      Left = 296
      Top = 16
      Width = 121
      Height = 21
      TabOrder = 1
    end
    object Button1: TButton
      Left = 400
      Top = 48
      Width = 121
      Height = 25
      Caption = #29983#25104#25253#34920'(&O)'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #23435#20307
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 2
      OnClick = Button1Click
    end
    object Button4: TButton
      Left = 216
      Top = 48
      Width = 121
      Height = 25
      Caption = #20462#25913#26412#26399#25968#25454'(&D)'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #23435#20307
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 3
      OnClick = Button4Click
    end
    object DateTimePicker1: TDateTimePicker
      Left = 528
      Top = 16
      Width = 186
      Height = 21
      CalAlignment = dtaLeft
      Date = 39690.4707042014
      Time = 39690.4707042014
      DateFormat = dfShort
      DateMode = dmComboBox
      Kind = dtkDate
      ParseInput = False
      TabOrder = 4
    end
    object Button6: TButton
      Left = 584
      Top = 48
      Width = 129
      Height = 25
      Caption = #28165#31354#21382#21490#25968#25454'(&C)'
      TabOrder = 5
      OnClick = Button6Click
    end
    object Button5: TButton
      Left = 8
      Top = 48
      Width = 145
      Height = 25
      Caption = #32534#36753#29289#21697#31181#31867'(&C)'
      Font.Charset = ANSI_CHARSET
      Font.Color = clWindowText
      Font.Height = -13
      Font.Name = #23435#20307
      Font.Style = [fsBold]
      ParentFont = False
      TabOrder = 6
      OnClick = Button5Click
    end
  end
  object GroupBox2: TGroupBox
    Left = 64
    Top = 136
    Width = 729
    Height = 385
    Caption = #25253#34920#26126#32454
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = #23435#20307
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 1
    object ListView1: TListView
      Left = 8
      Top = 24
      Width = 713
      Height = 345
      Columns = <
        item
          Caption = #32534#21495
        end
        item
          Caption = #21697'  '#31181
          Width = 60
        end
        item
          Caption = #26412#26399#25968#37327
          Width = 70
        end
        item
          Caption = #26412#26399#37329#39069
          Width = 70
        end
        item
          Caption = #27490#26376#25968#37327
          Width = 70
        end
        item
          Caption = #27490#26376#37329#39069
          Width = 70
        end
        item
          Caption = #27490#26376#24179#22343#20215
          Width = 80
        end
        item
          Caption = #27490#24180#25968#37327
          Width = 70
        end
        item
          Caption = #27490#24180#37329#39069
          Width = 70
        end
        item
          Caption = #27490#24180#24179#22343#39069
          Width = 80
        end>
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -11
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      GridLines = True
      RowSelect = True
      ParentFont = False
      TabOrder = 0
      ViewStyle = vsReport
    end
  end
  object Button2: TButton
    Left = 128
    Top = 528
    Width = 129
    Height = 25
    Caption = #23548#20986#21040'Excel'#65288'&E'#65289
    Font.Charset = GB2312_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = #23435#20307
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 2
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 584
    Top = 760
    Width = 129
    Height = 25
    Caption = #25171'    '#21360'(&P)'
    Font.Charset = ANSI_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = #23435#20307
    Font.Style = [fsBold]
    ParentFont = False
    TabOrder = 3
    Visible = False
  end
end
