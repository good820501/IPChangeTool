object DataModule1: TDataModule1
  OldCreateOrder = False
  Left = 538
  Top = 216
  Height = 379
  Width = 336
  object ADOConnection1: TADOConnection
    ConnectionString = 
      'Provider=Microsoft.Jet.OLEDB.4.0;Jet OLEDB:Database Password=111' +
      '111;User ID=admin;Data Source=E:\pdj\ServicePDJ\DB\PDJInfo.mdb;P' +
      'ersist Security Info=True'
    LoginPrompt = False
    Mode = cmShareDenyNone
    Provider = 'Microsoft.Jet.OLEDB.4.0'
    Left = 144
    Top = 48
  end
  object ADOQuery1: TADOQuery
    Connection = ADOConnection1
    Parameters = <>
    Left = 64
    Top = 128
  end
  object ADOQuery2: TADOQuery
    Connection = ADOConnection1
    Parameters = <>
    Left = 216
    Top = 128
  end
end
