[General]
SyntaxVersion=2
BeginHotkey=121
BeginHotkeyMod=0
PauseHotkey=0
PauseHotkeyMod=0
StopHotkey=123
StopHotkeyMod=0
RunOnce=1
EnableWindow=
MacroID=c88b2a9c-a9c4-47a3-8c68-0c85aab0e583
Description=DD≤‚ ‘
Enable=1
AutoRun=0
[Repeat]
Type=0
Number=1
[SetupUI]
Type=2
QUI=
[Relative]
SetupOCXFile=
[Comment]

[Script]
Private Declare Function DD_mov Lib "DD32.dll" (ByVal x As Long, ByVal y As Long) As Long
Private Declare Function DD_movR Lib "DD32.dll" (ByVal dx As Long, ByVal dy As Long) As Long
Private Declare Function DD_btn Lib "DD32.dll" (ByVal btn As Long) As Long
Private Declare Function DD_whl Lib "DD32.dll" (ByVal whl As Long) As Long
Private Declare Function DD_key Lib "DD32.dll" (ByVal key As Long, ByVal flag As Long) As Long
Private Declare Function DD_str Lib "DD32.dll" (ByVal str As String) As Long


Call  DD_movR(100, 100)

'http://www.ddxoft.com/