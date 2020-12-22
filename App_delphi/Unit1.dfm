object Form1: TForm1
  Left = 873
  Top = 374
  Caption = 'DD '#31034#20363
  ClientHeight = 412
  ClientWidth = 477
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnClose = FormClose
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object GroupBox1: TGroupBox
    Left = 120
    Top = 33
    Width = 225
    Height = 176
    Caption = #21151#33021#36873#39033
    TabOrder = 0
    object RadioButton1: TRadioButton
      Left = 30
      Top = 40
      Width = 83
      Height = 17
      Caption = #40736#26631#31227#21160
      TabOrder = 0
      OnClick = RadioButton1Click
    end
    object RadioButton2: TRadioButton
      Left = 134
      Top = 40
      Width = 75
      Height = 17
      Caption = #40736#26631#28857#20987
      TabOrder = 1
      OnClick = RadioButton2Click
    end
    object RadioButton3: TRadioButton
      Left = 30
      Top = 84
      Width = 83
      Height = 17
      Caption = #40736#26631#28378#36718
      TabOrder = 2
      OnClick = RadioButton3Click
    end
    object RadioButton4: TRadioButton
      Left = 134
      Top = 84
      Width = 75
      Height = 17
      Caption = #38190#30424#25353#38190
      TabOrder = 3
      OnClick = RadioButton4Click
    end
    object RadioButton5: TRadioButton
      Left = 30
      Top = 129
      Width = 83
      Height = 17
      Caption = #38190#30424#23383#31526
      TabOrder = 4
      OnClick = RadioButton5Click
    end
    object RadioButton6: TRadioButton
      Left = 134
      Top = 129
      Width = 75
      Height = 17
      Caption = 'Demo'
      Enabled = False
      TabOrder = 5
      OnClick = RadioButton6Click
    end
  end
  object Button2: TButton
    Left = 254
    Top = 232
    Width = 75
    Height = 25
    Caption = #20572#27490
    Enabled = False
    TabOrder = 1
    OnClick = Button2Click
  end
  object Button1: TButton
    Left = 150
    Top = 232
    Width = 75
    Height = 25
    Caption = #24320#22987
    TabOrder = 2
    OnClick = Button1Click
  end
  object Edit1: TEdit
    Left = 56
    Top = 280
    Width = 361
    Height = 21
    TabOrder = 3
    Text = 'Edit1'
  end
  object Button3: TButton
    Left = 184
    Top = 320
    Width = 113
    Height = 25
    Caption = #23450#20301'DD'#20837#21475#25991#20214
    TabOrder = 4
    OnClick = Button3Click
  end
  object Timer1: TTimer
    Interval = 5000
    OnTimer = Timer1Timer
  end
  object OpenTextFileDialog1: TOpenTextFileDialog
    Filter = 'DD'#20837#21475#25991#20214'|*.DLL'
    Top = 64
  end
end
