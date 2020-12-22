Public Class Form1
    Private dd As CDD

    Private Sub Form1_Load(ByVal sender As Object, ByVal e As System.EventArgs) Handles Me.Load
        Me.RegHotKey()               '注册热键
        Me.GroupBox1.Enabled = False
        Me.button_start.Enabled = False
        dd = New CDD
    End Sub

    Private Sub Form1_FormClosing(ByVal sender As Object, ByVal e As System.Windows.Forms.FormClosingEventArgs) Handles Me.FormClosing
        Me.UnRegHotKey()   '注销热键
    End Sub

    Private Sub button1_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles button1.Click
        '可从注册表中直接获取
        Dim dllfile As String = My.Computer.Registry.GetValue("HKEY_LOCAL_MACHINE\SOFTWARE\DD XOFT", "path", "")
        ' LoadDDEntry(dllfile) : Exit Sub

        '或者手动定位
        Dim ofd As New OpenFileDialog()
        ofd.Filter = "DD|*.DLL"

        If ofd.ShowDialog() <> DialogResult.OK Then Return

        ' 载入Dll 文件 
        LoadDDEntry(ofd.FileName)
    End Sub

    Private Sub button2_Click(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles button_start.Click
        If button_start.Text = "开始" Then
            button_start.Text = "停止"
            timer1.Enabled = True
        Else
            button_start.Text = "开始"
            timer1.Enabled = False
        End If
    End Sub

    Private Sub timer1_Tick(ByVal sender As System.Object, ByVal e As System.EventArgs) Handles timer1.Tick
        If radioButton1.Checked = True Then           '测试键盘TAB按键 
            Dim ddcode As Int32 = 300                      'TAB键位在DD码表中3区第一个键
            dd.key(ddcode, 1)                                     ' 1=按下 2=放开
            dd.key(ddcode, 2)
            Exit Sub
        End If

        If radioButton2.Checked = True Then            '测试鼠标点击 
            dd.btn(MouseBtn.左下)                              ' 1= 左键按下 ' 2=左键放开 '4=右键按下 '8=右键放开
            dd.btn(MouseBtn.左上)
            Exit Sub
        End If

        If radioButton3.Checked = True Then            '测试鼠标移动 
            dd.movR(20, 20)
            Exit Sub
        End If

        If RadioButton4.Checked = True Then            '测试鼠标滚轮
            dd.whl(1)                                                    '前滚
            System.Threading.Thread.Sleep(200)           '休息一会 
            dd.whl(2)                                                    '后滚
        End If
    End Sub

    Private Sub LinkLabel1_LinkClicked(ByVal sender As System.Object, ByVal e As System.Windows.Forms.LinkLabelLinkClickedEventArgs) Handles LinkLabel1.LinkClicked
        Dim url As String = "http://" & LinkLabel1.Text
        System.Diagnostics.Process.Start(url)
    End Sub

    '载入DLL 文件
    Private Sub LoadDDEntry(ByVal dllfile As String)
        Me.button_start.Enabled = False    '禁止测试
        Me.GroupBox1.Enabled = False

        Dim fileExists As Boolean = My.Computer.FileSystem.FileExists(dllfile)
        If fileExists = False Then MessageBox.Show("没找到文件") : Exit Sub

        Dim ret As Int32 = dd.Load(dllfile)

        If ret <> 1 Then MessageBox.Show("加载Dll时发生错误") : Exit Sub

        'MessageBox.Show("DD虚拟驱动加载正确！")
        Me.button_start.Enabled = True     '允许测试
        Me.GroupBox1.Enabled = True
        Me.TextBox1.Text = dllfile

        dd.btn(0)

    End Sub

#Region "热键相关代码"
    Private Declare Function RegisterHotKey Lib "user32" (ByVal hwnd As IntPtr, ByVal id As Integer, ByVal fsModifiers As KeyModifiers, ByVal vk As Integer) As Integer
    Private Declare Function UnregisterHotKey Lib "user32" (ByVal hwnd As IntPtr, ByVal id As Integer) As Integer

    '注册热键
    Private Sub RegHotKey()
        RegisterHotKey(Me.Handle, 80, 0, Keys.F8)                                                                 '第二个参数是热键ID,就是通过这个ID进行识别
        RegisterHotKey(Me.Handle, 90, 0, Keys.F9)
        RegisterHotKey(Me.Handle, 100, KeyModifiers.Shift Or KeyModifiers.Control, Keys.K) '热键为 SHIFT+CTRL+K
        RegisterHotKey(Me.Handle, 200, KeyModifiers.Alt, Keys.D0)                                        '定义热键为Alt+0
    End Sub

    '注销热键
    Private Sub UnRegHotKey()
        UnregisterHotKey(Me.Handle, 80)
        UnregisterHotKey(Me.Handle, 90)
        UnregisterHotKey(Me.Handle, 100)
        UnregisterHotKey(Me.Handle, 200)
    End Sub

    Protected Overrides Sub WndProc(ByRef m As System.Windows.Forms.Message)
        Static WM_HOTKEY As Long = &H312  '表示消息来自用户自定义热键
        If m.Msg = WM_HOTKEY Then
            ProcessHotkey(m)
        End If
        MyBase.WndProc(m)
    End Sub
    Private Sub ProcessHotkey(ByVal m As Message)
        ' 根据热键ID做不同的处理
        Select Case m.WParam.ToInt32
            Case 80
                Fun80() '调用相关函数
            Case 90
                Fun90()
            Case 100
                Fun100()
        End Select
    End Sub

    Private Sub Fun80()
        dd.str(" Keyboard char [A-Za_z] {@$} ") ' 输入 键盘上可见字符
    End Sub

    Private Sub Fun90()
        '模拟 系统热键 CTRL+ALT+DEL
        If dd.key IsNot Nothing Then
            dd.key(600, 1)                                  'ctrl = 6区第1个键
            dd.key(602, 1)                                  'alt  = 6区第3个键
            dd.key(706, 1)                                  'del = 7区第7个键
            System.Threading.Thread.Sleep(50)  '一休哥
            dd.key(706, 2)
            dd.key(602, 2)
            dd.key(600, 2)
        End If
    End Sub

    Private Sub Fun100()
        MessageBox.Show("组合热键SHIFT+CTRL+K测试")
    End Sub


#End Region


End Class
