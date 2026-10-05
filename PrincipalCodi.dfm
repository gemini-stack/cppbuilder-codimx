object FCodiMX: TFCodiMX
  Left = 0
  Top = 0
  Caption = 'Pasarela de pago CoDi M'#233'xico'
  ClientHeight = 512
  ClientWidth = 379
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  DesignSize = (
    379
    512)
  TextHeight = 15
  object IQRCodi: TImage
    Left = 39
    Top = 32
    Width = 300
    Height = 300
    Center = True
    Stretch = True
  end
  object LabelEstado: TLabel
    Left = 8
    Top = 8
    Width = 63
    Height = 15
    Caption = 'LabelEstado'
  end
  object BtnGenerarCobroCoDi: TBitBtn
    Left = 8
    Top = 338
    Width = 137
    Height = 25
    Caption = 'Generar Cobro CoDi'
    TabOrder = 0
    OnClick = BtnGenerarCobroCoDiClick
  end
  object Memo1: TMemo
    Left = 8
    Top = 369
    Width = 361
    Height = 135
    Anchors = [akLeft, akTop, akRight, akBottom]
    Lines.Strings = (
      'Memo1')
    TabOrder = 1
    ExplicitWidth = 357
    ExplicitHeight = 134
  end
  object BtnGenerarCobroCel: TBitBtn
    Left = 232
    Top = 338
    Width = 137
    Height = 25
    Caption = 'Cobro CoDi Celular'
    TabOrder = 2
    OnClick = BtnGenerarCobroCelClick
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 15000
    OnTimer = Timer1Timer
    Left = 344
    Top = 8
  end
end
