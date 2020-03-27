object Form2: TForm2
  Left = 464
  Top = 113
  BorderStyle = bsSingle
  Caption = 'Database'
  ClientHeight = 600
  ClientWidth = 800
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 24
    Top = 16
    Width = 111
    Height = 37
    Caption = 'Items:'
    Font.Charset = BALTIC_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
  end
  object Label2: TLabel
    Left = 224
    Top = 160
    Width = 41
    Height = 16
    Caption = 'Type:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold]
    ParentFont = False
  end
  object Image: TImage
    Left = 640
    Top = 48
    Width = 105
    Height = 105
    Stretch = True
  end
  object Bevel1: TBevel
    Left = 16
    Top = 288
    Width = 769
    Height = 9
    Style = bsRaised
  end
  object Label3: TLabel
    Left = 24
    Top = 304
    Width = 159
    Height = 37
    Caption = 'Enemies:'
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -32
    Font.Name = 'MS Sans Serif'
    Font.Style = [fsBold, fsItalic]
    ParentFont = False
  end
  object Image2: TImage
    Left = 640
    Top = 416
    Width = 105
    Height = 105
  end
  object IList: TListBox
    Left = 16
    Top = 56
    Width = 193
    Height = 225
    Font.Charset = BALTIC_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Palatino Linotype'
    Font.Style = []
    ItemHeight = 22
    ParentFont = False
    TabOrder = 0
    OnClick = IListClick
    OnMouseDown = IListMouseDown
    OnMouseMove = IListMouseMove
    OnMouseUp = IListMouseUp
  end
  object lvl: TLabeledEdit
    Left = 224
    Top = 72
    Width = 89
    Height = 24
    EditLabel.Width = 48
    EditLabel.Height = 20
    EditLabel.Caption = 'Level:'
    EditLabel.Font.Charset = DEFAULT_CHARSET
    EditLabel.Font.Color = clWindowText
    EditLabel.Font.Height = -16
    EditLabel.Font.Name = 'MS Sans Serif'
    EditLabel.Font.Style = [fsBold]
    EditLabel.ParentFont = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    LabelPosition = lpAbove
    LabelSpacing = 3
    ParentFont = False
    TabOrder = 1
  end
  object price: TLabeledEdit
    Left = 224
    Top = 128
    Width = 89
    Height = 24
    EditLabel.Width = 41
    EditLabel.Height = 16
    EditLabel.Caption = 'Price:'
    EditLabel.Font.Charset = DEFAULT_CHARSET
    EditLabel.Font.Color = clWindowText
    EditLabel.Font.Height = -13
    EditLabel.Font.Name = 'MS Sans Serif'
    EditLabel.Font.Style = [fsBold]
    EditLabel.ParentFont = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    LabelPosition = lpAbove
    LabelSpacing = 3
    ParentFont = False
    TabOrder = 2
  end
  object att: TLabeledEdit
    Left = 328
    Top = 72
    Width = 89
    Height = 24
    EditLabel.Width = 48
    EditLabel.Height = 16
    EditLabel.Caption = 'Attack:'
    EditLabel.Font.Charset = DEFAULT_CHARSET
    EditLabel.Font.Color = clWindowText
    EditLabel.Font.Height = -13
    EditLabel.Font.Name = 'MS Sans Serif'
    EditLabel.Font.Style = [fsBold]
    EditLabel.ParentFont = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    LabelPosition = lpAbove
    LabelSpacing = 3
    ParentFont = False
    TabOrder = 3
  end
  object def: TLabeledEdit
    Left = 424
    Top = 72
    Width = 89
    Height = 24
    EditLabel.Width = 63
    EditLabel.Height = 16
    EditLabel.Caption = 'Defence:'
    EditLabel.Font.Charset = DEFAULT_CHARSET
    EditLabel.Font.Color = clWindowText
    EditLabel.Font.Height = -13
    EditLabel.Font.Name = 'MS Sans Serif'
    EditLabel.Font.Style = [fsBold]
    EditLabel.ParentFont = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    LabelPosition = lpAbove
    LabelSpacing = 3
    ParentFont = False
    TabOrder = 4
  end
  object dem: TLabeledEdit
    Left = 520
    Top = 72
    Width = 89
    Height = 24
    EditLabel.Width = 64
    EditLabel.Height = 16
    EditLabel.Caption = 'Demage:'
    EditLabel.Font.Charset = DEFAULT_CHARSET
    EditLabel.Font.Color = clWindowText
    EditLabel.Font.Height = -13
    EditLabel.Font.Name = 'MS Sans Serif'
    EditLabel.Font.Style = [fsBold]
    EditLabel.ParentFont = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    LabelPosition = lpAbove
    LabelSpacing = 3
    ParentFont = False
    TabOrder = 5
  end
  object hp: TLabeledEdit
    Left = 328
    Top = 128
    Width = 89
    Height = 24
    EditLabel.Width = 50
    EditLabel.Height = 16
    EditLabel.Caption = 'Health:'
    EditLabel.Font.Charset = DEFAULT_CHARSET
    EditLabel.Font.Color = clWindowText
    EditLabel.Font.Height = -13
    EditLabel.Font.Name = 'MS Sans Serif'
    EditLabel.Font.Style = [fsBold]
    EditLabel.ParentFont = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    LabelPosition = lpAbove
    LabelSpacing = 3
    ParentFont = False
    TabOrder = 6
  end
  object mp: TLabeledEdit
    Left = 424
    Top = 128
    Width = 89
    Height = 24
    EditLabel.Width = 43
    EditLabel.Height = 16
    EditLabel.Caption = 'Mana:'
    EditLabel.Font.Charset = DEFAULT_CHARSET
    EditLabel.Font.Color = clWindowText
    EditLabel.Font.Height = -13
    EditLabel.Font.Name = 'MS Sans Serif'
    EditLabel.Font.Style = [fsBold]
    EditLabel.ParentFont = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    LabelPosition = lpAbove
    LabelSpacing = 3
    ParentFont = False
    TabOrder = 7
  end
  object sta: TLabeledEdit
    Left = 520
    Top = 128
    Width = 89
    Height = 24
    EditLabel.Width = 57
    EditLabel.Height = 16
    EditLabel.Caption = 'Stamina'
    EditLabel.Font.Charset = DEFAULT_CHARSET
    EditLabel.Font.Color = clWindowText
    EditLabel.Font.Height = -13
    EditLabel.Font.Name = 'MS Sans Serif'
    EditLabel.Font.Style = [fsBold]
    EditLabel.ParentFont = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    LabelPosition = lpAbove
    LabelSpacing = 3
    ParentFont = False
    TabOrder = 8
  end
  object name: TLabeledEdit
    Left = 272
    Top = 240
    Width = 185
    Height = 30
    EditLabel.Width = 46
    EditLabel.Height = 16
    EditLabel.Caption = 'Name:'
    EditLabel.Font.Charset = DEFAULT_CHARSET
    EditLabel.Font.Color = clWindowText
    EditLabel.Font.Height = -13
    EditLabel.Font.Name = 'MS Sans Serif'
    EditLabel.Font.Style = [fsBold]
    EditLabel.ParentFont = False
    Font.Charset = BALTIC_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Palatino Linotype'
    Font.Style = []
    LabelPosition = lpAbove
    LabelSpacing = 3
    ParentFont = False
    TabOrder = 9
  end
  object add: TButton
    Left = 216
    Top = 232
    Width = 49
    Height = 33
    Caption = '<<'
    Font.Charset = BALTIC_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Arial Narrow'
    Font.Style = []
    ParentFont = False
    TabOrder = 10
    OnClick = addClick
  end
  object save: TButton
    Left = 512
    Top = 224
    Width = 75
    Height = 33
    Caption = 'Save'
    Font.Charset = ARABIC_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 11
    OnClick = saveClick
  end
  object TypeCombo: TComboBox
    Left = 224
    Top = 184
    Width = 169
    Height = 30
    Font.Charset = BALTIC_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Palatino Linotype'
    Font.Style = []
    ItemHeight = 22
    ParentFont = False
    TabOrder = 12
    Text = 'Type'
    OnChange = TypeComboChange
    Items.Strings = (
      'Ingredients'
      'Ring'
      'Helmet'
      'Amulet'
      'Weapon'
      'Chest Armor'
      'Shield'
      'Gloves'
      'Pants'
      'Boots'
      'Consumable items')
  end
  object del: TButton
    Left = 512
    Top = 176
    Width = 75
    Height = 33
    Caption = 'Delete'
    Font.Charset = ARABIC_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 13
    OnClick = delClick
  end
  object load: TButton
    Left = 672
    Top = 160
    Width = 75
    Height = 25
    Caption = 'Load'
    Font.Charset = ARABIC_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 14
    OnClick = loadClick
  end
  object EList: TListBox
    Left = 16
    Top = 344
    Width = 193
    Height = 201
    Font.Charset = BALTIC_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Palatino Linotype'
    Font.Style = []
    ItemHeight = 22
    ParentFont = False
    TabOrder = 15
    OnClick = EListClick
    OnMouseDown = EListMouseDown
    OnMouseMove = EListMouseMove
    OnMouseUp = EListMouseUp
  end
  object Ehp: TLabeledEdit
    Left = 224
    Top = 344
    Width = 89
    Height = 24
    EditLabel.Width = 46
    EditLabel.Height = 16
    EditLabel.Caption = 'Health'
    EditLabel.Font.Charset = DEFAULT_CHARSET
    EditLabel.Font.Color = clWindowText
    EditLabel.Font.Height = -13
    EditLabel.Font.Name = 'MS Sans Serif'
    EditLabel.Font.Style = [fsBold]
    EditLabel.ParentFont = False
    Font.Charset = BALTIC_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    LabelPosition = lpAbove
    LabelSpacing = 3
    ParentFont = False
    TabOrder = 16
  end
  object Espeed: TLabeledEdit
    Left = 328
    Top = 344
    Width = 89
    Height = 24
    EditLabel.Width = 47
    EditLabel.Height = 16
    EditLabel.Caption = 'Speed'
    EditLabel.Font.Charset = DEFAULT_CHARSET
    EditLabel.Font.Color = clWindowText
    EditLabel.Font.Height = -13
    EditLabel.Font.Name = 'MS Sans Serif'
    EditLabel.Font.Style = [fsBold]
    EditLabel.ParentFont = False
    Font.Charset = BALTIC_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    LabelPosition = lpAbove
    LabelSpacing = 3
    ParentFont = False
    TabOrder = 17
  end
  object Esight: TLabeledEdit
    Left = 432
    Top = 344
    Width = 89
    Height = 24
    EditLabel.Width = 36
    EditLabel.Height = 16
    EditLabel.Caption = 'Sight'
    EditLabel.Font.Charset = DEFAULT_CHARSET
    EditLabel.Font.Color = clWindowText
    EditLabel.Font.Height = -13
    EditLabel.Font.Name = 'MS Sans Serif'
    EditLabel.Font.Style = [fsBold]
    EditLabel.ParentFont = False
    Font.Charset = BALTIC_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    LabelPosition = lpAbove
    LabelSpacing = 3
    ParentFont = False
    TabOrder = 18
  end
  object Eatt: TLabeledEdit
    Left = 224
    Top = 400
    Width = 89
    Height = 24
    EditLabel.Width = 44
    EditLabel.Height = 16
    EditLabel.Caption = 'Attack'
    EditLabel.Font.Charset = DEFAULT_CHARSET
    EditLabel.Font.Color = clWindowText
    EditLabel.Font.Height = -13
    EditLabel.Font.Name = 'MS Sans Serif'
    EditLabel.Font.Style = [fsBold]
    EditLabel.ParentFont = False
    Font.Charset = BALTIC_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    LabelPosition = lpAbove
    LabelSpacing = 3
    ParentFont = False
    TabOrder = 19
  end
  object Edef: TLabeledEdit
    Left = 328
    Top = 400
    Width = 89
    Height = 24
    EditLabel.Width = 59
    EditLabel.Height = 16
    EditLabel.Caption = 'Defence'
    EditLabel.Font.Charset = DEFAULT_CHARSET
    EditLabel.Font.Color = clWindowText
    EditLabel.Font.Height = -13
    EditLabel.Font.Name = 'MS Sans Serif'
    EditLabel.Font.Style = [fsBold]
    EditLabel.ParentFont = False
    Font.Charset = BALTIC_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    LabelPosition = lpAbove
    LabelSpacing = 3
    ParentFont = False
    TabOrder = 20
  end
  object Edem: TLabeledEdit
    Left = 432
    Top = 400
    Width = 89
    Height = 24
    EditLabel.Width = 60
    EditLabel.Height = 16
    EditLabel.Caption = 'Demage'
    EditLabel.Font.Charset = DEFAULT_CHARSET
    EditLabel.Font.Color = clWindowText
    EditLabel.Font.Height = -13
    EditLabel.Font.Name = 'MS Sans Serif'
    EditLabel.Font.Style = [fsBold]
    EditLabel.ParentFont = False
    Font.Charset = BALTIC_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    LabelPosition = lpAbove
    LabelSpacing = 3
    ParentFont = False
    TabOrder = 21
  end
  object Eexp: TLabeledEdit
    Left = 224
    Top = 456
    Width = 89
    Height = 24
    EditLabel.Width = 79
    EditLabel.Height = 16
    EditLabel.Caption = 'Expierence'
    EditLabel.Font.Charset = DEFAULT_CHARSET
    EditLabel.Font.Color = clWindowText
    EditLabel.Font.Height = -13
    EditLabel.Font.Name = 'MS Sans Serif'
    EditLabel.Font.Style = [fsBold]
    EditLabel.ParentFont = False
    Font.Charset = BALTIC_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    LabelPosition = lpAbove
    LabelSpacing = 3
    ParentFont = False
    TabOrder = 22
  end
  object Egold: TLabeledEdit
    Left = 328
    Top = 456
    Width = 89
    Height = 24
    EditLabel.Width = 34
    EditLabel.Height = 16
    EditLabel.Caption = 'Gold'
    EditLabel.Font.Charset = DEFAULT_CHARSET
    EditLabel.Font.Color = clWindowText
    EditLabel.Font.Height = -13
    EditLabel.Font.Name = 'MS Sans Serif'
    EditLabel.Font.Style = [fsBold]
    EditLabel.ParentFont = False
    Font.Charset = BALTIC_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    LabelPosition = lpAbove
    LabelSpacing = 3
    ParentFont = False
    TabOrder = 23
  end
  object Ename: TLabeledEdit
    Left = 272
    Top = 504
    Width = 185
    Height = 30
    EditLabel.Width = 42
    EditLabel.Height = 16
    EditLabel.Caption = 'Name'
    EditLabel.Font.Charset = DEFAULT_CHARSET
    EditLabel.Font.Color = clWindowText
    EditLabel.Font.Height = -13
    EditLabel.Font.Name = 'MS Sans Serif'
    EditLabel.Font.Style = [fsBold]
    EditLabel.ParentFont = False
    Font.Charset = BALTIC_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Palatino Linotype'
    Font.Style = []
    LabelPosition = lpAbove
    LabelSpacing = 3
    ParentFont = False
    TabOrder = 24
  end
  object Eadd: TButton
    Left = 216
    Top = 504
    Width = 49
    Height = 33
    Caption = '<<'
    Enabled = False
    Font.Charset = BALTIC_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Arial Narrow'
    Font.Style = []
    ParentFont = False
    TabOrder = 25
    OnClick = EaddClick
  end
  object ItemCombo: TComboBox
    Left = 584
    Top = 376
    Width = 161
    Height = 30
    Font.Charset = BALTIC_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Palatino Linotype'
    Font.Style = []
    ItemHeight = 22
    ParentFont = False
    TabOrder = 26
    Text = 'Drops'
    OnChange = ItemComboChange
  end
  object Edrop: TLabeledEdit
    Left = 584
    Top = 344
    Width = 113
    Height = 24
    EditLabel.Width = 114
    EditLabel.Height = 16
    EditLabel.Caption = 'Drop rate (10/x):'
    EditLabel.Font.Charset = DEFAULT_CHARSET
    EditLabel.Font.Color = clWindowText
    EditLabel.Font.Height = -13
    EditLabel.Font.Name = 'MS Sans Serif'
    EditLabel.Font.Style = [fsBold]
    EditLabel.ParentFont = False
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -13
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    LabelPosition = lpAbove
    LabelSpacing = 3
    ParentFont = False
    TabOrder = 27
  end
  object Esave: TButton
    Left = 480
    Top = 488
    Width = 75
    Height = 33
    Caption = 'Save'
    Font.Charset = ARABIC_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 28
    OnClick = EsaveClick
  end
  object Edel: TButton
    Left = 480
    Top = 440
    Width = 75
    Height = 33
    Caption = 'Delete'
    Enabled = False
    Font.Charset = ARABIC_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 29
    OnClick = EdelClick
  end
  object Eload: TButton
    Left = 672
    Top = 528
    Width = 75
    Height = 25
    Caption = 'Load'
    Font.Charset = ARABIC_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'MS Sans Serif'
    Font.Style = []
    ParentFont = False
    TabOrder = 30
    OnClick = EloadClick
  end
  object Eok: TButton
    Left = 696
    Top = 344
    Width = 49
    Height = 25
    Caption = 'Ok'
    Font.Charset = BALTIC_CHARSET
    Font.Color = clWindowText
    Font.Height = -11
    Font.Name = 'Palatino Linotype'
    Font.Style = []
    ParentFont = False
    TabOrder = 31
    OnClick = EokClick
  end
  object Button1: TButton
    Left = 544
    Top = 344
    Width = 33
    Height = 57
    Caption = '>>'
    Font.Charset = BALTIC_CHARSET
    Font.Color = clWindowText
    Font.Height = -19
    Font.Name = 'Arial Narrow'
    Font.Style = []
    ParentFont = False
    TabOrder = 32
    OnClick = Button1Click
  end
  object OpenDialog1: TOpenDialog
    Filter = 'Bitmap Image (*.bmp)|*.bmp'
    Left = 152
    Top = 16
  end
end
