object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'DD'
  ClientHeight = 273
  ClientWidth = 563
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 411
    Top = 180
    Width = 30
    Height = 13
    AutoSize = False
  end
  object Edit1: TEdit
    Left = 42
    Top = 18
    Width = 481
    Height = 21
    TabOrder = 0
    Text = 'Edit1'
  end
  object Button1: TButton
    Left = 232
    Top = 45
    Width = 105
    Height = 25
    Caption = #23450#20301'DD'#20837#21475#25991#20214
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 232
    Top = 224
    Width = 75
    Height = 25
    Caption = #24320#22987
    Enabled = False
    TabOrder = 2
    OnClick = Button2Click
  end
  object RadioGroup1: TRadioGroup
    Left = 188
    Top = 88
    Width = 185
    Height = 105
    Caption = #27979#35797#39033#30446#65306
    Columns = 2
    ItemIndex = 0
    Items.Strings = (
      #40736#26631#28857#20987
      #40736#26631#31227#21160
      #40736#26631#28378#36718
      #38190#30424#25353#38190
      #23383#31526#36755#20837
      'DEMO')
    TabOrder = 3
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 3000
    OnTimer = Timer1Timer
    Left = 16
    Top = 136
  end
  object OpenDialog1: TOpenDialog
    Left = 48
    Top = 136
  end
end
