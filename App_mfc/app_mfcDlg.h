
// app_mfcDlg.h : ͷ�ļ�
//

#pragma once
#include "DD.h"

// Capp_mfcDlg �Ի���
class Capp_mfcDlg : public CDialog
{
// ����
public:
	Capp_mfcDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_APP_MFC_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonfindfile();
	afx_msg void OnBnClickedButtontest();
	afx_msg void OnHotKey(UINT nHotKeyId, UINT nKey1, UINT nKey2);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClose();

public:
	void SetStatus(int val);
	void SetHotKey(void);
	void UnHotKey(void);
	CString LoadFromReg();
	CString m_dllfile;
	int m_sel;
	CDD dd ;  // DD ��
};
