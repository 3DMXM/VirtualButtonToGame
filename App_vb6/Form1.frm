VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "DD ����"
   ClientHeight    =   3795
   ClientLeft      =   60
   ClientTop       =   345
   ClientWidth     =   4815
   LinkTopic       =   "Form1"
   ScaleHeight     =   3795
   ScaleWidth      =   4815
   StartUpPosition =   3  '����ȱʡ
   Begin VB.CommandButton Command2 
      Caption         =   "ֹͣ"
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
      Caption         =   "����ѡ��"
      Height          =   3015
      Left            =   720
      TabIndex        =   1
      Top             =   360
      Width           =   1935
      Begin VB.OptionButton Option1 
         Caption         =   "�����ַ�"
         Height          =   375
         Index           =   4
         Left            =   360
         TabIndex        =   6
         TabStop         =   0   'False
         Top             =   2160
         Width           =   1335
      End
      Begin VB.OptionButton Option1 
         Caption         =   "���̰���"
         Height          =   375
         Index           =   3
         Left            =   360
         TabIndex        =   5
         TabStop         =   0   'False
         Top             =   1740
         Width           =   1335
      End
      Begin VB.OptionButton Option1 
         Caption         =   "������"
         Height          =   375
         Index           =   2
         Left            =   360
         TabIndex        =   4
         TabStop         =   0   'False
         Top             =   1320
         Width           =   1335
      End
      Begin VB.OptionButton Option1 
         Caption         =   "�����"
         Height          =   375
         Index           =   1
         Left            =   360
         TabIndex        =   3
         TabStop         =   0   'False
         Top             =   900
         Width           =   1335
      End
      Begin VB.OptionButton Option1 
         Caption         =   "����ƶ�"
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
      Caption         =   "��ʼ"
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

'��������ѷϳ� Private Declare Function DD_chk Lib "DD32.dll" () As Long

Private Declare Function DD_MouseMove Lib "DD32.dll" (ByVal hwnd As Long, ByVal x As Long, ByVal y As Long) As Long
Private Declare Function DD_SnapPic Lib "DD32.dll" (ByVal hwnd As Long, ByVal x As Long, ByVal y As Long, ByVal w As Long, ByVal h As Long) As Long
Private Declare Function DD_PickColor Lib "DD32.dll" (ByVal hwnd As Long, ByVal x As Long, ByVal y As Long, Optional ByVal mode As Long = 2) As Long
Private Declare Function DD_GetActiveWindow Lib "DD32.dll" () As Long


Dim sel As Integer '����ѡ��

'��ʼ
Private Sub Command1_Click()
  Timer1.Enabled = True
  Command1.Enabled = False
  Command2.Enabled = True
End Sub

'ֹͣ
Private Sub Command2_Click()
  Timer1.Enabled = False
  Command1.Enabled = True
  Command2.Enabled = False
End Sub

Private Sub Form_Load()
  '�ɴ�ע��� HKEY_LOCAL_MACHINE\SOFTWARE\DD XOFT\path �ж�ȡDD����ļ�λ��
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
    'ret = DD_mov(20, 20) '�������ƶ�
    ret = DD_movR(20, 20) '�������ƶ�
   Case 2
    ret = DD_btn(1)      '�����
    ret = DD_btn(2)
  
   Case 3
    ret = DD_whl(1)      '������
    ret = DD_whl(2)
   
   Case 4
    ret = DD_key(300, 1)  '����TAB���� ,TAB����DD�����3����1λ��
    ret = DD_key(300, 2)
   
   Case 5                 '��������Ͽɼ��ַ�
    ret = DD_str("!@# ,./ FucXxx Janpan ")
 End Select
 
 
End Sub

Private Sub Demo()
  Dim hwnd As Long
  hwnd = DD_GetActiveWindow 'ȡ��ǰ����ھ����������ͨAPI�޷���ȡʱ����ʹ���������

  Dim ret As Long
  ret = DD_MouseMove(hwnd, 130, 100)    '�ƶ���꣬��hwnd=0ʱ����ͬDD_mov
  ret = DD_SnapPic(hwnd, 50, 50, 100, 100)  'ץͼ��������c:\dd snap �ļ���

  Dim clr As Long
  clr = DD_PickColor(hwnd, 130, 100)   'ȡɫ����hwnd=0ʱ����ȫ������ȡɫ�������Դ�������ȡɫ��
  Me.BackColor = clr

End Sub

