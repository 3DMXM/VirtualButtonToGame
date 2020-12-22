Imports System.Runtime.InteropServices

'鼠标按键枚举 
Public Enum MouseBtn
    左下 = 1
    左上 = 2
    右下 = 4
    右上 = 8
End Enum

'组合键枚举
Public Enum KeyModifiers
    None = 0
    Alt = 1
    Control = 2
    Shift = 4
    Windows = 8
End Enum


Public Class CDD

    <DllImport("Kernel32")> Private Shared Function LoadLibrary(ByVal dllfile As String) As System.IntPtr
    End Function
    <DllImport("Kernel32")> Private Shared Function GetProcAddress(ByVal hModule As System.IntPtr, ByVal lpProcName As String) As System.IntPtr
    End Function
    <DllImport("Kernel32")> Private Shared Function FreeLibrary(ByVal hModule As System.IntPtr) As Boolean
    End Function

    Public Delegate Function pDD_btn(ByVal btn As Int32) As Int32
    Public Delegate Function pDD_whl(ByVal whl As Int32) As Int32
    Public Delegate Function pDD_key(ByVal keycode As Int32, ByVal flag As Int32) As Int32
    Public Delegate Function pDD_mov(ByVal x As Int32, ByVal y As Int32) As Int32
    Public Delegate Function pDD_chk() As Int32
    Public Delegate Function pDD_str(ByVal instr As String) As Int32
    Public Delegate Function pDD_todc(ByVal vk As Int32) As Int32
    Public Delegate Function pDD_movR(ByVal dx As Int32, ByVal dy As Int32) As Int32

    Public btn As pDD_btn        ' 鼠标点击 
    Public whl As pDD_whl        ' 鼠标滚动 
    Public mov As pDD_mov     ' 绝对鼠标移动 
    Public movR As pDD_movR     ' 相对鼠标移动 
    Public key As pDD_key        ' 键盘按键 
    Public str As pDD_str           ' 键盘字符 
    Private m_hinst As IntPtr

    Protected Overrides Sub Finalize()
        Try
            If Not m_hinst.Equals(IntPtr.Zero) Then
                Dim b As Boolean = FreeLibrary(m_hinst)
            End If
        Finally
            MyBase.Finalize()
        End Try
    End Sub

    Public Function Load(ByVal dllfile As String) As Int32
        m_hinst = LoadLibrary(dllfile)

        If m_hinst.Equals(IntPtr.Zero) Then
            Return -2
        Else
            Return GetDDfunAddress(m_hinst)
        End If
    End Function

    Private Function GetDDfunAddress(ByVal hinst As IntPtr) As Int32
        Dim ptr As System.IntPtr = IntPtr.Zero

        ptr = GetProcAddress(hinst, "DD_btn")    '鼠标按键
        If ptr.Equals(IntPtr.Zero) Then Return -1
        btn = TryCast(Marshal.GetDelegateForFunctionPointer(ptr, GetType(pDD_btn)), pDD_btn)

        ptr = GetProcAddress(hinst, "DD_whl")    '鼠标按键
        If ptr.Equals(IntPtr.Zero) Then Return -1
        whl = TryCast(Marshal.GetDelegateForFunctionPointer(ptr, GetType(pDD_whl)), pDD_whl)

        ptr = GetProcAddress(hinst, "DD_mov")  '鼠标移动
        If ptr.Equals(IntPtr.Zero) Then Return -1
        mov = TryCast(Marshal.GetDelegateForFunctionPointer(ptr, GetType(pDD_mov)), pDD_mov)

        ptr = GetProcAddress(hinst, "DD_movR")  '鼠标移动
        If ptr.Equals(IntPtr.Zero) Then Return -1
        movR = TryCast(Marshal.GetDelegateForFunctionPointer(ptr, GetType(pDD_movR)), pDD_movR)

        ptr = GetProcAddress(hinst, "DD_key")    '键盘按键
        If ptr.Equals(IntPtr.Zero) Then Return -1
        key = TryCast(Marshal.GetDelegateForFunctionPointer(ptr, GetType(pDD_key)), pDD_key)

        ptr = GetProcAddress(hinst, "DD_str")       '键盘字符
        If ptr.Equals(IntPtr.Zero) Then Return -1
        str = TryCast(Marshal.GetDelegateForFunctionPointer(ptr, GetType(pDD_str)), pDD_str)



        Return 1

    End Function

End Class
