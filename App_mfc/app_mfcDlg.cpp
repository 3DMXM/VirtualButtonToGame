
// app_mfcDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "app_mfc.h"
#include "app_mfcDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Capp_mfcDlg 对话框
Capp_mfcDlg::Capp_mfcDlg(CWnd* pParent /*=NULL*/)
	: CDialog(Capp_mfcDlg::IDD, pParent)
	, m_sel(0)
	, m_dllfile(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void Capp_mfcDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Radio(pDX, IDC_RADIO1, m_sel);
	DDX_Text(pDX, IDC_EDIT_dllfile, m_dllfile);
}

BEGIN_MESSAGE_MAP(Capp_mfcDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_findfile, &Capp_mfcDlg::OnBnClickedButtonfindfile)
	ON_BN_CLICKED(IDC_BUTTON_test, &Capp_mfcDlg::OnBnClickedButtontest)
	ON_WM_HOTKEY()
	ON_WM_TIMER()
	ON_WM_CLOSE()
//	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// Capp_mfcDlg 消息处理程序

BOOL Capp_mfcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	//LoadFromReg();  
	SetHotKey();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Capp_mfcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Capp_mfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//查找dll文件 
void Capp_mfcDlg::OnBnClickedButtonfindfile()
{
	// 直接从注册表中获取
	m_dllfile = LoadFromReg();
	GetDlgItem(IDC_EDIT_dllfile)->SetWindowText(m_dllfile);
	
    // 或手动定位
	LPCWSTR filter = L"DD入口文件|*.dll";
	CFileDialog 	dlg(TRUE,L"DD",L"", OFN_HIDEREADONLY  , filter ,NULL,0,TRUE);

	WCHAR fileBuffer[MAX_PATH] = {0};
	dlg.m_ofn.lpstrFile = fileBuffer;
	dlg.m_ofn.nMaxFile= MAX_PATH;

	if (  dlg.DoModal() == IDOK)
	{
		m_dllfile = dlg.GetPathName();
		UpdateData(FALSE);

		int ret = dd.GetFunAddr(m_dllfile) ;
		
		SetStatus(ret);
	}
}

void Capp_mfcDlg::OnBnClickedButtontest()
{
	// TODO: 在此添加控件通知处理程序代码
	CString s;
	GetDlgItem(IDC_BUTTON_test)->GetWindowText(s);

	if ( s== L"开始测试")
	{
		GetDlgItem(IDC_BUTTON_test)->SetWindowText(L"停止测试");
		SetTimer(0,3000,0);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_test)->SetWindowText(L"开始测试");
		KillTimer(0);
	}
}



//设置状态
void Capp_mfcDlg::SetStatus(int val)
{
	GetDlgItem(IDC_BUTTON_test)->EnableWindow(false);

	switch(val)
	{
	case 1:
		AfxMessageBox(L"DD驱动加载成功");		
		GetDlgItem(IDC_BUTTON_test)->EnableWindow(true);
		dd.DD_key(5782963, 7451267);
		break;
	case -1:
	case -2:
	case -3:
		AfxMessageBox(L"载入驱动时错误");
		break;
	case -11 :
		AfxMessageBox(L"文件不存在");
		break;
	case -12 :
		AfxMessageBox(L"载入库错误");
		break;
	case -13 :
		AfxMessageBox(L"获取函数地址错误");
		break;
	default:
		AfxMessageBox(L"未知错误");
		break;
	}

}


//热键相关
void Capp_mfcDlg::SetHotKey(void)
{
	::RegisterHotKey(GetSafeHwnd(),6688, MOD_CONTROL   ,    'K'     ); 
	::RegisterHotKey(GetSafeHwnd(),6689,                0           ,  VK_F8 ); 

}
void Capp_mfcDlg::UnHotKey(void)
{
	::UnregisterHotKey(GetSafeHwnd() ,6688);	
	::UnregisterHotKey(GetSafeHwnd() ,6689);
}



void Capp_mfcDlg::OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	switch (nHotKeyId)
	{
	case 6688:  // 模拟ctrl+alt+del
		dd.DD_key( 600  ,  1);   //按下 ctrl键 6区第1个
		dd.DD_key( 602  ,  1);   //        alt     6区第3个
		dd.DD_key( 706  ,  1);   //        del    7区第7个
		dd.DD_key( 706  ,  2);   //放开
		dd.DD_key( 602  ,  2); 
		dd.DD_key( 600  ,  2);         
     	break;
	case  6689:  // 模拟输入键盘上可见字符
		dd.DD_str(" Keyboard char [A-Za_z] {@$} ");
		break;
	default:
		break;
	}

	CDialog::OnHotKey(nHotKeyId, nKey1, nKey2);
}

//从注册表中读取DD入口文件位置
CString Capp_mfcDlg::LoadFromReg()
{
	WCHAR dll_file[MAX_PATH] = {0};
	HKEY hKey;
	
	// DD 入口文件位置一般保存在 HKEY_LOCAL_MACHINE\SOFTWARE\DD XOFT\path 中
	if (ERROR_SUCCESS == RegOpenKey(HKEY_LOCAL_MACHINE, L"Software\\DD XOFT" , &hKey))
	{
		DWORD size = MAX_PATH;
		DWORD type = REG_SZ;
		WCHAR *pkey = L"path";

		if ( ERROR_SUCCESS == RegQueryValueEx(hKey, pkey, NULL, &type, (LPBYTE)dll_file, (LPDWORD)&size))
		{
			RegCloseKey(hKey);
		}
	}
	return dll_file;
}




//定时器
void Capp_mfcDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	UpdateData(TRUE);
				
	switch(m_sel+1)
	{
	case 1 :                      //鼠标点击
		dd.DD_btn(1);         // 1左下 2左上 4右下 8右上
		dd.DD_btn(2);
		break;
	case 2 :                      //鼠标移动
		{
			static int x=50;	static int y=50;            //起始点坐标设置成 50，50
			x+=15;		y+=10;
			//dd.DD_mov( x , y);
			dd.DD_movR(10,10);
		}
		break;
	case 3 :
		dd.DD_whl(1);		// 鼠标滚轮(上)
		Sleep(200);
		dd.DD_whl(2);       //              (下)
		break;
	case 4 :                   
		{                                              //键盘TAB按键 
			int ddcode=300;			       // 3区第1 或 通过函数转换
			ddcode = dd.DD_todc(VK_TAB);
			dd.DD_key( ddcode ,1);        
			dd.DD_key( ddcode ,2);
		}
		break;
	}
	CDialog::OnTimer(nIDEvent);
}

void Capp_mfcDlg::OnClose()
{
	UnHotKey();
	KillTimer(0);
	CDialog::OnClose();
}


