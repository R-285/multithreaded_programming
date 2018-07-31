object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'BusSchedule'
  ClientHeight = 235
  ClientWidth = 792
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 8
    Width = 162
    Height = 13
    Caption = #1050#1086#1083#1080#1095#1077#1089#1090#1074#1086' '#1072#1074#1090#1086#1073#1091#1089#1086#1074' (<=20): '
  end
  object Label2: TLabel
    Left = 8
    Top = 37
    Width = 115
    Height = 13
    Caption = #1054#1089#1090#1072#1085#1086#1074#1082#1072' '#8470'1  (1000)'
  end
  object Label3: TLabel
    Left = 8
    Top = 62
    Width = 115
    Height = 13
    Caption = #1054#1089#1090#1072#1085#1086#1074#1082#1072' '#8470'2  (4000)'
  end
  object Label4: TLabel
    Left = 8
    Top = 89
    Width = 115
    Height = 13
    Caption = #1054#1089#1090#1072#1085#1086#1074#1082#1072' '#8470'3  (6000)'
  end
  object Label5: TLabel
    Left = 8
    Top = 116
    Width = 121
    Height = 13
    Caption = #1054#1089#1090#1072#1085#1086#1074#1082#1072' '#8470'4  (10000)'
  end
  object Label6: TLabel
    Left = 8
    Top = 143
    Width = 121
    Height = 13
    Caption = #1054#1089#1090#1072#1085#1086#1074#1082#1072' '#8470'5  (12000)'
  end
  object label7: TLabel
    Left = 512
    Top = 15
    Width = 19
    Height = 13
    Caption = 'M/C'
  end
  object Label8: TLabel
    Left = 600
    Top = 15
    Width = 8
    Height = 13
    Caption = 'M'
  end
  object Edit1: TEdit
    Left = 169
    Top = 3
    Width = 24
    Height = 21
    ReadOnly = True
    TabOrder = 0
    Text = '5'
  end
  object ButtonPlus: TButton
    Left = 199
    Top = 3
    Width = 25
    Height = 25
    Caption = '+'
    TabOrder = 1
    OnClick = ButtonPlusClick
  end
  object ButtonMinus: TButton
    Left = 230
    Top = 3
    Width = 27
    Height = 25
    Caption = '-'
    TabOrder = 2
    OnClick = ButtonMinusClick
  end
  object Memo1: TMemo
    Left = 448
    Top = 34
    Width = 321
    Height = 159
    Lines.Strings = (
      'Memo1')
    TabOrder = 3
  end
  object StartButton: TButton
    Left = 584
    Top = 199
    Width = 75
    Height = 25
    Caption = 'Start'
    TabOrder = 4
    OnClick = StartButtonClick
  end
  object StopButton: TButton
    Left = 680
    Top = 199
    Width = 75
    Height = 25
    Caption = 'Stop'
    TabOrder = 5
    OnClick = StopButtonClick
  end
  object Memo2: TMemo
    Left = 160
    Top = 34
    Width = 273
    Height = 159
    Lines.Strings = (
      'Memo2')
    TabOrder = 6
  end
  object Timer1: TTimer
    Interval = 100
    OnTimer = Timer1Timer
    Left = 48
    Top = 160
  end
end
