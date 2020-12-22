VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "DD 例程"
   ClientHeight    =   3795
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4815
   LinkTopic       =   "Form1"
   ScaleHeight     =   3795
   ScaleWidth      =   4815
   StartUpPosition =   3  '窗口缺省
   Begin VB.CommandButton Command2 
      Caption         =   "停止"
      Height          =   615
      Left            =   3120
      TabIndex        =   7
      Top             =   2040
      Width           =   1215
   End
   Begin VB.Timer Timer1 
      Interval        =   3000
      Left            =   120
      Top             =   120
   End
   Begin VB.Frame Frame1 
      Caption         =   "功能选项"
      Height          =   3015
      Left            =   720
      TabIndex        =   1
      Top             =   360
      Width           =   1935
      Begin VB.OptionButton Option1 
         Caption         =   "键盘字符"
         Height          =   375
         Index           =   4
         Left            =   360
         TabIndex        =   6
         TabStop         =   0   'False
         Top             =   2160
         Width           =   1335
      End
      Begin VB.OptionButton Option1 
         Caption         =   "键盘按键"
         Height          =   375
         Index           =   3
         Left            =   360
         TabIndex        =   5
         TabStop         =   0   'False
         Top             =   1740
         Width           =   1335
      End
      Begin VB.OptionButton Option1 
         Caption         =   "鼠标滚轮"
         Height          =   375
         Index           =   2
         Left            =   360
         TabIndex        =   4
         TabStop         =   0   'False
         Top             =   1320
         Width           =   1335
      End
      Begin VB.OptionButton Option1 
         Caption         =   "鼠标点击"
         Height          =   375
         Index           =   1
         Left            =   360
         TabIndex        =   3
         TabStop         =   0   'False
         Top             =   900
         Width           =   1335
      End
      Begin VB.OptionButton Option1 
         Caption         =   "鼠标移动"
         Height          =   375
         Index           =   0
         Left            =   360
         TabIndex        =   2
         TabStop         =   0   'False
         Top             =   480
         Width           =   1335
      End
   End
   Begin VB.CommandButton Command1 
      Caption         =   "开始"
      Height          =   615
      Left            =   3120
      TabIndex        =   0
      Top             =   720
      Width           =   1215
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Private Declare Function DD_mov Lib "DD32.dll" (ByVal x As Long, ByVal y As Long) As Long
Private Declare Function DD_btn Lib "DD32.dll" (ByVal btn As Long) As Long
Private Declare Function DD_whl Lib "DD32.dll" (ByVal whl As Long) As Long
Private Declare Function DD_key Lib "DD32.dll" (ByVal key As Long, ByVal flag As Long) As Long
Private Declare Function DD_str Lib "DD32.dll" (ByVal str As String) As Long
Private Declare Function DD_movR Lib "DD32.dll" (ByVal dx As Long, ByVal dy As Long) As Long

'这个函数已废除 Private Declare Function DD_chk Lib "DD32.dll" () As Long

Private Declare Function DD_MouseMove Lib "DD32.dll" (ByVal hwnd As Long, ByVal x As Long, ByVal y As Long) As Long
Private Declare Function DD_SnapPic Lib "DD32.dll" (ByVal hwnd As Long, ByVal x As Long, ByVal y As Long, ByVal w As Long, ByVal h As Long) As Long
Private Declare Function DD_PickColor Lib "DD32.dll" (ByVal hwnd As Long, ByVal x As Long, ByVal y As Long, Optional ByVal mode As Long = 2) As Long
Private Declare Function DD_GetActiveWindow Lib "DD32.dll" () As Long


Dim sel As Integer '功能选择

'开始
Private Sub Command1_Click()
  Timer1.Enabled = True
  Command1.Enabled = False
  Command2.Enabled = True
End Sub

'停止
Private Sub Command2_Click()
  Timer1.Enabled = False
  Command1.Enabled = True
  Command2.Enabled = False
End Sub

Private Sub Form_Load()
  '可从注册表 HKEY_LOCAL_MACHINE\SOFTWARE\DD XOFT\path 中读取DD入口文件位置
  Command1.Enabled = True
  Command2.Enabled = False
  
End Sub

Private Sub Option1_Click(Index As Integer)
  sel = Index + 1
End Sub

Private Sub Timer1_Timer()
  Dim ret As Long
 
  Select Case sel
   Case 1
    'ret = DD_mov(20, 20) '鼠标绝对移动
    ret = DD_movR(20, 20) '鼠标相对移动
   Case 2
    ret = DD_btn(1)      '鼠标点击
    ret = DD_btn(2)
  
   Case 3
    ret = DD_whl(1)      '鼠标滚轮
    ret = DD_whl(2)
   
   Case 4
    ret = DD_key(300, 1)  '键盘TAB按键 ,TAB键在DD键码表3区第1位置
    ret = DD_key(300, 2)
   
   Case 5                 '输入键盘上可见字符
    ret = DD_str("!@# ,./ FucXxx Janpan ")
 End Select
 
 
End Sub

Private Sub Demo()
  Dim hwnd As Long
  hwnd = DD_GetActiveWindow '取当前激活窗口句柄，当用普通API无法获取时，可使用这个函数

  Dim ret As Long
  ret = DD_MouseMove(hwnd, 130, 100)    '移动鼠标，当hwnd=0时，等同DD_mov
  ret = DD_SnapPic(hwnd, 50, 50, 100, 100)  '抓图，保存在c:\dd snap 文件夹

  Dim clr As Long
  clr = DD_PickColor(hwnd, 130, 100)   '取色。当hwnd=0时，以全屏坐标取色，否则以窗口坐标取色。
  Me.BackColor = clr

End Sub

