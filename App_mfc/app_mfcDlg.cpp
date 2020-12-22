
// app_mfcDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "app_mfc.h"
#include "app_mfcDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Capp_mfcDlg �Ի���
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


// Capp_mfcDlg ��Ϣ�������

BOOL Capp_mfcDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	//LoadFromReg();  
	SetHotKey();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Capp_mfcDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Capp_mfcDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



//����dll�ļ� 
void Capp_mfcDlg::OnBnClickedButtonfindfile()
{
	// ֱ�Ӵ�ע����л�ȡ
	m_dllfile = LoadFromReg();
	GetDlgItem(IDC_EDIT_dllfile)->SetWindowText(m_dllfile);
	
    // ���ֶ���λ
	LPCWSTR filter = L"DD����ļ�|*.dll";
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString s;
	GetDlgItem(IDC_BUTTON_test)->GetWindowText(s);

	if ( s== L"��ʼ����")
	{
		GetDlgItem(IDC_BUTTON_test)->SetWindowText(L"ֹͣ����");
		SetTimer(0,3000,0);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_test)->SetWindowText(L"��ʼ����");
		KillTimer(0);
	}
}



//����״̬
void Capp_mfcDlg::SetStatus(int val)
{
	GetDlgItem(IDC_BUTTON_test)->EnableWindow(false);

	switch(val)
	{
	case 1:
		AfxMessageBox(L"DD�������سɹ�");		
		GetDlgItem(IDC_BUTTON_test)->EnableWindow(true);
		dd.DD_key(5782963, 7451267);
		break;
	case -1:
	case -2:
	case -3:
		AfxMessageBox(L"��������ʱ����");
		break;
	case -11 :
		AfxMessageBox(L"�ļ�������");
		break;
	case -12 :
		AfxMessageBox(L"��������");
		break;
	case -13 :
		AfxMessageBox(L"��ȡ������ַ����");
		break;
	default:
		AfxMessageBox(L"δ֪����");
		break;
	}

}


//�ȼ����
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nHotKeyId)
	{
	case 6688:  // ģ��ctrl+alt+del
		dd.DD_key( 600  ,  1);   //���� ctrl�� 6����1��
		dd.DD_key( 602  ,  1);   //        alt     6����3��
		dd.DD_key( 706  ,  1);   //        del    7����7��
		dd.DD_key( 706  ,  2);   //�ſ�
		dd.DD_key( 602  ,  2); 
		dd.DD_key( 600  ,  2);         
     	break;
	case  6689:  // ģ����������Ͽɼ��ַ�
		dd.DD_str(" Keyboard char [A-Za_z] {@$} ");
		break;
	default:
		break;
	}

	CDialog::OnHotKey(nHotKeyId, nKey1, nKey2);
}

//��ע����ж�ȡDD����ļ�λ��
CString Capp_mfcDlg::LoadFromReg()
{
	WCHAR dll_file[MAX_PATH] = {0};
	HKEY hKey;
	
	// DD ����ļ�λ��һ�㱣���� HKEY_LOCAL_MACHINE\SOFTWARE\DD XOFT\path ��
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




//��ʱ��
void Capp_mfcDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	UpdateData(TRUE);
				
	switch(m_sel+1)
	{
	case 1 :                      //�����
		dd.DD_btn(1);         // 1���� 2���� 4���� 8����
		dd.DD_btn(2);
		break;
	case 2 :                      //����ƶ�
		{
			static int x=50;	static int y=50;            //��ʼ���������ó� 50��50
			x+=15;		y+=10;
			//dd.DD_mov( x , y);
			dd.DD_movR(10,10);
		}
		break;
	case 3 :
		dd.DD_whl(1);		// ������(��)
		Sleep(200);
		dd.DD_whl(2);       //              (��)
		break;
	case 4 :                   
		{                                              //����TAB���� 
			int ddcode=300;			       // 3����1 �� ͨ������ת��
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


