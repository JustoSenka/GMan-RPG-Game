object Form1: TForm1
  Left = 189
  Top = 109
  Width = 808
  Height = 654
  Caption = 'GMan RPG Map Creator'
  Color = clBtnFace
  Font.Charset = BALTIC_CHARSET
  Font.Color = clWindowText
  Font.Height = -15
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  OnKeyUp = FormKeyUp
  OnMouseDown = FormMouseDown
  OnMouseMove = FormMouseMove
  OnMouseUp = FormMouseUp
  OnResize = FormResize
  PixelsPerInch = 96
  TextHeight = 16
  object Memo1: TMemo
    Left = 440
    Top = 272
    Width = 129
    Height = 89
    TabStop = False
    Enabled = False
    Lines.Strings = (
      'Memo1')
    TabOrder = 0
  end
  object Button1: TButton
    Left = 288
    Top = 24
    Width = 369
    Height = 65
    Caption = 'Start the Game'
    Font.Charset = ARABIC_CHARSET
    Font.Color = clWindowText
    Font.Height = -53
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 4
    OnClick = Button1Click
  end
  object Draw: TButton
    Left = 344
    Top = 272
    Width = 75
    Height = 25
    Caption = 'Draw'
    Font.Charset = ARABIC_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 1
    TabStop = False
    OnClick = DrawClick
  end
  object Save: TButton
    Left = 344
    Top = 304
    Width = 75
    Height = 25
    Caption = 'Save'
    Font.Charset = ARABIC_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 2
    TabStop = False
    OnClick = SaveClick
  end
  object Load: TButton
    Left = 344
    Top = 336
    Width = 75
    Height = 25
    Caption = 'Load'
    Font.Charset = ARABIC_CHARSET
    Font.Color = clWindowText
    Font.Height = -15
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 3
    TabStop = False
    OnClick = LoadClick
  end
  object MainMenu1: TMainMenu
    Left = 104
    Top = 32
    object File1: TMenuItem
      Caption = 'File'
      object New1: TMenuItem
        Caption = 'New'
        ShortCut = 16462
        OnClick = New1Click
      end
      object Load1: TMenuItem
        Caption = 'Open'
        OnClick = Load1Click
      end
      object N1: TMenuItem
        Caption = '-'
      end
      object Save1: TMenuItem
        Caption = 'Save'
        ShortCut = 16467
        OnClick = Save1Click
      end
      object SaveAs1: TMenuItem
        Caption = 'Save As...'
        OnClick = SaveAs1Click
      end
      object N2: TMenuItem
        Caption = '-'
      end
      object Draw1: TMenuItem
        Caption = 'Draw'
        OnClick = Draw1Click
      end
      object Exit2: TMenuItem
        Caption = 'Exit'
        OnClick = Exit2Click
      end
    end
    object Edit1: TMenuItem
      Caption = 'Edit'
      object Undo1: TMenuItem
        Caption = 'Undo'
        ShortCut = 16474
        OnClick = Undo1Click
      end
      object Delete1: TMenuItem
        Caption = 'Delete'
        ShortCut = 16452
        OnClick = Delete1Click
      end
    end
    object Tools1: TMenuItem
      Caption = 'Tools'
      object CenterPlayer1: TMenuItem
        Caption = 'Center Player'
        OnClick = CenterPlayer1Click
      end
      object Usellect1: TMenuItem
        Caption = 'Unselect'
        OnClick = Usellect1Click
      end
      object Database1: TMenuItem
        Caption = 'Database'
        OnClick = Database1Click
      end
    end
    object Exit1: TMenuItem
      Caption = 'Exit'
      OnClick = Exit1Click
    end
  end
  object Timer1: TTimer
    Interval = 500
    OnTimer = Timer1Timer
    Left = 48
    Top = 32
  end
  object OpenDialog1: TOpenDialog
    Filter = 'GMan RPG Map file (*.map)|*.map'
    Left = 144
    Top = 32
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = '*.map'
    Filter = 'GMan RPG Map file (*.map)|*.map'
    Left = 176
    Top = 32
  end
end
